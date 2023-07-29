#include "application.h"
#include <thread>


Application::Application(Detect *det,QWidget *parent) : QMainWindow(parent), det(det)
{
    //this->setFixedSize(400,500);
    create_window();
    connect(resize_butt, SIGNAL(clicked()), this, SLOT(send_data()));
    connect(recognize_butt, SIGNAL(clicked()), this, SLOT(recognize()));
    connect(browse_dirs, SIGNAL(clicked()), this, SLOT(open_browse_dialog()));
    connect(line_edit, &QLineEdit::textChanged, this, [this](){
        resize_butt->setEnabled(true);
        recognize_butt->setEnabled(true);
    });

    connect(video_camera, SIGNAL(clicked()), this, SLOT(camera_open()));

    grid = new QGridLayout(this);

    grid->addWidget(line_edit,0,0,1,2);
    grid->addWidget(recognize_butt,1,0);
    grid->addWidget(video_camera, 1,1);
    grid->addWidget(resize_butt,1,2);
    grid->addWidget(browse_dirs,0,2);

    QWidget *centr = new QWidget(this);
    centr->setLayout(grid);
    setCentralWidget(centr);
}

void Application::open_browse_dialog()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open Image", "", "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)");
    if (!filePath.isEmpty())
    {
        // Конвертируем путь из QString в std::string
        std::string stdFilePath = filePath.toStdString();

        // Вызываем функцию для работы с изображением
        std::cout << stdFilePath << std::endl;
        line_edit->setText(filePath);
    }
    else
    {
        std::cout << "Some problems with choosing file";
    }

}

void Application::create_window()
{
    this->setStyleSheet("background-color : Gray;");
    this->setGeometry(200,100,300,500);
    this->setWindowTitle("OpenCV");

    line_edit = new QLineEdit;
    line_edit->setStyleSheet("background-color : white;");
    line_edit->setFixedWidth(300);
    line_edit->setPlaceholderText("Enter path or select 'browse'...");

    resize_butt = new QPushButton;
    resize_butt->setText("resize");
    resize_butt->setStyleSheet("background-color : white;");
    resize_butt->setFixedWidth(130);
    resize_butt->setEnabled(false);

    recognize_butt = new QPushButton;
    recognize_butt->setStyleSheet("background-color : white;");
    recognize_butt->setText("Recognize faces");
    recognize_butt->setEnabled(false);

    video_camera = new QPushButton;
    video_camera->setText("Camera");
    video_camera->setStyleSheet("background-color : white;");

    browse_dirs = new QPushButton;
    browse_dirs->setStyleSheet("background-color : white;");
    browse_dirs->setText("Browse");
}

void Application::send_data()
{
    string data = line_edit->text().toStdString();
    det->get_data(data);

    std::thread th(&Detect::resize_image, det, det->file_path);
    th.join();
}

void Application::recognize()
{
    string str = line_edit->text().toStdString();
    while (true)
    {
        int key = cv::waitKey(1);
        if (key == 27) // Код 27 соответствует клавише "Escape", выход из цикла
            break;
        
        cv::imshow("Press 'Esc' to exit", det->detect_faces(str));
    }
    cv::destroyWindow("Press 'Esc' to exit");
}  

void Application::camera_open()
{
    det->video();  
}