#ifndef __RT_ISICG_BRDF_OREN_NAYAR__
#define __RT_ISICG_BRDF_OREN_NAYAR__

#include "defines.hpp"
#include "hit_record.hpp"
#include "lights/light_sample.hpp"
#include "ray.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const float p_slope ) : _kd( p_kd ), _slope(p_slope) {}

		Vec3f evaluate(const Vec3f & p_n, const Vec3f & p_rayDir, const Vec3f & p_lightDir) const;

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float _slope = 0.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_OREN_NAYAR__