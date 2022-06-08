#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>

#include <QImageReader>
#include <QImageWriter>

#include <QMessageBox>
using namespace std; 

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_graphicsScene = new QGraphicsScene();
    myProcessor = new processor(ui->textBrowser); 
    m_graphicsScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    QImage bground(50, 50, QImage::Format_RGB888);
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 25; x++)
        {
            bground.setPixel(x, y, qRgb(0xCA, 0xCA, 0xCA));
            bground.setPixel(x + 25, y, qRgb(0xFF, 0xFF, 0xFF));
            bground.setPixel(x, y + 25, qRgb(0xFF, 0xFF, 0xFF));
            bground.setPixel(x + 25, y + 25, qRgb(0xCA, 0xCA, 0xCA));
        }
    }
    m_graphicsScene->setBackgroundBrush(QPixmap::fromImage(bground));

    ui->m_graphicsView->setScene(m_graphicsScene);

    //ui->statusBar->showMessage("ready", 0);
    ui->textBrowser->append("ready"); 
    ui->textBrowser->append("To start, Load an image");

    ui->grayscale->setDisabled(true); 
    ui->globalBinarize->setDisabled(true);
    ui->globalThresholdSlider->setDisabled(true);
    ui->NickGPU1->setDisabled(true);
    ui->NickGPU2->setDisabled(true);
    ui->NickGPU3->setDisabled(true);
    ui->NickCPU->setDisabled(true);
    ui->NickGPU1->setStyleSheet("background-color: rgb(175, 175, 175)"); 
    ui->NickGPU2->setStyleSheet("background-color: rgb(175, 175, 175)");
    ui->NickGPU3->setStyleSheet("background-color: rgb(175, 175, 175)");
    ui->windowSizeSlider->setDisabled(true);
    ui->kSlider->setDisabled(true);
    ui->GlobalThresholdText->setDisabled(true); 
    ui->windowSizeText->setDisabled(true);
    ui->evenNumber->setDisabled(true);
    ui->kText->setDisabled(true);
    ui->label->setDisabled(true);
    ui->btnFitWindow->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPressLoadImage()
{
    QString qStrFilePath = QFileDialog::getOpenFileName(this,
        tr("Open Image"),
        QStandardPaths::writableLocation(QStandardPaths::CacheLocation),
        tr("Image Files (*.png *.jpg *.bmp)"));


    ui->textBrowser->append(QString::fromStdString("Image Path: ") + qStrFilePath);

    if (qStrFilePath.isEmpty())
        return;

    QImageReader reader(qStrFilePath);
    bool canRead; 
    if (!reader.canRead())
    {
        canRead = false;
        QMessageBox msgBox;
        msgBox.setText("Cannot read file");
        msgBox.exec();
        return;
    }
    else
    {
        canRead = true; 
    }
    if (!m_graphicsScene->sceneRect().isEmpty())
    {
        m_graphicsScene->clear();
    }
    QImage qimg = reader.read();
    m_graphicsScene->setSceneRect(qimg.rect());
    m_graphicsScene->addPixmap(QPixmap::fromImage(qimg));

    ui->m_graphicsView->viewFit();
    
    //ui->statusBar->showMessage("image loaded", 0);
    if (canRead)
    {
        ui->label->setDisabled(false);
        ui->btnFitWindow->setDisabled(false);
        ui->textBrowser->append("image loaded in the visualizer");
    }
    
    if (myProcessor->ReadFile(qStrFilePath.toStdString()) == 0)
    {
        
        if ((myProcessor->getWidth() > 10000) || (myProcessor->getHeight() > 10000))
        {
            ui->textBrowser->append("ERROR: image should be smaller than 10.000 x 10.000 pixels. Load another image. ");
        }
        else
        {
            ui->grayscale->setDisabled(false);
            ui->globalBinarize->setDisabled(false);
            ui->globalThresholdSlider->setDisabled(false);
            ui->NickGPU1->setDisabled(false);
            ui->NickGPU2->setDisabled(false);
            ui->NickGPU3->setDisabled(false);
            ui->NickCPU->setDisabled(false);
            ui->NickGPU1->setStyleSheet("background-color: rgb(118, 185, 0)");
            ui->NickGPU2->setStyleSheet("background-color: rgb(118, 185, 0)");
            ui->NickGPU3->setStyleSheet("background-color: rgb(118, 185, 0)");
            ui->windowSizeSlider->setDisabled(false);
            ui->kSlider->setDisabled(false);
            ui->GlobalThresholdText->setDisabled(false);
            ui->windowSizeText->setDisabled(false);
            ui->evenNumber->setDisabled(false);
            ui->kText->setDisabled(false);
        }
    }
    
    ui->textBrowser->append("ready \n \n");
}
/*
void MainWindow::onPressSaveImage()
{
    if (m_graphicsScene->sceneRect().isEmpty())
        return;

    m_graphicsScene->clearSelection();
    QImage img(m_graphicsScene->sceneRect().size().toSize(), QImage::Format_RGB888);
    QPainter painter(&img);
    m_graphicsScene->render(&painter);

    QString qStrFilePath = QFileDialog::getSaveFileName(this,
            tr("Save Image"),
            QStandardPaths::writableLocation(QStandardPaths::CacheLocation).replace("cache", "newfile.jpg"),
            tr("JPG file (*.jpg);;PNG file (*.png);;BMP file (*.bmp)"));

    if (qStrFilePath.isEmpty())
        return;

    QImageWriter writer(qStrFilePath);
    if(!writer.canWrite())
    {
        QMessageBox msgBox;
        msgBox.setText("Cannot write file");
        msgBox.exec();
        return;
    }
    writer.write(img);

    ui->statusBar->showMessage("image saved", 0);
}
*/

void MainWindow::onPressFitWindow()
{
    ui->m_graphicsView->viewFit();
}

void MainWindow::onWindowSizeSliderChanged(int newValue)
{
   
    ui->windowSizeText->setText(QString::fromStdString("width size of window: " + to_string(newValue)));
    if ((newValue % 2) != 0)
    {
        ui->evenNumber->setStyleSheet("background-color: rgb(255, 0, 0)"); 
        ui->NickCPU->setDisabled(true); 
        ui->NickGPU1->setDisabled(true);
        ui->NickGPU2->setDisabled(true);
        ui->NickGPU3->setDisabled(true);
        ui->NickGPU1->setStyleSheet("background-color: rgb(175, 175, 175)");
        ui->NickGPU2->setStyleSheet("background-color: rgb(175, 175, 175)");
        ui->NickGPU3->setStyleSheet("background-color: rgb(175, 175, 175)");
    }
    else
    {
        ui->evenNumber->setStyleSheet("");
        ui->NickCPU->setDisabled(false);
        ui->NickGPU1->setDisabled(false);
        ui->NickGPU2->setDisabled(false);
        ui->NickGPU3->setDisabled(false);
        ui->NickGPU1->setStyleSheet("background-color: rgb(0, 255, 0)");
        ui->NickGPU2->setStyleSheet("background-color: rgb(0, 255, 0)");
        ui->NickGPU3->setStyleSheet("background-color: rgb(0, 255, 0)");
    }
}

void MainWindow::onkSilderChanged(int newValue)
{
    ui->kText->setText(QString::fromStdString("k value: " + to_string(newValue/100.f)));
}

void MainWindow::onGrayscaleClicked()
{
    string path = myProcessor->RGBtoGRAYSCALE(); 
    ui->textBrowser->append("Opening Grayscaled image in the visualizer");
    m_graphicsScene->clear();
    QImageReader reader(QString::fromStdString(path));
    QImage qimg = reader.read();
    m_graphicsScene->setSceneRect(qimg.rect());
    m_graphicsScene->addPixmap(QPixmap::fromImage(qimg));
    ui->textBrowser->append("Grayscaled image opened in the visualizer");
    ui->textBrowser->append("ready \n \n");
}

void MainWindow::onGlobalThresholdSliderChanged(int newValue)
{
    ui->GlobalThresholdText->setText(QString::fromStdString("GLOBAL threshold value: " + to_string(newValue)));
}

void MainWindow::onGlobalBinarizeClicked()
{
    string path = myProcessor->globalBinaritzation(ui->globalThresholdSlider->value());
    ui->textBrowser->append("Opening Globally Binarized image in the visualizer");
    m_graphicsScene->clear();
    QImageReader reader(QString::fromStdString(path));
    QImage qimg = reader.read();
    m_graphicsScene->setSceneRect(qimg.rect());
    m_graphicsScene->addPixmap(QPixmap::fromImage(qimg));
    ui->textBrowser->append("Globally Binarized image opened in the visualizer");
    ui->textBrowser->append("ready \n \n");
}


void MainWindow::onNickGPU1Clicked()
{
    string path = myProcessor->NICKBinaritzationGPU1(ui->windowSizeSlider->value(), (float)((ui->kSlider->value()) / 100.f));
    ui->textBrowser->append("Opening Nick GPU method1 Binarized image in the visualizer");
    m_graphicsScene->clear();
    QImageReader reader(QString::fromStdString(path));
    QImage qimg = reader.read();
    m_graphicsScene->setSceneRect(qimg.rect());
    m_graphicsScene->addPixmap(QPixmap::fromImage(qimg));
    ui->textBrowser->append("Nick GPU method1 binarized image opened in the visualizer");
    ui->textBrowser->append("ready \n \n");
}

void MainWindow::onNickGPU2Clicked()
{
}

void MainWindow::onNickGPU3Clicked()
{
}

void MainWindow::onNickCPUClicked()
{
    string path = myProcessor->NICKBinaritzationCPU(ui->windowSizeSlider->value(), (float)( (ui->kSlider->value())  / 100.f) );
    ui->textBrowser->append("Opening Nick cpu Binarized image in the visualizer");
    m_graphicsScene->clear();
    QImageReader reader(QString::fromStdString(path));
    QImage qimg = reader.read();
    m_graphicsScene->setSceneRect(qimg.rect());
    m_graphicsScene->addPixmap(QPixmap::fromImage(qimg));
    ui->textBrowser->append("Nick CPU binarized image opened in the visualizer");
    ui->textBrowser->append("ready \n \n");

}
