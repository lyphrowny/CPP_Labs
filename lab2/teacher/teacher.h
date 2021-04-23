#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <queue>
#include <map>

#include "../pupils/base_pupil.h"
#include "../solution/solution.h"

class Teacher {
private:
    std::queue<Solution> queue = {};
    std::map<std::pair<std::string, std::string>, double> perf_table = {};
public:
    void push(const Solution& solution);

    void updateTable();

    void publish();

    static bool check(const std::array<double, 3> &coeffs, const std::array<double, 2> &roots, double epsilon);
};

#endif // TEACHER_H