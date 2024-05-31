#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "frameless/frameless.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Frameless::Frameless *fl = nullptr;
    bool nativeEvent(const QByteArray & eventType, void * message, long * result);
    bool eventFilter(QObject *o, QEvent *e);
    void showEvent(QShowEvent *event);
    void loadthemesetting();

    void closeEvent(QCloseEvent*event);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
