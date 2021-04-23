#include <cmath>
#include <iomanip>

#include "teacher.h"
#include "../exceptions/no_real_roots_exc.h"

void Teacher::publish() {
    this->updateTable();
    int first = 14, second = 24, third = 8;
    std::cout << std::left << std::setw(first) << "Name" << std::setw(second) << "List of tasks"
              << std::setw(third) << "Solved " << std::endl;
    for (const auto &pair : this->perf_table) {
        std::cout << std::left << std::setw(first) << pair.first.first << std::setw(second) << pair.first.second
        << std::setw(third) << pair.second << std::endl;
    }
    std::cout << std::endl;
}

void Teacher::push(const Solution &solution) {
    this->queue.push(solution);
}

bool Teacher::check(const std::array<double, 3> &coeffs, const std::array<double, 2> &roots, double epsilon = 0.001) {
    const auto[a, b, c] = coeffs;
    const auto[x0, x1] = roots;
    return std::abs((x0 + x1) * a - (-b)) < epsilon && std::abs(x0 * x1 * a - c) < epsilon;
}

void Teacher::updateTable() {
    while (!this->queue.empty()) {
        const auto[name, filename, coeffs, roots] = queue.front();
        queue.pop();
        this->perf_table[std::make_pair(name, filename.substr(filename.rfind('/') + 1))] += check(coeffs, roots);
    }
}