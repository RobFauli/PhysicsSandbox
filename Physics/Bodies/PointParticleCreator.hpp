#ifndef POINTPARTICLECREATOR_HPP
#define POINTPARTICLECREATOR_HPP

#include <iostream> // For testing.

#include <memory>
#include "PointParticle.hpp"

//! Creator of point particles (Factory Method).

class PointParticleCreator {
public:
	virtual std::unique_ptr<PointParticle> CreatePointParticle(
			double mass, double charge) const;
};



#endif
