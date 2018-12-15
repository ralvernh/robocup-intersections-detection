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


/// Global Variables
const int nb_templates = 12;
bool use_mask;
Mat img; Mat templ[nb_templates]; Mat mask; Mat result[nb_templates];
const char* image_window = "Source Image";
const char* result_window = "Result window";
const char* motif_croix = "+";
const char* motif_T = "T";
const char* motif_angleDroit = "L";

int match_method=CV_TM_SQDIFF_NORMED;  // NB: TOUJOURS INITIALISER LES TRACKBARS...
int max_Trackbar = 4; //5


/// Function Headers
void MatchingMethod( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
  if (argc < 2)
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

  if(argc > 2) {
    use_mask = true;
    mask = imread( argv[2], IMREAD_COLOR );
  }

  if(img.empty() || templ[0].empty() || (use_mask && mask.empty()))
  {
    cout << "Can't read one of the images" << endl;
    return -1;
  }

  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  //namedWindow( result_window, WINDOW_AUTOSIZE );


  /// Create Trackbar
  const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

  MatchingMethod( 0, 0 );


  waitKey(0);
  return 0;

}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  Mat img_display;
  img.copyTo( img_display );

  int k;
  int result_cols;
  int result_rows;

  for(k=0; k<=nb_templates; k++ ){ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Create the result matrix
    result_cols =  img.cols - templ[k].cols + 1;
    result_rows = img.rows - templ[k].rows + 1;

    result[k].create( result_rows, result_cols, CV_32FC1 ); //CV_8UC4

    cout<< img.type()<<endl;
    cout<< templ[k].type()<<endl;
    //imshow( "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", templ[k] );
    //waitKey(0);
  //////////////////////////////////////////////////////GLOIRE A RAPTOR JESUS!!!!!!!!////////////////////////////////////////////////////////////////////
    if(templ[k].type() != img.type()){
      templ[k]=templ[k-1];
    }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Do the Matching and Normalize
    bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);

    if (use_mask && method_accepts_mask)
      //{ matchTemplate( img, templ, result, match_method, mask); }
      { matchTemplate( img, templ[k], result[k], match_method); }
    else
      { matchTemplate( img, templ[k], result[k], match_method); }


    normalize( result[k], result[k], 0, 1, NORM_MINMAX, -1, Mat() );


    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result[k], &minVal, &maxVal, &minLoc, &maxLoc, Mat() );


    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
      { matchLoc = minLoc; }
    else
      { matchLoc = maxLoc; }

/*
    if(????.result[k] <= seuil){  //calculer chsais pasquoi dans la Mat result
      /// Show me what you got
      rectangle( img_display, matchLoc, Point( matchLoc.x + templ[k].cols , matchLoc.y + templ[k].rows ), Scalar(0, 255, 0), 2, 8, 0 );
    
      if(0 <= k <= xxx)
        putText(img_display, motif_croix, matchLoc, FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(255,0,0), 2);
      else if(xxx < k <= yyy)
        putText(img_display, motif_T, matchLoc, FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(255,0,0), 2);
      else if(yyy < k)
        putText(img_display, motif_angleDroit, matchLoc, FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(255,0,0), 2);
    }
*/

    /// Show me what you got
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ[k].cols , matchLoc.y + templ[k].rows ), Scalar(0, 255, 0), 2, 8, 0 );
    //rectangle( result[k], matchLoc, Point( matchLoc.x + templ[k].cols , matchLoc.y + templ[k].rows ), Scalar(0, 255, 0), 2, 8, 0 );
    
    //pour visualiser:
    putText(img_display, motif_croix, matchLoc, FONT_HERSHEY_SIMPLEX, 0.75,  Scalar(255,0,0), 2);
    

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  }
  imshow( image_window, img_display );
  imshow( result_window, result[1] );

  return;
}
