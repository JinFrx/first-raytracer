#include "whitted_integrator.hpp"

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		// on considere qu'on tire un rayon primaire depuis le vide, d'ou false au depart
		return _trace( p_scene, p_ray, p_tMin, p_tMax, 0, false);
	}

	Vec3f WhittedIntegrator::_trace(const Scene& p_scene,
							        const Ray& p_ray,
								    const float p_tMin,
		                            const float p_tMax,
									const int countBounces,
		                            const bool isInside) const
	{
		Vec3f	  color		  = BLACK;
		LightList sceneLights = p_scene.getLights();
		HitRecord hitRecord;
		float	  cosTheta;

		if (p_scene.intersect(p_ray, p_tMin, p_tMax, hitRecord))
		{	
			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				//==========================================================================
				// Eclairage indirect type mirroir
				//==========================================================================
				
				//----------
				// Reflexion
				//----------

				if ( countBounces >= _nbBounces ) return BLACK;
				else
				{
					Vec3f reflectDir = glm::reflect( p_ray.getDirection(), hitRecord._normal );
					Ray	  reflectRay = Ray( hitRecord._point, reflectDir );
					reflectRay.offset( hitRecord._normal );
					
					color += _trace( p_scene, reflectRay, p_tMin, p_tMax, countBounces + 1, isInside );
				}
			}
			else if ( hitRecord._object->getMaterial()->isTransparent() )
			{
				//==========================================================================
				// Eclairage indirect type transparent
				//==========================================================================
				
				if ( countBounces >= _nbBounces ) return BLACK;
				else
				{
					Vec3f reflectColor = BLACK, refractColor = BLACK;
					
					float n1 = 1.f; // vide
					float n2 = hitRecord._object->getMaterial()->getIOR();

					if ( isInside )
					{
						n1 = hitRecord._object->getMaterial()->getIOR();
						n2 = 1.f; // vide
					}
					
					//----------
					// Reflexion
					//----------

					Vec3f reflectDir = glm::reflect( p_ray.getDirection(), hitRecord._normal );
					Ray	  reflectRay = Ray( hitRecord._point, reflectDir );
					reflectRay.offset( hitRecord._normal );

					// on conserve la valeur de isInside car le rayon peut etre reflechi a l'interieur
					reflectColor += _trace( p_scene, reflectRay, p_tMin, p_tMax, countBounces + 1, isInside );

					//-----------
					// Refraction
					//-----------
					
					Vec3f refractDir = glm::refract( p_ray.getDirection(), hitRecord._normal, n1 / n2 );
					
					if ( refractDir == VEC3F_ZERO )
						color += reflectColor;
					else
					{
						Ray refractRay = Ray( hitRecord._point, refractDir );
						refractRay.offset( -hitRecord._normal );

						refractColor += _trace( p_scene, refractRay, p_tMin, p_tMax, countBounces + 1, !isInside );

						// Approximation de Schlick pour le coefficient de Fresnel
						/*
						float R0	   = pow( ( n1 - n2 ) / ( n1 + n2 ), 2 );
						float cosTheta = glm::dot( -p_ray.getDirection(), hitRecord._normal );
						float kr	   = R0 + (double(1.f) - R0) * pow( 1.f - cosTheta, 5 );
						
						color += ( 1.f - kr ) * refractColor + kr * reflectColor;
						*/

						// Coefficient de Fresnel
						float cosTheta_i = glm::dot( -p_ray.getDirection(), hitRecord._normal );
						float cosTheta_t = glm::dot( -refractDir, hitRecord._normal );
						float Rs = pow( ( n1 * cosTheta_i - n2 * cosTheta_t ) / ( n1 * cosTheta_i + n2 * cosTheta_t ), 2 );
						float Rp = pow( ( n1 * cosTheta_t - n2 * cosTheta_i ) / ( n1 * cosTheta_t + n2 * cosTheta_i ), 2 );
						float kr = 1.f / 2.f * ( Rs + Rp );
						float kr_transmitted = 1.f / 2.f * ( 1.f - Rs + 1.f - Rp );

						color += kr_transmitted * refractColor + kr * reflectColor;
						
					}
				}
			}
			else
			{
				//==========================================================================
				// Eclairage direct
				//==========================================================================

				for ( int i = 0; i < sceneLights.size(); i++ )
				{
					//==========================================================================
					// Type de source lumineuse
					//==========================================================================

					if ( sceneLights[ i ]->getIsSurface() )
					{
						//----------------------------
						// Source lumineuse surfacique
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
								
								//------
								// Shade
								//------

								color += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample )
											* lightSample._radiance * cosTheta;
							}
						}

						color /= _nbLightSamples;
					}
					else
					{
						//------------
						// Point Light
						//------------

						LightSample lightSample = sceneLights[ i ]->sample( hitRecord._point );
						Ray			shadowRay	= Ray( hitRecord._point, lightSample._direction );
						// hitRecord._normal deja normalise
						shadowRay.offset( hitRecord._normal );

						if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
						{
							cosTheta = glm::dot( normalize( lightSample._direction ), hitRecord._normal );
							if ( cosTheta < 0.f ) cosTheta = 0.f;
							
							//------
							// Shade
							//------

							color += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample )
									    * lightSample._radiance * cosTheta;
						}
					}
				}
			}

			return color;
		}
		else
			return _backgroundColor;
	}

} // namespace RT_ISICG