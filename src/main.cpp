#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QPair>


#include "./maintitlebarbutton.h"


#if defined Q_OS_ANDROID
#include "QtAndroid"
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

#include <qtandroidcls/qtandroidcls.h>
#endif

#include "frameless/frameless.h"
#include "frameless/__frameless_include__.h"
#include "frameless/titlebar/titlebarlikewindows10.h"
#include "frameless/titlebar/titlebarlikeandroid.h"
#include "frameless/utils.h"

void loadthemesetting(){
    Frameless::__global__ & fg = Frameless::G();
#ifdef Q_OS_ANDROID
    QtAndroidCls *qac = QtAndroidCls::instance();
    if (fg.currentTheme==Frameless::Theme::Light || fg.currentTheme==Frameless::Theme::White){
        qac->to_statusbar_text_black();
    }else{
        qac->to_statusbar_text_white();
    }
#endif

    QPalette p = qApp->palette();
    p.setColor(QPalette::Window, QColor(240,240,240));
    p.setColor(QPalette::Button, QColor(240,240,240));

#ifdef Q_OS_ANDROID
    int _fontsize = 14;
#elif defined Q_OS_WIN
    int _fontsize = 9;
#elif defined Q_OS_LINUX
    int _fontsize = 9;
#endif

    //    ui->widget_8->setStyleSheet(QString("font-size:%1pt;").arg(QString::number(_fontsize)));
    //    ui->pushButton->setStyleSheet(QString(R"(
    //QLabel{
    //    padding:3 2 3 0;
    //    font-size:字体大小pt;
    //    font-weight:bold;
    //}
    //QPushButton{
    //    text-align: left;
    //    padding:3 2 3 0;
    //    font-size:字体大小pt;
    //}
    //)").replace(QString("字体大小"),QString::number(_fontsize)));
    //    ui->pushButton_2->setStyleSheet(ui->pushButton->styleSheet());
    //    ui->label->setStyleSheet(ui->pushButton->styleSheet());

    //    ui->listWidget->setObjectName("listWidget_itemlist");
    QString _t(R"(*{font:字体大小pt \"微软雅黑\";outline:0px;}
QMainWindow{border:1px solid rgb(160,160,160);}
#widget_10_chat{
background:rgb(253,253,253);
border: 1px solid rgb(185,185,185);
}
QListWidget::item#listWidget_setting {
    padding: 3px 0;
}
QListView#listWidget_itemlist{
    selection-background-color:rgba(152,209,255,200);
}
QListView::item:selected#listWidget_itemlist{
    background-color:rgba(152,209,255,200);
}
)");
    _t = _t.replace(QString("字体大小"),QString::number(_fontsize));

#ifdef Q_OS_LINUX
    _t = _t.replace(QString("微软雅黑"),"Ubuntu");
#endif
    if (fg.currentTheme==Frameless::Theme::Gray){ // 暗色
        // ui->line->setFixedHeight(2);
        _t = _t.replace(QString("rgb(253,253,253)"),"rgb(56,56,56)");
        _t = _t.replace(QString("rgba(152,209,255,200)"),"rgba(0,142,255,100)");
        _t = _t.replace(QString("rgb(160,160,160)"),"rgb(37,37,37)");
        _t = _t.replace(QString("rgb(185,185,185)"),"rgba(100,100,100,170)");
        _t = _t.replace(QString("padding: 3px 0;"),R"(padding: 3px 0;color:rgb(255,255,255);)");
        _t += QString(R"(
QMainWindow,QDialog{background:rgb(62,62,62);}
QScrollArea,
#scrollAreaWidgetContents,#scrollAreaWidgetContents_2,#scrollAreaWidgetContents_3,
#scrollAreaWidgetContents_4,#scrollAreaWidgetContents_5,#scrollAreaWidgetContents_6,
#scrollAreaWidgetContents_7,#scrollAreaWidgetContents_8{
    background:rgb(62,62,62);
}
*{color:rgb(230,230,230);}
*:disabled{color:rgb(164,164,164);}
QFrame#line{
    background-color:rgba(124,124,124,160);
    border:1px solid;
    border-top-color:rgba(37,37,37,240);
    border-bottom-color:rgba(0,0,0,0);
    border-left-color:transparent;
    border-right-color:transparent;
}
QProgressBar{
  background-color: rgb(72,72,72);
}

QSpinBox,QDoubleSpinBox,QPushButton,QToolButton,QComboBox {
    background-color: rgb(52,52,52);
    selection-background-color:rgb(0,120,215);
}
QListView,QTreeView,QTextBrowser,QTextEdit{
    selection-background-color:rgb(0,120,215);
    background-color: rgb(72,72,72);
}
QListView:disabled,QTextBrowser:disabled,QTextEdit:disabled{
    selection-background-color:rgb(0,120,215);
    background-color: rgb(65,65,65);
}
QPlainTextEdit{
    selection-background-color:rgb(0,120,215);
    background-color: rgb(65,65,65);
}
QPlainTextEdit:disabled{
    selection-background-color:rgb(0,120,215);
    background-color: rgb(59,59,59);
}
QTreeView::item:selected{
    background-color:rgb(0,120,215);
    color:rgb(255,255,255);
}
QListView::item:selected,QListWidget::item:selected{
    background-color:rgb(0,120,215);
}
QLineEdit{
    color:rgba(207,207,207,255);
    background-color: rgb(52,52,52);
}
QLineEdit:disabled{
    background-color: rgb(58,58,58);
}

QCheckBox{spacing: 2px;}
QCheckBox::indicator{width:15px;height:15px;}
QCheckBox::indicator:unchecked{image:url(:/resource/qss/gray/checkbox_unchecked.png);}
QCheckBox::indicator:checked{image:url(:/resource/qss/gray/checkbox_checked.png);}
QCheckBox::indicator:indeterminate{image:url(:/resource/qss/gray/checkbox_checked.png);}
QToolTip{background-color:rgb(44,44,44);color:rgb(207,207,207);border:1px solid rgb(60,60,60);padding: 0 0 0 0;margin:0 0 0 0;}

QRadioButton::indicator{width:13px;height:13px;}
QRadioButton::indicator::unchecked{image:url(:/resource/qss/gray/radiobutton_unchecked.png);}
QRadioButton::indicator::unchecked:disabled{image:url(:/resource/qss/gray/radiobutton_unchecked_disable.png);}
QRadioButton::indicator::checked{image:url(:/resource/qss/gray/radiobutton_checked.png);}
QRadioButton::indicator::checked:disabled{image:url(:/resource/qss/gray/radiobutton_checked_disable.png);}

QMenu{color:rgb(230,230,230);menu-scrollable: 1;
background-color:rgb(64,64,64);
border:1px solid rgb(37,37,37);padding: 0 0 0 0;margin:0 0 0 0;}

QMenu::item{padding: 3 30 3 24;margin:0 0 0 0;}
QMenu::icon{padding-left:4;}

QLabel > QMenu::item, QLineEdit > QMenu::item, QTextEdit > QMenu::item, QPlainTextEdit > * > QMenu::item, QTextEdit > * > QMenu::item
{padding: 3 30 3 SELF_TextMenu_前方留空;margin:0 0 0 0;}
QLabel > QMenu::item > QMenu::item, QLineEdit > QMenu::item > QMenu::item, QTextEdit > QMenu::item > QMenu::item, QPlainTextEdit > * > QMenu::item > QMenu::item, QTextEdit > * > QMenu::item > QMenu::item
{padding: 3 30 3 24;margin:0 0 0 0;}

QMenu::indicator{width:16px;height:16px;padding: 0 -19 0 4;margin:0 0 0 0;}
QMenu::indicator::checked{image:url(:/resource/qss/gray/checkbox_checked.png);}
QMenu::indicator:unchecked{image:url(:/resource/qss/gray/checkbox_unchecked.png);}
QMenu::right-arrow{image:url(:/resource/qss/gray/right.png);width:10px;height:10px;padding: 0 3 0 0;}
QMenu::item:selected{color:rgb(230,230,230);background: rgb(91,91,91);}
QMenu::separator{height:1px;background:rgb(93,93,93);padding: 0 0 0 0;margin:0 3 0 24;}
QMenu::item#nocheckbox{padding: 3 30 3 8;margin:0 0 0 0;}
QMenu::icon#nocheckbox{padding-left:12;}
QMenu:disabled{color:rgb(154,155,154);}

QGroupBox::indicator::checked{image:url(:/resource/qss/gray/checkbox_checked.png);}
QGroupBox::indicator:unchecked{image:url(:/resource/qss/gray/checkbox_unchecked.png);}
QGroupBox{border:1px solid rgb(37,37,37);margin-top:SELF_组标题偏移;}

)").replace("SELF_TextMenu_前方留空",
    #ifdef Q_OS_WIN
            "24"
    #else
            "4"
    #endif
            ).replace(QString("SELF_组标题偏移"),
              #ifdef Q_OS_WIN
                      QString("7ex")
              #else
                      QString("3.5ex")
              #endif
                      );

        p.setColor(QPalette::Window, QColor(53,53,53));
        p.setColor(QPalette::Button, QColor(53,53,53));
        //    p.setColor(QPalette::Highlight, QColor(142,45,197));
        //    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    }else if(fg.currentTheme==Frameless::Theme::Light){
        _t += QString(R"(

)");
    }
    qApp->setPalette(p);
    qApp->setStyleSheet(_t);

}


int main(int argc, char *argv[]){
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

    Frameless::__global__ & fg = Frameless::G();
    //    fg.theme_config[Frameless::Theme::White].round4 = {28,28,0,0};
    //    fg.theme_config[Frameless::Theme::Light].round4 = {15,15,0,0};
    //    fg.theme_config[Frameless::Theme::Dark].round4 = {0,0,0,0};
    //    fg.theme_config[Frameless::Theme::Gray].round4 = {0,0,0,0};
    fg.swithTheme(Frameless::Theme::White);

    MainWindow w;
    w.setWindowTitle("framelessdemo");
    w.connect(&fg.SIGNAL,&Frameless::__signal__::themeChanged,&w,[&](){
        loadthemesetting();
    });
    loadthemesetting();
#if defined Q_OS_ANDROID
    w.connect(qac,&QtAndroidCls::statusbarHeightChanged, &w,[=](const qint32 &height){
    });
#endif

#ifndef Q_OS_ANDROID
    auto fl_tb = Frameless::template_windows10<Frameless::TitlebarLikeWindows10>(w,28,44);
    Maintitlebarbutton* maintitlebarbutton = new Maintitlebarbutton(&w);
    fl_tb.second->w3layout()->addWidget(maintitlebarbutton);
    fl_tb.second->set_title("v1.0");
    fl_tb.second->set_title_enable(false);
#else
    auto fl_tb = Frameless::template_windows10<Frameless::TitlebarLikeAndroid>(w,qac->get_statusbar_qwiget_height());
    w.show();
    // W_startscreen *w_ss = new W_startscreen(&w);
    // w_ss->showFullScreen();
    QTimer::singleShot(50,qac,[&](){
        qac->to_statusbar_text_white();
        QtAndroid::hideSplashScreen(100);
        // w_ss->exec();
        if (fg.currentTheme==Frameless::Theme::Light || fg.currentTheme==Frameless::Theme::White){
            qac->to_statusbar_text_black();
        }else{
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

