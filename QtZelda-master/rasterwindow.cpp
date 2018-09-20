#include "rasterwindow.h"

RasterWindow::RasterWindow(QWindow *parent)
    : QWindow(parent)
    , m_backingStore(new QBackingStore(this))
{
    setGeometry(100, 100, 300, 200);
}

void RasterWindow::exposeEvent(QExposeEvent *event)
{
    if (isExposed())
        renderNow();
}

void RasterWindow::resizeEvent(QResizeEvent *event)
{
    m_backingStore->resize(event->size());
    if (isExposed())
        renderNow();
}

void RasterWindow::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), Qt::white);
    render(&painter);

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}

void RasterWindow::render(QPainter *painter)
{
    painter->drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "Hello, World!");
}

void RasterWindow::renderLater()
{
    requestUpdate();
}

bool RasterWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest)
    {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}
