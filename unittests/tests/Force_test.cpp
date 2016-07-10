#include "gtest/gtest.h"
#include "../../Physics/Simulation.hpp"
#include "../../Physics/PhysicalConstants.hpp"

//SCENARIO("Neutral particles and only the gravitational force") {
TEST(Force, GravityEarthSurface) {
    GravitationalForce GForce;
    PointParticleCreator PPC;
    //GIVEN("Particle one earth radius from Earth in x-direction") {
    Vector3<double> pos_tp(6371e3, 0, 0);
    Vector3<double> pos_earth(0, 0, 0);
    Vector3<double> nullVelocity(0, 0, 0);
    double tp_mass = 10.0;

    auto tp = PPC.CreatePointParticle(tp_mass, 0);
    tp->setPosition(pos_tp);
    tp->setVelocity(nullVelocity);

    auto earth = PPC.CreatePointParticle(g_earth_mass_SI, 0);
    earth->setPosition(pos_earth);
    earth->setVelocity(nullVelocity);

    //THEN("The force from earth on the particle is") {
    auto F = GForce.getForceVectorFromAonB(*earth, *tp);
    EXPECT_NEAR(-(9.81*tp_mass), F.x, 0.1);
}

// With ly as unit of length and yr as unit of time
TEST(Gravity, EarthSurface_ly_yr) {

    GravitationalForce GForce;
    GForce.changeLengthUnitsTo("ly");
    GForce.changeTimeUnitsTo("yr");
    PointParticleCreator PPC;

    Vector3<double> pos_tp(g_earth_radius_SI*PhysicalConstantsHolder::mToX.at("ly"), 0, 0);
    Vector3<double> pos_earth(0, 0, 0);
    Vector3<double> nullVelocity(0, 0, 0);
    double tp_mass = 10.0;

    auto tp = PPC.CreatePointParticle(tp_mass, 0);
    tp->setPosition(pos_tp);
    tp->setVelocity(nullVelocity);

    auto earth = PPC.CreatePointParticle(g_earth_mass_SI, 0);
    earth->setPosition(pos_earth);
    earth->setVelocity(nullVelocity);

    //THEN("The force from earth on the particle is") {
    auto F = GForce.getForceVectorFromAonB(*earth, *tp);
    EXPECT_NEAR(
        -(9.81 * tp_mass * pow(PhysicalConstantsHolder::sToX.at("yr"), -2)
            * PhysicalConstantsHolder::mToX.at("ly")), F.x, 0.1);
}
