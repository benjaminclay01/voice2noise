#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "backend/AudioHandler.h"
#include "backend/MP3Player.h"
#include <QString>
#include <QFileDialog>
#include <QSettings>

//global audio handler object
AudioHandler audio;
MP3Player player;

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
    connect(ui->sensitivitySlider, &QSlider::valueChanged, this, &MainWindow::sensitivityUpdate);

    //read settings
    readSettings();
}

void MainWindow::startStop(){
    //set up MP3 file
    std::string filePath = this->mp3Path.toStdString();
    player.loadMP3(filePath);

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

void MainWindow::sensitivityUpdate(){
    int Sens = ui->sensitivitySlider->value();
    ui->sensitivityLCD->display(Sens);
    audio.setThreshold(Sens);
}

void MainWindow::writeSettings(){
    QSettings settings("CaptBucket", "voice2noise");
    //save sensitivity
    settings.setValue("sensitivity", this->ui->sensitivitySlider->value());

    //save file pick
    if(!this->mp3Path.isEmpty()){
        settings.setValue("audioFile", this->mp3Path);
    }

    //save I/O IDs and Names
    settings.beginGroup("Devices");
    settings.setValue("inputID", this->inputID);
    settings.setValue("inputName", this->ui->inputBox->itemText(this->inputID));
    settings.setValue("outputID", this->outputID);
    settings.setValue("outputName", this->ui->outputBox->itemText(this->outputID));
    settings.endGroup();
}

void MainWindow::readSettings(){
    //set sensitivity
    QSettings settings("CaptBucket", "voice2noise");
    this->ui->sensitivitySlider->setValue(settings.value("sensitivity", 16).toInt());

    //set file pick
    this->mp3Path = settings.value("audioFile").toString();
    if(this->mp3Path.isEmpty()){
        this->ui->fileName->setText("No File Selected...");
    } else {
        size_t fileNameBegin = mp3Path.toStdString().find_last_of('/');
        QString fileName = QString::fromStdString(mp3Path.toStdString().substr(fileNameBegin + 1));
        this->ui->fileName->setText(fileName);
    }

    //set IDs and Names if they match in the new device list
    settings.beginGroup("Devices");
    QString oldDevice = settings.value("inputName", "").toString();
    if(this->ui->inputBox->itemText(settings.value("inputID", -1).toInt()) == oldDevice){
        this->ui->inputBox->setCurrentIndex(settings.value("inputID").toInt());
        this->inputID = settings.value("inputID").toInt();
    }
    oldDevice = settings.value("outputName", "").toString();
    if(this->ui->outputBox->itemText(settings.value("outputID", -1).toInt()) == oldDevice){
        this->ui->outputBox->setCurrentIndex(settings.value("outputID").toInt());
        this->outputID = settings.value("outputID").toInt();
    }
    settings.endGroup();
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete ui;
}

