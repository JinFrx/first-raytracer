#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "base_light.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight( const Vec3f & p_color, const float p_power, const Vec3f & p_position, const Vec3f & p_u, const Vec3f & p_v)
			: BaseLight( p_color, p_power ), _position( p_position ), _u( p_u ), _v( p_v )
		{
			_isSurface = true;
			_n = normalize( glm::cross( _u, _v ) );
			_area = glm::length( _u ) * glm::length( _v );
		}
		
		virtual ~QuadLight() = default;

		inline const Vec3f & getPosition() const { return _position; }

		LightSample sample(const Vec3f & p_point) const;

	  private:
		Vec3f _position;
		Vec3f _u, _v, _n;
		float _area;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_QUAD_LIGHT__