#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QPixmap image(":/resources/img/splashscreen.png");
    QSplashScreen splashScreen(image);

    int timeIntervalsCounter = 0;
    constexpr int cycleSleepTime = 50;
    constexpr int splashScreenDuration = 3000 / cycleSleepTime;
    splashScreen.show();
    while (timeIntervalsCounter < splashScreenDuration)
    {
        Sleep(cycleSleepTime);
        ++timeIntervalsCounter;
    }

    MainWindow mainWindow;
    mainWindow.show();
    splashScreen.finish(&mainWindow);

    return application.exec();
}
