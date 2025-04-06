#ifndef MAINTITLEBARBUTTON_H
#define MAINTITLEBARBUTTON_H

#include <QWidget>

namespace Ui {
class Maintitlebarbutton;
}

class Maintitlebarbutton : public QWidget {
    Q_OBJECT

  public:
    explicit Maintitlebarbutton(QWidget *parent = nullptr);
    ~Maintitlebarbutton();

  private:
    Ui::Maintitlebarbutton *ui;
};

#endif // MAINTITLEBARBUTTON_H
