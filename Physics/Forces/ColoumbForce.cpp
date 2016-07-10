#include "ColoumbForce.hpp"

Vector3<double> ColoumbForce::getForceVectorFromAonB(
	const Body& A, const Body& B) const
{
	return getUnitR_AB(B, A)*_pch.getColoumbsConstant()*A.getCharge()*B.getCharge()/(
		getR2(B, A) + _softR2);
}

Vector3<double> ColoumbForce::getForceVectorFromAonB(const Body &A,
													 const Body &B,
													 const Vector3<double> &BOffset) const {
	return getUnitR_AB(B, A, BOffset)*_pch.getColoumbsConstant()*A.getCharge()*B.getCharge()/(
		   getR2(B, A, BOffset) + _softR2);
}

