#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !
		bool  is_intersected = false;
		Vec3f direction = normalize(p_ray.getDirection());
		Vec3f origin	= p_ray.getOrigin();
		// a vaut 1 car la direction est normalisee
		float b = 2.f * ( dot( direction, ( origin - _center ) ) );
		// (O - C)^2 pareil que dot(O - C, O - C) ?
		float c = dot( origin - _center, origin - _center) - _radius * _radius;
		float delta = b * b - 4 * c;

		if (delta > 0){
			p_t1 = (-b - sqrt(delta)) / 2;
			p_t2 = (-b + sqrt(delta)) / 2;
			is_intersected = true;
		}
		else if (delta == 0) {
			p_t1 = -b / 2;
			p_t2 = p_t1;
			is_intersected = true;
		}
		else{
			p_t1 = -1.f;
			p_t2 = -1.f;
		}
		
		return is_intersected;
	}

} // namespace RT_ISICG
