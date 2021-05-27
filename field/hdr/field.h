#pragma once

#include <QGridLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QWidgetData>

#include "../../tile/hdr/tile.h"

class Field : public QGridLayout {
Q_OBJECT

signals:

    void tileAdded(Tile*, int, int);

public slots:

    void tilePressed(Tile* pressedTile);

private:
    void shiftTiles(QVector<QPoint> &bonuses);

    void genBonuses(QVector<QPoint> &bonuses);

    void renewBonusTile(int row, int col);

    void checkIsHidden(const QString &str);

    void renew(bool shiftNeeded);

    void renewTile(int row, int col);

    bool isAllowed(int row, int col);

    bool checkEquality(int row, int col, int row_, int col_);

    QPoint searchLine(int row, int col, int dx, int dy);

    bool findSeqs();

    void genBonus(int row, int col);

    void addTile(Tile* tile, int row, int col);

    void addNewTile(Tile* tile, int row, int col);

    void swapTiles(int row, int col, int row_, int col_);

public:
    Field(QWidget* parent, int rows = 10, int cols = 10);

    Tile* getRandomTile(int row, int col, int r_low = 0, int r_up = -1, int c_low = 0, int c_up = -1);

    QPoint getRandomPos(int row, int col, int r_low, int r_up, int c_low, int c_up);
};