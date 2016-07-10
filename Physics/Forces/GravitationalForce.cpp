#include "GravitationalForce.hpp"

Vector3<double> GravitationalForce::getForceVectorFromAonB(
	const Body& A, const Body& B) const
{
	return getUnitR_AB(B, A)*_pch.getUniversalGravitationalConstant()*A.getMass()*B.getMass()/(
		getR2(B, A) + _softR2);
}

Vector3<double> GravitationalForce::getForceVectorFromAonB
		(const Body &A, const Body &B,
		 const Vector3<double> &BOffset) const
{
	return getUnitR_AB(B, A, BOffset)*_pch.getUniversalGravitationalConstant()*A.getMass()*B.getMass()/(
		   getR2(B, A, BOffset) + _softR2);
}
