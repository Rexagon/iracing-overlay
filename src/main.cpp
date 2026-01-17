#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "pedals_overlay.h"

using namespace app;

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QCoreApplication::addLibraryPath("./");

    QQmlApplicationEngine engine;
    PedalsOverlay overlay;
    overlay.setEngine(&engine);

    engine.rootContext()->setContextProperty("app", &overlay);
    overlay.reload();

    return app.exec();
}
