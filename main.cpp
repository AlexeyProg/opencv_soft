#include <opencv2/opencv.hpp>
#include <iostream>
#include <QtWidgets/QApplication>
#include "graphics/application.h"
#include "obj/detect.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
    Detect det;
    Application main_wind(&det);

    // cout << "Path : " << det.file_path << endl;
    main_wind.show();
    return app.exec();
}


    
