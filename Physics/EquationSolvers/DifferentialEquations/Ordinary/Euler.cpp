#include "Euler.h"

void Euler::step(const double dt,
                 std::vector<std::unique_ptr<Body>> &bodies,
                 std::vector<std::shared_ptr<Force>> const &forces) {
    std::vector<Vector3<double>> netForces(bodies.size());
    for (const auto& F : forces) {
        auto netFIt = netForces.begin();
        for (const auto& netF : F->getNetForceStrengths(bodies)) {
            *netFIt++ += netF;
        }
    }

    // Go a step:
    auto netFIt = netForces.begin();
    for (auto& body : bodies) {
        body->adjustPosition(body->getVelocity() * dt);
        body->adjustVelocity(*netFIt * dt / body->getMass());
    }
}
