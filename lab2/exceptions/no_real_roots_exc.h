#ifndef NO_REAL_ROOTS_EXC_H
#define NO_REAL_ROOTS_EXC_H

#include <exception>
#include <array>
#include <sstream>
#include <string>
#include <iostream>

class NoRealRootsException : public std::exception {
private:
    std::array<double, 3> coeffs = {0, 0, 0};
    std::stringstream str_coeffs = {};
    const char* p = nullptr;
public:
    NoRealRootsException(const double a, const double b, const double c) { this->coeffs = {a, b, c}; };

    NoRealRootsException(const std::array<double, 3>& coeffs) { this->coeffs = coeffs; };

    const char* what() const noexcept override {
        return "the equation with these coefficients doesn't have real roots";
    };

    const char* get_coeffs() noexcept {
        str_coeffs.precision(4);
        for (auto c: this->coeffs)
            str_coeffs << c << " ";
        p = str_coeffs.str().c_str();
        return p;
    };
};

#endif // NO_REAL_ROOTS_EXC_H