#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight( const Vec3f & p_color, const float p_power, const Vec3f & p_position )
			: BaseLight( p_color, p_power ), _position( p_position ) {}
		virtual ~PointLight() = default;

		inline const Vec3f & getPosition() const { return _position; }

		LightSample sample( const Vec3f & p_point ) const;

	  private:
		Vec3f _position = VEC3F_ZERO;
	};
} // namespace RTISICG

#endif // __RT_ISICG_POINT_LIGHT__
