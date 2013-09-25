function plugin() {
    return document.getElementById("plugin");
}

function TestController($scope) {
    var frames = 0;
    function onFrame(f) {
        $scope.frame = f;
        $scope.$apply();
        ++frames;
    }

    setInterval(function() {
        $scope.fps = frames;
        $scope.$apply();
        frames = 0;
    }, 1000);

    function onError() {
        $scope.error = "Failed to connect to camera";
    }

    if ( plugin().version ) {
        plugin().loopFrames(onFrame, onError);
    } else {
        $scope.error = "Failed to load plugin";
    }
}
