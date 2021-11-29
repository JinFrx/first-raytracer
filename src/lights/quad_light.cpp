#include "quad_light.hpp"

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const
	{
		Vec3f randomPoint = _position + randomFloat() * _u + randomFloat() * _v;
		Vec3f direction	= normalize(randomPoint - p_point);
		float distance = glm::distance(randomPoint, p_point);
		float pdf = 1.f / _area * distance * distance / glm::dot( _n, direction );

		return LightSample( direction, distance, (_color * _power) / pdf, pdf);
	}
}