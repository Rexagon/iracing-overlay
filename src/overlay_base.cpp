#include "overlay_base.h"

#include <QCursor>
#include <QQmlApplicationEngine>

namespace app
{
void OverlayBase::reload() const
{
    assert(m_engine != nullptr);
    m_engine->load(m_modulePath);
}

QPoint OverlayBase::mousePos() const
{
    return QCursor::pos();
}

}  // namespace app
