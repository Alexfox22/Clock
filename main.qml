import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

Window{
    width: 460
    height: 240
    visible: true
    title: qsTr("Time")

    RowLayout{
        id: layout
        width: 0.8*parent.width
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
            text: PrepareData.seconds
        }

        MyText{
            id: format
            text: PrepareData.format
        }
    }

    OpacityAnimator{
        loops: Animation.Infinite
        from: 1.0
        to: 0.0
        duration:1000
        target: firstColon
        running:true
        onFinished: second.start()
    }

    OpacityAnimator{
        loops: Animation.Infinite
        from: 1.0
        to: 0.0
        duration:1000
        target: secondColon
        running:true
        onFinished: second.start()
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                PrepareData.changeFormat()
            }
        }
    }
}
