#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsItem>
#include <QTextStream>
#include <QIODevice>
#include <QObject>
#include <QMetaType>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "platefinder.h"
#include "recognise.h"
#include "detect.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

//    void image_grayscale();

//    void image_binary();

    void show_image(QGraphicsScene *scnn, QString image_path);

    void on_nextButton_0_clicked();

    void on_preButton_1_clicked();

    void on_nextButton_1_clicked();

    void on_preButton_2_clicked();

    void on_nextButton_2_clicked();

    void on_preButton_3_clicked();

    void on_nextButton_3_clicked();

    void on_preButton_4_clicked();

    void on_nextButton_4_clicked();

    void on_preButton_5_clicked();

    void on_exitButton_5_clicked();

    void on_openButton_clicked();

    void on_runButton_clicked();

    void on_loadButton_clicked();

    void on_trainButton_clicked();

private:
    Ui::MainWindow *ui;

public:
    QString trainPath;
    QString fileName;
    QString tam;

    QImage image;
    QImage image0;
    QImage image1;
    QImage image2;
    QImage image3;
    QImage image4;
    QImage image5;
    QImage image6;
    QImage image7;
    QImage image8;
    QImage image9;


    QGraphicsScene *scene;
    QGraphicsScene *scene0;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;
    QGraphicsScene *scene5;
    QGraphicsScene *scene6;
    QGraphicsScene *scene7;
    QGraphicsScene *scene8;
    QGraphicsScene *scene9;

    QPixmap pixmap;
    QPixmap pixmap0;
    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QPixmap pixmap4;
    QPixmap pixmap5;
    QPixmap pixmap6;
    QPixmap pixmap7;
    QPixmap pixmap8;
    QPixmap pixmap9;

    QGraphicsScene *scn;
    QGraphicsScene *scn0;
    QGraphicsScene *scn1;
    QGraphicsScene *scn2;
    QGraphicsScene *scn3;
    QGraphicsScene *scn4;
    QGraphicsScene *scn5;
    QGraphicsScene *scn6;
    QGraphicsScene *scn7;
    QGraphicsScene *scn8;
    QGraphicsScene *scn9;

    PlateFinder fp;
    Recognise rc;
    vector<IplImage*> pvt;
//    cv::Mat picture;
//    cv::Mat graycolor;
//    cv::Mat binarycolor;

};

#endif // MAINWINDOW_H
