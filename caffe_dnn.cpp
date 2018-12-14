#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "caffe_dnn.h"
 
using namespace std;

//  http://www.coldvision.io/2016/07/29/image-classification-deep-learning-cnn-caffe-opencv-3-x-cuda/

int main(int argc, char **argv)
{
	string imagePath = (argc > 1) ? argv[1] : "../data/img_test_1/img_color_1.jpg";
 
	bool cpuOnly = true;
	string modelPath   = "../data/bvlc_caffenet/deploy.prototxt";
	string trainedPath = "../data/bvlc_caffenet/bvlc_reference_caffenet.caffemodel";
	string meanPath    = "../data/bvlc_caffenet/imagenet_mean.binaryproto";
	string labelPath   = "../data/bvlc_caffenet/synset_words.txt";
	testCaffeDnn(modelPath, trainedPath, meanPath, labelPath, imagePath, cpuOnly);
 
	cpuOnly = false;
	modelPath   = "../data/bvlc_caffenet/deploy.prototxt";
	trainedPath = "../data/bvlc_caffenet/bvlc_reference_caffenet.caffemodel";
	meanPath    = "../data/bvlc_caffenet/imagenet_mean.binaryproto";
	labelPath   = "../data/bvlc_caffenet/synset_words.txt";
	testCaffeDnn(modelPath, trainedPath, meanPath, labelPath, imagePath, cpuOnly);
 
	return 0;
} //main
