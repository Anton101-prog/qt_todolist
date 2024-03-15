import QtQuick

Item {
    id: root
    Rectangle {
        color: "white"
        height: windowroot.height / 5
        width: listView.width // Используем listView для определения ширины

        Rectangle {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 1
            color: "black"  // Цвет верхней границы
        }

        Rectangle {
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            height: 1
            color: "black"  // Цвет нижней границы
        }

        Text {
            anchors.centerIn: parent
            text: model.text
        }
    }
}
