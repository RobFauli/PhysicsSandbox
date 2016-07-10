#include "Leapfrog.hpp"

void Leapfrog::step(const double dt,
                  std::vector<std::unique_ptr<Body>> &bodies,
                  std::vector<std::shared_ptr<Force>> const &forces)
{
	if (initSet_)
		{ }
	else
		makeInitials(dt, bodies, forces);

    std::vector<Vector3<double>> netForces_i(bodies.size());
    for (auto &F : forces) {
		auto netFIt = netForces_i.begin();
        for (auto &netF : F->getNetForceStrengths(bodies)) {
			*netFIt++ += netF;
		}
    }

    std::vector<Vector3<double>> x_ip1;
	auto v_halfIt = v_half_.begin();
    auto netFIt = netForces_i.begin();
    for (auto const &body : bodies) {
        *v_halfIt = (*v_halfIt + dt * *netFIt++ / body->getMass());
		body->adjustPosition(dt * *v_halfIt++);
    }

    std::vector<Vector3<double>> netForces_ip1(bodies.size());
    for (auto const &F : forces) {
		auto netFIt2 = netForces_ip1.begin();
        for (auto &netF : F->getNetForceStrengths(bodies)) {
			*netFIt2++ += netF;
		}
    }

	auto v_halfCIt = v_half_.cbegin();
	auto netFIt2 = netForces_ip1.begin();
	for (auto &body : bodies) {
		body->adjustVelocity(*v_halfCIt++
				+ 0.5 * *netFIt2++ * dt / body->getMass());
	}
}

void Leapfrog::makeInitials(const double dt,
							const std::vector<std::unique_ptr<Body>> &bodies,
							const std::vector<std::shared_ptr<Force>> &forces) {
	std::vector<Vector3<double>> netForces_i(bodies.size());
	for (auto &F : forces) {
		auto netFIt = netForces_i.begin();
		for (auto &netF : F->getNetForceStrengths(bodies)) {
			*netFIt++ += netF;
		}
	}

	auto netFIt = netForces_i.cbegin();
	for (auto const &body : bodies) {
		v_half_.push_back(body->getVelocity() + 0.5 * dt * *netFIt++ / body->getMass());
	}

	initSet_ = true;
}
