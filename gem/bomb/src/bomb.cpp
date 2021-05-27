#include <QGridLayout>
#include <QVector>
#include <QDebug>

#include "../hdr/bomb.h"

bool BombGem::action() {
    bool needShift = false;
    if (!isBonus)
        return needShift;
    if (this->parentWidget() != nullptr && this->parentWidget()->parentWidget() != nullptr) {
        if (++countUses >= maxUses)
            isBonus = false;
        qDebug() << "bomb action" << countUses;
        auto* parent = qobject_cast<QGridLayout*>(this->parentWidget()->parentWidget()->layout());
        int cols = parent->columnCount() - 1, rows = parent->rowCount() - 1;
        QVector<QLayoutItem*> to_delete = {parent->itemAtPosition(this->_row, qMin(this->_col + 1, cols)), // right
                                           parent->itemAtPosition(this->_row, qMax(0, this->_col - 1)), // left
                                           parent->itemAtPosition(qMin(this->_row + 1, rows), this->_col), // bottom
                                           parent->itemAtPosition(qMax(0, this->_row - 1), this->_col), // top
                                           parent->itemAtPosition(this->_row, this->_col)}; // current
        for (auto item : to_delete)
            if (!item->widget()->isHidden()) {
                needShift = true;
                item->widget()->hide();
            }
    }
    return needShift;
}
