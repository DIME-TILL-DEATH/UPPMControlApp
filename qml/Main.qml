import QtQuick
import QtQuick.Dialogs
import QtQuick.Window

import CppObjects 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("UPPM Control")

    EthSettings{
        id: _ethSettings

        anchors.fill: parent
        visible: true
    }

    ControlScreen{
        id: _controlScreen

        anchors.fill: parent
        visible: false
    }

    MessageDialog
    {
        id: _msgErrorDialog

        buttons: MessageDialog.Ok
        title: qsTr("Error")
    }

    Connections{
        target: EthGui

        function onSgErrorMsg(msg)
        {
           _msgErrorDialog.text = msg;
           _msgErrorDialog.open();
        }

        function onSgConnectionOpened()
        {
            console.log("Connection opened");
            _ethSettings.visible = false;
            _controlScreen.visible = true;
        }
    }
}
