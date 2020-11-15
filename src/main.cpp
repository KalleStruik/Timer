#include <QtWidgets/QApplication>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Usage: timer <hours> <minutes> <seconds>" << std::endl;
        return 1;
    }

    qRegisterMetaType<TimeData>("TimeData");

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}


