//
// Created by robertfa on 5/6/16.
//

#include <iostream>
#include "PhysicalConstantsHolder.hpp"

const std::map<const std::string, const double> PhysicalConstantsHolder::sToX = {
    {"s", 1}, {"yr", 1.0/(365.25*24*3600)},
};
const std::map<const std::string, const double> PhysicalConstantsHolder::mToX{
    {"nm", 1e9}, {"cm", 1e2}, {"m", 1}, {"km", 1e-3}, {"ly", 1.057e-16}
};

double PhysicalConstantsHolder::getVacuumPermeability() const
{
    return m_vacuumPermeability;
}
double PhysicalConstantsHolder::getVacuumPermittivity() const
{
    return m_vacuumPermittibity;
}
double PhysicalConstantsHolder::getColoumbsConstant() const
{
    return m_coloumbsConstant;
}
double PhysicalConstantsHolder::getUniversalGravitationalConstant() const
{
    return m_universalGravitationalConstant;
}
double PhysicalConstantsHolder::getSunMass() const
{
    return m_sun_mass;
}
double PhysicalConstantsHolder::getEarthMass() const
{
    return m_earth_mass;
}
double PhysicalConstantsHolder::getEarthRadius() const
{
    return m_earth_radius;
}

void PhysicalConstantsHolder::changeLengthUnitsTo(std::string unit_str)
{
    auto factor = mToX.at(unit_str)/mToX.at(m_lenghtUnit);
    m_speedOfLight *= factor;
    m_vacuumPermeability /= factor;
    m_vacuumPermittibity /= pow(factor, 3);
    m_coloumbsConstant *= pow(factor, 3);
    m_universalGravitationalConstant *= pow(factor, 3);
    m_earth_radius *= factor;

    m_lenghtUnit = unit_str;
}

void PhysicalConstantsHolder::changeTimeUnitsTo(std::string unit_str)
{
    auto factor = sToX.at(unit_str)/sToX.at(m_timeUnit);
    m_speedOfLight /= factor;
    m_vacuumPermeability *= factor;
    m_vacuumPermittibity *= factor*factor;
    m_coloumbsConstant /= factor*factor;
    m_universalGravitationalConstant /= (factor*factor);

    m_timeUnit = unit_str;
}












