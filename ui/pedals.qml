import QtQuick
import QtQuick.Window

Window {
    id: window
    visible: true
    flags: Qt.WindowStaysOnTopHint

    Shortcut {
        sequence: "F5"
        onActivated: {
            window.close();
            app.reload();
        }
    }

    Shortcut {
        sequence: "Esc"
        onActivated: {
            Qt.quit();
        }
    }

    Rectangle {
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: "hello world"
        }
    }
}
