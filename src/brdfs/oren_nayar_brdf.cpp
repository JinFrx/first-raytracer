#include "oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	Vec3f OrenNayarBRDF::evaluate( const Vec3f & p_n,
								   const Vec3f & p_rayDir,
		                           const Vec3f & p_lightDir ) const
	{
		float slope_square	= _slope * _slope;
		float a				= 1.f - .5f * ( slope_square / ( slope_square + .33f ) );
		float b				= .45f * ( slope_square / ( slope_square + .09f ) );
		float cosTheta_i	= glm::dot( p_n, p_lightDir );
		float cosTheta_o	= glm::dot( p_n, p_rayDir );
		float alpha         = glm::max( acos( cosTheta_i ), glm::acos( cosTheta_o ) );
		float beta          = glm::min( acos( cosTheta_i ), glm::acos( cosTheta_o ) );
		Vec3f lightDirPhi   = glm::normalize(p_lightDir - p_n * cosTheta_i);
		Vec3f rayDirPhi     = glm::normalize(p_rayDir - p_n * cosTheta_o);
		float maxCosPhiDiff = glm::max( 0.f, glm::dot( lightDirPhi, rayDirPhi ) );
		
		return _kd * INV_PIf * ( a + ( b * maxCosPhiDiff ) * glm::sin(alpha) * glm::tan(beta) );
	}

} // namespace RT_ISICG