#ifndef DETECT
#define DETECT
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "platefinder.h"

using namespace std;
using namespace cv;


int loadImage(Mat *storage_image, char* file_path);

Mat extractDescription(Mat image_object);

int saveDescriptorToFile(vector<Mat> descriptor_vect, string file_name);

int loadDescriptorFromFile(vector<Mat> &descriptor_vect, string file_name);

void addDescriptorToFile(vector<Mat> descriptor_vect, string file_name);

double compareDiscriptor(Mat descriptors_object, Mat descriptors_scene);

void training(char* train_path);

int detectImage(Mat image);

void saveNumberToFile(vector<IplImage*> revector, char file_name[]);

#endif // DETECT

