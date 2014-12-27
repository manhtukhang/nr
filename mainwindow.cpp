#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    QDir dir9("data");


    
    if (!dir9.exists()){
	    dir9.mkpath(".");
    }

    scn = new QGraphicsScene(this);
    scn0 = new QGraphicsScene(this);
    scn1 = new QGraphicsScene(this);
    scn2 = new QGraphicsScene(this);
    scn3 = new QGraphicsScene(this);
    scn4 = new QGraphicsScene(this);
    scn5 = new QGraphicsScene(this);
    scn6 = new QGraphicsScene(this);
    scn7 = new QGraphicsScene(this);
    scn8 = new QGraphicsScene(this);
    scn9 = new QGraphicsScene(this);

    scene = new QGraphicsScene(this);
    scene0 = new QGraphicsScene(this);
    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);
    scene5 = new QGraphicsScene(this);
    scene6 = new QGraphicsScene(this);
    scene7 = new QGraphicsScene(this);
    scene8 = new QGraphicsScene(this);
    scene9 = new QGraphicsScene(this);

    ui->setupUi(this);
    QMainWindow::showMaximized();

    connect(ui->exitButton_5,SIGNAL(clicked()),this,SLOT(close()));
}


MainWindow::~MainWindow()
{
    delete scn;
    delete scn0;
    delete scn1;
    delete scn2;
    delete scn3;
    delete scn4;
    delete scn5;
    delete scn6;
    delete scn7;
    delete scn8;
    delete scn9;

    delete scene;
    delete scene0;
    delete scene1;
    delete scene2;
    delete scene3;
    delete scene4;
    delete scene5;
    delete scene6;
    delete scene7;
    delete scene8;
    delete scene9;

    delete ui;

}

void MainWindow::show_image(QGraphicsScene *scnn, QString image_path)
{
    QImage img;
    QPixmap pix;
    img.load(image_path);
    pix = QPixmap::fromImage(img);
    scnn->addPixmap(pix);
}

void MainWindow::on_openButton_clicked()//nút load ảnh
{
	QDir dir("processing");
    QDir dir0("processing/source");
    QDir dir1("processing/result");
    QDir dir2("processing/step1");
    QDir dir3("processing/step2");
    QDir dir4("processing/step3");
    QDir dir5("processing/step4");
    QDir dir6("processing/step5");
    QDir dir7("processing/step6");
    QDir dir8("processing/step7");
    if (dir.exists()){
    dir.removeRecursively();
    }
    dir.mkpath(".");
    dir0.mkpath(".");
    dir1.mkpath(".");
    dir2.mkpath(".");
    dir3.mkpath(".");
    dir4.mkpath(".");
    dir5.mkpath(".");
    dir6.mkpath(".");
    dir7.mkpath(".");
    dir8.mkpath(".");

    ui->textEdit->clear();
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Mở ảnh"),"~/",tr("Image Files (*.png *.jpg *.bmp)"));
    tam = fileName;
    qDeleteAll(scn->items());
    show_image(scn,fileName);

    //write image to processing folder
//    if(QFile::exists("processing/source/image.jpg"))
//    {
//        QFile::remove("processing/source/image.jpg");
//    }
    QFile::copy(fileName,"processing/source/image.jpg");

    ///
    if(!fileName.isNull())
    {
        ui->graphicsView->setScene(scn);
        ui->graphicsView->fitInView(scn->sceneRect());
        ui->graphicsView_0->setScene(scn);
        vector<IplImage*> number_image = fp.image_grayscale();
        saveNumberToFile(number_image, "processing/result/result.txt");
    }

}

void MainWindow::on_runButton_clicked() //nút chạy all
{
    if(fileName.isNull())
    {
        ui->textEdit->setPlainText("Chưa có ảnh để nhận dạng!!");
    }
    else
    {
        ui->textEdit->clear();
        QFile file("processing/result/result.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream textStream(&file);
        QString result = textStream.readAll();
        file.close();
        ui->textEdit->setPlainText(result);
    }
}

void MainWindow::on_nextButton_0_clicked()//nút chuyển sang page_1
{
    if(fileName.isNull())
    {
        ui->nextButton_0->setEnabled(false);
        ui->nextButton_0->setEnabled(true);
    }
    else {
        ui->nextButton_0->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(1);

        QString a = QDir::currentPath();
        fileName = a+"/processing/step1/grayscale.jpg";
        qDeleteAll(scn->items());
        show_image(scn,fileName);
        ui->graphicsView_1->setScene(scn);
        ui->graphicsView_1->fitInView(scn->sceneRect());
    }
}

void MainWindow::on_preButton_1_clicked()//nút trở lại page_0
{
    ui->stackedWidget->setCurrentIndex(0);

    QString a = QDir::currentPath();
    fileName = a+"/processing/step1/grayscale.jpg";
    qDeleteAll(scn->items());
    show_image(scn,tam);
    ui->graphicsView_1->setScene(scn);
    ui->graphicsView_1->fitInView(scn->sceneRect());

}

void MainWindow::on_nextButton_1_clicked()//nút chuyển sang page_2
{
    ui->stackedWidget->setCurrentIndex(2);

    QString a = QDir::currentPath();
    fileName = a+"/processing/step2/binary.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_2->setScene(scn);
    ui->graphicsView_2->fitInView(scn->sceneRect());
}

void MainWindow::on_preButton_2_clicked()//nút trở lại page_1
{
    ui->stackedWidget->setCurrentIndex(1);

    QString a = QDir::currentPath();
    fileName = a+"/processing/step1/grayscale.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_1->setScene(scn);
    ui->graphicsView_1->fitInView(scn->sceneRect());
}

void MainWindow::on_nextButton_2_clicked()//nút chuyển sang page_3
{
    ui->stackedWidget->setCurrentIndex(3);

    QString a = QDir::currentPath();
    fileName = a+"/processing/step3/filter.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_3->setScene(scn);
    ui->graphicsView_3->fitInView(scn->sceneRect());
}

void MainWindow::on_preButton_3_clicked()//nút trở lại page_2
{
    ui->stackedWidget->setCurrentIndex(2);

    QString a = QDir::currentPath();
    fileName = a+"/processing/step2/binary.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_2->setScene(scn);
    ui->graphicsView_2->fitInView(scn->sceneRect());
}

void MainWindow::on_nextButton_3_clicked()//nút chuyển sang page_4
{
    ui->stackedWidget->setCurrentIndex(4);
    QString a = QDir::currentPath();
    fileName = a+"/processing/step5/a.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_4->setScene(scn);
    ui->graphicsView_4->fitInView(scn->sceneRect());



}

void MainWindow::on_preButton_4_clicked()//nút trở lại page_3
{
    ui->stackedWidget->setCurrentIndex(3);

    QString a = QDir::currentPath();
    fileName = a+"/processing/step3/filter.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_3->setScene(scn);
    ui->graphicsView_3->fitInView(scn->sceneRect());
}

void MainWindow::on_nextButton_4_clicked()//nút chuyển sang page_5
{
    ui->stackedWidget->setCurrentIndex(5);


        ui->textEdit_5->clear();
        QFile file("processing/result/result.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream textStream(&file);
        QString result = textStream.readAll();
        file.close();
        ui->textEdit_5->setPlainText(result);
}

void MainWindow::on_preButton_5_clicked()//nút trở lại page_4
{
    ui->stackedWidget->setCurrentIndex(4);
    QString a = QDir::currentPath();
    fileName = a+"/processing/step5/a.jpg";
    qDeleteAll(scn->items());
    show_image(scn,fileName);
    ui->graphicsView_4->setScene(scn);
    ui->graphicsView_4->fitInView(scn->sceneRect());
}

void MainWindow::on_exitButton_5_clicked()
{

}

void MainWindow::on_loadButton_clicked()
{
    trainPath = QFileDialog::getExistingDirectory(this, tr("Mở thư mục"),
                                                "./",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if (!trainPath.isNull()){
    QString filename0 = trainPath+"/0.jpg";
    QString filename1 = trainPath+"/1.jpg";
    QString filename2 = trainPath+"/2.jpg";
    QString filename3 = trainPath+"/3.jpg";
    QString filename4 = trainPath+"/4.jpg";
    QString filename5 = trainPath+"/5.jpg";
    QString filename6 = trainPath+"/6.jpg";
    QString filename7 = trainPath+"/7.jpg";
    QString filename8 = trainPath+"/8.jpg";
    QString filename9 = trainPath+"/9.jpg";

    qDeleteAll(scn0->items());
    qDeleteAll(scn1->items());
    qDeleteAll(scn2->items());
    qDeleteAll(scn3->items());
    qDeleteAll(scn4->items());
    qDeleteAll(scn5->items());
    qDeleteAll(scn6->items());
    qDeleteAll(scn7->items());
    qDeleteAll(scn8->items());
    qDeleteAll(scn9->items());

    show_image(scn0,filename0);
    show_image(scn1,filename1);
    show_image(scn2,filename2);
    show_image(scn3,filename3);
    show_image(scn4,filename4);
    show_image(scn5,filename5);
    show_image(scn6,filename6);
    show_image(scn7,filename7);
    show_image(scn8,filename8);
    show_image(scn9,filename9);

    ui->graphicsView_2_0->setScene(scn0);
    ui->graphicsView_2_1->setScene(scn1);
    ui->graphicsView_2_2->setScene(scn2);
    ui->graphicsView_2_3->setScene(scn3);
    ui->graphicsView_2_4->setScene(scn4);
    ui->graphicsView_2_5->setScene(scn5);
    ui->graphicsView_2_6->setScene(scn6);
    ui->graphicsView_2_7->setScene(scn7);
    ui->graphicsView_2_8->setScene(scn8);
    ui->graphicsView_2_9->setScene(scn9);

    ui->trainButton->setEnabled(true);
    } else {
       ui->trainButton->setEnabled(false);
    }
}

void MainWindow::on_trainButton_clicked()
{
    if (!trainPath.isNull()){
    char* p = new char[trainPath.length() + 1];
    strcpy(p, trainPath.toLatin1().constData());
    training(p);
    ui->trainButton->setEnabled(false);
    }
}
