PROJECT(CDO_Data_Science_Detect_Face_1)

# install OpenCV into /opt/opencv3

# for OSX

SET(FACE_DETECT_SOURCES ObjectDetection.cpp
)

SET(CMAKE_BUILD_TYPE "Release")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

INCLUDE_DIRECTORIES(BEFORE /opt/opencv3/include)

ADD_EXECUTABLE(CDO_DataScience_Detect_Face_V1 ${FACE_DETECT_SOURCES})

TARGET_LINK_LIBRARIES(CDO_DataScience_Detect_Face_V1
    "/opt/opencv3/lib/libopencv_objdetect.dylib"
    "/opt/opencv3/lib/libopencv_core.dylib"
    "/opt/opencv3/lib/libopencv_highgui.dylib"
    "/opt/opencv3/lib/libopencv_imgproc.dylib"
    "/opt/opencv3/lib/libopencv_videoio.dylib"
)
