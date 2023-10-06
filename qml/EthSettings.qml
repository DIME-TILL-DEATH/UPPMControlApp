import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import CppObjects

Item {
    function acceptChanges()
    {
        var conversionResult = EthGui.setDstIp(_dstIpField.text);
        if(conversionResult) EthGui.selectItf(_itfList.selectedItfName);
    }

    Column{

        anchors.fill: parent
        anchors.margins: width/50

        spacing: height/75

        Rectangle{
            height: parent.height*0.1
            width: parent.width

            radius: width/50
            border.width: 1
            Text {
                id: _sampletext
                text: qsTr("Доступные интерфесы:")

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle{
            height: parent.height/2
            width: parent.width

            radius: width/50
            border.width: 1
            ListView{
                id: _itfList

                width: parent.width*0.95
                height: parent.height*0.9

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                property string selectedItfName: currentItem.itfName

                currentIndex: 0

                focus: true

                highlight: Rectangle {

                    color: "lightsteelblue";
                    radius: 2
                }

                model: EthGui.itfList

                delegate: Item{
                    width: _itfList.width
                    height: _itfList.height/10

                    property string itfName: modelData

                    Text {
                        text: modelData
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked:
                        {
                            _itfList.currentIndex = index;
                        }

                        onDoubleClicked: {
                            _itfList.currentIndex = index;
                            acceptChanges();
                        }
                    }
                }
            }
        }

        Rectangle{
            height: parent.height*0.1
            width: parent.width

            radius: width/50
            border.width: 1
            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: width/20
                Label{
                    text: "IP адрес ППМ"
                }

                TextField{
                    id: _dstIpField
                    text: "10.0.0.151"
                }

                Label{
                   text: "Порт:"
                }

                TextField{
                    text: "40003"
                    enabled: false
                }
            }
        }

        Item{
            height: parent.height*0.1
            width: parent.width

            Button{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Далее"

                onClicked: {
                    acceptChanges();
                }
            }
        }
    }
}
