#pragma once

#include <QWidget>
#include <QDebug>

#include "../../gem/base_gem/hdr/base_gem.h"
#include "../../marker/hdr/marker.h"

class Tile : public QWidget {
Q_OBJECT

signals:

    void gemClicked();

public slots:

    void _gemClicked() { qDebug() << "tile clicked"; emit gemClicked(); };

private:
    Marker* marker = nullptr;
    BaseGem* gem = nullptr;

    QSize sizeHint() const override { return gem->size(); };

    QSize minimumSizeHint() const override { return gem->size(); };

    void addNewGem();

    void removeGem();

    void hideEvent(QHideEvent* e) override {
        QWidget::hideEvent(e);
        gem->strictHide();
    };

public:
    explicit Tile(QWidget* parent);

    void renew();

    void renewBonus();

    void setPos(Tile* tile, int row, int col) { if (tile == this) gem->setPos(row, col); };

    void action() { gem->action(); };

    void setRandomColor() { gem->setRandomColor(); };

    void setColor(const QColor &color) { gem->setColor(color); };

    const int getRadius() const { return gem->getRadius(); };

    const QColor* getColor() const { return gem->getColor(); };

    QPoint getPos() const { return gem->getPos(); };

    bool operator==(const Tile &tile) const;
};