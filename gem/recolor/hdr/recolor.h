#pragma once

#include "../../swap/hdr/swap.h"

class RecolorGem : public SwapGem {
Q_OBJECT

private:
    const int maxUses = 1;
    int countUses = 0;
    bool isBonus = true;

    const int maxRecolor = 2;
    const QString text = "R";

    void removeText() { tileText = ""; };

public:
    RecolorGem(QWidget* parent) : SwapGem(parent) { tileText = text; };

    bool action() override;

    void beforeHidden() override { if (isBonus) action(); else SwapGem::beforeHidden(); };
};