#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int lowThreshold;
int const max_lowThreshold = 100;
int hightThreshold;
int const min_hightThreshold = 80;
const char* window_name = "hello there";

Mat src;

//  https://www.codepool.biz/opencv-line-detection.html
//  https://scholar.google.fr/scholar?q=opencv+intersection+detection&hl=fr&as_sdt=0&as_vis=1&oi=scholart
//  https://github.com/VAUTPL/Detecting-lines
//  https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html


void DetectLines( const char* destName)
{
    //Mat src = imread(filename, 0);  //ou CV_LOAD_IMAGE_COLOR
    //cout<<"affichage de"<<sourceName<<endl;
    /*
    if (src.empty())
    {
        cout << "can not open " << filename << endl;
        return EXIT_FAILURE;
    }
*/

    Mat dst, cdst;// dst2;
    //Canny(src, dst, 50, 200, 3);


    Canny(src, dst, lowThreshold, hightThreshold, 3);
    //equalizeHist( src, dst2 );

    cvtColor(dst, cdst, COLOR_GRAY2BGR);


    vector<Vec4i> lines;
    //HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);

    HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 2);
    }

    imshow("sourceName", src);
    imshow(destName, cdst);

}


void DetectLines_demo( int, void* )
{
  DetectLines( "line dest");
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

    src = imread(argv[1], 0);  //ou CV_LOAD_IMAGE_COLOR

    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    /// Create a Trackbars for user to enter thresholds
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, DetectLines_demo );
    createTrackbar( "Max Threshold:", window_name, &hightThreshold, min_hightThreshold, DetectLines_demo );

    DetectLines_demo(0,0);
    //DetectLines(argv[1], "line src", "line dest");
    //DetectLines("..\\2.jpg", "door src", "door dest");
    waitKey();

    return 0;
}
