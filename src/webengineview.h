#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWebEngineView>

class WebEngineView : public QWebEngineView
{
    Q_OBJECT

public:
    WebEngineView();

private:
    bool _isPageLoaded = false;

    void updateFarParent();

private slots:
    void onLoadFinished(bool isOk);
};

#endif // WEBENGINEVIEW_H
