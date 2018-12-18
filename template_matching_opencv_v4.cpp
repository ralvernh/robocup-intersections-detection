#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>

using namespace cv;
using namespace std;

//  http://answers.opencv.org/question/6544/how-can-i-display-timer-results-with-a-c-puttext-command/
//  https://www.learnopencv.com/object-tracking-using-opencv-cpp-python/
//  http://answers.opencv.org/question/77543/how-to-reduce-false-detection-of-template-matching/

// bien mais en python, unfortunate :https://stackoverflow.com/questions/41470063/duplicate-matches-in-template-matching-using-opencv-with-c


/// Global Variables
const int nb_templates = 13;
bool use_mask;
Mat img; Mat templ[nb_templates]; Mat mask; Mat result[nb_templates];
const char* image_window = "Source Image";
const char* result_window = "Result window";
const char* motif_croix = "L";
const char* motif_T = "X";
const char* motif_angleDroit = "T";
int minMatchQuality = 50;

// NB: TOUJOURS INITIALISER LES TRACKBARS...
int max_Trackbar = 100;

/// Function Headers
void Detection( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
  if (argc < 1)
  {
    cout << "Not enough parameters" << endl;
    cout << "Usage:\n./MatchTemplate_Demo <image_name> [<mask_name>]" << endl;
    return -1;
  }

  /// Load image and template
  img = imread( argv[1], CV_LOAD_IMAGE_COLOR );
  char chemin_super_templates[] = "../super_templates/img1.png";

  /////////////////////////////////////  SORCELLERIE!!!!!!!!  //////////////////////////////////
  string string_tmp = "string";
  int len_srt;
  int chazam=0;
  string tmp;
  string tumfaichier;
  while( chazam <= nb_templates){
    templ[chazam] = imread( chemin_super_templates, CV_LOAD_IMAGE_COLOR);//CV_LOAD_IMAGE_GRAYSCALE

    chazam++;

    //incrémentons l'image lue
    string_tmp=string(chemin_super_templates); //passage en string
    len_srt=string_tmp.length();
    string_tmp.erase(22,len_srt);
    cout<< "lecture du template"<< string_tmp << " "<< chazam -1<<endl; //debug

    stringstream ss;
    ss << chazam;
    tmp = ss.str();
    //itoa(chazam, tmp,8);
    string_tmp.append(tmp);
    //string_tmp.append(itoa(chazam));
    string_tmp.append(".png");

    //chemin_super_templates = string_tmp.c_str(); //revenir vers char*
    tumfaichier= string_tmp.c_str();
    tumfaichier.copy(chemin_super_templates, len_srt,0);
  }
//////////////////////////////////////  FIN DE LA SORCELLERIE  ////////////////////////////////////////////


  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  //namedWindow( result_window, WINDOW_AUTOSIZE );


  /// Create Trackbar
  createTrackbar( "seuil", image_window, &minMatchQuality, max_Trackbar, Detection );

  Detection( 0, 0 );


  waitKey(0);
  return 0;

}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void Detection( int, void* )
{
  Mat img_display;
  img.copyTo( img_display );

  int k;
  int result_cols;
  int result_rows;

  for(k=1; k<=nb_templates; k++ ){ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Create the result matrix
    result_cols =  img.cols - templ[k].cols + 1;
    result_rows = img.rows - templ[k].rows + 1;

    result[k].create( result_rows, result_cols, CV_32FC1 ); //CV_8UC4

    templ[k].convertTo(templ[k], img.type(), 1, 0 );
    //cvtColor(templ[k], templ[k], CV_GRAY2BGR);

  //////////////////////////////////////////////////////GLOIRE A RAPTOR JESUS!!!!!!!!////////////////////////////////////////////////////////////////////

    if(templ[k].type() != img.type()){
      templ[k]=templ[k-1];
      //cvtColor(templ[k], templ[k], CV_GRAY2BGR);
    }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /// Do the Matching and Normalize
    matchTemplate( img, templ[k], result[k], CV_TM_CCOEFF_NORMED);  //CV_TM_CCOEFF_NORMED

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result[k], &minVal, &maxVal, &minLoc, &maxLoc,  Mat() );
    //Core.MinMaxLocResult mmr = Core.minMaxLoc(result);

    normalize( result[k], result[k], 0, 255, NORM_MINMAX, -1, Mat() ); //then,for imshow

    //when you use "CV_TM_CCOEFF_NORMED" you have to do:
    matchLoc = maxLoc;

    double seuiltmp = 0.5; //0.7
    seuiltmp = minMatchQuality / 100.0000001;

    if(maxVal > seuiltmp){  //calculer chsais pasquoi dans la Mat result //if(????.result[k] <= seuil)
      /// Show me what you got
      rectangle( img_display, matchLoc, Point( matchLoc.x + templ[k].cols , matchLoc.y + templ[k].rows ), Scalar(0, 255, 0), 2, 8, 0 );

      if((1 <= k)&& (k <= 4))
        putText(img_display, motif_croix, Point( matchLoc.x + templ[k].cols/2 , matchLoc.y + templ[k].rows/2 ), FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(0,0,255), 2);
      else if((4 < k)&&( k<= 10))
        putText(img_display, motif_T, Point( matchLoc.x + templ[k].cols/2 , matchLoc.y + templ[k].rows/2 ), FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(0,0,255), 2);
      else if(10 < k)
        putText(img_display, motif_angleDroit, Point( matchLoc.x + templ[k].cols/2 , matchLoc.y + templ[k].rows/2 ), FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(0,0,255), 2);

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  }
  imshow( image_window, img_display );
  imwrite( "../templatematching.png", img_display );
  //imshow( result_window, result[1] );

  return;
}
