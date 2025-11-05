#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "backend/AudioHandler.h"
#include "backend/MP3Player.h"
#include <QString>
#include <QFileDialog>

//global audio handler object
AudioHandler audio;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Populate device lists
    auto device_list = audio.listDevices();
    for(const auto& d : device_list){
        std::string listing = std::to_string(d.id) + ": " + d.name;
        ui->inputBox->addItem(QString::fromStdString(listing));
        ui->outputBox->addItem(QString::fromStdString(listing));
    }

    //connect buttons to actions
    connect(ui->StartStopButton, &QPushButton::clicked, this, &MainWindow::startStop);
    connect(ui->inputBox, &QComboBox::activated, this,  &MainWindow::setInputDevice);
    connect(ui->outputBox, &QComboBox::activated, this,  &MainWindow::setOutputDevice);
    connect(ui->fileBrowseButton, &QPushButton::clicked, this, &MainWindow::setMP3File);
}

void MainWindow::startStop(){
    //set up MP3 file
    std::string filePath = this->mp3Path.toStdString();
    MP3Player player(filePath);

    //ensure fields are valid
    if(inputID == -1){
        this->ui->StartStopButton->setText("Select input device!");
        return;
    }else if(outputID == -1){
        this->ui->StartStopButton->setText("Select output device!");
        return;
    }else if(mp3Path.isEmpty()){
        this->ui->StartStopButton->setText("Select mp3!");
        return;
    } else {
        if(!player.isLoaded()){
            this->ui->StartStopButton->setText("Error setting up MP3 file!");
            return;
        }
    }

    //if all checks pass, start audio processing
    if(!this->active && audio.openStream(this->inputID, this->outputID, &player)){
         audio.start();
         this->ui->StartStopButton->setText("Active! Press to stop.");
         //lock fields
         this->ui->inputBox->setDisabled(true);
         this->ui->outputBox->setDisabled(true);
         this->ui->fileBrowseButton->setDisabled(true);
         this->active = true;

    } else if(this->active){
        audio.stop();
        this->ui->StartStopButton->setText("Start");
        //unlock fields
        this->ui->inputBox->setDisabled(false);
        this->ui->outputBox->setDisabled(false);
        this->ui->fileBrowseButton->setDisabled(false);
        this->active = false;
    }
}

void MainWindow::setInputDevice(int id){
    this->inputID = id;
}

void MainWindow::setOutputDevice(int id){
    this->outputID = id;
}

void MainWindow::setMP3File(){
    this->mp3Path = QFileDialog::getOpenFileName(this, tr("Select your new voice!"),"/home", tr("MP3(*.mp3)"));
    if(!mp3Path.isEmpty()){
        size_t fileNameBegin = mp3Path.toStdString().find_last_of('/');
        QString fileName = QString::fromStdString(mp3Path.toStdString().substr(fileNameBegin + 1));
        this->ui->fileName->setText(fileName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

