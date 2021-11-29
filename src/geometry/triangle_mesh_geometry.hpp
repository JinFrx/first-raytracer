#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "base_geometry.hpp"

#include "aabb.hpp" // ajout BVH

namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		TriangleMeshGeometry( const uint p_v0, const uint p_v1, const uint p_v2, MeshTriangle * p_refMesh );

		bool intersect( const Ray & p_ray, float & p_t, float & p_u, float & p_v ) const;

		bool intersectAny( const Ray & p_ray, float & p_t ) const;

		inline const Vec3f & getFaceNormal() const { return _faceNormal; }

		const Vec3f & getInterpolatedNormal( const float p_u, const float p_v ) const;

		//-----------
		// Ajouts BVH
		//-----------
		
		inline MeshTriangle * getRefMesh() const { return _refMesh; }

		inline const AABB getAABB() const { return _aabb; }

		void setBounds();
		
		const Vec3f computeBarycenter() const;

	  private:
		MeshTriangle * _refMesh;
		union
		{
			struct
			{
				uint _v0, _v1, _v2;
			};
			uint _v[ 3 ] = { 0, 0, 0 };
		};

		Vec3f _faceNormal;

		AABB _aabb;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__
