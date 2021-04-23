#ifndef CPP_NO_TEACHER_ASSIGNED_EXC_H
#define CPP_NO_TEACHER_ASSIGNED_EXC_H

#include <exception>

#include "../pupils/base_pupil.h"

class NoTeacherAssigned : public std::exception {
private:
//    const BasePupil* pupil = nullptr;
//    const char* p = nullptr;
public:

//    explicit NoTeacherAssigned(const BasePupil* pupil) { this->pupil = pupil; };

    const char* what() const noexcept override {
        return "the pupil doesn't have a teacher";
    };
};

#endif //CPP_NO_TEACHER_ASSIGNED_EXC_H
