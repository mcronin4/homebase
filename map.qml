//From QmlMap map.qml
//QML Interactive Map qml components
//edited from source : https://github.com/sonds1/QmlMap.git
import QtQuick 2.15
import QtPositioning
import QtLocation

Rectangle {
    id: window

    property double oldLat: 44.2333
    property double oldLng: -76.5000
    property Component comMarker: mapMarker



    MapView {
        id: view
        anchors.fill: parent
        map.plugin: Plugin { name: "osm" }
        map.center: QtPositioning.coordinate(oldLat, oldLng);
        map.zoomLevel: 12

        map.onZoomLevelChanged: {
                var apiKey = "MAP API HERE";
                var url = "https://tile.thunderforest.com/neighbourhood/" + zoomLevel + "/" + center.latitude + "/" + center.longitude + ".png?key=" + apiKey;
                mapView.plugin.parameters = [{ name: "osm.mapping.custom.host", value: url }];
            }
    }

    function setCenter(lat, lng) {
        MapView.pan(oldLat - lat, oldLng - lng)
        oldLat = lat
        oldLng = lng
    }

    function addMarker(lat, lng) {
        var item = comMarker.createObject(window, {
                                           coordinate: QtPositioning.coordinate(lat, lng)
                                          })
        MapView.addMapItem(item)
    }

    Component {
        id: mapMarker
        MapQuickItem {
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "https://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }
}
