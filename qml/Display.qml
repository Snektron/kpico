import QtQuick 2.0
import QtQuick.Dialogs 1.0
import QtGraphicalEffects 1.0
import KPico 1.0
import Pico80.Components 1.0

View {
	color: Theme.kpico.display.background

	toolbar: Row {
		spacing: 2
		anchors.leftMargin: 4
		anchors.fill: parent

		PicoToolButton {
			id: rompickerbutton
			text: "\uF0F6"
			anchors.verticalCenter: parent.verticalCenter
			onClicked: rompicker.open()

			property url rom: Settings.value("KPico/ROM", "");

			Component.onCompleted: loadRom(rom)

			tooltip: PicoToolTip {
				text: "Select ROM image\nCurrent ROM: " + rompickerbutton.getRomName(rompickerbutton.rom)
			}

			FileDialog {
				id: rompicker
				onAccepted: rompickerbutton.loadRom(fileUrl)
			}

			function getRomName(url) {
				if (url === "")
					return "None"
				else
					return url.toString().replace(/^(file:\/{3})/,"")
			}

			function loadRom(url) {
				rompickerbutton.rom = url
				Settings.setValue("KPico/ROM", url);
				KPico.asic.loadRom(url);
			}
		}

		PicoToolButton {
			text: "\uF011"
			anchors.verticalCenter: parent.verticalCenter

			tooltip: PicoToolTip {
				text: "Start emulator"
			}
		}
	}

	Item {
		anchors.margins: 10
		anchors.fill: parent

		onWidthChanged: shadow.updateAspect(width, height)
		onHeightChanged: shadow.updateAspect(width, height)

		RectangularGlow {
			id: shadow
			anchors.centerIn: parent

			glowRadius: 5
			spread: 0.2
			color: Theme.kpico.display.shadow
			cornerRadius: 15

			function updateAspect(parentWidth, parentHeight) {
				var min = Math.min(parentWidth, parentHeight * 1.5);
				width = min
				height = min / 1.5
			}

			Lcd {
				id: lcd
				objectName: "LCD"
				anchors.fill: parent
			}
		}
	}
}
