#include "aboutwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

AboutWindow::AboutWindow(const QString &title)
    : QFrame(),
      _information(new QLabel), _closeButton(new QPushButton("Закрыть"))
{
    setWindowTitle(title);
    setFixedSize(500, 300);

    auto layout = new QGridLayout(this);

    _information->setText("[Информация о программе]");
    layout->addWidget(_information, 0, 0, 9, 5);

    connect(_closeButton, &QPushButton::clicked, this, &QFrame::hide);
    layout->addWidget(_closeButton, 9, 4, 1, 1);
}

AboutWindow::~AboutWindow()
{
    delete _information;
    delete _closeButton;
}
