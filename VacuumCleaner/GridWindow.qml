import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    id: root
    visible: true
    width: 360
    height: 500
    Column{
        Repeater{
            model: getRowsNumber(root.height)
            delegate: Row{
                property int externalIdx: index
                Repeater{
                    model: getColumnsNumber(root.width)
                    delegate: Rectangle{
                        property bool selected: false
                        property color originalColor: (index + externalIdx) % 2 == 0 ? "black" : "white"

                        width:20
                        height: 20
                        color: selected ? "red" : originalColor
                        border.width: 1
                        border.color: "black"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: parent.selected = !parent.selected
                        }
                    }
                }
            }
        }
    }

    function getColumnsNumber(width){
        return width/20;
    }
    function getRowsNumber(height){
        return height/20;
    }
}
