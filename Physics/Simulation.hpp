#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <sstream>
#include <utility>

#include "EquationSolvers/DifferentialEquations/Ordinary/ODESolver.hpp"
#include "EquationSolvers/DifferentialEquations/Ordinary/Euler.h"
#include "Forces/Force.hpp"
#include "Forces/ColoumbForce.hpp"
#include "Forces/GravitationalForce.hpp"
#include "Bodies/PointParticleCreator.hpp"

//! A region of space possibly with content that can be simulated.

class Simulation {
public:
	Simulation();
	//~Simulation();

	void runNSteps(const unsigned int& N);
	void runOneTimeStep();
	void setSaveDataEveryXIteration(const unsigned int X);
	void setNoDataSaving() { m_dataSaveInterval = 0; }
	void setDT(const double DT) { m_dt = DT; };
	void addPointParticle(
		const double& mass, const double& charge,
		const Vector3<double>& pos, const Vector3<double>& velocity);
    void addBody(std::shared_ptr<Body> body);
	void addForce(std::shared_ptr<Force> &F);
    void changeODESolver(std::unique_ptr<ODESolver> odes) {
        m_evolve = std::move(odes);
    }

	void changeLenghtUnitsTo(std::string unit_str);
	void changeTimeUnitsTo(std::string unit_str);

	std::vector<Vector3<double>> getAllPositions() const;

	std::stringstream getData() const;

private:
	std::vector<std::shared_ptr<Force>> m_forces;
	PointParticleCreator m_PPC;
	std::vector<std::shared_ptr<Body>> m_AllBodies;
	std::unique_ptr<ODESolver> m_evolve;

	std::vector<std::vector<Vector3<double>>> m_positionsHistory;

	double m_dt;

	unsigned int m_dataSaveInterval;
	unsigned int m_iterationCounter;

};
#endif /* SIMULATION_HPP */
