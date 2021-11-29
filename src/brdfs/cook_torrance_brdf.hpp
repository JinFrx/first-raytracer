#ifndef __RT_ISICG_BRDF_COOK_TORRANCE__
#define __RT_ISICG_BRDF_COOK_TORRANCE__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd, const float p_slope) :
			_kd( p_kd ), _slope( p_slope )
		{
			_alpha = p_slope * p_slope;
		}

		Vec3f evaluate( const Vec3f & p_n, const Vec3f & p_rayDir, const Vec3f & p_lightDir ) const;

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd	 = WHITE;
		float _slope = 0.f;
		float _alpha	 = 0.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_COOK_TORRANCE__