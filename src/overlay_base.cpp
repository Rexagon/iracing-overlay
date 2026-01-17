#include "overlay_base.h"

#include <QQmlApplicationEngine>

namespace app
{
void OverlayBase::reload() const
{
    assert(m_engine != nullptr);
    m_engine->load(m_modulePath);
}
}  // namespace app
