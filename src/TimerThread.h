//
// Created by kalle on 11/15/20.
//

#ifndef TIMER_TIMERTHREAD_H
#define TIMER_TIMERTHREAD_H


#include <QtCore/QThread>
#include "Structs.h"

class TimerThread : public QThread {
    Q_OBJECT

public:
    explicit TimerThread(int hours, int minutes, int seconds);
    [[noreturn]] void run() override;

public slots:
    void onPauseChanged();
    void onReset();

private:
    TimeData initialTimeData{};
    TimeData timeDate{};
    bool paused;

signals:
    void timeUpdated(TimeData);
    void changeColor(char*);
};


#endif //TIMER_TIMERTHREAD_H
