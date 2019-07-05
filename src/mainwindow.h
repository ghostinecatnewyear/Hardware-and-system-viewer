#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QWebEngineView>
#include <QPushButton>
#include "aboutwindow.h"
#include "outerfileincluder.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenuBar *_menuBar;
    OuterFileIncluder *_stylesIncluder;
    OuterFileIncluder *_scriptsIncluder;
    QPushButton *_collectDataButton;
    QLabel *_warningMessage;
    QWebEngineView *_dataVisualizer;
    AboutWindow *_aboutWindow;

private slots:
    void onCollectData();
    void onExitProgram();
};

#endif // MAINWINDOW_H
