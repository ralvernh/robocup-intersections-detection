#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int lowThreshold=69; //27
int const max_lowThreshold = 100;
int hightThreshold=70; //63
int const min_hightThreshold = 100;

int low_h=30;
int low_s=183; //186
int low_v=0;
int const max_low_h = 360;
int const max_low_s = 360;
int const max_low_v = 360;
int hight_h=61; //96
int hight_s=360;
int hight_v=210;
int const min_hight_h = 360;
int const min_hight_s = 360;
int const min_hight_v = 360;

const char* window_name = "hello there";

Mat src, HSV;

//  https://www.codepool.biz/opencv-line-detection.html
//  https://scholar.google.fr/scholar?q=opencv+intersection+detection&hl=fr&as_sdt=0&as_vis=1&oi=scholart
//  https://github.com/VAUTPL/Detecting-lines
//  https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html
//  https://www.learnopencv.com/color-spaces-in-opencv-cpp-python/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mat Erosion( Mat image_input ,int erosion_size )
{
  Mat image_output;
  int erosion_type = 0;
  int erosion_elem = 2;

  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  //![kernel]
  Mat element = getStructuringElement( erosion_type,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
  //![kernel]

  /// Apply the erosion operation
  erode( image_input, image_output, element );
  //imshow( "Erosion_Demo", image_output );
  return (image_output);
}


Mat Dilation( Mat image_input ,int dilation_size )
{
  Mat image_output;
  int dilation_type = 0;
  int dilation_elem = 2;

  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );

  /// Apply the dilation operation
  dilate( image_input, image_output, element );
  //imshow( "Dilation_Demo", image_output );
  return (image_output);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DetectLines( )
{

    vector<Mat> hsv_planes;
    split(HSV, hsv_planes);
    Mat h = hsv_planes[0]; // H channel
    Mat s = hsv_planes[1]; // S channel
    Mat v = hsv_planes[2]; // V channel

    Scalar hsv_upper_l(low_h,low_s,low_v); //30,90,30
    Scalar hsv_upper_h(hight_h,hight_s,hight_v);  //100,180,200
    Mat green_hue_upper;
    inRange(HSV, hsv_upper_l, hsv_upper_h, green_hue_upper);

    Mat whole_green_hue = green_hue_upper;

    //imshow("outpute", whole_green_hue);
    src=whole_green_hue.clone();
    //--------------------------------------------------------------------------
    Mat cdst;


    cvtColor(src, cdst, COLOR_GRAY2BGR);
    imwrite( "../apres_hsv.png", cdst );

    int nb_dillations_erosions = 2;
    for( int k=0; k < nb_dillations_erosions ;k++){
      src = Dilation( src ,4 );
    }
    for( int kk=0; kk<nb_dillations_erosions ;kk++){
      src = Erosion( src ,4 );
    }
    imwrite( "../apres_erosion.png", src );

    //--------------------------------------------------------------------------

    Canny(src, src, 50, 200, 3);

    int rows=cdst.rows;
    int cols=cdst.cols;
    Mat image_lignes_rouge(rows,cols,CV_8UC1,Scalar(0,0,0));
    cvtColor(image_lignes_rouge, image_lignes_rouge, COLOR_GRAY2BGR);

    ////////////////////////////////////////////////////////////////////////////////////////
    // Standard Hough Line Transform
    vector<Vec2f> linesss; // will hold the results of the detection
    HoughLines(src, linesss, 1, CV_PI/180, lowThreshold, hightThreshold, 10 ); // runs the actual detection


    // Draw the lines
    for( size_t i = 0; i < linesss.size(); i++ ){
      float rho = linesss[i][0], theta = linesss[i][1];
      Point pt1, pt2;
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      pt1.x = cvRound(x0 + 1000*(-b));
      pt1.y = cvRound(y0 + 1000*(a));
      pt2.x = cvRound(x0 - 1000*(-b));
      pt2.y = cvRound(y0 - 1000*(a));
      line( cdst, pt1, pt2, Scalar(0,0,255), 3, 2); //LINE_AA
    }
    ////////////////////////////////////////////////////////////////////////////////////////

    imshow("sourceName", src);
    imshow("houghtlines", cdst);
    //imshow(destName, cdst);
    cvtColor(image_lignes_rouge, image_lignes_rouge, COLOR_BGR2GRAY);

}


void DetectLines_demo( int, void* )
{
  DetectLines();
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

    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    /// TRACKBARS HSV
    createTrackbar( "H_min", window_name, &low_h, max_low_h, DetectLines_demo );
    createTrackbar( "H_max", window_name, &hight_h, min_hight_h, DetectLines_demo );

    createTrackbar( "S_min", window_name, &low_s, max_low_s, DetectLines_demo );
    createTrackbar( "S_max", window_name, &hight_s, min_hight_s, DetectLines_demo );

    createTrackbar( "V_min", window_name, &low_v, max_low_v, DetectLines_demo );
    createTrackbar( "V_max", window_name, &hight_v, min_hight_v, DetectLines_demo );

    //  TRACKBARS OUF_LINES
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, DetectLines_demo );
    createTrackbar( "Max Threshold:", window_name, &hightThreshold, min_hightThreshold, DetectLines_demo );


    DetectLines_demo(0,0);
    
    waitKey();

    return 0;
}
