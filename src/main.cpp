#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <atomic>
#include <chrono>
#include <thread>

#include "pedals_overlay.h"

using namespace app;

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QCoreApplication::addLibraryPath("./");

    QQmlApplicationEngine engine;
    PedalsOverlay overlay;
    overlay.setEngine(&engine);

    engine.rootContext()->setContextProperty("overlay", &overlay);
    overlay.reload();

    std::atomic_bool isRunning{true};
    std::thread provideInput([&overlay, &isRunning] {
        const auto screenSize = QGuiApplication::primaryScreen()->geometry();

        const auto interval = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / 60;

        auto now = std::chrono::steady_clock::now();
        while (isRunning.load(std::memory_order_relaxed)) {
            // TEMP
            const auto mousePos = overlay.mousePos();
            overlay.setBrake(static_cast<int>(mousePos.x() * 100 / (screenSize.width() - 1)));
            overlay.setThrottle(static_cast<int>(mousePos.y() * 100 / (screenSize.height() - 1)));

            overlay.flushChart();

            now += interval;
            std::this_thread::sleep_until(now);
        }
    });

    const auto res = app.exec();
    isRunning.store(false, std::memory_order_relaxed);
    provideInput.join();

    return res;
}
