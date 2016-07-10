#include "PointParticleCreator.hpp"

std::unique_ptr<PointParticle> PointParticleCreator::CreatePointParticle(
		double mass, double charge) const
{
	return std::make_unique<PointParticle>(PointParticle(mass, charge));
}
