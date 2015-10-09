#include <QtWidgets>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    bt_flag = false;
    setMouseTracking(true);
    //setFixedSize(500,600);
    setWindowTitle(tr("画像表示テスト1"));
    // サイズをMainWindowに合わせる
    setCentralWidget(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// 終了
void MainWindow::on_actionExit_triggered()
{
    this->close();
}
// 開く
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("画像ファイルのオープン"),
                                    "",
                                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

    if (!fileName.isEmpty()){
        loadFile(fileName);
    }
}
// 保存
void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                    tr("画像ファイルの保存"),
                                    "",
                                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    if (!fileName.isEmpty()){
        qDebug() << fileName;
        saveFile(fileName);
    }
}

// ファイルのロード処理
void MainWindow::loadFile(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
    }
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(image));
    // 文字列テスト
    scene->addText(tr("こんにちは、世界"));

    QApplication::restoreOverrideCursor();
    ui->statusBar->showMessage(tr("File loaded"), 2000);
}
// ファイルの保存処理
void MainWindow::saveFile(const QString &fileName)
{
    QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);
}
// 画像のフィット(Aspect Ratio)縦横比を維持しない
void MainWindow::imageFit()
{
   ui->graphicsView->fitInView(scene->sceneRect(),Qt::IgnoreAspectRatio);
}
// 画像のフィット(Aspect Ratio)縦横比を維持する
void MainWindow::imageFitKeep()
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
// 画像のフィット(Aspect Ratio)縦横比を拡大して維持する
void MainWindow::imageFitKeepByExpanding()
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatioByExpanding);
}
// 画像のスケール設定
void MainWindow::imageScale(qreal s_size)
{
    ui->graphicsView->scale(s_size,s_size);
}


void MainWindow::on_actionImageFit_triggered()
{
    imageFit();
}

void MainWindow::on_actionImageFitKeep_triggered()
{
    imageFitKeep();
}

void MainWindow::on_actionScale_2_triggered()
{
    imageScale(2.0);
}

void MainWindow::on_actionScale_3_triggered()
{
    imageScale(3.0);
}

void MainWindow::on_actionScale_1_2_triggered()
{
    imageScale(0.5);
}
void MainWindow::on_actionScale_1_3_triggered()
{
    imageScale(0.33);
}

void MainWindow::on_actionScale_1_4_triggered()
{
    imageScale(0.25);
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove) // マウス移動
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
  }
  return false;
}
