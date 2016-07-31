#include <EquationSolvers/DifferentialEquations/Ordinary/Leapfrog.hpp>
#include <random>
#include <math.h>
//#include <gd.h>
#include "gtest/gtest.h"
#include "Simulation.hpp"

// Testing of full simulation scenarios.

class OrbitTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        testSimu = Simulation();
        std::shared_ptr<GravitationalForce> gravity(new GravitationalForce());
        std::shared_ptr<Force> force = gravity;
        testSimu.addForce(force);
    }

    double range(const Vector3<double>& A, const Vector3<double>& B) const {
        auto r_BA = B - A;
        return sqrt(r_BA * r_BA);
    }

    Simulation testSimu;

    double OrbitVelo(const double r, const double m,
                     const double G = g_universalGravitationalConstant_SI) {
        return sqrt(G*m/r);
    }

    Vector3<double> nullV3;
};

TEST_F(OrbitTest, EulerStability) {
    double tpMass = 10;
    double tp_r0 = g_earth_radius_SI + 413e3; // Initial range to earth in m.
    Vector3<double> tpPos(tp_r0, 0, 0); // Like the ISS.
    auto tpYVelo = OrbitVelo(tpPos.x, g_earth_mass_SI);
    testSimu.addPointParticle(tpMass, 0, tpPos, Vector3<double>(0, tpYVelo, 0));
    testSimu.addPointParticle(g_earth_mass_SI, 0, nullV3, nullV3);

    auto bodies = testSimu.getAllPositions();
    auto tp = bodies[0];
    auto Earth = bodies[1];
    ASSERT_EQ(tp_r0, range(Earth, tp));

    double dt = 0.01;
    testSimu.setDT(dt);
    unsigned int maxIterations = 95*60/dt; // 95 min is one approx orbit for ISS
    for(unsigned int i = 0; i < maxIterations; ++i) {
        testSimu.runOneTimeStep();
        bodies = testSimu.getAllPositions();
        tp = bodies[0];
        Earth = bodies[1];

        EXPECT_NEAR(range(Earth, tp), tp_r0, 0.2*tp_r0);
    }
}

TEST_F(OrbitTest, LeapfrogStability) {
    double tpMass = 10;
    double tp_r0 = g_earth_radius_SI + 413e3; // Initial range to earth in m.
    Vector3<double> tpPos(tp_r0, 0, 0); // Like the ISS.
    auto tpYVelo = OrbitVelo(tpPos.x, g_earth_mass_SI);
    testSimu.addPointParticle(tpMass, 0, tpPos, Vector3<double>(0, tpYVelo, 0));
    testSimu.addPointParticle(g_earth_mass_SI, 0, nullV3, nullV3);

    std::unique_ptr<ODESolver> leapfrog_ptr = std::make_unique<Leapfrog>(Leapfrog());
    testSimu.changeODESolver(std::move(leapfrog_ptr));

    auto bodies = testSimu.getAllPositions();
    auto tp = bodies[0];
    auto Earth = bodies[1];
    ASSERT_EQ(tp_r0, range(Earth, tp));

    double dt = 0.01;
    testSimu.setDT(dt);
    unsigned int maxIterations = 95*60/dt; // 95 min is one approx orbit for ISS
    for(unsigned int i = 0; i < maxIterations; ++i) {
        testSimu.runOneTimeStep();
        bodies = testSimu.getAllPositions();
        tp = bodies[0];
        Earth = bodies[1];

        EXPECT_NEAR(range(Earth, tp), tp_r0, 0.2 * tp_r0);
    }
}

TEST_F(OrbitTest, LeapfrogStability_in_ly_and_yr) {
    PhysicalConstantsHolder pch = PhysicalConstantsHolder();
    pch.changeTimeUnitsTo("yr");
    pch.changeLengthUnitsTo("ly");

    double tpMass = 10;
    double tp_r0 = 1; // Initial range to earth in m.
    Vector3<double> tpPos(tp_r0, 0, 0); // Like the ISS.
    auto tpYVelo = OrbitVelo(tpPos.x, g_sun_mass_SI, pch.getUniversalGravitationalConstant());
    testSimu.addPointParticle(tpMass, 0, tpPos, Vector3<double>(0, tpYVelo, 0));
    testSimu.addPointParticle(g_sun_mass_SI, 0, nullV3, nullV3);

    std::unique_ptr<ODESolver> leapfrog_ptr = std::make_unique<Leapfrog>(Leapfrog());
    testSimu.changeODESolver(std::move(leapfrog_ptr));

    testSimu.changeLenghtUnitsTo("ly");
    testSimu.changeTimeUnitsTo("yr");


    auto bodies = testSimu.getAllPositions();
    auto tp = bodies[0];
    auto Earth = bodies[1];
    ASSERT_EQ(tp_r0, range(Earth, tp));

    double dt = 1;
    testSimu.setDT(dt);
    unsigned int maxIterations = 1e7; //95*60/dt;
    for(unsigned int i = 0; i < maxIterations; ++i) {
        testSimu.runOneTimeStep();
        bodies = testSimu.getAllPositions();
        tp = bodies[0];
        Earth = bodies[1];

        EXPECT_NEAR(range(Earth, tp), tp_r0, 0.1 * tp_r0);
    }
}

class ColdCollapseTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        Vector3<double> nullV3;
    Simulation testSim;
    auto GForce = std::make_shared<GravitationalForce>(GravitationalForce());
    GForce->setSoftener(0.15*0.15);
    std::shared_ptr<Force> force = GForce;
    testSim.addForce(force);
	std::unique_ptr<ODESolver> leapfrog_ptr = std::make_unique<Leapfrog>(Leapfrog());
	testSim.changeODESolver(std::move(leapfrog_ptr));

    testSim.changeTimeUnitsTo("yr");
    testSim.changeLenghtUnitsTo("ly");

    double dt = 1e5;
    testSim.setDT(dt);
    //testSim.setSaveDataEveryXIteration(1);

    double M = 1*g_sun_mass_SI;
    double r_max = 20.0;

    std::default_random_engine rng;
    std::uniform_real_distribution<double> r(0.01, r_max);
    std::uniform_real_distribution<double> theta(0.0, M_PI);
    std::uniform_real_distribution<double> phi(0.0, 2*M_PI);
    for (int k = 0; k<200; ++k)
        testSim.addPointParticle(M, 0, Vector3<double>(r(rng)*sin(theta(rng))*cos(phi(rng)),
                                                       r(rng)*sin(theta(rng))*sin(phi(rng)),
                                                       r(rng)*cos(theta(rng))), nullV3);
    }
};
