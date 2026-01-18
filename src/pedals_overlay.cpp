#include "pedals_overlay.h"

#include "pedals_chart.h"

namespace app
{

const auto UI_PATH = QStringLiteral("qrc:/qt/qml/Overlay/ui/pedals.qml");

PedalsOverlay::PedalsOverlay(QObject* parent)
    : OverlayBase(QUrl(UI_PATH), parent)
{
}

void PedalsOverlay::setPedalsChart(PedalsChart* chart)
{
    m_chart = chart;
}

void PedalsOverlay::flushChart()
{
    if (!m_chart) {
        return;
    }

    m_chart->addPoint(PedalsChartPoint{
        .clutch = m_clutch,
        .brake = m_brake,
        .throttle = m_throttle,
    });
}

}  // namespace app
