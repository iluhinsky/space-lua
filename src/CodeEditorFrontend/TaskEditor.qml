import QtQuick 2.4

TaskEditorForm {
    sendLuaButton.onClicked: {
        sendLuaCode(codeArea.text, shipTextArea.text)
    }

    startSimulationButton.onClicked: {
        simulatorDownloader.startSimulator("/../../bin/GameEngineDebug.exe", shipTextArea.text,
                                           codeArea.text)
    }

    function sendLuaCode (code, ship) {
        var http = new XMLHttpRequest()
        var url = "http://0.0.0.0:5000/send_code"
        var paramCode = "code=" + code
        var paramShip = "ship=" + ship
        url = url + '?' + paramCode + '&' + paramShip
        http.open("GET", url, true)

        http.onreadystatechange = function() { // Call a function when the state changes.
            if (http.readyState == 4) {
                if (http.status == 200) {
                    console.log("ok")
                } else {
                    console.log("error: " + http.status)
                }
            }
        }
        http.send()
    }
}
