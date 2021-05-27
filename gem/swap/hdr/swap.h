#pragma once

#include "../../base_gem/hdr/base_gem.h"

class SwapGem : public BaseGem {
Q_OBJECT

protected:
    // cannot be any other type of gem, because action is dispatched class-wise
    static SwapGem* previouslyPressed;

public:
    SwapGem(QWidget* parent) : BaseGem(parent) {};

    bool action() override;
    void softHide() override { BaseGem::softHide(); previouslyPressed = nullptr; };
    void beforeHidden() override { previouslyPressed = nullptr; };
};

