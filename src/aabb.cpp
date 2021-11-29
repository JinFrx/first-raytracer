#include "aabb.hpp"

namespace RT_ISICG
{
	void AABB::extend( const Vec3f & p_v )
	{
		_min = glm::min( _min, p_v );
		_max = glm::max( _max, p_v );
	}

	void AABB::extend( const AABB & p_aabb )
	{
		_min = glm::min( _min, p_aabb.getMin() );
		_max = glm::max( _max, p_aabb.getMax() );
	}

	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		//     ^
		//     |
		// <---+

		const Vec3f & o = p_ray.getOrigin();
		const Vec3f & d = p_ray.getDirection();
		
		// traiter l'intersection du rayon avec la AABB sur une seule dimension
		float txMin = ( _min.x - o.x ) / d.x;
		float txMax = ( _max.x - o.x ) / d.x;
		// echanger les valeurs sur l'axe selon l'orientation du rayon :
		// le rayon est tire de gauche a droite, ou de droite a gauche
		if (txMin > txMax) std::swap(txMin, txMax);

		float tyMin = ( _min.y - o.y ) / d.y;
		float tyMax = ( _max.y - o.y ) / d.y;
		// echanger les valeurs sur l'axe selon l'orientation du rayon :
		// le rayon est tire de haut en bas, ou de bas en haut
		if ( tyMin > tyMax ) std::swap( tyMin, tyMax );

		float tzMin = ( _min.z - o.z ) / d.z;
		float tzMax = ( _max.z - o.z ) / d.z;
		// echanger les valeurs sur l'axe selon l'orientation du rayon :
		// le rayon est tire de devant a derriere, ou de derriere a devant
		if ( tzMin > tzMax ) std::swap( tzMin, tzMax );

		// on veut le tMin le plus proche de la AABB, donc le plus grand
		float tMin = glm::max( txMin, tyMin );
		// on veut le tMax le plus proche de la AABB, donc le plus petit
		float tMax = glm::min( txMax, tyMax );

		// tester si le rayon est en dehors de la AABB
		if ( txMin > tyMax || tyMin > txMax ) return false;
		if ( tMin > tzMax || tzMin > tMax ) return false;
		if ( tMin > p_tMax || p_tMin > tMax ) return false;
		if ( tzMin > p_tMax || p_tMin > tzMax ) return false;
		
		return true;
	}
} // namespace RT_ISICG
