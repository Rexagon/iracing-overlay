#pragma once

#include "overlay_base.h"
#include "util.h"

namespace app
{
class PedalsChart;

class PedalsOverlay : public OverlayBase {
    Q_OBJECT

    Q_PROPERTY(int clutch MEMBER m_clutch NOTIFY clutchChanged)
    Q_PROPERTY(int brake MEMBER m_brake NOTIFY brakeChanged)
    Q_PROPERTY(int throttle MEMBER m_throttle NOTIFY throttleChanged)

public:
    explicit PedalsOverlay(QObject* parent = nullptr);

    ~PedalsOverlay() override = default;

    IMPL_PROPERTY(int, clutch, setClutch, clutchChanged, m_clutch)
    IMPL_PROPERTY(int, brake, setBrake, brakeChanged, m_brake)
    IMPL_PROPERTY(int, throttle, setThrottle, throttleChanged, m_throttle)

    Q_INVOKABLE void setPedalsChart(PedalsChart* chart);

    void flushChart();

signals:
    void clutchChanged();
    void brakeChanged();
    void throttleChanged();

private:
    int m_clutch = 0;
    int m_brake = 0;
    int m_throttle = 0;

    PedalsChart* m_chart = nullptr;
};
}  // namespace app
