//
// Created by kalle on 10/30/20.
//

#ifndef TIMER_MAINWINDOW_H
#define TIMER_MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QMouseEvent>
#include "TimerThread.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow() override;
    void mousePressEvent(QMouseEvent *event);

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QLabel *label;
    TimerThread *timerThread;
    QString *labelStyle;
    QString *labelString;

private slots:
    void on_actionExit_triggered();
    void onTimeUpdated(TimeData);
    void onChangeColor(char*);
    static std::string padStringLeft(const std::string&, int);

signals:
    void pauseTimer();
    void resetTimer();

};


#endif //TIMER_MAINWINDOW_H
