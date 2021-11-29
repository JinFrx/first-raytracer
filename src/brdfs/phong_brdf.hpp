#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_kd, const Vec3f & p_ks, const float p_s ) : _kd( p_kd ), _ks( p_ks ), _s( p_s ) {}

		Vec3f evaluate( const Vec3f & p_n, const Vec3f & p_rayDir, const Vec3f & p_lightDir ) const;

		inline const Vec3f & getKd() const { return _kd; }

		inline const Vec3f & getKs() const { return _ks; }

	  private:
		Vec3f _kd = WHITE;
		Vec3f _ks = WHITE;
		float _s = 0.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__