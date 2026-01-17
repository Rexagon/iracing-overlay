#pragma once

#include "overlay_base.h"

namespace app
{
class PedalsOverlay : public OverlayBase {
    Q_OBJECT

public:
    explicit PedalsOverlay(QObject* parent = nullptr);

    ~PedalsOverlay() override = default;
};
}  // namespace app
