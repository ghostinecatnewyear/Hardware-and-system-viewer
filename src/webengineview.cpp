#include "webengineview.h"

WebEngineView::WebEngineView()
    : QWebEngineView()
{
    setPage(&_page);
    connect(&_page, &QWebEnginePage::loadFinished, this, &WebEngineView::onLoadFinished);
}

void WebEngineView::updateFarParent()
{
    QWidget *widget = nullptr;
    QWidget *next   = this;

    while (next != nullptr)
    {
        widget = next;
        next   = next->parentWidget();
    }

    widget->update();
}

Q_SLOT void WebEngineView::onLoadFinished(bool isOk)
{
    if (isOk)
    {
        show();
        hide();
        show();
        updateFarParent();
        _isPageLoaded = true;
    }
    else if (!_isPageLoaded)
    {
        hide();
    }
}
