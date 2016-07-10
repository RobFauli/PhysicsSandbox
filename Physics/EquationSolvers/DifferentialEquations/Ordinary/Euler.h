#ifndef PHYSICSSANDBOX_EULER_H
#define PHYSICSSANDBOX_EULER_H


#include "ODESolver.hpp"

class Euler : public ODESolver {
public:
    virtual void step(const double dt,
					  std::vector<std::unique_ptr<Body>> &bodies,
					  std::vector<std::shared_ptr<Force>> const &forces)
			override; //!< Advance by one step.

};


#endif //PHYSICSSANDBOX_EULER_H
