#include "Force.hpp"

std::vector<Vector3<double>> Force::getNetForceStrengths(
		const std::vector<std::shared_ptr<Body>> &bodies) const
{
	std::vector<Vector3<double>> NetForce(bodies.size()); // F_i
	auto FoIt = NetForce.begin();
	for (auto oIt = bodies.cbegin(); oIt != bodies.cend(); ++oIt) {
		auto FiIt = NetForce.begin();
		for (auto iIt = bodies.cbegin(); iIt != oIt; ++iIt) {
			auto F = getForceVectorFromAonB(**oIt, **iIt);
			*FiIt++ += F;
			*FoIt += -F;
		}
		++FoIt;
	}

	return NetForce;
}

std::vector<Vector3<double>> Force::getNetForceStrengths(
		std::vector<std::unique_ptr<Body>> const &bodies,
		std::vector<Vector3<double>> const &x_ip1) const {

	std::vector<Vector3<double>> NetForce(bodies.size()); // F_i+indexOffset
	auto FoIt = NetForce.begin();
	for (auto &obody : bodies) {
		auto FiIt = NetForce.begin();
		auto x_ip1It = x_ip1.cbegin();
		for (auto &ibody : bodies) {
			if (obody->getPosition() == ibody->getPosition()) { // rather by ID
				continue;
			}
			auto F = getForceVectorFromAonB(*obody, *ibody, *x_ip1It);
			*FiIt++ += F;
		}
		++FoIt;
	}

	return NetForce;
}

double Force::getR2(const Body &A, const Body &B,
					const Vector3<double> &Boffset) const
{
	Vector3<double> temp(B.getPosition() + Boffset-A.getPosition());
	return temp*temp;
}

Vector3<double> Force::getUnitR_AB(const Body &A, const Body &B,
								   const Vector3<double> &Boffset
								   = Vector3<double>(0, 0, 0)) const
{
	return (B.getPosition() + Boffset - A.getPosition())/sqrt(getR2(A, B, Boffset));
}
double Force::getR2(const Body& A, const Body& B) const
{
	Vector3<double> temp(B.getPosition() - A.getPosition());
	return temp*temp;
}

Vector3<double> Force::getUnitR_AB(const Body& A, const Body& B) const
{
	return (B.getPosition() - A.getPosition())/sqrt(getR2(A, B));
}


