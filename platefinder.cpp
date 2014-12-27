#ifndef _PLATE_FINDER_
#define  _PLATE_FINDER_
#include "platefinder.h"
#include "recognise.h"


const CvScalar RED = CV_RGB(255, 0,0);
const CvScalar GREEN = CV_RGB(0,255, 0);
const CvScalar BLUE = CV_RGB(0, 0, 255);



PlateFinder::PlateFinder()
{
    S1 = cvCreateStructuringElementEx(6, 1, 2, 0, CV_SHAPE_RECT, NULL);
    S2 = cvCreateStructuringElementEx(12, 1, 3, 0, CV_SHAPE_RECT, NULL);
    Plate = NULL;
}

PlateFinder::~PlateFinder()
{
    if (Plate)
    {
        S1 = NULL;
        S2 = NULL;
        Plate = NULL;
    }
}

vector<IplImage*> PlateFinder::image_grayscale()
{
    vector<IplImage*> Plvector;
    IplImage *src = cvLoadImage("processing/source/image.jpg");
    resizeImg = cvCreateImage(cvSize(800, 600), src->depth, src->nChannels);	// Anh resize
    cvResize(src, resizeImg);

    //Convert sang anh xam
    IplImage *grayImg = cvCreateImage(cvGetSize(resizeImg), IPL_DEPTH_8U, 1);	// Anh resize
    cvCvtColor(resizeImg, grayImg, CV_RGB2GRAY);
    cvNormalize(grayImg, grayImg, 0, 255, CV_MINMAX);
    cvSaveImage("processing/step1/grayscale.jpg", grayImg);
    ImageRestoration(grayImg);
    Plvector = FindPlate(resizeImg);
//    int cnt =0;
     vector<IplImage*>  Revector;
    for(unsigned int i =0; i<Plvector.size();i++)
    {
        //cnt++;
        if(Plvector[i])
        {
//            vector<IplImage*>  Revector;
            Recognise Re;
            Revector = Re.FindCharacter(Plvector.at(i));

            for(unsigned int j =0; j<Revector.size();j++)
            {
                // lưu ảnh ký tự định dạng nhị phân
                IplImage *Tam;
                IplImage *Tam2;
                Tam = Revector.at(j);
                Tam2 = cvCreateImage(cvSize(96, 128), Tam->depth, Tam->nChannels);
                cvResize(Tam, Tam2);
                char *name;
                name = new char[100];
                sprintf(name,"processing/step7/%d.jpg",j);
                cvSaveImage(name,Tam2);
                //cvShowImage(name,Tam2);
                delete name;

                /*saveImg = cvCreateImage(cvSize(Tam2->width, Tam2->height), IPL_DEPTH_8U, 1);
                     cvCvtColor(Tam2, saveImg, CV_RGB2GRAY);
                     cvAdaptiveThreshold(saveImg, saveImg, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 13, 2)*/;
            }

        }
    }
    return Revector;
}

void PlateFinder::ImageRestoration(IplImage *src)
{
    int w = src->width;
    int h = src->height;


    IplImage *mImg = cvCreateImage(cvSize(w / 2, h / 2), IPL_DEPTH_8U, 1);		// Anh su dung cho bien doi hinh thai hoc
    IplImage *src_pyrdown = cvCreateImage(cvSize(w / 2, h / 2), IPL_DEPTH_8U, 1);
    IplImage *tmp = cvCreateImage(cvSize(w / 2, h / 2), IPL_DEPTH_8U, 1);
    IplImage *thresholed = cvCreateImage(cvSize(w / 2, h / 2), IPL_DEPTH_8U, 1);	// Anh nhi phan voi nguong
    IplImage *mini_thresh = cvCreateImage(cvSize(w / 2, h / 2), IPL_DEPTH_8U, 1);
    IplImage *dst = cvCreateImage(cvSize(w / 2, h / 2), IPL_DEPTH_8U, 1);			// Anh lam ro vung bien so

    cvPyrDown(src, src_pyrdown);
    cvMorphologyEx(src_pyrdown, mImg, tmp, S2, CV_MOP_BLACKHAT);
    cvNormalize(mImg, mImg, 0, 255, CV_MINMAX);
    // Nhi phan hoa anh mImg
    cvThreshold(mImg, thresholed, (int)10 * cvAvg(mImg).val[0], 255, CV_THRESH_BINARY);
    cvZero(dst);
    cvCopy(thresholed, mini_thresh);
    cvSaveImage("processing/step2/binary.jpg", mini_thresh);
    int cnt;
    int nonZero1, nonZero2, nonZero3, nonZero4;
    CvRect rect; //khung hình.
    for (int i = 0; i < mini_thresh->width - 16; i += 4)
    {
        for (int j = 0; j < mini_thresh->height - 16; j += 4)
        {
            rect = cvRect(i, j, 8, 8); // hình chữ nhật có tọa độ i,j kích thước 16x8;
            cvSetImageROI(mini_thresh, rect);	//ROI = Region of Interest
            nonZero1 = cvCountNonZero(mini_thresh);
            cvResetImageROI(mini_thresh);

            rect = cvRect(i + 16, j, 16, 8);
            cvSetImageROI(mini_thresh, rect);	//ROI = Region of Interest
            nonZero2 = cvCountNonZero(mini_thresh); // đếm điểm trắng.
            cvResetImageROI(mini_thresh);

            rect = cvRect(i, j + 8, 16, 8);
            cvSetImageROI(mini_thresh, rect);	//ROI = Region of Interest
            nonZero3 = cvCountNonZero(mini_thresh);
            cvResetImageROI(mini_thresh);

            rect = cvRect(i + 16, j + 8, 16, 8);
            cvSetImageROI(mini_thresh, rect);	//ROI = Region of Interest
            nonZero4 = cvCountNonZero(mini_thresh);
            cvResetImageROI(mini_thresh);
            cnt = 0;
            if (nonZero1 > 7) { cnt++; }
            if (nonZero2 > 7) { cnt++; }
            if (nonZero3 > 7) { cnt++; }
            if (nonZero4 > 7) { cnt++; }
            if (cnt > 2)
            {
                rect = cvRect(i, j, 32, 16);
                cvSetImageROI(dst, rect);
                cvSetImageROI(mini_thresh, rect);
                cvCopy(mini_thresh, dst);
                cvResetImageROI(dst);
                cvResetImageROI(mini_thresh);
            }
        }
    }

    IplImage* dst_clone = cvCloneImage(dst);

    cvDilate(dst, dst, NULL, 2);
    cvErode(dst, dst, NULL, 2);
    cvDilate(dst, dst, S1, 9);
    cvErode(dst, dst, S1, 10);
    cvDilate(dst, dst);

    //    cvShowImage("mImg", mImg);
    //    cvShowImage("mini_thresh", mini_thresh);
    //    cvShowImage("dst_clone", dst_clone);
    //    cvShowImage("dst", dst);
    cvPyrUp(dst, src);
    cvSaveImage("processing/step3/filter.jpg", dst);
    cvReleaseImage(&mini_thresh);
    cvReleaseImage(&mImg);
    cvReleaseImage(&tmp);
    cvReleaseImage(&dst);
    cvReleaseImage(&src_pyrdown);
    cvReleaseImage(&thresholed);
    cvReleaseImage(&dst_clone);
}

vector<IplImage*>  PlateFinder::FindPlate(IplImage *src) {
    vector < IplImage*> platevector;
    vector<CvRect> rectvector;
    IplImage* plate;
    IplImage* contourImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);	// anh tim contour
    IplImage* grayImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);	// anh xam
    cvCvtColor(src, grayImg, CV_RGB2GRAY);

    IplImage* cloneImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
    cloneImg = cvCloneImage(src);

    // tien xu ly anh
    cvCopy(grayImg, contourImg);
    cvNormalize(contourImg, contourImg, 0, 255, CV_MINMAX);
    ImageRestoration(contourImg);

    IplImage* rectImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
    cvMerge(contourImg, contourImg, contourImg, NULL, rectImg); // tron anh

    // tim contour cua buc anh
    CvMemStorage *storagePlate = cvCreateMemStorage(0);
    CvSeq *contours = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storagePlate);
    cvFindContours(contourImg, storagePlate, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

    // bao lại contour.
    while (contours) {
        double ratio;
        CvRect rect = cvBoundingRect(contours);
        ratio = (double)rect.height / rect.width;
        if (ratio > 1.2 || ratio < 1){
            cvRectangle(cloneImg, cvPoint(rect.x, rect.y),
                        cvPoint(rect.x + rect.width, rect.y + rect.height), RED, 3);
        }


        cvSaveImage("processing/step4/segments.jpg",cloneImg);
        // cắt ảnh.

        plate = cvCreateImage(cvSize(rect.width, rect.height), IPL_DEPTH_8U, 3);
        cvSetImageROI(src, rect);
        cvCopy(src, plate, NULL);
        cvResetImageROI(src);
        //        cvShowImage("abcsdcsdiu",src);
        // đưa vùng nghi là ký tự vào
        platevector.push_back(cvCloneImage(plate));

        contours = contours->h_next;


    }
    for (unsigned int i = 0; i < platevector.size(); i++)
    {
        char *name;
        name = new char[100];
        sprintf(name, "processing/step6/vunkytu%d.jpg", i + 1);
        cvSaveImage(name, platevector.at(i));
        delete name;
    }
    cvReleaseImage(&plate);
    cvReleaseImage(&contourImg);
    cvReleaseImage(&grayImg);
    return platevector;
}
#endif

