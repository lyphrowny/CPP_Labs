#include <cmath>
#include <regex>
#include <fstream>
#include <iostream>

#include "base_pupil.h"
#include "../exceptions/no_teacher_assigned_exc.h"
#include "../exceptions/no_real_roots_exc.h"


std::array<double, 3> BasePupil::parseTask(const std::string &task) {
    std::array<double, 3> coeffs = {};
    std::regex e(R"(\b(\d+\.\d+|\d+)\b)");
    auto begin = std::sregex_iterator(task.begin(), task.end(), e);
    std::sregex_iterator end;

    auto it = begin;
    for (int i = 0; i < coeffs.size(); i++, it++) {
        if (it != end)
            coeffs[i] = std::stof(it->str());
    }
    return coeffs;
}

const std::array<double, 2> BasePupil::solve(const std::array<double, 3> &coeffs) noexcept(false) {
    const auto[a, b, c] = coeffs;
    double d = sqrt(b * b  - 4 * a * c);
    if (d >= 0)
        return {(-b - d) / (2 * a), (-b + d) / (2 * a)};
    else
        throw NoRealRootsException(coeffs);
}

void BasePupil::solveTask(const std::string &filename) {
    std::fstream file(filename, std::ios::in);

    if (!file)
        std::cout << " file wasn't opened..." << std::endl;
    else {
        std::string line;
        while (std::getline(file, line)) {
            auto coeffs = this->parseTask(line);
            auto roots = this->solve(coeffs);
            this->send(filename, coeffs, this->solve(coeffs));
        }
    }
    file.close();
}

void BasePupil::send(const std::string& filename, const std::array<double, 3> &coeffs, const std::array<double, 2> &roots) {
    if (this->teacher != nullptr)
        this->teacher->push({this->name, filename, coeffs, roots});
    else
        throw NoTeacherAssigned();
}