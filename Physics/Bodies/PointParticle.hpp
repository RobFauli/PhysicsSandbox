#ifndef POINTPARTICLE_HPP
#define POINTPARTICLE_HPP

#include "Body.hpp"

//! Particles that do not extend geometrically in space. They do not have a geometry, thus they can also not rotate.

class PointParticle : public Body {
public:
    PointParticle(double mass, double charge) : m(mass), q(charge) { }

    virtual double getMass() const override { return m; };
    virtual double getCharge() const override { return q; };
private:
    double m; //!< Mass in kg.
    double q; //!< Charge in C. We allow for fractional charges like one finds in quarks.
};

#endif /* POINTPARTICLE_HPP */
