#ifndef CPP_SOLUTION_H
#define CPP_SOLUTION_H

#include <string>

#include <array>
#include <utility>

class Solution {
public:
    const std::string name;
    const std::string filename;
    const std::array<double, 3> coeffs;
    const std::array<double, 2> roots;

    Solution(std::string  name, std::string  filename, const std::array<double, 3> &coeffs, const std::array<double, 2> &roots) :
            name(std::move(name)),
            filename(std::move(filename)),
            coeffs(coeffs),
            roots(roots) {};
};


#endif //CPP_SOLUTION_H
