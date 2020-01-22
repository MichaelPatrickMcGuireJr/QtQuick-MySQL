import QtQuick 2.12
import QtQuick.Window 2.12
import TableModel 0.1

Window {
    visible: true
    width: 902
    height: 480
    title: qsTr("Hello MySQL World")

    TableView {
          anchors.fill: parent
          columnSpacing: 1
          rowSpacing: 1
          clip: true

          model: TableModel {}

          delegate: Rectangle {
              implicitWidth: 300
              implicitHeight: 50
              border.color: "black"
              border.width: 2
              color: (heading==true)?"red":"green"
              Text {
                  text: tabledata
                  font.pointSize: 20
                  anchors.centerIn: parent
              }
          }


}
}
