#include "torus.hpp"

namespace RT_ISICG
{
	bool Torus::intersect(const Ray& p_ray, const float p_tMin, const float p_tMax, HitRecord& p_hitRecord) const
	{
		float t;

		if ( _surface.intersect( p_ray, p_tMin, p_tMax, t ) )
		{
			// Intersection found, fill p_hitRecord.
			p_hitRecord._point	= p_ray.pointAtT( t );
			p_hitRecord._normal = _surface.computeNormal( p_hitRecord._point );
			p_hitRecord.faceNormal( p_ray.getDirection() );
			p_hitRecord._distance = t;
			p_hitRecord._object	  = this;

			return true;
		}

		return false;
	}

	bool Torus::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float t;

		if ( _surface.intersect( p_ray, p_tMin, p_tMax, t ) )
			return true;

		return false;
	}

}