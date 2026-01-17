#pragma once

#include <QObject>
#include <QPoint>
#include <QUrl>
#include <utility>


class QQmlApplicationEngine;

namespace app
{
class OverlayBase : public QObject {
    Q_OBJECT

public:
    explicit OverlayBase(QUrl modulePath, QObject* parent = nullptr)
        : QObject(parent)
        , m_modulePath(std::move(modulePath))
    {
    }

    ~OverlayBase() override = default;

    Q_INVOKABLE void reload() const;
    Q_INVOKABLE QPoint mousePos() const;

    void setEngine(QQmlApplicationEngine* engine) { m_engine = engine; }

private:
    QUrl m_modulePath;
    QQmlApplicationEngine* m_engine = nullptr;
};
}  // namespace app
