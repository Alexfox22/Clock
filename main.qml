import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

Window{
    width: 460
    height: 240
    visible: true
    title: qsTr("Time")

    property bool running: true

    RowLayout{
        id: layout
        width: 0.8 * parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 0

        MyText{

            text: PrepareData.hours
        }

        MyText{
            id: firstColon
            text: ":"
        }

        MyText{
            text: PrepareData.minutes
        }

        MyText{
            id: secondColon
            text: ":"
        }

        MyText{
            id: seconds
            text: PrepareData.seconds

        }

        MyText{
            id: format
            text: PrepareData.format
        }
    }

    OpacityAnimator{
        from: 1.0
        to: 0.0
        duration: 600
        target: firstColon
        running: PrepareData.update
    }

    OpacityAnimator{
        from: 1.0
        to: 0.0
        duration: 600
        target: secondColon
        running: PrepareData.update
    }

    MouseArea{
        id: mousearea
        anchors.fill: parent
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                PrepareData.changeFormat()
                Logger.log("Clicked")
            }
        }
    }
}
