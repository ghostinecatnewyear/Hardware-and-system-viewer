#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "outerfileincluder.h"
#include <QPushButton>
#include <QWebEngineView>
#include "aboutwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QMenuBar          _menuBar;
    OuterFileIncluder _stylesIncluder;
    OuterFileIncluder _scriptsIncluder;
    QPushButton       _collectDataButton;
    QLabel            _warningMessage;
    QWebEngineView    _dataVisualizer;
    AboutWindow       _aboutWindow;

private slots:
    void onCollectData();
    void onExitProgram();
};

#endif // MAINWINDOW_H
