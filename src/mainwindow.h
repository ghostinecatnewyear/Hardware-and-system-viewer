#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenuBar;
class OuterFileIncluder;
class QPushButton;
class QLabel;
class WebEngineView;
class AboutWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenuBar          *_menuBar;
    OuterFileIncluder *_stylesIncluder;
    OuterFileIncluder *_scriptsIncluder;
    QPushButton       *_collectDataButton;
    QLabel            *_warningMessage;
    WebEngineView     *_dataVisualizer;
    AboutWindow       *_aboutWindow;

    void initializeMenuBar();

private slots:
    void onCollectData();
    void onExitProgram();
};

#endif // MAINWINDOW_H
