Ubuntu 18.04:
===

```
sudo apt-get install qt5-default
sudo apt-get install qtmultimedia5-dev
sudo apt-get install libqt5multimedia5-plugins
sudo apt-get install libqt5multimediawidgets5
```

Note
===
if you got 'gst_vaapi_window_x11_new_with_xid' error,
remove the library as below...

```
sudo apt-get remove gstreamer1.0-vaapi 
```

ref: https://forum.qt.io/topic/82324/qvideowidget-shows-qmediaplayer-the-playing-media-as-green-screen


following library may be relevant:
```
sudo apt-get install gstreamer1.0-qt5 
sudo apt-get install libgstreamer1.0-dev 
sudo apt-get install libqglviewer-dev-qt5
```
