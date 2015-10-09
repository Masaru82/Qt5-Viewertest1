#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setAttribute(Qt::WA_AcceptTouchEvents);
    w.setWindowTitle("画像表示とペイントのテスト1");
    w.show();

    return a.exec();
}
