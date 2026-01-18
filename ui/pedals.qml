import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Window {
    id: window
    visible: true
    modality: Qt.WindowModal
    flags: Qt.CustomizeWindowHint | Qt.WindowStaysOnTopHint
    width: 500
    height: 100
    color: "#202028"

    readonly property int padding: 5
    readonly property color clutchColor: "#0159cd"
    readonly property color brakeColor: "#b31e1b"
    readonly property color throttleColor: "#58d42e"

    Shortcut {
        sequence: "Esc"
        onActivated: {
            Qt.quit();
        }
    }

    MouseArea {
        anchors.fill: parent
        property var clickPos

        onPressed: {
            clickPos = {
                x: overlay.mousePos().x - window.x,
                y: overlay.mousePos().y - window.y
            };
        }

        onPositionChanged: {
            window.x = overlay.mousePos().x - clickPos.x;
            window.y = overlay.mousePos().y - clickPos.y;
        }
    }

    Rectangle {
        anchors.left: pedals.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: window.padding
        radius: 2
        color: "#101018"

        PedalsChart {
            id: pedalsChart
            clutchColor: window.clutchColor
            brakeColor: window.brakeColor
            throttleColor: window.throttleColor
            anchors.fill: parent
            Component.onCompleted: {
                overlay.setPedalsChart(pedalsChart);
            }
        }
    }

    Rectangle {
        id: pedals
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: window.padding
        width: 90
        radius: 2
        color: '#303038'

        readonly property int padding: 5
        readonly property color textColor: '#d6d6d6'
        readonly property color backgroundColor: window.color

        RowLayout {
            anchors.fill: parent
            anchors.margins: pedals.padding
            spacing: pedals.padding
            uniformCellSizes: true

            ColumnLayout {
                id: clutchPedal
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    Layout.alignment: Qt.AlignCenter
                    color: pedals.textColor
                    text: overlay.clutch
                    font.bold: true
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    color: pedals.backgroundColor
                    radius: 2

                    Rectangle {
                        anchors.fill: parent
                        anchors.topMargin: parent.height * (1.0 - overlay.clutch / 100.0)
                        color: window.clutchColor
                        radius: 2
                    }
                }
            }

            ColumnLayout {
                id: brakePedal
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    Layout.alignment: Qt.AlignCenter
                    color: pedals.textColor
                    text: overlay.brake
                    font.bold: true
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    color: pedals.backgroundColor
                    radius: 2

                    Rectangle {
                        anchors.fill: parent
                        anchors.topMargin: parent.height * (1.0 - overlay.brake / 100.0)
                        color: window.brakeColor
                        radius: 2
                    }
                }
            }

            ColumnLayout {
                id: throttlePedal
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    Layout.alignment: Qt.AlignCenter
                    color: pedals.textColor
                    text: overlay.throttle
                    font.bold: true
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    color: pedals.backgroundColor
                    radius: 2

                    Rectangle {
                        anchors.fill: parent
                        anchors.topMargin: parent.height * (1.0 - overlay.throttle / 100.0)
                        color: window.throttleColor
                        radius: 2
                    }
                }
            }
        }
    }
}
