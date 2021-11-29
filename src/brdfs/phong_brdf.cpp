#include "phong_brdf.hpp"

namespace RT_ISICG
{
	Vec3f PhongBRDF::evaluate( const Vec3f & p_n,
		                       const Vec3f & p_rayDir,
		                       const Vec3f & p_lightDir ) const
	{
		// Phong
		//Vec3f w_r = glm::reflect(p_lightDir, p_n);
		//float cos_alpha = glm::dot(p_rayDir, w_r);

		// Blinn-Phong
		Vec3f h		= normalize(p_lightDir + p_rayDir);
		float cos_alpha = glm::dot( p_n, h );

		return _kd / PIf + _ks * pow( cos_alpha, _s );
	}

} // namespace RT_ISICG