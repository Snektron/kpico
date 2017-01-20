import QtQuick 2.0
import QtGraphicalEffects 1.0
import KPico 1.0
import Pico80.Components 1.0

View {
	color: theme.display_placeholder.background

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
			color: "#A0212121"
			cornerRadius: 15

			function updateAspect(parentWidth, parentHeight) {
				var min = Math.min(parentWidth, parentHeight * 1.5);
				width = min
				height = min / 1.5
			}

			Display {
				id: display
				anchors.fill: parent
			}
		}
	}
}

/*
Image {
	fillMode: Image.PreserveAspectFit
	source: "qrc:/textures/test.png"
}
*/
