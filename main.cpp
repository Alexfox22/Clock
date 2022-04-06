#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QThread>
#include <trigger.h>
#include <preparedata.h>
#include <logger.h>
#include <Singletone.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    if (argc > 1)
    {
        Singletone<Logger>::instance()->setMode(Logger::FILE, argv[1]);
    }
    PrepareData secondClass;
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
       context->setContextProperty("PrepareData", &secondClass);
       context->setContextProperty("Logger", Singletone<Logger>::instance());

       QTime time = QTime::currentTime();
       Singletone<Logger>::instance()->log("Time start ", time);
       //Singletone<Logger>::instance()->setMode(Logger::CONSOLE);

       Trigger* thread = new Trigger();
       PrepareData* pointer = &secondClass;
       Trigger::connect(thread, &Trigger::sendSignal, pointer, &PrepareData::receiveSignal);
       Trigger::connect(pointer, &PrepareData::exit_proc, thread, &Trigger::getSignal);
       Trigger::connect(thread, &Trigger::finished, thread, &Trigger::deleteLater);
       thread->start();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

