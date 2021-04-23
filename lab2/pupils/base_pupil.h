#ifndef BASE_PUPIL_H
#define BASE_PUPIL_H

#include <array>

#include "../solution/solution.h"

class Teacher;

#include "../teacher/teacher.h"

class BasePupil {
protected:
    Teacher* teacher = nullptr;
    std::string name;

public:

    explicit BasePupil(const std::string &name) { this->name = name; }

    explicit BasePupil(const char* name) { this->name = name; }

    void assignTeacher(Teacher* tchr) { this->teacher = tchr; };

    void solveTask(const std::string &filename);

    static std::array<double, 3> parseTask(const std::string &task);

    virtual const std::array<double, 2> solve(const std::array<double, 3> &coeffs);

    void send(const std::string &filename, const std::array<double, 3> &coeffs, const std::array<double, 2> &roots);

    virtual ~BasePupil() = default;
};

#endif //BASE_PUPIL_H
