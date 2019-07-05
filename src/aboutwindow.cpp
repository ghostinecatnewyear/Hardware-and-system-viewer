#include "aboutwindow.h"
#include <QGridLayout>

AboutWindow::AboutWindow(const QString &title)
{
    setWindowTitle(title);
    setFixedSize(500, 300);

    QGridLayout *layout = new QGridLayout;
    setLayout(layout);

    _information = new QLabel("[Информация о программе]", this);
    layout->addWidget(_information, 0, 0, 9, 5);

    _closeButton = new QPushButton("Закрыть", this);
    connect(_closeButton, SIGNAL(clicked()), this, SLOT(hide()));
    layout->addWidget(_closeButton, 9, 4, 1, 1);
}

AboutWindow::~AboutWindow()
{
    delete _information;
    delete _closeButton;
}
