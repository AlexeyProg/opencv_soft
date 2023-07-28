#include "detect.h"
#include <thread>

Detect::Detect()
{

}

// void Detect::video()
// {
//     VideoCapture video(0);
//     Mat img;
//     while(true)
//     {
//         video.read(img);
//         imshow("frame", img);
//         waitKey(1);
//     }
// }

void Detect::get_data(const string &data)
{
    file_path = data;
}

 Mat Detect::detect_faces(string path)
{
    string name = "";
    int i = path.size() - 1;
    while(path[i] != '/')
    {
        name += path[i];
        i--;
    }
    reverse(name.begin(), name.end());

    // Загрузка изображения
    Mat image = imread(path, IMREAD_COLOR);

    // Проверка на успешную загрузку
    if (image.empty()) {
        cerr << "Failed to load the image." << endl;
        return {};
    }

    //  face recognation 
    CascadeClassifier faceCascade;
    string cascade_path = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
    bool checkCascade = faceCascade.load(samples::findFile(cascade_path));
    if(!checkCascade)
        cout << "cascade is not found";

    // Обнаружение лиц на изображении
    vector<Rect> faces;

    faceCascade.detectMultiScale(image, faces, 1.8, 1, 0 | CASCADE_SCALE_IMAGE, Size(25,25));

    // Рисование прямоугольников вокруг обнаруженных лиц
    for (const auto& face : faces) {
        rectangle(image, face, Scalar(255, 0, 0), 2);
    }

    // Отображение изображения с обнаруженными лицами в окне
    
    //imshow("Image with Detected Faces", image);
    return image;
    // Ожидание нажатия клавиши
   //waitKey(0);
}

void Detect::resize_image(const string &path)
{
    // сделать name из path
    string name  = "";
    int i = path.size() - 1;
    while(path[i] != '/')
    {
        name += path[i];
        i--;
    }
    reverse(name.begin(), name.end());

    Mat image = imread(path, IMREAD_COLOR);

    // Проверка на успешную загрузку
    if (image.empty()) {
        cerr << "Failed to load the image." << endl;
        return ;
    }
        
    // Изменение размера изображения (уменьшим в 50%)
    Mat resizedImage;
    resize(image, resizedImage, Size(), 0.5, 0.5);
    

    // отображение картинки
    // imshow("Image",image);
    // waitKey(0);

    // Сохранение изображения
    string s = "re" + name;
    if (imwrite(s, resizedImage)) 
    {
        cout << "Image saved successfully." << endl;
    } 
    else 
    {
        cerr << "Failed to save the image." << endl;
    }
}

Detect::~Detect()
{

}