#include "../hdr/tile.h"

Tile::Tile(QWidget* parent) : QWidget(parent) {
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);

    marker = new Marker(nullptr);
    gem = BaseGem::createRandomGem(this);
    addNewGem();
}

void Tile::addNewGem() {
    marker->setParent(gem);

    connect(gem, SIGNAL(clicked()), marker, SLOT(toggle()));
    connect(gem, SIGNAL(untoggle()), marker, SLOT(toggle()));
    connect(gem, SIGNAL(clicked()), this, SLOT(_gemClicked()));

    marker->setChecked(false);
}

void Tile::removeGem() {
    // softHide here is because renew called when the tile is hidden
    // if the tile is hidden, it's inactive, however can a hidden tile act?
    // I doubt that
    gem->softHide();
    gem->setParent(nullptr);
}

void Tile::renew() {
    removeGem();
    gem = BaseGem::createRandomGem(this);
    addNewGem();
    show();
}

void Tile::renewBonus() {
    BaseGem* tmp = BaseGem::createBonus(this);
    if (tmp == nullptr)
        return;
    qDebug() << "bonus not null";
    removeGem();

    gem = tmp;
    addNewGem();
    // for the reason yet unknown, the gem is hidden
    // however the same is not true for the basic gem (in renew)
    gem->show();
    show();
}

bool Tile::operator==(const Tile &tile) const {
    return !isHidden() && !tile.isHidden() && *gem == *tile.gem;
}
