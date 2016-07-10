#ifndef GRAVITATIONALFORCE_HPP
#define GRAVITATIONALFORCE_HPP

#include "Force.hpp"
#include "../Bodies/Body.hpp"
#include "../PhysicalConstants.hpp"
#include <cmath>

class GravitationalForce : public Force {
public:
	Vector3<double> getForceVectorFromAonB(
		const Body& A, const Body& B) const override;

	Vector3<double> getForceVectorFromAonB(
			const Body &A, const Body &B,
			const Vector3<double> &BOffset) const override;
};

#endif /* GRAVITATIONALFORCE_HPP */
