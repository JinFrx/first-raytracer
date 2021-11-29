#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry() = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_point, const Vec3f & p_n ): _point( p_point ), _n(p_n) {}

		inline const Vec3f & getPoint() const { return _point; }
		inline const Vec3f & getNormal() const { return _n; }

		bool intersect( const Ray & p_ray, float & p_t ) const;

	  private:
		Vec3f _point = VEC3F_ZERO;
		Vec3f _n = Vec3f(0.f, 1.f, 0.f);

	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__
