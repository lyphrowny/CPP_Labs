#pragma once

#include <QPushButton>
#include <QColor>
#include <QRandomGenerator>

#include <QDebug>

class BaseGem : public QPushButton {
Q_OBJECT

signals:

    void untoggle();

private:
    static const int _minSize = 50;
    static const int randFrom = 100;
    static const int genBorderRadius = 3;
    const QVector<QColor> _colors = {QColorConstants::White, QColorConstants::Gray, QColorConstants::Red,
                                     QColorConstants::Green, QColorConstants::Cyan, QColorConstants::Magenta,
                                     QColorConstants::Yellow};

    void paintEvent(QPaintEvent* e) override;

protected:
    int _row, _col;
    QColor* _color = nullptr;
    QString tileText = "";

public:
    BaseGem(QWidget* parent) : QPushButton(parent) {
        setFixedSize(_minSize, _minSize);
        setRandomColor();
    }

    static BaseGem* createRandomGem(QWidget* parent = nullptr);

    static BaseGem* createBonus(QWidget* parent = nullptr);

    virtual void softHide() { QPushButton::hide(); };

    virtual void strictHide() {
        beforeHidden();
        QPushButton::hide();
    };

    // virtual to, for example, ignore in Bomb class
    virtual void setColor(const QColor &color) { *_color = color; };

    virtual void setRandomColor() {
        _color = const_cast<QColor*>(&_colors[QRandomGenerator::global()->generate() % _colors.size()]);
    };

    void setPos(int row, int col) { _row = row, _col = col; };

    const int getRadius() const { return genBorderRadius; };

    const QColor* getColor() const { return _color; };

    QPoint getPos() { return QPoint(_row, _col); };

    virtual void action() = 0;

    virtual void beforeHidden() = 0;

    virtual bool operator==(const BaseGem &gem) const { return *getColor() == *gem.getColor(); };

    virtual ~BaseGem() = default;
};