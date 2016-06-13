# Open CV Face Detection

An experiemt using OpenCV V3 to detect faces, eyes, nose.
Build and install OpenCV to /opt/opencv3:

```Shell
cd ~/opencv-3.1.0
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
```
There is a bug in OpenCV 3.1.0 which will cause the application to crash after 100 seconds. To fix comment out the line
```
NSTimer scheduledTimerWithTimeInterval:100 target:capture selector:@selector(doFireTimer:) userInfo:nil repeats:YES];
```
in opencv-3.1.0/modules/videoio/src/cap_qtkit.mm

Building
========
On OSX/Linux run the script build.sh.
