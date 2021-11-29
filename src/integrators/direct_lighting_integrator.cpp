#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li(const Scene& p_scene,
									   const Ray& p_ray,
									   const float p_tMin,
		                               const float p_tMax) const
	{
		Vec3f	  li = VEC3F_ZERO;
		LightList sceneLights = p_scene.getLights();
		HitRecord hitRecord;
		float	  cosTheta;

		if (p_scene.intersect(p_ray, p_tMin, p_tMax, hitRecord))
		{	
			for ( int i = 0; i < sceneLights.size(); i++ )
			{
				if ( sceneLights[ i ]->getIsSurface() )
				{
					//----------------------------
					// Source lumineuse Surfacique
					//----------------------------

					for ( int j = 0; j < _nbLightSamples; j++ )
					{
						LightSample lightSample = sceneLights[ i ]->sample( hitRecord._point );
						Ray			shadowRay	= Ray( hitRecord._point, lightSample._direction );
						// hitRecord._normal deja normalise
						shadowRay.offset( hitRecord._normal );

						if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
						{
							cosTheta = glm::dot( normalize( lightSample._direction ), hitRecord._normal );
							if ( cosTheta < 0.f ) cosTheta = 0.f;

							li += hitRecord._object->getMaterial()->shade(p_ray, hitRecord, lightSample) *
								  lightSample._radiance * cosTheta;
						}
					}

					li /= _nbLightSamples;
				}
				else
				{
					//------------
					// Point Light
					//------------

					LightSample lightSample = sceneLights[ i ]->sample( hitRecord._point );
					Ray			shadowRay	= Ray( hitRecord._point, lightSample._direction );
					shadowRay.offset( hitRecord._normal );

					if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
					{
						cosTheta = glm::dot( normalize( lightSample._direction ), hitRecord._normal );
						if ( cosTheta < 0.f ) cosTheta = 0.f;

						// point observe = hitRecord._point
						li += hitRecord._object->getMaterial()->shade(p_ray, hitRecord, lightSample) *
							  lightSample._radiance * cosTheta;
					}
				}
			}

			return li;
		}
		else
			return _backgroundColor;
	}

} // namespace RT_ISICG