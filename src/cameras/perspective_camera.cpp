#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// TODO ! _u ? _v ? _w ?
		// 4.1 Une camera positionnable
		Vec3f direction = p_lookAt - p_position;

		_w = normalize( -direction );
		_u = glm::cross( p_up, _w);
		_v = glm::cross(_w, _u);
		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
		/// *DONE* "2 Camera, rayons et projection perspective - 1"
		float viewportHeight = tan( _fovy * 0.5f * PIf / 180 ) * 2.f * _focalDistance;
		float viewportWidth	 = viewportHeight * _aspectRatio;

		_viewportU = viewportWidth * _u;
		_viewportV = viewportHeight * _v;
		_viewportTopLeftCorner = 0.5f * -_viewportU + 0.5f * _viewportV + _focalDistance * -_w;
	}

} // namespace RT_ISICG
