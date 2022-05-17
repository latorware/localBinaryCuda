﻿#include "mainwindow.h"
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
    ui->NickGPU->setDisabled(true);
    ui->NickCPU->setDisabled(true);
    ui->NickGPU->setStyleSheet("background-color: rgb(175, 175, 175)"); 
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
    if (!reader.canRead())
    {
        QMessageBox msgBox;
        msgBox.setText("Cannot read file");
        msgBox.exec();
        return;
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
    if (reader.canRead())
    {
        ui->label->setDisabled(false);
        ui->btnFitWindow->setDisabled(false);
        ui->textBrowser->append("image loaded in the visualizer");
    }

    if (myProcessor->ReadFile(qStrFilePath.toStdString()) == 0)
    {


        ui->grayscale->setDisabled(false);
        ui->globalBinarize->setDisabled(false);
        ui->globalThresholdSlider->setDisabled(false);
        ui->NickGPU->setDisabled(false);
        ui->NickCPU->setDisabled(false);
        ui->NickGPU->setStyleSheet("background-color: rgb(0, 255, 0)");
        ui->windowSizeSlider->setDisabled(false);
        ui->kSlider->setDisabled(false);
        ui->GlobalThresholdText->setDisabled(false);
        ui->windowSizeText->setDisabled(false);
        ui->evenNumber->setDisabled(false);
        ui->kText->setDisabled(false);
    }
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
        ui->NickGPU->setDisabled(true);
        ui->NickGPU->setStyleSheet("background-color: rgb(175, 175, 175)");
    }
    else
    {
        ui->evenNumber->setStyleSheet("");
        ui->NickCPU->setDisabled(false);
        ui->NickGPU->setDisabled(false);
        ui->NickGPU->setStyleSheet("background-color: rgb(0, 255, 0)");
    }
}

void MainWindow::onkSilderChanged(int newValue)
{
    ui->kText->setText(QString::fromStdString("k value: " + to_string(newValue/100.f)));
}

void MainWindow::onGrayscaleClicked()
{
}

void MainWindow::onGlobalThresholdSliderChanged(int newValue)
{
    ui->GlobalThresholdText->setText(QString::fromStdString("GLOBAL threshold value: " + to_string(newValue)));
}

void MainWindow::onGlobalBinarizeClicked()
{
}

void MainWindow::onNickGPUClicked()
{
}

void MainWindow::onNickCPUClicked()
{
}
