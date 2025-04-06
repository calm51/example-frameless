#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QPair>


#include "./maintitlebarbutton.h"


#if defined Q_OS_ANDROID
#include "QtAndroid"
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroidExtras>

#include <qtandroidcls/qtandroidcls.h>
#endif

#include "frameless/__frameless_include__.h"
#include "frameless/frameless.h"
#include "frameless/titlebar/titlebarlikeandroid.h"
#include "frameless/titlebar/titlebarlikewindows10.h"
#include "frameless/utils.h"


#include <qtturnblack/qtturnblack.h>
#include <QDebug>
#include <QStyleFactory>


void loadthemesetting() {
    Frameless::__global__ &fg = Frameless::G();
#ifdef Q_OS_ANDROID
    QtAndroidCls *qac = QtAndroidCls::instance();
    if (fg.currentTheme == Frameless::Theme::Light || fg.currentTheme == Frameless::Theme::White) {
        qac->to_statusbar_text_black();
    } else {
        qac->to_statusbar_text_white();
    }
#endif

#ifdef Q_OS_ANDROID
    int _fontsize = 14;
#elif defined Q_OS_WIN
    int _fontsize = 9;
#elif defined Q_OS_LINUX
    int _fontsize = 9;
#endif


    QString _t(R"(
*{font:字体大小pt \"微软雅黑\";outline:0px;}
)");
    _t = _t.replace(QString("字体大小"), QString::number(_fontsize));

#ifdef Q_OS_LINUX
    _t = _t.replace(QString("微软雅黑"), "Ubuntu");
#endif

    Qtturnblack::qtb qtb;
    if (fg.currentTheme == Frameless::Theme::Gray) { // 暗色
        qtb = Qtturnblack::get(Qtturnblack::Color::Gray);
    } else if (fg.currentTheme == Frameless::Theme::Light) {
        qtb = Qtturnblack::get(Qtturnblack::Color::Default);
    }
    _t += qtb.styleSheet;

    qApp->setPalette(qtb.palette);
    qApp->setStyleSheet(_t);
}


int main(int argc, char *argv[]) {
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);
    a.setAttribute(Qt::ApplicationAttribute::AA_UseHighDpiPixmaps);
    a.setQuitOnLastWindowClosed(false);
    a.setStyle("Fusion");
#if defined Q_OS_ANDROID
    QtAndroidCls *qac = QtAndroidCls::instance("ca/calm/framelessdemo/framelessdemo");
#endif
    a.setWindowIcon(QIcon(":/resource/icon/main.ico"));

    Frameless::__global__ &fg = Frameless::G();
    //    fg.theme_config[Frameless::Theme::White].round4 = {28,28,0,0};
    //    fg.theme_config[Frameless::Theme::Light].round4 = {15,15,0,0};
    //    fg.theme_config[Frameless::Theme::Dark].round4 = {0,0,0,0};
    //    fg.theme_config[Frameless::Theme::Gray].round4 = {0,0,0,0};
    fg.swithTheme(Frameless::Theme::White);

    MainWindow w;
    w.setWindowTitle("framelessdemo");
    w.connect(&fg.SIGNAL, &Frameless::__signal__::themeChanged, &w, [&]() { loadthemesetting(); });
    loadthemesetting();
#if defined Q_OS_ANDROID
    w.connect(qac, &QtAndroidCls::statusbarHeightChanged, &w, [=](const qint32 &height) {});
#endif

#ifndef Q_OS_ANDROID
    auto fl_tb = Frameless::template_windows10<Frameless::TitlebarLikeWindows10>(w, 28, 44);
    Maintitlebarbutton *maintitlebarbutton = new Maintitlebarbutton(&w);
    fl_tb.second->w3layout()->addWidget(maintitlebarbutton);
    fl_tb.second->set_title("v1.0");
    fl_tb.second->set_title_enable(false);
#else
    auto fl_tb = Frameless::template_windows10<Frameless::TitlebarLikeAndroid>(w, qac->get_statusbar_qwiget_height());
    w.show();
    // W_startscreen *w_ss = new W_startscreen(&w);
    // w_ss->showFullScreen();
    QTimer::singleShot(50, qac, [&]() {
        qac->to_statusbar_text_white();
        QtAndroid::hideSplashScreen(100);
        // w_ss->exec();
        if (fg.currentTheme == Frameless::Theme::Light || fg.currentTheme == Frameless::Theme::White) {
            qac->to_statusbar_text_black();
        } else {
            qac->to_statusbar_text_white();
        }
    });
    qac->up_statusbar_height();
#endif
    a.installNativeEventFilter(fl_tb.first);


    //    Frameless::Frameless fl(&w);
    //    a.installNativeEventFilter(&fl);
    //#ifndef Q_OS_ANDROID
    //    fl.titlebar_MinimumHeight = 28; // 24-40 28-44 28-46
    //    fl.init(w); fl.loadthemesetting(); w.fl = &fl;
    //    Frameless::TitlebarLikeWindows10 titlebar(&fl,44,&w);
    //    titlebar.loadthemesetting();
    //    fl.set_titlebar(titlebar);
    //    fl.titlebar_widget->setWindowIcon(w.windowIcon());
    //    Maintitlebarbutton* maintitlebarbutton = new Maintitlebarbutton(&w);
    //    titlebar.w3layout()->addWidget(maintitlebarbutton);
    //    titlebar.set_title("v1.0");
    //    titlebar.set_title_enable(false);
    //#else
    //    fl.titlebar_MinimumHeight = qac->get_statusbar_qwiget_height();
    //    fl.init(w); fl.loadthemesetting(); w.fl = &fl;
    //    Frameless::TitlebarLikeAndroid titlebar(&fl,&w);
    //    titlebar.loadthemesetting();
    //    titlebar.setFixedHeight(fl.titlebar_MinimumHeight);
    //    fl.set_titlebar(titlebar);
    //    w.show();
    //    // W_startscreen *w_ss = new W_startscreen(&w);
    //    // w_ss->showFullScreen();
    //    QTimer::singleShot(50,qac,[&](){
    //        qac->to_statusbar_text_white();
    //        QtAndroid::hideSplashScreen(100);
    //        // w_ss->exec();
    //        if (fg.currentTheme==Frameless::Theme::Light){
    //            qac->to_statusbar_text_black();
    //        }else{
    //            qac->to_statusbar_text_white();
    //        }
    //    });
    //    qac->up_statusbar_height();
    //#endif


    w.show();
#ifndef Q_OS_ANDROID
    // w.trayicon->show();
#else
#endif

    return a.exec();
}
