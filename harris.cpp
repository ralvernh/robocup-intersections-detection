#include <iostream>
#include <cstdlib>

#include <opencv/cv.hpp>

using namespace cv;
using namespace std;


void showImage (const char* winname, const Mat &image)
{
    imshow (winname, image);
    waitKey (0);
}


void
process(const char* imsname)
{
    Mat image = imread (imsname, IMREAD_GRAYSCALE),
        dst = Mat::zeros(image.size(), image.type());
    if (image.empty())
    {
        cout << "Error: couldn't load or find the given image:\t" << imsname << endl;
        return;
    }

    int blockSize = 20;
    int apertureSize = 3;
    double k = 0.04;

    cornerHarris(image, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

    showImage("Line Detection Source", image);
    showImage("Line Detection", dst);
} 


void
usage (const char *s)
{
    std::cerr<<"Usage: "<<s<<"im-se ims imd"<<std::endl;
    exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
    if(argc != (param+1))
        usage(argv[0]);
    process(argv[1]);
    return EXIT_SUCCESS;
}