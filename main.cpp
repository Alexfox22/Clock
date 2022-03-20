#include <QGuiApplication>
#include <QQmlContext>
#include <QThread>
#include <QQmlApplicationEngine>

#include <trigger.h>
#include <preparedata.h>

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Trigger firstClass;
    PrepareData secondClass;
    QQmlApplicationEngine engine;
    //qmlRegisterType<Trigger>("Trigger", 1, 0, "Trigger");
    //qmlRegisterType<PrepareData>("PrepareData", 1, 0, "PrepareData");
    QQmlContext* context = engine.rootContext();
        context->setContextProperty("Trigger", &firstClass);
        context->setContextProperty("PrepareData", &secondClass);
    //qDebug() << "I am MAIN " << QThread::currentThread();
    QThread* thread = new QThread();
    Trigger* pointer = &firstClass;
    pointer->moveToThread(thread);
    QThread::connect(thread, &QThread::started, pointer, &Trigger::runThread);
    thread->start();
    QObject::connect(&firstClass, &Trigger::sendSignal,
                   &secondClass, &PrepareData::receiveSignal);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
