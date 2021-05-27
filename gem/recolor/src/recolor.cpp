#include <QGridLayout>
#include <QRandomGenerator>
#include <QDebug>

#include "../hdr/recolor.h"
#include "../../../tile/hdr/tile.h"


void RecolorGem::action() {
    if (!isBonus) {
        qDebug() << "swap action in recolor";
        return SwapGem::action();
    }
    if (this->parentWidget() != nullptr && this->parentWidget()->parentWidget() != nullptr) {
        qDebug() << "recolor action";
        auto* parent = qobject_cast<QGridLayout*>(this->parentWidget()->parentWidget()->layout());

        if (previouslyPressed != nullptr) {
            previouslyPressed->untoggle();
            previouslyPressed = nullptr;
        }

        int r, c;
        Tile* tile;
        QLayoutItem* item;

        for (int i = 0; i < maxRecolor; i++) {
            item = nullptr;
            do {
                r = QRandomGenerator::global()->bounded(0, parent->rowCount());
                c = QRandomGenerator::global()->bounded(0, parent->columnCount());
            } while (abs(r - this->_row) + abs(c - this->_col) <= 1 &&
                     (item = parent->itemAtPosition(r, c)) != nullptr);
            if (!item)
                item = parent->itemAtPosition(r, c);

            qDebug() << item->widget() << r << c;
            tile = qobject_cast<Tile*>(item->widget());
            tile->setColor(*_color);
            tile->repaint();
        }
        // no longer bonus
        if (++countUses >= maxUses) {
            isBonus = false;
            removeText();
            repaint();
        }
        emit untoggle();
    }
}
