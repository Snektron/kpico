import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Pico80.Components 1.0

View {
	icon: "\uF188"
	caption: "Debug"
	toolbar: Row {
		spacing: 2
		anchors.leftMargin: 4
		anchors.fill: parent

		PicoToolCheckBox {
			id: debugEnableBtn
			text: checked ? "\uF04C" : "\uF04B"
			anchors.verticalCenter: parent.verticalCenter
			disabledColor: Theme.toolbar.button.checked

			tooltip: PicoToolTip {
				text: (debugEnableBtn.checked ? "Run" : "Pause") + " the emulator"
			}
		}

		PicoToolButton {
			text: "\uF021"
			anchors.verticalCenter: parent.verticalCenter
			onClicked: KPico.debugger.refresh()

			tooltip: PicoToolTip {
				text: "Reparse instructions"
			}
		}

		PicoToolButton {
			text: "\uF051"
			anchors.verticalCenter: parent.verticalCenter
			onClicked: {
				KPico.debugger.step()
				KPico.debugger.refresh()
			}

			tooltip: PicoToolTip {
				text: "Step instruction"
			}
		}
	}

	ListView {
		id: instructions
		boundsBehavior: Flickable.StopAtBounds
		flickableDirection: Flickable.VerticalFlick
		anchors.fill: parent
		model: KPico.debugger.instructions

		Connections {
			target: KPico.debugger
			onRefreshed: instructions.positionViewAtIndex(
							 KPico.debugger.instructions.current, ListView.Center)
		}

		delegate: Rectangle {
			width: parent ? parent.width : 0
			height: childrenRect.height
			color: {
				if (KPico.debugger.instructions.current === index)
					return "#FF8A80"
				return index % 2 == 0 ? "#FFFFFF" : "#F5F5F5"
			}

			Row {
				anchors.left: parent.left
				anchors.right: parent.right
				spacing: 4

				Text {
					text: fmtAddress()
					width: 50
					textFormat: Text.PlainText
					font.pixelSize: 13
					font.family: "Roboto"
					renderType: Text.NativeRendering

					function fmtAddress() {
						var str = "0000" + address.toString(16).toUpperCase();
						return "0x" + str.substring(str.length - 4, str.length);
					}
				}

				Text {
					text: hexdata
					width: 50
					textFormat: Text.PlainText
					font.pixelSize: 13
					font.family: "Roboto Light"
					font.capitalization: Font.AllUppercase
					renderType: Text.NativeRendering
				}

				Text {
					text: size
					width: 10
					textFormat: Text.PlainText
					font.pixelSize: 13
					font.family: "Roboto Light"
					renderType: Text.NativeRendering
				}

				Text {
					text: instruction
					width: 100
					textFormat: Text.PlainText
					font.pixelSize: 13
					font.family: "Roboto Light"
					font.capitalization: Font.AllLowercase
					renderType: Text.NativeRendering
				}
			}
		}

		ScrollBar.vertical: PicoScrollBar {}
	}
}
