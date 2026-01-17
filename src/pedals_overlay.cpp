#include "pedals_overlay.h"

namespace app
{

const auto UI_PATH = QStringLiteral("qrc:/qt/qml/Overlay/ui/pedals.qml");

PedalsOverlay::PedalsOverlay(QObject* parent)
    : OverlayBase(QUrl(UI_PATH), parent)
{
}

}  // namespace app
