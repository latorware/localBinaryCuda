#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "processor.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* m_graphicsScene;
    processor* myProcessor; 

private slots:
    void onPressLoadImage();
    //void onPressSaveImage();
    void onPressFitWindow();

    
    void onWindowSizeSliderChanged(int newValue); 
    void onkSilderChanged(int newValue); 
    void onGrayscaleClicked(); 
    void onGlobalThresholdSliderChanged(int newValue); 
    void onGlobalBinarizeClicked(); 
    void onNickGPU1Clicked();
    void onNickGPU2Clicked();
    void onNickGPU3Clicked();
    void onNickCPUClicked();

};

#endif // MAINWINDOW_H
