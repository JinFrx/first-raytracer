#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"

#include <algorithm>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;
		_root	   = new BVHNode();

		Chrono chr;
		chr.start();
		
		_buildRec( _root, 0, (uint) _triangles->size() - 1, 1 );

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
	}

	void BVH::_buildRec( BVHNode *	p_node,
						 const uint p_firstTriangleId,
						 const uint p_lastTriangleId,
						 const uint p_depth )
	{
		p_node->_firstTriangleId = p_firstTriangleId;
		p_node->_lastTriangleId	 = p_lastTriangleId;
		
		//--------------------------------
		// Construire la AABB du noeud BVH
		//--------------------------------

		p_node->_aabb = AABB();
		
		for ( uint i = p_firstTriangleId; i <= p_lastTriangleId; i++ )
		{
			// definir les bords du triangle courant avec une AABB
			( *_triangles )[ i ].setBounds();

			// etendre la AABB du noeud avec la AABB du triangle courant
			p_node->_aabb.extend( ( *_triangles )[ i ].getAABB() );
		}
		
		//--------------------------------
		// Construction des noeuds enfants
		//--------------------------------

		uint nbTriangles = p_lastTriangleId - p_firstTriangleId + 1;
		//std::cout << nbTriangles << std::endl;

		if ( nbTriangles > _maxTrianglesPerLeaf && p_depth < _maxDepth )
		{
			// choisir l'axe le plus long de la AABB pour la repartition
			int partAxis = (int) p_node->_aabb.largestAxis();

			// trier les triangles dans la range [p_firstTriangleId, p_lastTriangleId]
			// selon leur barycentre et par rapport a l'axe le plus grand
			auto begin = _triangles->begin() + p_firstTriangleId;
			auto end   = _triangles->begin() + p_lastTriangleId;

			std::sort( begin, end,
				[ partAxis ]( TriangleMeshGeometry t1, TriangleMeshGeometry t2 ) {
					return t1.computeBarycenter()[ partAxis ] < t2.computeBarycenter()[ partAxis ];
				} );

			//---------------------------------------
			// Partitionnement coupe otimale SAH (TD)
			//---------------------------------------

			/*float nodeSA = p_node->_aabb.computeSurfaceArea();
			float sahMin = FLT_MAX;
			uint  partId = 0;

			for ( uint i = p_firstTriangleId; i < p_lastTriangleId; i++ )
			{
				float hLeft = ( *_triangles )[ i ].getAABB().computeSurfaceArea() * i;
				float hRight = ( *_triangles )[ i + 1 ].getAABB().computeSurfaceArea() * ( p_lastTriangleId - i + 2 );
				float sah = ( hLeft + hRight ) / nodeSA;

				if ( sah < sahMin ) {
					sahMin = sah;
					partId = i;
				}
			}*/
			
			//-----------------------------------
			// Partitionnement avec centroid AABB
			//-----------------------------------
			Vec3f cut = p_node->_aabb.centroid();

			// retourne le TriangleMeshGeometry qui se situe juste apres la decoupe
			auto secondPartFirst = std::partition( begin, end,
				[ partAxis, cut ]( TriangleMeshGeometry t ) {
					AABB tAABB = t.getAABB();
					return tAABB.getMin()[ partAxis ] < cut[ partAxis ];
				} );
			
			// s'assurer qu'il y ait bien une decoupe, dans le cas ou tous les triangles sont du
			// meme cote de la partition
			if ( secondPartFirst == begin || secondPartFirst == end )
				secondPartFirst = begin + ( end - begin ) / 2;
			
			// retrouver a partir du triangle secondPartFirst l'indice dans _triangles de la decoupe
			uint partId = (uint) std::distance( _triangles->begin(), secondPartFirst );
			
			// construire les noeuds enfants recursivement
			p_node->_left = new BVHNode();
			p_node->_right = new BVHNode();

			_buildRec( p_node->_left, p_firstTriangleId, partId, p_depth + 1 );
			_buildRec( p_node->_right, partId, p_lastTriangleId, p_depth + 1 );
		}
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		if ( !p_node->_aabb.intersect(p_ray, p_tMin, p_tMax) )
			return false;

		if ( !p_node->isLeaf() )
		{
			// descendre dans le noeud fils gauche
			bool leftHitted = _intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, p_hitRecord );
			// descendre dans le noeud fils droit
			bool rightHitted = _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, p_hitRecord );

			return leftHitted || rightHitted;
		}

		//---------------
		// Feuille du BVH
		//---------------

		float  tClosest = p_tMax; // Hit distance.
		uint hitTri	= p_node->_lastTriangleId + 1; // Hit triangle id.
		
		float u = 0.f, v = 0.f; // coordonnees barycentriques

		for ( uint i = p_node->_firstTriangleId; i <= p_node->_lastTriangleId; i++ )
		{
			float t; // distance hitPoint
			float cur_u, cur_v; // coordonnees barycentriques du triangle courant
			if ( (*_triangles)[ i ].intersect( p_ray, t, cur_u, cur_v ) )
			{
				if ( t >= p_tMin && t <= tClosest )
				{
					tClosest	 = t;
					hitTri		 = i;
					u			 = cur_u;
					v			 = cur_v;
				}
			}
		}
		if ( hitTri != p_node->_lastTriangleId + 1 ) // Intersection found.
		{
			p_hitRecord._point = p_ray.pointAtT( tClosest );
			//p_hitRecord._normal = (*_triangles)[ hitTri ].getFaceNormal();
			p_hitRecord._normal = (*_triangles)[ hitTri ].getInterpolatedNormal(u, v);
			p_hitRecord.faceNormal( p_ray.getDirection() );
			p_hitRecord._distance = tClosest;

			return true;
		}

		return false;
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) return false;

		if ( !p_node->isLeaf() )
		{
			// descendre dans le noeud fils gauche
			bool leftHitted = _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax );
			// descendre dans le noeud fils droit
			bool rightHitted = _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax );

			return leftHitted || rightHitted;
		}

		//---------------
		// Feuille du BVH
		//---------------
		
		for ( size_t i = p_node->_firstTriangleId; i <= p_node->_lastTriangleId; i++ )
		{
			float t; // distance hitPoint
			if ( (*_triangles)[ i ].intersectAny( p_ray, t ) )
			{
				if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
			}
		}
		return false;
	}
} // namespace RT_ISICG
