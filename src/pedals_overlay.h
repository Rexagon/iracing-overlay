#pragma once

#include "overlay_base.h"

namespace app
{
class PedalsOverlay : public OverlayBase {
    Q_OBJECT

    Q_PROPERTY(int clutch MEMBER m_clutch NOTIFY clutchChanged)
    Q_PROPERTY(int brake MEMBER m_brake NOTIFY brakeChanged)
    Q_PROPERTY(int throttle MEMBER m_throttle NOTIFY throttleChanged)

public:
    explicit PedalsOverlay(QObject* parent = nullptr);

    ~PedalsOverlay() override = default;

#define IMPL_PROPERTY(type, prop, setProp, propChanged, member) \
    type prop() const { return member; }                        \
    void setProp(type value)                                    \
    {                                                           \
        if (value == member) {                                  \
            return;                                             \
        }                                                       \
        member = value;                                         \
        emit propChanged();                                     \
    }

    IMPL_PROPERTY(int, clutch, setClutch, clutchChanged, m_clutch)
    IMPL_PROPERTY(int, brake, setBrake, brakeChanged, m_brake)
    IMPL_PROPERTY(int, throttle, setThrottle, throttleChanged, m_throttle)

signals:
    void clutchChanged();
    void brakeChanged();
    void throttleChanged();

private:
    int m_clutch = 50;
    int m_brake = 0;
    int m_throttle = 0;
};
}  // namespace app
