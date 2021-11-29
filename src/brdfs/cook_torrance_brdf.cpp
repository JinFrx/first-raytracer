#include "cook_torrance_brdf.hpp"

namespace RT_ISICG
{
	Vec3f CookTorranceBRDF::evaluate(const Vec3f & p_n,
								     const Vec3f & p_rayDir,
		                             const Vec3f & p_lightDir) const
	{
		// demi-vecteur
		Vec3f h = normalize(p_rayDir + p_lightDir);

		// NDF avec distrib GGX/Trowbridge-Reitz
		float dot_n_h = glm::dot( p_n, h );
		float alpha_square = _alpha * _alpha;
		float den_factor	   = dot_n_h * dot_n_h * ( alpha_square - 1 ) + 1;
		float D = alpha_square / ( PIf * den_factor * den_factor );

		// fonction d'ombrage avec modele de Smith et approxim de Schlick pour GGX
		float x_wo	= glm::dot( p_n, p_rayDir );
		float x_wi	= glm::dot( p_n, p_lightDir );
		float k		= ( ( _slope + 1.f ) * ( _slope + 1.f ) ) / 8.f;
		float G1_wo = x_wo / ( x_wo * ( 1.f - k ) + k );
		float G1_wi = x_wi / (x_wi * (1.f - k) + k);
		float G		= G1_wo * G1_wi;
		
		// equation de Fresnel avec approxim de Schlick
		Vec3f F = _kd + ( 1.f - _kd ) * powf( ( 1.f - ( glm::dot( h, p_rayDir ) ) ), 5 );

		return (D * F * G) / (4 * glm::dot(p_rayDir, p_n) * glm::dot(p_lightDir, p_n));
	}

} // namespace RT_ISICG