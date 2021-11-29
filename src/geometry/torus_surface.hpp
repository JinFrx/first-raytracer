#ifndef __RT_ISICG_TORUS_SURFACE__
#define __RT_ISICG_TORUS_SURFACE__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class TorusSurface : public ImplicitSurface
	{
	  public:
		TorusSurface() = delete;
		virtual ~TorusSurface() = default;

		TorusSurface( const Vec3f & p_center, const float p_R, const float p_r ) : _center( p_center ), _R( p_R ), _r( p_r ) {}

		inline float sdf( const Vec3f & p_point ) const override
		{
			float x = _center.x - p_point.x; // translation vers le centre
			float y = _center.y - p_point.y;
			float z = _center.z - p_point.z;

			//return glm::length( Vec3f( x, y, z ) ) - _R; // exemple sphere
			
			float q = _R - glm::sqrt( x * x + y * y );
			return glm::sqrt( q * q + z * z ) - _r * _r;
		};

		inline const Vec3f & computeNormal( const Vec3f & p_point ) const override
		{
			// trouver le gradient a partir d'un point proche de p_point sur la surface
			float t = sdf( p_point );
			float eps = 0.01f;

			return normalize( Vec3f( sdf( p_point + Vec3f( 1.f, 0.f, 0.f ) * eps - t ),
								     sdf( p_point + Vec3f( 0.f, 1.f, 0.f ) * eps - t ),
								     sdf( p_point + Vec3f( 0.f, 0.f, 1.f ) * eps - t ) ) );
		}

	  private:
		Vec3f _center;
		float _R;
		float _r;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_TORUS_SURFACE__