#pragma once

#include <QRadioButton>

class Marker : public QRadioButton {
Q_OBJECT

public:
    explicit Marker(QWidget* parent) : QRadioButton(parent) {
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        setAttribute(Qt::WA_TransparentForMouseEvents);
    };
    virtual ~Marker() {};
};