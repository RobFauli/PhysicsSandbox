#ifndef PHYSICSSANDBOX_LEAPFROG_HPP
#define PHYSICSSANDBOX_LEAPFROG_HPP

#include "ODESolver.hpp"

class Leapfrog : public ODESolver {
public:
	Leapfrog()
			: v_half_({}), initSet_(false) { }

	virtual void step(
			const double dt,
			std::vector<std::unique_ptr<Body>>& bodies,
			std::vector<std::shared_ptr<Force>> const &forces) override;

	void makeInitials(
			const double dt,
			std::vector<std::unique_ptr<Body>> const &bodies,
			std::vector<std::shared_ptr<Force>> const &forces);
private:
	std::vector<Vector3<double>> v_half_;
	bool initSet_;
};


#endif //PHYSICSSANDBOX_LEAPFROG_HPP
