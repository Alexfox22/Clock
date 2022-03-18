#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

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
    QQmlContext* context = engine.rootContext();
        context->setContextProperty("Trigger", &firstClass);
        context->setContextProperty("PrepareData", &secondClass);
    //qDebug() << "I am MAIN " << QThread::currentThread();
    QThread* thread = new QThread();
    Trigger* wow = &firstClass;
    wow->moveToThread(thread);
    QThread::connect( thread, &QThread::started, wow, &Trigger::runThread);
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
