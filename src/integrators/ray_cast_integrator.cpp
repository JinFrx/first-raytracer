#include "ray_cast_integrator.hpp"

namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		float theta;

		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			/// TODO ! cos theta...
			// 3.2. Votre premier objet : une sphere
			// il faut normaliser le vecteur normal pour avoir un bon resultat
			theta = glm::dot( -p_ray.getDirection(), normalize(hitRecord._normal) );
			if ( theta < 0.f ) theta = 0.f;
			return hitRecord._object->getMaterial()->getFlatColor() * theta;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
