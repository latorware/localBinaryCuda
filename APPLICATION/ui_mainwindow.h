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
    QPushButton *NickGPU1;
    QPushButton *NickGPU2;
    QPushButton *NickGPU3;
    QSlider *windowSizeSlider;
    QLabel *windowSizeText;
    QLabel *evenNumber;
    QSlider *kSlider;
    QLabel *kText;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *btnFitWindow;
    QPushButton *clear;
    QTextBrowser *textBrowser;
    MyGraphicsView *m_graphicsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1038, 1600);
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

        NickGPU1 = new QPushButton(centralWidget);
        NickGPU1->setObjectName(QString::fromUtf8("NickGPU1"));
        NickGPU1->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0)"));

        verticalLayout->addWidget(NickGPU1);

        NickGPU2 = new QPushButton(centralWidget);
        NickGPU2->setObjectName(QString::fromUtf8("NickGPU2"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(247, 247, 247, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(160, 160, 160, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        NickGPU2->setPalette(palette);

        verticalLayout->addWidget(NickGPU2);

        NickGPU3 = new QPushButton(centralWidget);
        NickGPU3->setObjectName(QString::fromUtf8("NickGPU3"));

        verticalLayout->addWidget(NickGPU3);

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
        kSlider->setMaximum(10);
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

        clear = new QPushButton(centralWidget);
        clear->setObjectName(QString::fromUtf8("clear"));

        verticalLayout->addWidget(clear);


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
        QObject::connect(NickGPU1, SIGNAL(clicked()), MainWindow, SLOT(onNickGPU1Clicked()));
        QObject::connect(NickCPU, SIGNAL(clicked()), MainWindow, SLOT(onNickCPUClicked()));
        QObject::connect(NickGPU2, SIGNAL(clicked()), MainWindow, SLOT(onNickGPU2Clicked()));
        QObject::connect(NickGPU3, SIGNAL(clicked()), MainWindow, SLOT(onNickGPU3Clicked()));
        QObject::connect(clear, SIGNAL(clicked()), MainWindow, SLOT(onClearTextClicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qt5 Image Viewer", nullptr));
        btnLoadBG->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
        grayscale->setText(QCoreApplication::translate("MainWindow", "RGBtoGRAYSCALE (CPU)", nullptr));
        globalBinarize->setText(QCoreApplication::translate("MainWindow", "GlobalBinarize (CPU)", nullptr));
        GlobalThresholdText->setText(QCoreApplication::translate("MainWindow", "GLOBAL threshold value: 128", nullptr));
        NickCPU->setText(QCoreApplication::translate("MainWindow", "NICK (local binaritzation) (CPU)", nullptr));
        NickGPU1->setText(QCoreApplication::translate("MainWindow", "NICK method1 (local binaritzation) (GPU)", nullptr));
        NickGPU2->setText(QCoreApplication::translate("MainWindow", "NICK method2 (local binaritzation) (GPU)", nullptr));
        NickGPU3->setText(QCoreApplication::translate("MainWindow", "NICK method3 (local binaritzation) (GPU)", nullptr));
        windowSizeText->setText(QCoreApplication::translate("MainWindow", "width size of window: 6", nullptr));
        evenNumber->setText(QCoreApplication::translate("MainWindow", "window size has to be an EVEN number!", nullptr));
        kText->setText(QCoreApplication::translate("MainWindow", "k value: -0.2", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Scrolling(V) -> Mouse Wheel\n"
"Scrolling(H) -> Shift+Wheel\n"
"Zoom -> Ctrl+Wheel", nullptr));
        btnFitWindow->setText(QCoreApplication::translate("MainWindow", "Fit to window", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "Clear Text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
