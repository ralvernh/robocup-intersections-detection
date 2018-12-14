#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


//  https://www.codepool.biz/opencv-line-detection.html
//  https://scholar.google.fr/scholar?q=opencv+intersection+detection&hl=fr&as_sdt=0&as_vis=1&oi=scholart

int DetectLines(const char* filename, const char* sourceName, const char* destName)
{
    Mat src = imread(filename, 0);
    if (src.empty())
    {
        cout << "can not open " << filename << endl;
        return -1;
    }

    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 2);
    }

    imshow(sourceName, src);
    imshow(destName, cdst);

    return 0;
}

void usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname1 imsname2 \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1

int main(int argc, char** argv)
{
    if(argc != (param+1))
      usage(argv[0]);
    DetectLines(argv[1], "line src", "line dest");
    //DetectLines("..\\2.jpg", "door src", "door dest");
    waitKey();

    return 0;
}
