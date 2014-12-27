

#include "detect.h"

int loadImage(Mat *storage_image, char* file_path){
    *storage_image = imread(file_path, CV_LOAD_IMAGE_COLOR);
    if(! *storage_image->data ) // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    return 0;
}

Mat extractDescription(Mat image_object){

    int minHessian = 10;

    SurfFeatureDetector detector( minHessian );

    std::vector<KeyPoint> keypoints_object;
    Mat image;
    cvtColor(image_object, image, COLOR_BGR2GRAY );
    detector.detect( image, keypoints_object );


    SurfDescriptorExtractor extractor;

    Mat descriptors_object;

    extractor.compute( image, keypoints_object, descriptors_object );

    return descriptors_object;
}

//vector<Mat> extractDescriptionToVector()

int saveDescriptorToFile(vector<Mat> descriptor_vect, string file_name){
    char id[10];
    FileStorage storage(file_name, FileStorage::WRITE);
    double number = descriptor_vect.size();
    storage << "number" << number;
    for (unsigned int i=0; i<number; i++){
        sprintf(id, "sample_%d", i+1);
        storage << id << descriptor_vect.at(i);
    }
    storage.release();
    return 0;
}

int loadDescriptorFromFile(vector<Mat> &descriptor_vect, string file_name){
    char id[10];
    Mat temp_descriptor;

    descriptor_vect.clear();

    FileStorage storage(file_name, FileStorage::READ);

    double number;
    storage["number"] >> number;

    for (unsigned int i=0; i<number; i++){
        sprintf(id, "sample_%d", i+1);
        storage[id] >> temp_descriptor;
        descriptor_vect.push_back(temp_descriptor);
    }

    storage.release();
    return 0;
}


void addDescriptorToFile(vector<Mat> descriptor_vect, string file_name){
    vector<Mat> temp_descriptor_vect;
    loadDescriptorFromFile(temp_descriptor_vect, file_name);

    for (unsigned int i=0; i<descriptor_vect.size(); i++){
        temp_descriptor_vect.push_back(descriptor_vect.at(i));
    }

    saveDescriptorToFile(temp_descriptor_vect, file_name);
}

double compareDiscriptor(Mat descriptors_object, Mat descriptors_scene){
    //    int percentage;
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_object, descriptors_scene, matches );

    double max_dist = 0; double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_object.rows; i++ )    {
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    return (min_dist + max_dist);
}

void training(char* train_path){
    char train_path_name[200];
    char train_path_data[200];

    Mat train_image;
    for (int i=0; i<10; i++){
        vector<Mat> image_des;
        //        for (int j=0; j<5; j++){
        //            sprintf(train_path_name, "%s/%d.jpg", train_path, i, j);
        sprintf(train_path_name, "%s/%d.jpg", train_path, i);
        loadImage(&train_image, train_path_name);
        image_des.push_back(extractDescription(train_image));

        //        }
        sprintf(train_path_data, "data/%d.yml.gz", i);
        addDescriptorToFile(image_des, train_path_data);
    }
}

int detectImage(Mat image) {
    char filename[100];
    vector<double> compare_data;
    Mat image_dis = extractDescription(image);
    for (int i=0; i<10; i++){
        vector<Mat> sample_data;
        sprintf(filename, "data/%d.yml.gz", i);
        loadDescriptorFromFile(sample_data, filename);
        double best = 10;
        for (unsigned int j=0; j<sample_data.size(); j++){
            if (compareDiscriptor(image_dis, sample_data.at(j)) < best) {
                best = compareDiscriptor(image_dis, sample_data.at(j));
            }
        }
        compare_data.push_back(best);

    }
    int index=0;
    double best_c = compare_data.at(0);
    for (unsigned int i=1; i<compare_data.size(); i++){
        if (best_c > compare_data.at(i)) {
            best_c = compare_data.at(i);
            index = i;
        }
    }
    return index;
}

void saveNumberToFile(vector<IplImage*> revector, char file_name[]){
    int text;
    vector<char> numbers_vect;
    for (unsigned int i=0; i<revector.size(); i++){
        char name[200], numbers[1];
        sprintf(name,"processing/step7/%d.jpg", i);
        Mat image;
        loadImage(&image, name);
        text = detectImage(image);
        sprintf(numbers,"%d", text);
        numbers_vect.push_back(*numbers);

    }
//    char numbers[20];
    std::string detected_numbers(numbers_vect.begin(), numbers_vect.end());
    ofstream myfile;
    myfile.open(file_name);
    myfile << detected_numbers;
    myfile.close();
}
