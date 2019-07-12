#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QFrame>

class QLabel;
class QPushButton;

class AboutWindow : public QFrame
{
public:
    AboutWindow(const QString &title = "О программе");
    ~AboutWindow();

private:
    QLabel      *_information;
    QPushButton *_closeButton;
};

#endif // ABOUTWINDOW_H
