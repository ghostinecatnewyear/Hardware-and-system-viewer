#include "mainwindow.h"
#include <QGridLayout>
#include <QMenu>
#include "aboutwindow.h"
#include <QMenuBar>
#include "outerfileincluder.h"
#include <QPushButton>
#include <QLabel>
#include "webengineview.h"
#include <QTimer>
#include "systemdatacollector.h"
#include <QFileDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _menuBar(new QMenuBar),
      _stylesIncluder(new OuterFileIncluder("Подключение CSS", "*.css")),
      _scriptsIncluder(new OuterFileIncluder("Подключение JavaScript", "*.js")),
      _collectDataButton(new QPushButton("Собрать данные")),
      _warningMessage(new QLabel("Неверный путь к CSS и/или JavaScript файлу!")),
      _dataVisualizer(new WebEngineView),
      _aboutWindow(new AboutWindow)
{
    resize(750, 550);

    auto centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    auto layout = new QGridLayout(centralWidget);

    initializeMenuBar();

    layout->addWidget(_stylesIncluder, 0, 0, 1, 3);

    layout->addWidget(_scriptsIncluder, 0, 3, 1, 3);

    connect(_collectDataButton, &QPushButton::clicked, this, &MainWindow::onCollectData);
    layout->addWidget(_collectDataButton, 1, 0, 1, 1);

    _warningMessage->hide();
    layout->addWidget(_warningMessage, 1, 1, 1, 2);

    layout->addWidget(_dataVisualizer, 2, 0, 9, 6);
}

MainWindow::~MainWindow()
{
    delete _menuBar;
    delete _stylesIncluder;
    delete _scriptsIncluder;
    delete _collectDataButton;
    delete _warningMessage;
    delete _dataVisualizer;
    delete _aboutWindow;
}

void MainWindow::initializeMenuBar()
{
    auto fileMenu = new QMenu("Файл");

    auto exitAction = new QAction("Выход");
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitProgram);
    fileMenu->addAction(exitAction);

    auto referenceMenu = new QMenu("Справка");

    auto aboutAction = new QAction("О программе");
    connect(aboutAction, &QAction::triggered, _aboutWindow, &AboutWindow::show);
    referenceMenu->addAction(aboutAction);

    _menuBar->addMenu(fileMenu);
    _menuBar->addMenu(referenceMenu);
    QLayout *layout = this->layout();
    layout->setMenuBar(_menuBar);
}

Q_SLOT void MainWindow::onCollectData()
{
    QString stylesFilePath(_stylesIncluder->getPath());
    QString scriptsFilePath(_scriptsIncluder->getPath());
    if ((_stylesIncluder->isActive() && !QFile::exists(stylesFilePath))
            || (_scriptsIncluder->isActive() && !QFile::exists(scriptsFilePath)))
    {
        _warningMessage->show();
        QTimer::singleShot(2000, _warningMessage, SLOT(hide()));
        return;
    }

    if (!_stylesIncluder->isActive())
        stylesFilePath.clear();
    if (!_scriptsIncluder->isActive())
        scriptsFilePath.clear();
    QString outFilePath(QFileDialog::getSaveFileName(nullptr, "Сохранение файла", "C:\\", "*.html"));
    SystemDataCollector::collectData(outFilePath, stylesFilePath, scriptsFilePath);
    _dataVisualizer->load(outFilePath);
}

Q_SLOT void MainWindow::onExitProgram()
{
    QApplication::quit();
}
