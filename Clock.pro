gui_config {
    QT += quick
    #CONFIG += qtc_runnable
    # You can make your code fail to compile if it uses deprecated APIs.
    # In order to do so, uncomment the following line.
    #DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
    CONFIG += c++17
    CONFIG += gui

    SOURCES += \
            logger.cpp \
            main.cpp \
            preparedata.cpp \
            trigger.cpp

    HEADERS += \
        Singletone.h \
        logger.h \
        preparedata.h \
        trigger.h

    RESOURCES += qml.qrc

    # Additional import path used to resolve QML modules in Qt Creator's code model
    QML_IMPORT_PATH =

    # Additional import path used to resolve QML modules just for Qt Quick Designer
    QML_DESIGNER_IMPORT_PATH =

    # Default rules for deployment.
    qnx: target.path = /tmp/$${TARGET}/bin
    else: unix:!android: target.path = /opt/$${TARGET}/bin
    !isEmpty(target.path): INSTALLS += target

    QT_LOGGING_RULES=qml=false
}

test_config {

    TARGET = unit_tests
    QT += testlib

    SOURCES += test.cpp \
               preparedata.cpp

    HEADERS += test.h \
               preparedata.h \
               Singletone.h

    CONFIG += console
}
