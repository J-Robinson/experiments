#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
//String face_cascade_name = "./haarcascade_frontalface_alt.xml";
//String eyes_cascade_name = "./haarcascade_eye.xml";
//String nose_cascade_name = "./haarcascade_mcs_nose.xml";

String face_cascade_name = "./haarcascade_frontalface_alt.xml";
//String eyes_cascade_name = "./haarcascade_eyes_45.xml";
String both_eyes_cascade_name = "./haarcascade_both_eyes.xml";
String left_eye_cascade_name = "./haarcascade_left_eye.xml";
String right_eye_cascade_name = "./haarcascade_right_eye.xml";
String nose_cascade_name = "./haarcascade_nose_25.xml";

CascadeClassifier face_cascade;
CascadeClassifier both_eyes_cascade;
CascadeClassifier nose_cascade;
CascadeClassifier left_eye_cascade;
CascadeClassifier right_eye_cascade;

string window_name = "CDO Data Science - Face detection";

RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
//    CvCapture* capture;
    VideoCapture capture;
    Mat frame;
  
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
    { 
        printf("--(!)Error loading face cascade\n"); 
        return -1; 
    }

    if( !both_eyes_cascade.load( both_eyes_cascade_name ) )
    { 
        printf("--(!)Error loading both eyes cascade\n"); 
        return -1; 
    }

    if( !left_eye_cascade.load( left_eye_cascade_name ) )
    { 
        printf("--(!)Error loading left eye cascade\n"); 
        return -1; 
    }
    
    if( !right_eye_cascade.load( right_eye_cascade_name ) )
    { 
        printf("--(!)Error loading right eye cascade\n"); 
        return -1; 
    }
    
    if (!nose_cascade.load( nose_cascade_name ))
    {
        printf("--(!)Error loading nose cascade\n");
        return -1;
    }
 
    //-- 2. Read the video stream
    capture.open(-1);
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );

        //-- bail out if escape was pressed
        int c = waitKey(5);
        if( (char)c == 27 ) { break; }
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;
  
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
  
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  
    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.4, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
    
        //-- In each face, detect both eyes
        both_eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        
        std::size_t numEyes = std::min(static_cast<std::size_t>(1), eyes.size());
       
        for( size_t j = 0; j < numEyes; j++ )
        {
            Point eyeCenter( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
            ellipse( frame, eyeCenter, Size( eyes[j].width*0.5, eyes[j].height*0.3), 0, 0, 360, Scalar( 255, 255, 0 ), 4, 8, 0 );
            //int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            //circle( frame, center, radius, Scalar( 255, 255, 0 ), 4, 8, 0 );
        }

        //-- Detect nose
        std::vector<Rect> nose;
        nose_cascade.detectMultiScale( faceROI, nose, 1.2, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        if (nose.size() > 0)
        {
            Point noseCenter( faces[i].x + nose[0].x + nose[0].width*0.5, faces[i].y + nose[0].y + nose[0].height*0.5 );
            ellipse( frame, noseCenter, Size( nose[0].width*0.2, nose[0].height*0.5), 0, 0, 360, Scalar( 0, 255, 255 ), 4, 8, 0 );
        }
       
        //-- Detect left eye
        std::vector<Rect> leftEye;
        left_eye_cascade.detectMultiScale( faceROI, leftEye, 1.2, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        //if (leftEye.size() > 0)
        for (size_t j=0 ; j < leftEye.size(); ++j)
        {
            Point leftEyeCenter( faces[i].x + leftEye[j].x + leftEye[j].width*0.5, faces[i].y + leftEye[j].y + leftEye[j].height*0.5 );
            ellipse( frame, leftEyeCenter, Size( leftEye[j].width*0.5, leftEye[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
        
        //-- Detect right eye
        std::vector<Rect> rightEye;
        left_eye_cascade.detectMultiScale( faceROI, rightEye, 1.2, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        //if (rightEye.size() > 0)
        for (size_t j=0 ; j < rightEye.size(); ++j)
        {
            Point rightEyeCenter( faces[i].x + rightEye[j].x + rightEye[j].width*0.5, faces[i].y + rightEye[j].y + rightEye[j].height*0.5 );
            ellipse( frame, rightEyeCenter, Size( rightEye[j].width*0.5, rightEye[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }

    putText(frame, "CDO Data Science", Point(10, frame.size().height-10), FONT_HERSHEY_PLAIN, 4.0 /*scale*/, CV_RGB(255,255,255), 4.0 /*lineType*/, LINE_AA);

    //-- Show what you got
    //namedWindow(window_name, CV_WINDOW_NORMAL);
    //setWindowProperty(window_name, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    imshow( window_name, frame );
}
