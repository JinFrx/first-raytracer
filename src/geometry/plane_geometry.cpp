#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect(const Ray& p_ray, float & p_t) const
	{
		const float den = glm::dot(normalize(p_ray.getDirection()), _n);
		
		if ( den == 0.f ) return false;
		
		p_t = glm::dot( ( _point - p_ray.getOrigin() ), _n ) / den;

		return true;
	}
}