#ifndef PHYSICS_SANDBOX_ODESOLVER_HPP
#define PHYSICS_SANDBOX_ODESOLVER_HPP

#include <vector>
#include <memory>
#include "Vector3.hpp"
#include "Bodies/Body.hpp"
#include "Forces/Force.hpp"

class ODESolver {
public:
    virtual void step(const double dt,
					  std::vector<std::unique_ptr<Body>> &bodies,
					  std::vector<std::shared_ptr<Force>> const &forces) = 0;

	virtual ~ODESolver() { };
};

#endif //PHYSICS_SANDBOX_ODESOLVER_HPP
