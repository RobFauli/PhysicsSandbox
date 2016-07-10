#ifndef PHYSICALCONSTANTS_HPP
#define PHYSICALCONSTANTS_HPP

//! This header holds physical constants in SI units.

#include <cmath>
#include <map>

//constexpr double M_PI = 3.14159265359; // M_PI not a part of standard C++wextern double speedOfLight = 2.99792458e8; //!< m/s
constexpr double g_speedOfLight_SI = 299792458; //!< m/s
constexpr double g_vacuumPermeability_SI = 4*M_PI*10e-7; //!< V*s/(A*m)
constexpr double g_vacuumPermittivity_SI = //!< A^2*s^2*kg^-1*m^-3
        1.0 / (g_vacuumPermeability_SI * g_speedOfLight_SI * g_speedOfLight_SI);

constexpr double g_coloumbsConstant_SI = //!< N*m^2*C^-2 = kg*m^3*C^-2*s^-2
        1.0 / (4 * M_PI * g_vacuumPermittivity_SI);

constexpr double g_universalGravitationalConstant_SI = 6.67408e-11; //!< m^3*kg^-1*s^-2

constexpr double g_sun_mass_SI = 1.989e30; //!< kg
constexpr double g_earth_mass_SI = 5.972e24; //!< kg
constexpr double g_earth_radius_SI = 6.371e6; //!< m



#endif /* PHYSICALCONSTANTS_HPP */
