#include "aboutwindow.h"
#include <QGridLayout>

AboutWindow::AboutWindow(const QString &title)
    : QFrame(),
      _closeButton("Закрыть")
{
    setWindowTitle(title);
    setFixedSize(500, 300);

    QGridLayout *layout = new QGridLayout(this);

    _information.setText("[Информация о программе]");
    layout->addWidget(&_information, 0, 0, 9, 5);

    connect(&_closeButton, &QPushButton::clicked, this, &QFrame::hide);
    layout->addWidget(&_closeButton, 9, 4, 1, 1);
}
