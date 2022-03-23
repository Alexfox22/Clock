#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QThread>

#include <trigger.h>
#include <preparedata.h>
#include <logger.h>
#include <Singletone.h>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtFatalMsg:
        Singletone<Logger>::instance()->log_console(localMsg.constData());
        abort();
    default:
        //fprintf("%s\n", msg.toStdString().c_str());
        //fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        Singletone<Logger>::instance()->log_console(localMsg.constData());
        break;
    }
}

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    PrepareData secondClass;
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
        context->setContextProperty("PrepareData", &secondClass);
        context->setContextProperty("Logger", Singletone<Logger>::instance());

       //qInstallMessageHandler(myMessageOutput);
       //Singletone<Logger>::instance()->log_console("wow, it works");
       //Singletone<Logger>::instance()->log_file("myLog.txt", "wow, it works", true);

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

