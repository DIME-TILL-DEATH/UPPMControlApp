import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import CppObjects

Item {
    function setPsFromCb()
    {
        var value = [_cb0.checked, _cb1.checked, _cb2.checked, _cb3.checked, _cb4.checked, _cb5.checked]
        CtrlGui.setPhaseShifter(value);
    }

    Column{
        anchors.fill: parent
        anchors.margins: width/50
        spacing: height/75

        Rectangle{
            height: parent.height*0.15
            width: parent.width

            radius: width/50
            border.width: 1
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                spacing: height/50

                Label{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Установки фильтров:"
                }

                ComboBox{
                    id: _comboFilter

                    anchors.horizontalCenter: parent.horizontalCenter
                    model: ["00", "01", "10", "11"]

                    onAccepted: {
                        filterCode = currentIndex
                    }
                }
            }

        }

        Rectangle{
            height: parent.height*0.3
            width: parent.width

            radius: width/50
            border.width: 1
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: width/5
                spacing: height/10

                GroupBox {
                    title: qsTr("Установки фазовращателя:")

                    anchors.horizontalCenter: parent.horizontalCenter

                    RowLayout {
                        id: _checkGroup

                        anchors.fill: parent
                        CheckBox { id: _cb0; text: "5,625°" }
                        CheckBox { id: _cb1; text: "11,25°" }
                        CheckBox { id: _cb2; text: "22,5°" }
                        CheckBox { id: _cb3; text: "45°" }
                        CheckBox { id: _cb4; text: "90°" }
                        CheckBox { id: _cb5; text: "180°" }
                    }

                    ButtonGroup{
                        buttons: _checkGroup.children
                        exclusive: false

                        onClicked: {
                            setPsFromCb();
                        }
                    }

                }

                Label{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Установленное значение: " + CtrlGui.phaseCode * 5.625 + "°"
                }
            }
        }

        Rectangle{
            height: parent.height*0.15
            width: parent.width

            radius: width/50
            border.width: 1
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: width/5
                spacing: height/10

                Label{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Статус:"
                }

                Label{
                    id: _labelFrameSend

                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "--------"
                }

                Label{
                    id: _labelAckRecieved

                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "--------"
                }
            }
        }

        Item{
            height: parent.height*0.15
            width: parent.width

            Button{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Запись"

                onClicked: {
                    CtrlGui.filterCode = _comboFilter.currentIndex;
                    setPsFromCb();
                    CtrlGui.sendFrame()

                    _labelFrameSend.text = Qt.formatTime(new Date(), "hh:mm:ss") + " <== Кадр отправлен";
                    _labelAckRecieved.text = "--------"
                }
            }
        }
    }

    Connections{
        target: CtrlGui

        function onSgAckRecieved()
        {
             _labelAckRecieved.text = Qt.formatTime(new Date(), "hh:mm:ss") + " ==> Подтверждение получено";
        }
    }
}
