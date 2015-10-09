#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QMainWindow>
#endif
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionImageFit_triggered();

    void on_actionScale_2_triggered();

    void on_actionScale_3_triggered();

    void on_actionScale_1_2_triggered();

    void on_actionScale_1_3_triggered();

    void on_actionScale_1_4_triggered();

    void on_actionImageFitKeep_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    bool bt_flag;
    void loadFile(const QString &fileName);
    void saveFile(const QString &fileName);
    void imageFit();
    void imageFitKeep();
    void imageFitKeepByExpanding();
    void imageScale(qreal s_size);

};

#endif // MAINWINDOW_H
