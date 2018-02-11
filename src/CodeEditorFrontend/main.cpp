#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QProcess>
#include <QQmlContext>
#include "simulatordownloader.h"

int main(int argc, char *argv[])
{
    SimulatorDownloader simulatorDownloader;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("simulatorDownloader", &simulatorDownloader);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
