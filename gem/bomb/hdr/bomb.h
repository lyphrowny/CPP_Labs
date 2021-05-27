#pragma once

#include "../../base_gem/hdr/base_gem.h"

class BombGem : public BaseGem {
Q_OBJECT

private:
    const int maxUses = 1;
    int countUses = 0;
    bool isBonus = true;

    const QString text = "B";
    const QColor* _color = new QColor(178, 22, 22);

public:
    BombGem(QWidget* parent) : BaseGem(parent) {
        tileText = text;
        BaseGem::_color = const_cast<QColor*>(_color);
    };

    // in case Recolor chooses Bomb as its target, ignore
    void setColor(const QColor &color) override {};

    void setRandomColor() override {};

    bool action() override;

    void beforeHidden() override { action(); };

    bool operator==(const BaseGem &gem) const override { return false; };
};