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


    

    main_wind.show();
    return app.exec();
    //     std::string path = "/Users"; // Замените на путь к директории, которую хотите открыть
    // std::filesystem::directory_iterator dirIter(path);

    // for (const auto& entry : dirIter) {
    //     std::cout << entry.path() << std::endl;
    // }

    // // Открыть файловую систему во внешнем файловом менеджере
    // openFileSystemInExternalFileManager(path);
    return 0;
}


    
