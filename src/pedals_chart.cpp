#include "pedals_chart.h"

#include <QPainter>

namespace app
{
namespace
{
void resetLines(std::vector<QPointF>& lines, int pointCount, qreal width, qreal height)
{
    const qreal step = width / pointCount;

    lines.clear();
    lines.resize(pointCount * 2, QPoint{});
    for (int point = 0; point < pointCount; ++point) {
        const auto i = point * 2;
        lines[i].setX(point * step);
        lines[i].setY(height);
        lines[i + 1].setX((point + 1) * step);
        lines[i + 1].setY(height);
    }
}

void shiftLines(std::vector<QPointF>& lines, int pointCount, qreal width, qreal height, int value)
{
    const qreal step = width / pointCount;

    assert(lines.size() == pointCount * 2);

    for (int point = 0; point < pointCount - 1; ++point) {
        const auto i = point * 2;
        lines[i].setX(point * step);
        lines[i].setY(lines[i + 2].ry());
        lines[i + 1].setX((point + 1) * step);
        lines[i + 1].setY(lines[i + 3].ry());
    }

    const auto i = (pointCount - 1) * 2;
    lines[i].setX((pointCount - 1) * step);
    lines[i].setY(lines[i + 1].ry());
    lines[i + 1].setX(width);
    lines[i + 1].setY(height - height * qreal(value) / 100.0);
}
}  // namespace

PedalsChart::PedalsChart(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    connect(this, SIGNAL(updateRequested()), this, SLOT(update()), Qt::QueuedConnection);
}

void PedalsChart::addPoint(PedalsChartPoint point)
{
    if (m_pointCount < 1) {
        return;
    }

    const auto _lock = std::unique_lock<std::mutex>(m_pointsMutex);

    shiftLines(m_clutchLines, m_pointCount, m_width, m_height, point.clutch);
    shiftLines(m_brakeLines, m_pointCount, m_width, m_height, point.brake);
    shiftLines(m_throttleLines, m_pointCount, m_width, m_height, point.throttle);

    emit updateRequested();
}

void PedalsChart::paint(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    const auto _lock = std::unique_lock<std::mutex>(m_pointsMutex);

    if (!m_clutchLines.empty()) {
        QPen pen(m_clutchColor, 2);
        painter->setPen(pen);
        painter->drawLines(m_clutchLines.data(), m_clutchLines.size() / 2);
    }
    if (!m_brakeLines.empty()) {
        QPen pen(m_brakeColor, 2);
        painter->setPen(pen);
        painter->drawLines(m_brakeLines.data(), m_brakeLines.size() / 2);
    }
    if (!m_throttleLines.empty()) {
        QPen pen(m_throttleColor, 2);
        painter->setPen(pen);
        painter->drawLines(m_throttleLines.data(), m_throttleLines.size() / 2);
    }
}

void PedalsChart::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    const auto width = newGeometry.width();
    const auto height = newGeometry.height();
    if (width <= 1.0 || height <= 1.0) {
        return;
    }
    m_width = width;
    m_height = height;

    m_pointCount = ceil(width);

    resetLines(m_clutchLines, m_pointCount, width, height);
    resetLines(m_brakeLines, m_pointCount, width, height);
    resetLines(m_throttleLines, m_pointCount, width, height);
}

}  // namespace app
