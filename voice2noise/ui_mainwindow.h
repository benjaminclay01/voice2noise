/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 250);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Impact")});
        font.setPointSize(48);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        StartStopButton = new QPushButton(centralwidget);
        StartStopButton->setObjectName("StartStopButton");
        StartStopButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(StartStopButton);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line);

        IOPickLayout = new QVBoxLayout();
        IOPickLayout->setObjectName("IOPickLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Impact")});
        font1.setPointSize(12);
        label_2->setFont(font1);

        IOPickLayout->addWidget(label_2);

        inputBox = new QComboBox(centralwidget);
        inputBox->setObjectName("inputBox");
        inputBox->setInsertPolicy(QComboBox::InsertAtTop);
        inputBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        inputBox->setFrame(true);

        IOPickLayout->addWidget(inputBox);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        IOPickLayout->addWidget(label_3);

        outputBox = new QComboBox(centralwidget);
        outputBox->setObjectName("outputBox");
        outputBox->setInsertPolicy(QComboBox::InsertAtTop);
        outputBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        IOPickLayout->addWidget(outputBox);


        horizontalLayout->addLayout(IOPickLayout);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_2);

        fileBrowseLayout = new QVBoxLayout();
        fileBrowseLayout->setObjectName("fileBrowseLayout");
        fileBrowseLayout->setContentsMargins(-1, 30, -1, 30);
        fileName = new QLabel(centralwidget);
        fileName->setObjectName("fileName");
        fileName->setAlignment(Qt::AlignCenter);

        fileBrowseLayout->addWidget(fileName);

        fileBrowseButton = new QPushButton(centralwidget);
        fileBrowseButton->setObjectName("fileBrowseButton");

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

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Welcome to Voice 2 Noise!", nullptr));
        StartStopButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Input Device", nullptr));
        inputBox->setCurrentText(QString());
        inputBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Select a Device...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Output Device", nullptr));
        outputBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Select a Device...", nullptr));
        fileName->setText(QCoreApplication::translate("MainWindow", "No File Selected...", nullptr));
        fileBrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
