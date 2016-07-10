//
// Created by robertfa on 5/6/16.
//

#ifndef PHYSICSSANDBOX_PHYSICALCONSTANTSHOLDER_HPP
#define PHYSICSSANDBOX_PHYSICALCONSTANTSHOLDER_HPP

#include "PhysicalConstants.hpp"

class PhysicalConstantsHolder
{
public:
    double getVacuumPermeability() const;
    double getVacuumPermittivity() const;
    double getColoumbsConstant() const;
    double getUniversalGravitationalConstant() const;
    double getSunMass() const;
    double getEarthMass() const;
    double getEarthRadius() const;

    void changeLengthUnitsTo(std::string unit_str);
    void changeTimeUnitsTo(std::string unit_str);

    // Maps of unit conversions:
    static const std::map<const std::string, const double> mToX;

    static const std::map<const std::string, const double> sToX;

private:
    // Current units:
    std::string m_lenghtUnit{"m"};
    std::string m_timeUnit{"s"};

    // Physical constants:
    double m_speedOfLight{g_speedOfLight_SI};
    double m_vacuumPermeability{g_vacuumPermeability_SI};
    double m_vacuumPermittibity{g_vacuumPermittivity_SI};
    double m_coloumbsConstant{g_coloumbsConstant_SI};
    double m_universalGravitationalConstant{g_universalGravitationalConstant_SI};

    // Sun properties:
    double m_sun_mass{g_sun_mass_SI};

    // Earth properties:
    double m_earth_mass{g_earth_mass_SI};
    double m_earth_radius{g_earth_radius_SI};
};





#endif //PHYSICSSANDBOX_PHYSICALCONSTANTSHOLDER_HPP
