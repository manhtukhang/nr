#ifndef PLATEFINDER_H
#define PLATEFINDER_H

#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>


#include <iostream>

using namespace std;

//extern vector<IplImage*>  Revector;

class PlateFinder
{
private:
    IplConvKernel *S1;
    IplConvKernel *S2;
    IplImage *Plate; //ảnh biển số.

public:

    PlateFinder();
    ~PlateFinder();
    vector<IplImage*> image_grayscale();
    void ImageRestoration(IplImage *scr); // tiền xử lý ảnh gốc.
    vector<IplImage*> FindPlate (IplImage *src);	// tim va cat ảnh chứa ký tự cho vào vector.
    IplImage *resizeImg;

};

#endif // PLATEFINDER_H
