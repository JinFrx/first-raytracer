#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "base_integrator.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public BaseIntegrator
	{
	  public:
		WhittedIntegrator() : BaseIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

		inline void setNbLightSamples( const int nbLightSamples ) { _nbLightSamples = nbLightSamples; }

		inline void setNbBounces( const int nbBounces ) { _nbBounces = nbBounces; }

		// Retourne la luminance arrivante en considerant les sources de lumieres de la scene.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;
		
	  private:
		int _nbLightSamples = 1;
		int _nbBounces		= 5;

		Vec3f _trace( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax, const int countBounces, const bool isInside ) const;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTED_INTEGRATOR__