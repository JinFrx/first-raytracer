#include "point_light.hpp"

namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const
	{
		float distance = glm::distance(_position, p_point);
		Vec3f radiance = _color * _power * ( 1.f / (distance * distance));

		return LightSample( normalize(_position - p_point), distance, radiance, 1.f );
	}
}
