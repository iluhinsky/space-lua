import QtQuick 2.4

MainPageForm {
    startButton.onClicked: {
        simulatorDownloader.startSimulator("/../../../bin/GameEngineDebug.exe", "123",
                                           "111")
    }
}
