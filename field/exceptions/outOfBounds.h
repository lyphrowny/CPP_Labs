#pragma once

#include <QException>

class outOfBounds : public QException {
private:
    std::string msg;
public:
    outOfBounds(const QPoint pos, const QPoint rowBound, const QPoint colBound) {
        msg = QString("trying to access member at (%1, %2) while the bounds are: row [%3, %4), col [%5, %6)").arg(
                pos.x()).arg(pos.y()).arg(rowBound.x()).arg(rowBound.y()).arg(colBound.x()).arg(
                colBound.y()).toStdString();
    };

    const char* what() const noexcept override { return msg.c_str(); };

    void raise() const override { throw *this; };

    outOfBounds* clone() const override { return new outOfBounds(*this); };
};