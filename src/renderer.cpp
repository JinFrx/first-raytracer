#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/direct_lighting_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"
#include <omp.h>

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
			case IntegratorType::DIRECT_LIGHTING:
				_integrator = new DirectLightingIntegrator();
				break;
			case IntegratorType::WHITTED:
				_integrator = new WhittedIntegrator();
				break;
			case IntegratorType::RAY_CAST:
			default:
				_integrator = new RayCastIntegrator();
				break;
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();
		
		#pragma omp parallel for schedule( dynamic )
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Vec3f color = VEC3F_ZERO;

				for ( int k = 0; k < _nbPixelSamples; k++ )
				{
					float sx = (float)i / ( width - 1 ) + randomFloat() / ( width - 1 );
					float sy = (float)j / ( height - 1 ) + randomFloat() / ( height - 1 );

					color += _integrator->Li( p_scene, p_camera->generateRay( sx, sy ), 0.f, 100.f );
				}

				p_texture.setPixel( i, j, glm::clamp( color / (float)( _nbPixelSamples ), 0.f, 1.f ) );
			}

			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
