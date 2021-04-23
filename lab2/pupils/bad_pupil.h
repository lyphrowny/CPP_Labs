#ifndef BAD_PUPIL_H
#define BAD_PUPIL_H

#include "base_pupil.h"

class BadPupil: public BasePupil {
public:
    using BasePupil::BasePupil;
    const std::array<double, 2> solve(const std::array<double, 3> &coeffs) override { return {0, 0};};
};

#endif // BAD_PUPIL_H
