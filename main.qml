import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
//import Trigger 1.0
//import PrepareData 1.0

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
        id: qwerty
        loops: Animation.Infinite
        from: 1.0
        to: 0.0
        duration:1000
        target: firstColon
        running: true
    }
    Text
    {
        id: mytesttext
        text: "meow"
    }
    State {
            name: "brighter"; when: true
            PropertyChanges { target: mytesttext; text: "wow" }
        }


    OpacityAnimator{
        id: animator
        loops: Animation.Infinite
        from: 1.0
        to: 0.0
        duration:1000
        target: secondColon
        running: true
    }

    State {
                name: "clicked"
                when: PrepareData.update
                PropertyChanges { target: animator;  loops: Animation.Infinite }
            }
   // MouseArea{
   //     id: mousearea
   //     anchors.fill: parent
//
    //    onClicked: {
     //       if (mouse.button == Qt.LeftButton) {
     //           PrepareData.changeFormat()
     //       }
     //   }
   // }
}
