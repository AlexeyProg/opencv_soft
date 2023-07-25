#ifndef DETECT_H
#define DETECT_H
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


class Detect
{
public:
    Detect();

    void detect_faces(string file_name, int &counter);
    void get_data(const string &data);
    void resize_image(const string &path);
    ~Detect();
    string file_path;
};

#endif // DETECT_H