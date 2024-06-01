#include "dialog1.h"
#include "ui_dialog1.h"

#if defined Q_OS_ANDROID
#include "QtAndroid"
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

#include <qtandroidcls/qtandroidcls.h>
#endif


Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    QtAndroidCls *qac = QtAndroidCls::instance();
    connect(qac,&QtAndroidCls::statusbarHeightChanged, this,[=](const qint32 &height){
        if (fl && height > 4){ fl->titlebar_MinimumHeight = height;if (fl->titlebar_widget){ fl->titlebar_widget->setFixedHeight(fl->titlebar_MinimumHeight);}fl->load();}
    });
#endif

    Frameless::__global__ & fg = Frameless::G();
    connect(&fg.SIGNAL,&Frameless::__signal__::themeChanged,this,[=](){
        loadthemesetting();
    });

}


Dialog1::~Dialog1()
{
    delete ui;
}

bool Dialog1::eventFilter(QObject *o, QEvent *e){
    return QDialog::eventFilter(o,e);
}
bool Dialog1::nativeEvent(const QByteArray &eventType, void *message, long *result){
    if (fl){ return fl->nativeEvent(eventType, message, result); }
    return false;
}
void Dialog1::showEvent(QShowEvent *event){
    if (this->parentWidget()){
        const QRect &parentGeometry = this->parentWidget()->geometry();
        const QRect &childGeometry = this->geometry();
        const int &x = parentGeometry.x() + (parentGeometry.width() - childGeometry.width()) / 2;
        const int & y = parentGeometry.y() + (parentGeometry.height() - childGeometry.height()) / 2;
        this->move(x, y);
    }
    return QDialog::showEvent(event);
}
void Dialog1::loadthemesetting(){
    Frameless::__global__ & fg = Frameless::G();
    if (fg.currentTheme==Frameless::Theme::Light){
        ui->widget->setStyleSheet(R"(
.QWidget,.QScrollArea{background:transparent;}

)");
    }else if (fg.currentTheme==Frameless::Theme::Dark){
        ui->widget->setStyleSheet(QString(R"(
.QWidget,.QScrollArea{background:transparent;}

)"));
    }

}
void Dialog1::accept_(){
    //    save();
    this->accept();
}
void Dialog1::reject_(){
    this->reject();
}
