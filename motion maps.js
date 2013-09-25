function plugin() {
    return document.getElementById("plugin");
}

$(document).ready(function() {
    $(window).resize(function() {
        var mapHeight = $(window).height();
        if ( $("#plugin_failed_alert").css('display') != 'none' || $("#no_plugin_alert").css('display') != 'none' )
            mapHeight -= 52;
        $("#map").css('height', mapHeight);
    });

    var normal;
    var hasMiddleFinger;
    var massCenterWorldY;
    var frames = 0;
    function onFrame(frame) {
        normal = null;
        hasMiddleFinger = false;
        massCenterWorldY = null;
        frame.gesture.nodes.forEach(function(node) {
            if ( "normal" in node )
                normal = node.normal;

            if ( "massCenterWorld" in node )
                massCenterWorldY = node.massCenterWorld.y;

            if ( node.body["fingerMiddle"] )
                hasMiddleFinger = true;
        });

        ++frames;
    }

    setInterval(function() {
        frames = 0;
    }, 1000);

    function onError() {
        $("#plugin_failed_alert").show();
        $("#map").css('top', 52);
        $("#map").css('height', $(window).height() - 52);
        setTimeout(function() {
            plugin().loopFrames(function(f) {
                $("#plugin_failed_alert").hide();
                $("#map").css('top', 0);
                $("#map").css('height', $(window).height());
                frame = f;
            }, onError);
        }, 2000);
    }

    if ( plugin().version ) {
        console.log("Loaded plugin version " + plugin().version);
        plugin().loopFrames(onFrame, onError);
    } else {
        console.log("Failed to load plugin");
        $("#no_plugin_alert").show();
        $("#map").css('top', 52);
        $("#map").css('height', $(window).height() - 52);
        var interval = setInterval(function() {
            console.log(plugin().version);
            $('#plugin').remove();
            var object = document.createElement('object');
            object.setAttribute('id', 'plugin');
            object.setAttribute('style', 'top: 0px; height: 0px');
            document.body.appendChild(object);
            plugin().setAttribute('type', 'application/x-motionmaps');
            if ( plugin().version ) {
                clearInterval(interval);
                $("#no_plugin_alert").hide();
                $("#map").css('top', 0);
                $("#map").css('height', $(window).height());
                plugin().loopFrames(onFrame, onError);
            }
        }, 2000);
    }

    var map = L.mapbox.map('map', 'jeremyspiegel.map-axci2wl8');
    map.addControl(L.mapbox.geocoderControl('jeremyspiegel.map-axci2wl8'));

    var intervalsSinceZoom = Number.MAX_VALUE;
    setInterval(function() {
        if ( intervalsSinceZoom < 5 )
        {
            ++intervalsSinceZoom;
            return;
        }

        if ( !normal || !massCenterWorldY || !hasMiddleFinger || frames == 0 )
            return;

        var x = normal.x;
        x *= ( x > 0 ? 15 : 25 );
        x = Math.pow(x, 2) * (x > 0 ? 1 : -1);
        if ( Math.abs(x) < 1.5 )
            x = 0;

        x = x > 0 ? Math.min(x, 50) : Math.max(x, -50);
        x = Math.round(x);

        var y = normal.z;
        if ( -0.60 < y && y <= -0.50 ) {
            y = 0;
        } else if ( y > -0.50 ) {
            y += 0.50;
            y *= 30;
            y = Math.pow(y, 2);
        } else {
            y = Math.abs(y) - 0.60;
            y *= 50;
            y = Math.pow(y, 2);
            y *= -1;
        }

        y = y > 0 ? Math.min(y, 50) : Math.max(y, -50);
        y = Math.round(y);

        map.panBy([x, y], { animate: false });

        if ( massCenterWorldY < 160 ) {
            intervalsSinceZoom = 0;
            massCenterWorldY = null;
            map.zoomIn();
        } else if ( massCenterWorldY > 280 ) {
            intervalsSinceZoom = 0;
            massCenterWorldY = null;
            map.zoomOut();
        }
    }, 100);
});
