#include "Simulation.hpp"

Simulation::Simulation()
: m_forces({}), m_PPC(PointParticleCreator()),  //m_AllBodies({}),
  m_positionsHistory({}), m_dt(1),
  m_dataSaveInterval(0), m_iterationCounter(0)
{
    m_evolve = std::make_unique<Euler>(Euler());
}

void Simulation::runNSteps(const unsigned int &N)
{
    for (unsigned int i = 0; i != N; ++i)
        runOneTimeStep();
}

void Simulation::runOneTimeStep()
{
    if (m_dataSaveInterval != 0)
        if (m_iterationCounter % m_dataSaveInterval == 0) {
            m_positionsHistory.push_back(std::vector<Vector3<double>>());
            for (const auto& body : m_AllBodies) {
                m_positionsHistory.back().push_back(body->getPosition());
            }
        }
        else
            { }
    else
        { }

    m_evolve->step(m_dt, m_AllBodies, m_forces);

    ++m_iterationCounter;

}

void Simulation::setSaveDataEveryXIteration(const unsigned int X)
{
    m_dataSaveInterval = X;
}

void Simulation::addPointParticle(
    const double& mass, const double& charge,
    const Vector3<double>& pos, const Vector3<double>& velocity)
{
    PointParticleCreator PPC;
    std::shared_ptr<Body> PP;
    m_AllBodies.push_back(PPC.CreatePointParticle(mass, charge));
    m_AllBodies.back()->setPosition(pos);
    m_AllBodies.back()->setVelocity(velocity);
}

std::stringstream Simulation::getData() const
{
    auto data = std::stringstream();
    unsigned int i = 0;
    for (const auto& snap : m_positionsHistory) {
        data << i++ ;
        for (const auto& pos : snap) {
            //std::cout << i << std::endl;
            data << " "; // New body.
            data << pos.x << " " << pos.y << " " << pos.z ;
        }
        data << "\n";
    }
    return std::move(data);
}

void Simulation::addForce(std::shared_ptr<Force> &F)
{
    m_forces.push_back(F);
}

std::vector<Vector3<double>> Simulation::getAllPositions() const
{
    std::vector<Vector3<double>> positions;
    for (auto &body : m_AllBodies)
        positions.push_back(body->getPosition());
    return positions;
}
void Simulation::changeLenghtUnitsTo(std::string unit_str)
{
    for (auto& force: m_forces) {
        force->changeLengthUnitsTo(unit_str);
    }
}
void Simulation::changeTimeUnitsTo(std::string unit_str)
{
    for (auto& force: m_forces) {
        force->changeTimeUnitsTo(unit_str);
    }
}






