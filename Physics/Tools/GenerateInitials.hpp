#ifndef PHYSICSSANDBOX_GENERATEINITIALS_HPP
#define PHYSICSSANDBOX_GENERATEINITIALS_HPP

#include <vector>
#include <random>
#include <cmath>

#include "Vector3.hpp"

std::vector<Vector3<double>> uniformRandomSpherePositions(double r_max, unsigned int N);

#endif //PHYSICSSANDBOX_GENERATEINITIALS_HPP
