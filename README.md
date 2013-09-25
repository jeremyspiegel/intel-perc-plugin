intel-perc-plugin
=================

Browser plugin enabling web sites to use the Intel Perceptual Computing SDK, used for the Motion Maps submission for the Intel Perceptual Computing Challenge hosted at motionmapsapp.com.

To build:
```
git clone git@github.com:jeremyspiegel/intel-perc-plugin.git
git clone git@github.com:firebreath/FireBreath.git
cd intel-perc-plugin
..\FireBreath\prep2012.cmd . build
msbuild "build\projects\Motion Maps\Motion Maps.sln" /p:Configuration=Release
```

To use, see test.html/test.js and motion maps.html/motion maps.js.
