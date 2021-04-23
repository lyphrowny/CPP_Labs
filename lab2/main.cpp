#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include "./teacher/teacher.h"
#include "./pupils/bad_pupil.h"
#include "./pupils/normal_pupil.h"
#include "./pupils/good_pupil.h"

int main() {
    auto teacher = new Teacher();
    std::vector<BasePupil*> pupils = {};
    std::vector<std::string> names = {"Vasya", "Petya", "Masha", "Dasha", "Evlapmiy", "Igor", "Tanya"};
    std::vector<std::string> filenames = {
            "/home/epicider/CC++/CLionProjects/Cpp/lab2/equations/int_coeffs.txt",
            "/home/epicider/CC++/CLionProjects/Cpp/lab2/equations/float_coeffs.txt"};

    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<int> distr(1, 100);
    auto rand = std::bind(distr, gen);

    for (int i = 0; i < rand() % 20; i++) {
        BasePupil* pupil;
        auto name = names.at(rand() % names.size()) + "_" + std::to_string(i);
        switch (rand() % 3) {
            case 0:
                pupil = new BadPupil(name);
                break;
            case 1:
                pupil = new NormalPupil(name);
                break;
            case 2:
                pupil = new GoodPupil(name);
                break;
        }
        pupils.push_back(pupil);
        pupil->assignTeacher(teacher);
        auto filename = filenames.at(rand() % filenames.size());
        pupil->solveTask(filename);
        teacher->publish();
    }

    for (auto &pupil : pupils)
        delete pupil;
    delete teacher;

    return 0;
}