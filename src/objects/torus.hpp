#ifndef __RT_ISICG_TORUS__
#define __RT_ISICG_TORUS__

#include "base_object.hpp"
#include "geometry/torus_surface.hpp"

namespace RT_ISICG
{
	class Torus : public BaseObject
	{
	  public:
		Torus()			 = delete;
		virtual ~Torus() = default;

		Torus( const std::string & p_name, const Vec3f & p_center, const float p_R, const float p_r )
			: BaseObject( p_name ), _surface( p_center, p_R, p_r ) {}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		bool intersect( const Ray & p_ray,
						const float p_tMin,
						const float p_tMax,
						HitRecord & p_hitRecord ) const override;

		// Check s'il y a une intersection avec le plan
		bool intersectAny( const Ray & p_ray,
			               const float p_tMin,
			               const float p_tMax ) const override;

	  private:
		TorusSurface _surface;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_TORUS__