#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/phong_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name,
			const Vec3f & p_diffuse, const Vec3f & p_specular,
			const float p_s, const float p_ratio=0.3f )
			: BaseMaterial( p_name ), _diffuse_brdf( p_diffuse ), _specular_brdf( p_diffuse, p_specular, p_s ), _ratio(p_ratio)
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f diffuse_color = _diffuse_brdf.evaluate();
			Vec3f specular_color = _specular_brdf.evaluate(p_hitRecord._normal,
				                                           -normalize(p_ray.getDirection()),
				                                           normalize(p_lightSample._direction));
			
			return (1.f - _ratio) * diffuse_color + _ratio * specular_color;
		}

		inline const Vec3f & getFlatColor() const override { return _diffuse_brdf.getKd(); }

	  protected:
		LambertBRDF _diffuse_brdf;
		PhongBRDF	_specular_brdf;
		float		_ratio; // ratio specular / diffuse between 0 and 1
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__