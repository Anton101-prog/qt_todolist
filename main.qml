import QtQuick
import QtQuick.Controls
import org.mydb 1.0
Window {
    id: windowroot
    visible: true
    color: "gray"

    MyDataBase {
        id: mydb
    }

    Page {
        signal newMessage(string msg)
        id: page
        anchors.fill: parent
        header: Rectangle {
            anchors.bottomMargin: 10
            height: windowroot.height / 6
            width: windowroot.width
            border.color: "gray"
            border.width: 0.5

            TextArea {
                id: textArea
                height: parent.height * 0.85
                placeholderText: "Введите текст: "
                wrapMode: Text.Wrap
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                // Keys.enabled: {

                // }

            }


        }


        footer: Rectangle {

            height: windowroot.height / 4
            width: windowroot.width
            Button {
                anchors.fill: parent

                text: "Добавить +"
                onClicked: {
                    if (textArea.text !== ''){
                        // textArea.clear()

                        page.newMessage(textArea.text)
                        mydb.insertItemDataBase(textArea.text);
                        console.log(mydb.countRowDataBase());
                        listView.positionViewAtEnd();
                        textArea.clear();
                    }


                }
            }
        }


        ListView {
            id: listView
            anchors.fill: parent
            model: listModel
            spacing: 10
            clip: true
            verticalLayoutDirection: ListView.BottomToTop


            delegate: Rectangle {
                color: "white"
                height: windowroot.height / 6
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
                    width: listView.width-20

                    anchors.centerIn: parent
                    text: model.text
                    wrapMode: Text.Wrap                }
            }


        }
        ListModel {
            id: listModel

            signal itemInserted(string text)

            Component.onCompleted: {
                loadFromDatabase();
            }

            function loadFromDatabase() {
                var rowCount = mydb.countRowDataBase();
                for (let i = 0; i < rowCount; ++i){
                    var data = mydb.getItemDataBase(i); // i + 1?
                    append({text: data});
                }
            }

        }
        onNewMessage: {
            var newMsg = {};
            newMsg.text = msg
            listModel.append(newMsg);
        }
    }


}
