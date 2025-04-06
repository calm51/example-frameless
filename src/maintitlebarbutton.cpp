#include "maintitlebarbutton.h"
#include "ui_maintitlebarbutton.h"

Maintitlebarbutton::Maintitlebarbutton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Maintitlebarbutton) {
    ui->setupUi(this);

    this->setStyleSheet(R"(
QToolButton {
    background-color: transparent;
    border: none;
}

QToolButton:hover {
    background-color: rgba(0, 0, 255, 50);
}

QToolButton:pressed {
    background-color: rgba(0, 0, 255, 100);
}

)");
}

Maintitlebarbutton::~Maintitlebarbutton() {
    delete ui;
}
