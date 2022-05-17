/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mygraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *btnLoadBG;
    QPushButton *grayscale;
    QSpacerItem *verticalSpacer_2;
    QPushButton *globalBinarize;
    QSlider *globalThresholdSlider;
    QLabel *GlobalThresholdText;
    QSpacerItem *verticalSpacer_3;
    QPushButton *NickCPU;
    QPushButton *NickGPU;
    QSlider *windowSizeSlider;
    QLabel *windowSizeText;
    QLabel *evenNumber;
    QSlider *kSlider;
    QLabel *kText;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *btnFitWindow;
    QTextBrowser *textBrowser;
    MyGraphicsView *m_graphicsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1053, 1600);
        MainWindow->setMinimumSize(QSize(0, 1300));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnLoadBG = new QPushButton(centralWidget);
        btnLoadBG->setObjectName(QString::fromUtf8("btnLoadBG"));

        verticalLayout->addWidget(btnLoadBG);

        grayscale = new QPushButton(centralWidget);
        grayscale->setObjectName(QString::fromUtf8("grayscale"));

        verticalLayout->addWidget(grayscale);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        globalBinarize = new QPushButton(centralWidget);
        globalBinarize->setObjectName(QString::fromUtf8("globalBinarize"));

        verticalLayout->addWidget(globalBinarize);

        globalThresholdSlider = new QSlider(centralWidget);
        globalThresholdSlider->setObjectName(QString::fromUtf8("globalThresholdSlider"));
        globalThresholdSlider->setMaximum(256);
        globalThresholdSlider->setSliderPosition(128);
        globalThresholdSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(globalThresholdSlider);

        GlobalThresholdText = new QLabel(centralWidget);
        GlobalThresholdText->setObjectName(QString::fromUtf8("GlobalThresholdText"));
        GlobalThresholdText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(GlobalThresholdText);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        NickCPU = new QPushButton(centralWidget);
        NickCPU->setObjectName(QString::fromUtf8("NickCPU"));
        NickCPU->setEnabled(true);

        verticalLayout->addWidget(NickCPU);

        NickGPU = new QPushButton(centralWidget);
        NickGPU->setObjectName(QString::fromUtf8("NickGPU"));
        NickGPU->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0)"));

        verticalLayout->addWidget(NickGPU);

        windowSizeSlider = new QSlider(centralWidget);
        windowSizeSlider->setObjectName(QString::fromUtf8("windowSizeSlider"));
        windowSizeSlider->setMaximum(100);
        windowSizeSlider->setSingleStep(2);
        windowSizeSlider->setPageStep(2);
        windowSizeSlider->setValue(6);
        windowSizeSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(windowSizeSlider);

        windowSizeText = new QLabel(centralWidget);
        windowSizeText->setObjectName(QString::fromUtf8("windowSizeText"));
        windowSizeText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(windowSizeText);

        evenNumber = new QLabel(centralWidget);
        evenNumber->setObjectName(QString::fromUtf8("evenNumber"));
        evenNumber->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(evenNumber);

        kSlider = new QSlider(centralWidget);
        kSlider->setObjectName(QString::fromUtf8("kSlider"));
        kSlider->setMinimum(-20);
        kSlider->setMaximum(-10);
        kSlider->setValue(-20);
        kSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(kSlider);

        kText = new QLabel(centralWidget);
        kText->setObjectName(QString::fromUtf8("kText"));
        kText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(kText);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        btnFitWindow = new QPushButton(centralWidget);
        btnFitWindow->setObjectName(QString::fromUtf8("btnFitWindow"));

        verticalLayout->addWidget(btnFitWindow);


        horizontalLayout->addLayout(verticalLayout);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMinimumSize(QSize(0, 300));
        textBrowser->setMaximumSize(QSize(16777215, 100));
        textBrowser->setBaseSize(QSize(0, 100));
        textBrowser->setAcceptDrops(true);
        textBrowser->setAcceptRichText(true);

        formLayout->setWidget(1, QFormLayout::SpanningRole, textBrowser);

        m_graphicsView = new MyGraphicsView(centralWidget);
        m_graphicsView->setObjectName(QString::fromUtf8("m_graphicsView"));
        m_graphicsView->setMinimumSize(QSize(800, 600));
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        formLayout->setWidget(0, QFormLayout::FieldRole, m_graphicsView);


        horizontalLayout_2->addLayout(formLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(btnLoadBG, SIGNAL(clicked()), MainWindow, SLOT(onPressLoadImage()));
        QObject::connect(btnFitWindow, SIGNAL(clicked()), MainWindow, SLOT(onPressFitWindow()));
        QObject::connect(windowSizeSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onWindowSizeSliderChanged(int)));
        QObject::connect(kSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onkSilderChanged(int)));
        QObject::connect(grayscale, SIGNAL(clicked()), MainWindow, SLOT(onGrayscaleClicked()));
        QObject::connect(globalThresholdSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onGlobalThresholdSliderChanged(int)));
        QObject::connect(globalBinarize, SIGNAL(clicked()), MainWindow, SLOT(onGlobalBinarizeClicked()));
        QObject::connect(NickGPU, SIGNAL(clicked()), MainWindow, SLOT(onNickGPUClicked()));
        QObject::connect(NickCPU, SIGNAL(clicked()), MainWindow, SLOT(onNickCPUClicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qt5 Image Viewer", nullptr));
        btnLoadBG->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
        grayscale->setText(QCoreApplication::translate("MainWindow", "RGBtoGRAYSCALE (CPU)", nullptr));
        globalBinarize->setText(QCoreApplication::translate("MainWindow", "GlobalBinarize (CPU)", nullptr));
        GlobalThresholdText->setText(QCoreApplication::translate("MainWindow", "GLOBAL threshold value: 128", nullptr));
        NickCPU->setText(QCoreApplication::translate("MainWindow", "NICK method (local binaritzation) (CPU)", nullptr));
        NickGPU->setText(QCoreApplication::translate("MainWindow", "NICK method (local binaritzation) (GPU)", nullptr));
        windowSizeText->setText(QCoreApplication::translate("MainWindow", "width size of window: 6", nullptr));
        evenNumber->setText(QCoreApplication::translate("MainWindow", "window size has to be an EVEN number!", nullptr));
        kText->setText(QCoreApplication::translate("MainWindow", "k value: -0.2", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Scrolling(V) -> Mouse Wheel\n"
"Scrolling(H) -> Shift+Wheel\n"
"Zoom -> Ctrl+Wheel", nullptr));
        btnFitWindow->setText(QCoreApplication::translate("MainWindow", "Fit to window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
