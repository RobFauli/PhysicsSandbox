set(Library_FILES
        Bodies/Body.cpp
        Forces/ColoumbForce.cpp
        Forces/Force.cpp
        Forces/GravitationalForce.cpp
        Bodies/PointParticle.cpp
        Bodies/PointParticleCreator.cpp
        Simulation.cpp
        EquationSolvers/DifferentialEquations/Ordinary/ODESolver.cpp
        EquationSolvers/DifferentialEquations/Ordinary/Euler.cpp
        EquationSolvers/DifferentialEquations/Ordinary/Leapfrog.cpp
        PhysicalConstantsHolder.cpp PhysicalConstantsHolder.hpp Tools/GenerateInitials.cpp ../Examples/SimulationConfigurations.cpp ../Examples/SimulationConfigurations.hpp)

add_library(physics ${Library_FILES})

target_include_directories(physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})