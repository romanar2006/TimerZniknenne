#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    currentTimeTimer = new QTimer(this);
    opacityEffect = new QGraphicsOpacityEffect(this);
    ui->labelToRemove->setGraphicsEffect(opacityEffect);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->resumeButton, &QPushButton::clicked, this, &MainWindow::resumeTimer);
    connect(currentTimeTimer, &QTimer::timeout, this, &MainWindow::updateCurrentTime);

    animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setDuration(10000);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);

    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::fadeOut);

    currentTimeTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    int minutes = ui->timeEdit->time().minute();
    int seconds = ui->timeEdit->time().second();
    timeLeft = QTime(0, minutes, seconds);
    timer->start(1000); // Запуск таймера с интервалом в 1 секунду
}

void MainWindow::updateTimer()
{
    if (timeLeft == QTime(0, 0, 0)) {
        timer->stop();
        ui->label->setText("Time's up!");
    } else {
        timeLeft = timeLeft.addSecs(-1);
        ui->label->setText(timeLeft.toString("mm:ss"));
    }
}

void MainWindow::stopTimer()
{
    timer->stop();
}

void MainWindow::resumeTimer()
{
    timer->start(1000);
}

void MainWindow::updateCurrentTime()
{
    ui->currentTimeLabel->setText("Сейчас " + QTime::currentTime().toString("hh:mm:ss"));
}

void MainWindow::fadeOut()
{
    animation->start();
}
