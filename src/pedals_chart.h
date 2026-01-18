#pragma once

#include <QColor>
#include <QtQuick/QQuickPaintedItem>
#include <mutex>
#include <vector>

#include "util.h"

namespace app
{

struct PedalsChartPoint {
    int clutch;
    int brake;
    int throttle;
};

class PedalsChart : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QColor clutchColor READ clutchColor WRITE setClutchColor FINAL)
    Q_PROPERTY(QColor brakeColor READ brakeColor WRITE setBrakeColor FINAL)
    Q_PROPERTY(QColor throttleColor READ throttleColor WRITE setThrottleColor FINAL)
    QML_ELEMENT

public:
    explicit PedalsChart(QQuickItem* parent = nullptr);
    ~PedalsChart() override = default;

    IMPL_PROPERTY(QColor, clutchColor, setClutchColor, clutchColorChanged, m_clutchColor)
    IMPL_PROPERTY(QColor, brakeColor, setBrakeColor, brakeColorChanged, m_brakeColor)
    IMPL_PROPERTY(QColor, throttleColor, setThrottleColor, throttleColorChanged, m_throttleColor)

    void addPoint(PedalsChartPoint point);

    void paint(QPainter* painter) override;

signals:
    void clutchColorChanged();
    void brakeColorChanged();
    void throttleColorChanged();

    void updateRequested();

private:
    void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;


    int m_pointCount = 0;
    qreal m_width = 0;
    qreal m_height = 0;

    QColor m_clutchColor;
    QColor m_brakeColor;
    QColor m_throttleColor;

    std::vector<QPointF> m_clutchLines{};
    std::vector<QPointF> m_brakeLines{};
    std::vector<QPointF> m_throttleLines{};

    std::mutex m_pointsMutex;
};

}  // namespace app
