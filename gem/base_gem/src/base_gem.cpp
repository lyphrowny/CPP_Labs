#include <QPushButton>
#include <QPainter>
#include <QRandomGenerator>
#include <QGridLayout>

#include "../hdr/base_gem.h"
#include "../../swap/hdr/swap.h"
#include "../../bomb/hdr/bomb.h"
#include "../../recolor/hdr/recolor.h"

void BaseGem::paintEvent(QPaintEvent* e) {
    QPushButton::paintEvent(e);
    QColor background = isDown() ? this->_color->darker(125) : *this->_color;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.translate(width() / 2., height() / 2.);

    painter.setPen(QPen(QColor("black"), 2));
    painter.setBrush(QBrush(background));
    auto rect = QRect(-width() / 2, -height() / 2, width(), height());
    painter.drawRect(rect);

    // printing text
    QFont font = painter.font();
    font.setPixelSize(_minSize);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, tileText);
}

BaseGem* BaseGem::createRandomGem(QWidget* parent) {
    auto choice = QRandomGenerator::global()->generate() % randFrom;

    // TODO place probabilities in one place, i.e. in the class itself?
    //  (how to check whether their sum is 100 or how to choose between them, then?)
    auto probSwap = 90, probBomb = 5, probRecolor = 5;
    if (choice < probSwap)
        return new SwapGem(parent);
    else if (choice < probSwap + probBomb)
        return new BombGem(parent);
    return new RecolorGem(parent);
}

BaseGem* BaseGem::createBonus(QWidget* parent) {
    auto choice = QRandomGenerator::global()->generate() % randFrom;

    auto probBomb = 7, probRecolor = 7;
    if (choice < probBomb)
        return new BombGem(parent);
    else if (choice > randFrom - probRecolor)
        return new RecolorGem(parent);
    return nullptr;
}
