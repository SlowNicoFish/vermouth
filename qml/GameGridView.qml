import QtQuick
import QtCore

GridView {
    id: gridView

    property real scaleFactor: 1.0
    property string viewType: "icon"
    property bool showNames: true
    property bool active: true
    property bool lightsOut: false

    Settings {
        id: viewSettings
        category: "GridView"
        property alias scaleFactor: gridView.scaleFactor
        property alias viewType: gridView.viewType
        property alias showNames: gridView.showNames
    }

    cellWidth: {
        var base = viewType === "hero" ? 306 : viewType === "grid" ? 200 : 140;
        base *= scaleFactor;
        if (width <= 0 || count <= 0)
            return base;
        var cols = Math.max(1, Math.floor(width / base));
        if (count <= cols)
            return Math.min(width / count, base);
        return Math.max(base, width / cols);
    }
    cellHeight: {
        var baseH = viewType === "hero" ? 143 : viewType === "grid" ? 300 : (showNames ? 140 : 120);
        baseH *= scaleFactor;
        var baseW = viewType === "hero" ? 306 : viewType === "grid" ? 200 : 140;
        baseW *= scaleFactor;
        return cellWidth * (baseH / baseW);
    }

    clip: true
    focus: true
    keyNavigationEnabled: true

    onActiveFocusChanged: {
        if (!activeFocus)
            currentIndex = -1;
    }

    TapHandler {
        onTapped: {
            gridView.currentIndex = -1;
        }
    }
}
