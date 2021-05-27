#include <QDebug>
#include <QGridLayout>

#include "../hdr/swap.h"

SwapGem* SwapGem::previouslyPressed = nullptr;

bool SwapGem::action() {
    if (previouslyPressed == nullptr) {
        qDebug() << "swap action, act1" << this;
        previouslyPressed = this;
    }
    else if (previouslyPressed == this) {
        qDebug() << "swap action, duplicate";
        previouslyPressed = nullptr;
    }
    else if (this->parentWidget() != nullptr && this->parentWidget()->parentWidget() != nullptr) {
        qDebug() << "swap action, act 2";
        // let's imagine, the parent cannot be anyone other than QGridLayout
        auto* parent = qobject_cast<QGridLayout*>(this->parentWidget()->parentWidget()->layout());
        if (parent == nullptr)
            return false;

        // untoggle in either case
        emit this->untoggle();

        qDebug() << getPos();
        if (abs(this->_row - previouslyPressed->_row) + abs(this->_col - previouslyPressed->_col) == 1) {
            QColor* tmp = this->_color;
            this->_color = previouslyPressed->_color;
            previouslyPressed->_color = tmp;
            // for the changed colors to be repainted
            this->repaint();
            previouslyPressed->repaint();

            // for the radio button to be untoggled
            emit previouslyPressed->untoggle();
            previouslyPressed = nullptr;
        }
    }
    // no Shift is needed;
    return false;
}