#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, float & p_t ) const
	{
		const Vec3f & o = p_ray.getOrigin();
		const Vec3f & d = p_ray.getDirection();

		// distance de marche
		float t = p_tMin;
		// distance par rapport a la surface
		float distFromSurface = FLT_MAX;

		for ( int i = 0; i < MAX_MARCHING_STEPS; i++ )
		{
			distFromSurface = sdf( p_ray.pointAtT( t ) );

			if ( abs( distFromSurface ) < MARCHING_EPSILON )
			{
				// le point de marche courant est assez proche de la surface
				p_t = t;

				return true;
			}

			// augmenter la distance de marche
			t += distFromSurface;

			if ( t > p_tMax ) return false; // le point de marche courant est trop loin
		}

		// maximum d'etapes atteint
		return false;
	}
}