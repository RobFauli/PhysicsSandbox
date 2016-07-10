#ifndef BODY_HPP
#define BODY_HPP

#include <bits/unique_ptr.h>
#include "Vector3.hpp"

//! Anything that can move and has a position will inherit from this class in some way.

class Body {
public:
	Vector3<double> getPosition() const { return position;} ;
	Vector3<double> getVelocity() const { return velocity;} ;
	virtual double getMass() const = 0;
	virtual double getCharge() const = 0;
	void setPosition(const Vector3<double>& pos) { position = pos; };
	void setVelocity(const Vector3<double>& velo) { velocity = velo; };
	void adjustVelocity(const Vector3<double>& adjustment) {
		velocity += adjustment; };
	void adjustPosition(const Vector3<double>& adjustment) {
		position += adjustment; };

	//virtual ~Body();
protected:
	//Body();

private:
	Vector3<double> position;
	Vector3<double> velocity;
};

#endif /* BODY_HPP */
