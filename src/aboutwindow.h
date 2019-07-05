#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>

class AboutWindow : public QFrame
{
    Q_OBJECT

public:
    AboutWindow(const QString &title = "О программе");
    ~AboutWindow();

private:
    QLabel *_information;
    QPushButton *_closeButton;
};

#endif // ABOUTWINDOW_H
