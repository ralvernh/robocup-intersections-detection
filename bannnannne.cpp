#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int low_h;
int low_s;
int low_v;
int const max_low_h = 360;
int const max_low_s = 360;
int const max_low_v = 360;
int hight_h;
int hight_s;
int hight_v;
int const min_hight_h = 360;
int const min_hight_s = 360;
int const min_hight_v = 360;

const char* window_name = "have fun";

Mat src, HSV;;

//http://colorizer.org/


void banane_demo( int, void* )
{
  Scalar hsv_upper_l(low_h,low_s,low_v); //30,90,30
  Scalar hsv_upper_h(hight_h,hight_s,hight_v);  //100,180,200
  Mat green_hue_upper;
  inRange(HSV, hsv_upper_l, hsv_upper_h, green_hue_upper);

  Mat whole_green_hue = green_hue_upper;

  imshow("outpute", whole_green_hue);
}

void usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname1 \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1

int main(int argc, char** argv)
{
    //char* window_name ="hellothere";
    if(argc != (param+1))
      usage(argv[0]);

    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);  //ou 0
    // Create a new matrix to hold the HSV image
    //Mat HSV;

    // convert RGB image to HSV
    cvtColor(src, HSV, CV_BGR2HSV);
    vector<Mat> hsv_planes;
    split(HSV, hsv_planes);
    Mat h = hsv_planes[0]; // H channel
    Mat s = hsv_planes[1]; // S channel
    Mat v = hsv_planes[2]; // V channel

/*
    namedWindow("hue", CV_WINDOW_AUTOSIZE);
    imshow("hue", h);
    //imwrite("h",h);
    namedWindow("saturation", CV_WINDOW_AUTOSIZE);
    imshow("saturation", s);
    //imwrite("s",s);
    namedWindow("value", CV_WINDOW_AUTOSIZE);
    imshow("value", v);
    //imwrite("v",v);
*/
    //// red color rangeS
    /*
    int n = 100;

    //Scalar hsv_upper_l(100, 100, 180-n);
    Scalar hsv_upper_l(100, 180-n, 100);
    Scalar hsv_upper_h(255, 255, 255);
    Mat green_hue_upper;
    inRange(HSV, hsv_upper_l, hsv_upper_h, green_hue_upper);
    */
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    /// Create a Trackbars for user to enter thresholds
    createTrackbar( "H_min", window_name, &low_h, max_low_h, banane_demo );
    createTrackbar( "H_max", window_name, &hight_h, min_hight_h, banane_demo );

    createTrackbar( "S_min", window_name, &low_s, max_low_s, banane_demo );
    createTrackbar( "S_max", window_name, &hight_s, min_hight_s, banane_demo );

    createTrackbar( "V_min", window_name, &low_v, max_low_v, banane_demo );
    createTrackbar( "V_max", window_name, &hight_v, min_hight_v, banane_demo );

    banane_demo(0,0);

/*
    Scalar hsv_upper_l(25,189,118); //30,90,30
    Scalar hsv_upper_h(95,255,198);  //100,180,200
    Mat green_hue_upper;
    inRange(HSV, hsv_upper_l, hsv_upper_h, green_hue_upper);
*/





/*
    Scalar hsv_lower_l(150, 0, 150);
    Scalar hsv_lower_h(255, 0+n, 255);
    Mat green_hue_lower;
    inRange(HSV, hsv_lower_l, hsv_lower_h, green_hue_lower);
    */

    //Mat whole_green_hue = green_hue_upper | green_hue_lower;

    waitKey(0);
    return 0;
}
