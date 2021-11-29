#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

#define EPSILON .000001f

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const uint	   p_v0,
												const uint	   p_v1,
												const uint	   p_v2,
												MeshTriangle * p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	//===================================
	// Moller-Trumbore one-sided triangle
	//===================================

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t, float & p_u, float & p_v ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		// aretes du triangle
		Vec3f e1 = v1 - v0;
		Vec3f e2 = v2 - v0;

		// produit vectoriel pour calculer le determinant et u
		Vec3f pVec = glm::cross( d, e2 );

		// determinant
		float det = glm::dot( pVec, e1 );

		if ( det < EPSILON )
			// eviter les rayons parallels qui amenent a une division par zero
			return false;

		// distance entre le sommet v0 du triangle et l'origine du rayon
		Vec3f tVec = o - v0;
		
		float u = glm::dot( pVec, tVec );
		if ( u < 0.f || u > det )
			return 0; // pt d'intersection en dehors du triangle

		// produit vectoriel pour calculer t et v
		Vec3f qVec = glm::cross( tVec, e1 );

		float v = glm::dot( qVec, d );
		if ( v < 0.f || u + v > det )
			return 0; // pt d'intersection en dehors du triangle
		
		float inv_det = 1.f / det;

		p_t = glm::dot( e2, qVec ) * inv_det;
		p_u = u * inv_det;
		p_v = v * inv_det;

		return true;
	}

	//=================================================
	// Moller-Trumbore one-sided triangle (shadow rays)
	//=================================================

	bool TriangleMeshGeometry::intersectAny( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		// aretes du triangle
		Vec3f e1 = v1 - v0;
		Vec3f e2 = v2 - v0;

		// produit vectoriel pour calculer le determinant et u
		Vec3f pVec = glm::cross( d, e2 );

		// determinant
		float det = glm::dot( pVec, e1 );

		if ( det < EPSILON )
			// eviter les rayons parallels qui amenent a une division par zero
			return false;
		
		// distance entre le sommet v0 du triangle et l'origine du rayon
		Vec3f tVec = o - v0;

		float u = glm::dot( pVec, tVec );
		if ( u < 0.f || u > det ) return 0; // pt d'intersection en dehors du triangle

		// produit vectoriel pour calculer t et v
		Vec3f qVec = glm::cross( tVec, e1 );

		float v = glm::dot( qVec, d );
		if ( v < 0.f || u + v > det ) return 0; // pt d'intersection en dehors du triangle
		
		float inv_det = 1.f / det;

		p_t = glm::dot( e2, qVec ) * inv_det;

		return true;
	}

	const Vec3f & TriangleMeshGeometry::getInterpolatedNormal(const float p_u, const float p_v) const
	{
		const Vec3f & n0 = _refMesh->_normals[ _v0 ];
		const Vec3f & n1 = _refMesh->_normals[ _v1 ];
		const Vec3f & n2 = _refMesh->_normals[ _v2 ];
		
		return ( 1.f - p_u - p_v ) * n0 + p_u * n1 + p_v * n2;
	}

	//----------
	// Ajout BVH
	//----------

	void TriangleMeshGeometry::setBounds()
	{
		Vec3f v0 = _refMesh->_vertices[ _v0 ];
		Vec3f v1 = _refMesh->_vertices[ _v1 ];
		Vec3f v2 = _refMesh->_vertices[ _v2 ];

		_aabb.extend( v0 );
		_aabb.extend( v1 );
		_aabb.extend( v2 );
	}

	const Vec3f TriangleMeshGeometry::computeBarycenter() const
	{
		Vec3f v0		 = _refMesh->_vertices[ _v0 ];
		Vec3f v1		 = _refMesh->_vertices[ _v1 ];
		Vec3f v2		 = _refMesh->_vertices[ _v2 ];

		return Vec3f( ( v0.x + v1.x + v2.x ) / 3.f,
			          ( v0.y + v1.y + v2.y ) / 3.f,
			          ( v0.z + v1.z + v2.z ) / 3.f );
	}

} // namespace RT_ISICG
