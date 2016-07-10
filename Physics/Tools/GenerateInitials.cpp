#include "GenerateInitials.hpp"

std::vector<Vector3<double>> uniformRandomSpherePositions(double r_max, unsigned int N)
{
    std::default_random_engine rng;
    std::uniform_real_distribution<double> u(0, 1);
    std::uniform_real_distribution<double> costheta(-1, 1);
    std::uniform_real_distribution<double> phi(0, 2*M_PI);
    auto theta = [&rng, &costheta]() {return costheta(rng);};
    auto r = [&rng, &u, &r_max]() {return r_max*cbrt(u(rng));};
    std::vector<Vector3<double>> coordinates(N);
    for (auto  &pos : coordinates) {
        pos = Vector3<double>(r() * sin(theta()) * cos(phi(rng)),
            r() * sin(theta()) * sin(phi(rng)),
            r() * cos(theta()));
    }

    return coordinates;
}