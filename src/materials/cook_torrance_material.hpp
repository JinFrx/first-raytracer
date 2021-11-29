#ifndef __RT_ISICG_COOK_TORRANCE_MATERIAL__
#define __RT_ISICG_COOK_TORRANCE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"
#include "brdfs/cook_torrance_brdf.hpp"

namespace RT_ISICG
{
	class CookTorranceMaterial : public BaseMaterial
	{
	  public:
		CookTorranceMaterial( const std::string & p_name,
							  const Vec3f &		  p_reflectance,
							  const float		  p_slope,
							  const float		  p_metalness )
			: BaseMaterial( p_name ), _diffuse_brdf( p_reflectance, p_slope ), _specular_brdf( p_reflectance, p_slope ),
			  _metalness( p_metalness )
		{
		}

		virtual ~CookTorranceMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f diffuse = _diffuse_brdf.evaluate(p_hitRecord._normal,
				                                   -normalize( p_ray.getDirection() ),
				                                   normalize( p_lightSample._direction )
			                                      );
			Vec3f specular = _specular_brdf.evaluate(p_hitRecord._normal,
				                                     -normalize( p_ray.getDirection() ),
				                                     normalize( p_lightSample._direction )
			                                        );
			return ( 1.f - _metalness ) * diffuse + _metalness * specular; 
		}

		inline const Vec3f & getFlatColor() const override { return _diffuse_brdf.getKd(); }

	  protected:
		OrenNayarBRDF    _diffuse_brdf;
		CookTorranceBRDF _specular_brdf;
		float			 _metalness = .0f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_COOK_TORRANCE_MATERIAL__