#include "recognise.h"
#include "platefinder.h"

Recognise::Recognise()
{
}


const CvScalar RED = CV_RGB(255, 0, 0);
const CvScalar GREEN = CV_RGB(0, 255, 0);
const CvScalar BLUE = CV_RGB(0, 0, 255);

// chia cắt từng ký tự
vector<IplImage *> Recognise::FindCharacter(IplImage *plate) {
    vector<IplImage *> charImgVector;
    vector<CvRect> rect;
    IplImage *resizeImg, *binaryImg, *cloneImg;

    resizeImg = cvCreateImage(cvSize(408, 70), IPL_DEPTH_8U, 3);
    binaryImg = cvCreateImage(cvSize(408, 70), IPL_DEPTH_8U, 1);
    // chuyển ảnh nhị phân
    cvResize(plate, resizeImg);
    cvCvtColor(resizeImg, binaryImg, CV_RGB2GRAY);
    cvAdaptiveThreshold(binaryImg, binaryImg, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 13, 2);

    cloneImg = cvCloneImage(resizeImg);
    // tìm contour
    CvMemStorage *storage = cvCreateMemStorage(0);
    CvSeq *contours = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage);
    cvFindContours(binaryImg, storage, &contours);


    double ratio, ratioWhite; // tỷ lệ rộng/cao và điểm trắng /s
    int s, white;

    while (contours) {
        CvRect r = cvBoundingRect(contours, 0);

        ratio = (double)r.width / r.height;
        s = r.width * r.height;

        cvSetImageROI(binaryImg, r);
        white = cvCountNonZero(binaryImg);
        cvResetImageROI(binaryImg);
        ratioWhite = (double)white / s;

        if (ratio > 0.3 && ratio < 1.1 &&
            s > 200 && r.width > 20 && r.width < 70 &&
            r.height > 30 && r.height < 80 &&
            ratioWhite > 0.2 && ratioWhite < 0.8)
        {
            cvRectangle(cloneImg, cvPoint(r.x, r.y), cvPoint(r.x + r.width, r.y + r.height), BLUE, 2);
            rect.push_back(r);
        }
        contours = contours->h_next;
    }
    cvSaveImage("processing/step5/a.jpg",cloneImg);

     //sap xep hình ảnh đã cắt
    for (unsigned int i = 0; i < rect.size() - 1; i++)
    {
        for (unsigned int j = i + 1; j < rect.size(); j++)
        {
            if (rect[i].x > rect[j].x)
            {
                CvRect sw;
                sw = rect[i];
                rect[i] = rect[j];
                rect[j] = sw;
            }
        }
    }

    // cat ky tu
    IplImage *charImg;
    for (unsigned int i = 0; i < rect.size(); i++)
    {
        charImg = cvCreateImage(cvSize(rect[i].width, rect[i].height), IPL_DEPTH_8U, 3);
        cvSetImageROI(resizeImg, rect[i]);
        cvCopy(resizeImg, charImg, NULL);
        cvResetImageROI(resizeImg);

        // đưa ảnh ky tu vao vector
        charImgVector.push_back(charImg);
    }

//        cvShowImage("character", cloneImg);

    return charImgVector;
}
