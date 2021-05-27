#include <QWidget>

#include "../hdr/field.h"
#include "../exceptions/outOfBounds.h"


Field::Field(QWidget* parent, int rows, int cols) : QGridLayout(parent) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            addNewTile(new Tile(nullptr), i, j);
            setSpacing(0);
        }
    }
    setSizeConstraint(SizeConstraint::SetFixedSize);

    renew();
}

void Field::renew() {
    do {
        shiftTiles();
        genBonuses();
    } while (findSeqs());
}

void Field::tilePressed(Tile* pressedTile) {
    pressedTile->action();
    renew();
}

void Field::addTile(Tile* tile, int row, int col) {
    addWidget(tile, row, col);
    emit tileAdded(tile, row, col);
}

void Field::addNewTile(Tile* tile, int row, int col) {
    connect(tile, &Tile::gemClicked, this, [this, tile]() { tilePressed(tile); });
    connect(this, &Field::tileAdded, tile, &Tile::setPos);
    addTile(tile, row, col);
}

void Field::genBonus(int row, int col) {
    // TODO take from Tile, which, presumably, takes from Gem
    const int genBorderRadius = 3;
    int r_low = qMax(row - genBorderRadius, 0), r_up = qMin(row + genBorderRadius, rowCount());
    int c_low = qMax(col - genBorderRadius, 0), c_up = qMin(col + genBorderRadius, columnCount());
    QPoint pos = getRandomPos(row, col, r_low, r_up, c_low, c_up);
    renewBonusTile(pos.x(), pos.y());
}

void Field::swapTiles(int row, int col, int row_, int col_) {
    qDebug() << "swapTiles" << row << col << row_ << col_;
    auto* tile = getTile(row, col), * tile_ = getTile(row_, col_);

    removeWidget(tile);
    removeWidget(tile_);
    addTile(tile, row_, col_);
    addTile(tile_, row, col);
}

Tile* Field::getRandomTile(int row, int col, int r_low, int r_up, int c_low, int c_up) {
    QPoint pos = getRandomPos(row, col, r_low, r_up, c_low, c_up);
    return getTile(pos.x(), pos.y());
}

QPoint Field::getRandomPos(int row, int col, int r_low, int r_up, int c_low, int c_up) {
    r_up = r_up == -1 ? rowCount() : r_up;
    c_up = c_up == -1 ? columnCount() : c_up;
    int r, c;
    do {
        r = QRandomGenerator::global()->bounded(r_low, r_up);
        c = QRandomGenerator::global()->bounded(c_low, c_up);
    } while (abs(r - row) + abs(c - col) <= 1);
    qDebug() << "random tile: " << r << c;
    return {r, c};
}

void Field::renewTile(int row, int col) {
    auto* tile = getTile(row, col);
    tile->renew();
    emit tileAdded(tile, row, col);
}

void Field::renewBonusTile(int row, int col) {
    auto* tile = getTile(row, col);
    tile->renewBonus();
    emit tileAdded(tile, row, col);
}

void Field::checkIsHidden(const QString &str) {
    for (int i = 0; i < columnCount(); i++)
        for (int j = 0; j < rowCount(); j++)
            if (isHidden(j, i))
                qDebug() << str << j << i << "is hidden";
}

void Field::shiftTiles() {
    qDebug() << "";
    checkIsHidden("before");
    for (int j = 0; j < columnCount(); j++) {
        int swap_pos = rowCount() - 1;
        for (int i = rowCount() - 1; i > 0; i--) {
            if (isHidden(i, j)) {
                if (!isHidden(i - 1, j)) {
                    *bonuses << QPoint(i, j);
                    swapTiles(swap_pos--, j, i - 1, j);
                }
            } else
                swap_pos--;
        }
        int row = 0;
        while (row < rowCount() && isHidden(row, j))
            renewTile(row++, j);
    }
    checkIsHidden("end of shift");
}

void Field::genBonuses() {
    for (auto &pos : *bonuses)
        genBonus(pos.x(), pos.y());
    bonuses->clear();
}

QWidget* Field::getWidget(int row, int col) {
    try {
        if (isAllowed(row, col))
            return itemAtPosition(row, col)->widget();
        throw outOfBounds({row, col}, {0, rowCount()}, {0, columnCount()});
    } catch (const outOfBounds &e) {
        qCritical() << e.what();
        exit(1);
    }
}

Tile* Field::getTile(int row, int col) {
    return qobject_cast<Tile*>(getWidget(row, col));
}

bool Field::isHidden(int row, int col) {
    return getWidget(row, col)->isHidden();
}

bool Field::isAllowed(int row, int col) {
    return row >= 0 && row < rowCount() && col >= 0 && col < columnCount();
}

bool Field::checkEquality(int row, int col, int row_, int col_) {
    return *getTile(row, col) == *getTile(row_, col_);
}

QPoint Field::searchLine(int row, int col, int dy, int dx) {
    QPoint end(row, col);

    while (row < rowCount() && col < columnCount()) {
        int row_ = row + dy, col_ = col + dx;
        if (isAllowed(row_, col_) && checkEquality(row, col, row_, col_))
            end.setX(row_), end.setY(col_);
        else
            break;
        row = row_, col = col_;
    }
    return end;
}

bool Field::findSeqs() {
    // search from left to right, from up to bottom
    int d_x = 0, d_y = 1;
    QVector<QPoint> points;
    QPoint hpoint, vpoint;
    for (int i = 0; i < rowCount(); i++) {
        for (int j = 0; j < columnCount(); j++) {
            // h (cols)
            hpoint = searchLine(i, j, d_x, d_y);
            // v (rows)
            vpoint = searchLine(i, j, d_y, d_x);
            if (hpoint.y() - j >= 2)
                for (int col = j; col <= hpoint.y(); col++)
                    points << QPoint(i, col);
            if (vpoint.x() - i >= 2)
                for (int row = i; row <= vpoint.x(); row++)
                    points << QPoint(row, j);
        }
    }
    for (auto &point : points)
        getWidget(point.x(), point.y())->hide();

    return !points.isEmpty();
}