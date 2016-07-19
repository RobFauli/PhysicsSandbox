#ifndef BODY_HPP
#define BODY_HPP

#include <bits/unique_ptr.h>
#include "Vector3.hpp"

//! Anything that can move and has a position will inherit from this class in some way.

class Body {
public:
	Vector3<double> getPosition() const { return _position;} ;
	Vector3<double> getVelocity() const { return _velocity;} ;
	virtual double getMass() const = 0;
	virtual double getCharge() const = 0;
	void setPosition(const Vector3<double>& pos) { _position = pos; };
    void setPosition(double x, double y, double z) { _position = Vector3<double>(x, y, z); };
	void setVelocity(const Vector3<double>& velo) { _velocity = velo; };
	void adjustVelocity(const Vector3<double>& adjustment) {
		_velocity += adjustment; };
	void move(const Vector3<double> &adjustment) {
		_position += adjustment; };
    void move(const double dx, const double dy, const double dz) {
        move(Vector3<double>(dx, dy, dz));
    }

	//virtual ~Body();
protected:
	//Body();

private:
	Vector3<double> _position;
	Vector3<double> _velocity;
};

#endif /* BODY_HPP */
