#ifndef FORCE_HPP
#define FORCE_HPP

//! Abstract class defining the interface for forces.
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <PhysicalConstantsHolder.hpp>
#include "../Vector3.hpp"
#include "../Bodies/Body.hpp"



class Force {
public:
	virtual Vector3<double> getForceVectorFromAonB(
		const Body& A, const Body& B) const = 0;

	virtual Vector3<double> getForceVectorFromAonB(
			const Body &A, const Body &B,
			const Vector3<double> &BOffset) const = 0;

	std::vector<Vector3<double>> getNetForceStrengths(
			const std::vector<std::unique_ptr<Body>> &bodies) const;

	std::vector<Vector3<double>> getNetForceStrengths(
			std::vector<std::unique_ptr<Body>> const &bodies,
			const std::vector<Vector3<double>> &x_ip1) const;

	void setSoftener(double softR2) {
		_softR2 = softR2;
	}

	void changeLengthUnitsTo(std::string unit_str)
	{
		_pch.changeLengthUnitsTo(unit_str);
	}
	void changeTimeUnitsTo(std::string unit_str)
	{
		_pch.changeTimeUnitsTo(unit_str);
	}

	Force() : _softR2(0), _pch(PhysicalConstantsHolder()) { };
	virtual ~Force() { };

protected:
	//Force() { };

	Vector3<double> getUnitR_AB(const Body &A, const Body &B,
								const Vector3<double> &Boffset) const;

	Vector3<double> getUnitR_AB(const Body &A, const Body &B) const;

	double getR2(const Body &A, const Body &B, const Vector3<double> &Boffset) const;

	double getR2(const Body &A, const Body &B) const;

	double _softR2;

	PhysicalConstantsHolder _pch;
};

#endif /* FORCE_HPP */
