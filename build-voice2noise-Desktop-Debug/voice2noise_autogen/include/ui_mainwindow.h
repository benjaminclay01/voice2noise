/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *StartStopButton;
    QFrame *line;
    QVBoxLayout *IOPickLayout;
    QLabel *label_2;
    QComboBox *inputBox;
    QLabel *label_3;
    QComboBox *outputBox;
    QFrame *line_2;
    QVBoxLayout *fileBrowseLayout;
    QLabel *fileName;
    QPushButton *fileBrowseButton;
    QVBoxLayout *sliderLayout;
    QLabel *sensiLabel;
    QHBoxLayout *sensitivity;
    QSlider *sensitivitySlider;
    QLCDNumber *sensitivityLCD;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(871, 348);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setFamilies({QString::fromUtf8("Impact")});
        font.setPointSize(48);
        titleLabel->setFont(font);
        titleLabel->setLayoutDirection(Qt::LeftToRight);
        titleLabel->setFrameShape(QFrame::NoFrame);
        titleLabel->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(titleLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        StartStopButton = new QPushButton(centralwidget);
        StartStopButton->setObjectName(QString::fromUtf8("StartStopButton"));
        StartStopButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(StartStopButton);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        IOPickLayout = new QVBoxLayout();
        IOPickLayout->setObjectName(QString::fromUtf8("IOPickLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Impact")});
        font1.setPointSize(12);
        label_2->setFont(font1);

        IOPickLayout->addWidget(label_2);

        inputBox = new QComboBox(centralwidget);
        inputBox->setObjectName(QString::fromUtf8("inputBox"));
        inputBox->setInsertPolicy(QComboBox::NoInsert);
        inputBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        inputBox->setFrame(true);

        IOPickLayout->addWidget(inputBox);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        IOPickLayout->addWidget(label_3);

        outputBox = new QComboBox(centralwidget);
        outputBox->setObjectName(QString::fromUtf8("outputBox"));
        outputBox->setInsertPolicy(QComboBox::NoInsert);
        outputBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        IOPickLayout->addWidget(outputBox);


        horizontalLayout->addLayout(IOPickLayout);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        fileBrowseLayout = new QVBoxLayout();
        fileBrowseLayout->setObjectName(QString::fromUtf8("fileBrowseLayout"));
        fileBrowseLayout->setContentsMargins(-1, 30, -1, 30);
        fileName = new QLabel(centralwidget);
        fileName->setObjectName(QString::fromUtf8("fileName"));

        fileBrowseLayout->addWidget(fileName);

        fileBrowseButton = new QPushButton(centralwidget);
        fileBrowseButton->setObjectName(QString::fromUtf8("fileBrowseButton"));
        fileBrowseButton->setAcceptDrops(false);

        fileBrowseLayout->addWidget(fileBrowseButton);

        fileBrowseLayout->setStretch(0, 1);
        fileBrowseLayout->setStretch(1, 1);

        horizontalLayout->addLayout(fileBrowseLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 5);
        horizontalLayout->setStretch(3, 2);
        horizontalLayout->setStretch(4, 2);

        verticalLayout->addLayout(horizontalLayout);

        sliderLayout = new QVBoxLayout();
        sliderLayout->setObjectName(QString::fromUtf8("sliderLayout"));
        sensiLabel = new QLabel(centralwidget);
        sensiLabel->setObjectName(QString::fromUtf8("sensiLabel"));

        sliderLayout->addWidget(sensiLabel);

        sensitivity = new QHBoxLayout();
        sensitivity->setSpacing(2);
        sensitivity->setObjectName(QString::fromUtf8("sensitivity"));
        sensitivity->setSizeConstraint(QLayout::SetDefaultConstraint);
        sensitivitySlider = new QSlider(centralwidget);
        sensitivitySlider->setObjectName(QString::fromUtf8("sensitivitySlider"));
        sensitivitySlider->setBaseSize(QSize(0, 0));
        sensitivitySlider->setMaximum(100);
        sensitivitySlider->setValue(50);
        sensitivitySlider->setSliderPosition(50);
        sensitivitySlider->setOrientation(Qt::Horizontal);
        sensitivitySlider->setInvertedAppearance(true);
        sensitivitySlider->setInvertedControls(false);
        sensitivitySlider->setTickPosition(QSlider::TicksAbove);
        sensitivitySlider->setTickInterval(10);

        sensitivity->addWidget(sensitivitySlider);

        sensitivityLCD = new QLCDNumber(centralwidget);
        sensitivityLCD->setObjectName(QString::fromUtf8("sensitivityLCD"));
        sensitivityLCD->setSmallDecimalPoint(true);
        sensitivityLCD->setDigitCount(3);
        sensitivityLCD->setSegmentStyle(QLCDNumber::Filled);
        sensitivityLCD->setProperty("value", QVariant(50.000000000000000));
        sensitivityLCD->setProperty("intValue", QVariant(50));

        sensitivity->addWidget(sensitivityLCD);

        sensitivity->setStretch(0, 10);
        sensitivity->setStretch(1, 2);

        sliderLayout->addLayout(sensitivity);

        sliderLayout->setStretch(0, 1);
        sliderLayout->setStretch(1, 3);

        verticalLayout->addLayout(sliderLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);
        verticalLayout->setStretch(2, 2);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Welcome to Voice 2 Noise!", nullptr));
        StartStopButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Input Device", nullptr));
        inputBox->setCurrentText(QString());
        inputBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Select a Device...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Output Device", nullptr));
        outputBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Select a Device...", nullptr));
        fileName->setText(QCoreApplication::translate("MainWindow", "No File Selected...", nullptr));
        fileBrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
        sensiLabel->setText(QCoreApplication::translate("MainWindow", "Sensitivity", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
