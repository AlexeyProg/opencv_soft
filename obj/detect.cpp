#include "detect.h"

Detect::Detect()
{

}

void Detect::get_data(const string &data)
{
    file_path = data;
}

 void Detect::detect_faces(string file_name, int &counter)
{
    // Загрузка изображения
    Mat image = imread(file_name, IMREAD_COLOR);

    // Проверка на успешную загрузку
    if (image.empty()) {
        cerr << "Failed to load the image." << endl;
        return ;
    }

    //  face recognation 
    CascadeClassifier faceCascade;
    string cascade_path = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
    bool checkCascade = faceCascade.load(samples::findFile(cascade_path));
    if(checkCascade)
    {
        cout << "cascade is found";
    }
    else
    {
        cout << "cascade is not found";
    }
    // Обнаружение лиц на изображении
    vector<Rect> faces;
    float factor_scale = 0;
    int neighbours = 0;
    Size face_size = Size(25,25);
    //если человек один
    if(counter <= 2)
    {
        factor_scale = 1.2;
        neighbours = 1;
        face_size = Size(25,25);
    }
    else
    {
        factor_scale = 1.5;
        neighbours = 4;
    }
    faceCascade.detectMultiScale(image, faces, factor_scale, neighbours, 0 | CASCADE_SCALE_IMAGE, face_size);

    // Рисование прямоугольников вокруг обнаруженных лиц
    for (const auto& face : faces) {
        rectangle(image, face, Scalar(255, 0, 0), 2);
    }

    // Отображение изображения с обнаруженными лицами в окне
    imshow("Image with Detected Faces", image);

    // Ожидание нажатия клавиши
    waitKey(0);
}

void Detect::resize_image(const string &path)
{

    // Загрузка изображения
    cout << path  << " - path in detect" << endl;

    // сделать name из path
    string name  = "";
    string test = path;
    int i = test.size();
    cout << " first  = " << test[i] << endl;
    while(test[i] != '/')
    {
        cout << test[i] << endl;
        i--;
    }


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
    string s = "re" + path;
    cout << " s - " << s << endl;
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