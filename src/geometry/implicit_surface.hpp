#ifndef __RT_ISICG_IMPLICIT_SURFACE__
#define __RT_ISICG_IMPLICIT_SURFACE__

#include "base_geometry.hpp"

#define MAX_MARCHING_STEPS 100
#define MARCHING_EPSILON .000001f

namespace RT_ISICG
{
	class ImplicitSurface : public BaseGeometry
	{
	  public:
		ImplicitSurface() = default;
		virtual ~ImplicitSurface() = default;
		
		virtual float sdf( const Vec3f & p_point ) const = 0;

		virtual const Vec3f & computeNormal( const Vec3f & p_point ) const = 0;

		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, float & p_t ) const;

	};
}

#endif // __RT_ISICG_IMPLICIT_SURFACE__