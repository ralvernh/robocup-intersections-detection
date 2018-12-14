#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;

//  http://opencvexamples.blogspot.com/2013/10/split-and-merge-functions.html

/*
char* source_window = "Source image";
char* corners_window = "Corners detected";
*/

/// Function header
void cornerHarris_demo( int, void* );


void usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname1 imsname2 \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1


/** @function main */
int main( int argc, char** argv )
{
  if(argc != (param+1))
    usage(argv[0]);
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window and a trackbar
  namedWindow( "Source image", CV_WINDOW_AUTOSIZE );
  createTrackbar( "Threshold: ", "Source image", &thresh, max_thresh, cornerHarris_demo );
  imshow( "Source image", src );

  cornerHarris_demo( 0, 0 );

  waitKey(0);
  return(0);
}

/** @function cornerHarris_demo */
void cornerHarris_demo( int, void* )
{

  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( src.size(), CV_32FC1 );

  /// Detector parameters
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;

  /// Detecting corners
  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

  /// Normalizing
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh )
              {
               circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
              }
          }
     }
  /// Showing the result
  namedWindow( "Corners detected", CV_WINDOW_AUTOSIZE );
  imshow( "Corners detected", dst_norm_scaled );
}