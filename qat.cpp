#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main( )
{
 
       Mat image;
 Mat img;
Mat dst, img_hist_equalized,dest,img1;
       // LOAD image
     
 img=imread("qatar.jpg", CV_LOAD_IMAGE_GRAYSCALE); 
 
  equalizeHist(img, img_hist_equalized);
Mat element = getStructuringElement(MORPH_RECT, Size(2, 2) );
Mat element1 = getStructuringElement(MORPH_RECT, Size(6, 6) );
Mat rImg,thers,cann,imge;

morphologyEx(img_hist_equalized, rImg, MORPH_TOPHAT, element);

      subtract(img_hist_equalized,rImg,dest); 
  threshold( dest, thers,150, 250, THRESH_BINARY_INV);

   
 

      Canny(thers,cann,100,300, 3);
dilate(cann, imge,  element);
 
    /// Find contours   
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
    findContours(imge, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    /// Draw contours
 /// Approximate contours to polygons + get bounding rects and circles
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );

 int w_threshold = 100;
    int h_threshold = 100;
 vector<int> selected;
    Mat drawing = Mat::zeros( imge.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar(rng.uniform(0,255) );
       Rect R = boundingRect(contours[i]);
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );

 if (R.width > w_threshold && R.height > h_threshold)
        {
            selected.push_back(i);
            drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        }

    }     
 for (size_t i = 0; i < selected.size(); i++)
        {
            rectangle(drawing, boundingRect(contours[selected[i]]), Scalar(0, 0, 255), 3);
        }

  

       imshow( "Gray", img ); // Show our image inside it.

imshow( "Morph Open", rImg); // Show our image inside it.
imshow( "Histo", dest);
imshow( "thers", thers);
imshow( "canny", cann);
imshow( "dil", imge);
       imshow( "Result window", drawing );
imshow( "dil", imge); 
     imwrite("result.jpg",imge);
 
       waitKey(0);                       // Wait for a keystroke in the window
       return 0;
}
