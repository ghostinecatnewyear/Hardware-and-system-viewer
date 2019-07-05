#include "mainwindow.h"
#include <QApplication>
#include <QGridLayout>
#include "outerfileincluder.h"
#include "datasaver.h"
#include "datacollector.h"
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(750, 550);

    _aboutWindow = new AboutWindow;

    QWidget *centralWidget = new QWidget;
    QGridLayout *layout = new QGridLayout;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    _menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("Файл");
    QAction *exitAction = new QAction("Выход");
    fileMenu->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitProgram()));
    QMenu *referenceMenu = new QMenu("Справка");
    QAction *aboutAction = new QAction("О программе");
    referenceMenu->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered()), _aboutWindow, SLOT(show()));
    _menuBar->addMenu(fileMenu);
    _menuBar->addMenu(referenceMenu);
    layout->addWidget(_menuBar, 0, 0, 1, 6);

    _stylesIncluder = new OuterFileIncluder("Подключение CSS", "*.css");
    layout->addWidget(_stylesIncluder, 1, 0, 1, 3);

    _scriptsIncluder = new OuterFileIncluder("Подключение JavaScript", "*.js");
    layout->addWidget(_scriptsIncluder, 1, 3, 1, 3);

    _collectDataButton = new QPushButton("Собрать данные");
    connect(_collectDataButton, SIGNAL(clicked()), this, SLOT(onCollectData()));
    layout->addWidget(_collectDataButton, 2, 0, 1, 1);

    _warningMessage = new QLabel("Неверный путь к CSS и/или JavaSript файлу!");
    _warningMessage->hide();
    layout->addWidget(_warningMessage, 2, 1, 1, 2);

    _dataVisualizer = new QWebEngineView;
    layout->addWidget(_dataVisualizer, 3, 0, 17, 6);
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

Q_SLOT void MainWindow::onCollectData()
{
    QString stylesFilePath(_stylesIncluder->getPath());
    QString scriptsFilePath(_scriptsIncluder->getPath());
    if ((_stylesIncluder->isActive() && !QFile::exists(stylesFilePath))
            || (_scriptsIncluder->isActive() && !QFile::exists(scriptsFilePath)))
    {
        _warningMessage->show();
        QTimer::singleShot(3000, _warningMessage, SLOT(hide()));
        return;
    }

    QString outFilePath(QFileDialog::getSaveFileName(nullptr, "Сохранение файла", "C:/", "*.html"));
    if (!QFile::exists(outFilePath))
        return;
    bool doIncludeStyles = _stylesIncluder->isActive();
    bool doIncludeScripts = _scriptsIncluder->isActive();
    DataCollector::collectData(outFilePath,
                               stylesFilePath, doIncludeStyles,
                               scriptsFilePath, doIncludeScripts);
    _dataVisualizer->load(QUrl::fromLocalFile(outFilePath));
    _dataVisualizer->show();
}

Q_SLOT void MainWindow::onExitProgram()
{
    QApplication::quit();
}
