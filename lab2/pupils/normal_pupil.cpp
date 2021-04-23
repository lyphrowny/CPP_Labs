#include <cstdlib>

#include "normal_pupil.h"


const std::array<double, 2> NormalPupil::solve(const std::array<double, 3> &coeffs) {
    if (rand() % 2)
        return BasePupil::solve(coeffs);
    return {2.718281828459045, 3.1415926535897932384626};
};