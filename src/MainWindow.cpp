//
// Created by kalle on 10/30/20.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <iomanip>
#include <iostream>
#include <QtCore/QCoreApplication>
#include "MainWindow.h"
#include "TimerThread.h"
#include "config.h"

MainWindow::MainWindow() {
    centralWidget = new QWidget();
    layout = new QVBoxLayout();
    label = new QLabel();

    labelStyle = new QString("font: 40pt; color: %1;");
    labelString = new QString("%1:%2:%3");

    label->setStyleSheet(labelStyle->arg(PAUSED_COLOR));

    layout->addWidget(label);

    this->setWindowFlag(Qt::FramelessWindowHint, true);
    this->setAttribute(Qt::WA_TranslucentBackground);

    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);

    this->timerThread = new TimerThread(QCoreApplication::arguments().at(1).toInt(),
                                        QCoreApplication::arguments().at(2).toInt(),
                                        QCoreApplication::arguments().at(3).toInt());

    connect(timerThread, &TimerThread::timeUpdated, this, &MainWindow::onTimeUpdated);
    connect(timerThread, &TimerThread::changeColor, this, &MainWindow::onChangeColor);
    connect(this, &MainWindow::pauseTimer, timerThread, &TimerThread::onPauseChanged);
    connect(this, &MainWindow::resetTimer, timerThread, &TimerThread::onReset);

    timerThread->start();
}

MainWindow::~MainWindow() {
    this->close();
}

void MainWindow::on_actionExit_triggered() {
    this->close();
}

void MainWindow::onTimeUpdated(TimeData timeData) {
    this->label->setText(QString::fromStdString(padStringLeft(std::to_string(timeData.hours), 2) + ":" + padStringLeft(std::to_string(timeData.minutes), 2) + ":" + padStringLeft(std::to_string(timeData.seconds), 2)));
}

void MainWindow::onChangeColor(char* color) {
    this->label->setStyleSheet(labelStyle->arg(color));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit pauseTimer();
        event->accept();
    } else if (event->button() == Qt::RightButton){
        emit resetTimer();
        event->accept();
    }
}

std::string MainWindow::padStringLeft(const std::string& string, int amount) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw (amount) << string;
    return ss.str();
}
