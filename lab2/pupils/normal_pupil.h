#ifndef NORMAL_PUPIL_H
#define NORMAL_PUPIL_H

#include "base_pupil.h"

class NormalPupil: public BasePupil{
public:
    using BasePupil::BasePupil;
    const std::array<double, 2>solve(const std::array<double, 3>& coeffs) override;
};

#endif // NORMAL_PUPIL_H
