#include "mainwindow.h"
#include <QApplication>
#include <QGridLayout>
#include "outerfileincluder.h"
#include "datacollector.h"
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(750, 550);

    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    QGridLayout *layout = new QGridLayout(centralWidget);

    QMenu *fileMenu = new QMenu("Файл");
    QAction *exitAction = new QAction("Выход");
    fileMenu->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitProgram()));
    QMenu *referenceMenu = new QMenu("Справка");
    QAction *aboutAction = new QAction("О программе");
    referenceMenu->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered()), &_aboutWindow, SLOT(show()));
    _menuBar.addMenu(fileMenu);
    _menuBar.addMenu(referenceMenu);
    layout->setMenuBar(&_menuBar);

    _stylesIncluder.setTitle("Подключение CSS");
    _stylesIncluder.setExtensionFilter("*.css");
    layout->addWidget(&_stylesIncluder, 0, 0, 1, 3);

    _scriptsIncluder.setTitle("Подключение JavaScript");
    _scriptsIncluder.setExtensionFilter("*.js");
    layout->addWidget(&_scriptsIncluder, 0, 3, 1, 3);

    _collectDataButton.setText("Собрать данные");
    connect(&_collectDataButton, SIGNAL(clicked()), this, SLOT(onCollectData()));
    layout->addWidget(&_collectDataButton, 1, 0, 1, 1);

    _warningMessage.setText("Неверный путь к CSS и/или JavaScript файлу!");
    _warningMessage.hide();
    layout->addWidget(&_warningMessage, 1, 1, 1, 2);

    layout->addWidget(&_dataVisualizer, 2, 0, 18, 6);

}

Q_SLOT void MainWindow::onCollectData()
{
    QString stylesFilePath(_stylesIncluder.getPath());
    QString scriptsFilePath(_scriptsIncluder.getPath());
    if ((_stylesIncluder.isActive() && !QFile::exists(stylesFilePath))
            || (_scriptsIncluder.isActive() && !QFile::exists(scriptsFilePath)))
    {
        _warningMessage.show();
        QTimer::singleShot(2000, &_warningMessage, SLOT(hide()));
        return;
    }

    QString outFilePath(QFileDialog::getSaveFileName(nullptr, "Сохранение файла", "C:/", "*.html"));
    DataCollector::collectData(outFilePath,
                               stylesFilePath,  _stylesIncluder.isActive(),
                               scriptsFilePath, _scriptsIncluder.isActive());
    _dataVisualizer.load(QUrl::fromLocalFile(outFilePath));
    _dataVisualizer.show();
}

Q_SLOT void MainWindow::onExitProgram()
{
    QApplication::quit();
}
