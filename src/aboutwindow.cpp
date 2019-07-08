#include "aboutwindow.h"
#include <QGridLayout>

AboutWindow::AboutWindow(const QString &title)
    : QFrame()
{
    setWindowTitle(title);
    setFixedSize(500, 300);

    QGridLayout *layout = new QGridLayout(this);

    _information.setText("[Информация о программе]");
    layout->addWidget(&_information, 0, 0, 9, 5);

    _closeButton.setText("Закрыть");
    connect(&_closeButton, SIGNAL(clicked()), this, SLOT(hide()));
    layout->addWidget(&_closeButton, 9, 4, 1, 1);
}
