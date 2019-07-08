#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>

class AboutWindow : public QFrame
{
public:
    AboutWindow(const QString &title = "О программе");

private:
    QLabel      _information;
    QPushButton _closeButton;
};

#endif // ABOUTWINDOW_H
