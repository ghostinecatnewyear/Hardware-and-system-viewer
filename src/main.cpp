#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QPixmap image(":/resources/img/splashscreen.png");
    QSplashScreen splashScreen(image);
    QTime stopwatch;
    const int splashScreenDuration = 3000;
    splashScreen.show();
    stopwatch.start();
    while (stopwatch.elapsed() < splashScreenDuration)
    {
    }

    MainWindow mainWindow;
    mainWindow.show();
    splashScreen.finish(&mainWindow);

    return application.exec();
}
