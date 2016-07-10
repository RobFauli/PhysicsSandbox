#ifndef COLOUMBFORCE_HPP
#define COLOUMBFORCE_HPP

#include "Force.hpp"
#include "../Bodies/Body.hpp"
#include "../PhysicalConstants.hpp"
#include <cmath>

class ColoumbForce : public Force {
public:
	Vector3<double> getForceVectorFromAonB(
		const Body& A, const Body& B) const override;

	virtual Vector3<double> getForceVectorFromAonB(
			const Body &A, const Body &B,
			const Vector3<double> &BOffset) const override;


};

#endif /* COLOUMBFORCE_HPP */
