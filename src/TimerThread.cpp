//
// Created by kalle on 11/15/20.
//

#include "TimerThread.h"
#include "config.h"

TimerThread::TimerThread(int hours, int minutes, int seconds) {
    initialTimeData.seconds = seconds;
    initialTimeData.minutes = minutes;
    initialTimeData.hours = hours;

    timeDate.seconds = seconds;
    timeDate.minutes = minutes;
    timeDate.hours = hours;

    paused = true;
}

void TimerThread::onPauseChanged() {
    paused = !paused;
    if (paused)
        emit changeColor(PAUSED_COLOR);
    else
        emit changeColor(RUNNING_COLOR);
}

void TimerThread::onReset() {
    paused = true;
    emit changeColor(PAUSED_COLOR);

    timeDate.seconds = initialTimeData.seconds;
    timeDate.minutes = initialTimeData.minutes;
    timeDate.hours = initialTimeData.hours;
    emit timeUpdated(timeDate);
}

[[noreturn]] void TimerThread::run() {
    while (true) {
        emit timeUpdated(timeDate);

        sleep(1);

        if (paused)
            continue;

        if (timeDate.seconds != 0) {
            timeDate.seconds--;
            continue;
        }
        timeDate.seconds = 59;

        if (timeDate.minutes != 0) {
            timeDate.minutes--;
            continue;
        }
        timeDate.minutes = 59;

        if  (timeDate.hours != 0) {
            timeDate.hours--;
            continue;
        }

        paused = true;
        timeDate.seconds = 0;
        timeDate.minutes = 0;
        timeDate.hours = 0;

        emit changeColor(DONE_COLOR);
    }
}




