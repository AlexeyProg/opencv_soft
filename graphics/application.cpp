#include "application.h"
#include <thread>


Application::Application(Detect *det,QWidget *parent) : QMainWindow(parent), det(det)
{
    //this->setFixedSize(400,550);
    create_window();
    connect(resize_butt, SIGNAL(clicked()), this, SLOT(send_data()));
    connect(recognize_butt, SIGNAL(clicked()), this, SLOT(recognize()));
    connect(test, SIGNAL(clicked()), this, SLOT(open_browse_dialog()));

    grid = new QGridLayout(this);

    grid->addWidget(line_edit,0,0,1,2);
    grid->addWidget(recognize_butt,1,0);
    grid->addWidget(resize_butt,1,2);
    grid->addWidget(test,0,2);

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
    this->setGeometry(200,100,300,500);
    this->setWindowTitle("OpenCV");
    line_edit = new QLineEdit;
    line_edit->setFixedWidth(300);

    resize_butt = new QPushButton;
    resize_butt->setText("resize");
    resize_butt->setFixedWidth(130);

    recognize_butt = new QPushButton;
    recognize_butt->setText("Recognize faces");

    test = new QPushButton;
    test->setText("Browse");
    // test->setFixedWidth(100);
}

void Application::send_data()
{
    string data = line_edit->text().toStdString();
    det->get_data(data);

    std::thread th(&Detect::resize_image, det, det->file_path);
    th.join();
    //det->resize_image(det->file_path);
}

void Application::recognize()
{
    string str = line_edit->text().toStdString();
    //std::thread th1(&Detect::detect_faces, det, str);
    //th1.join();  // из-за imshow не в гланом потоке - нельзя.

    //det->detect_faces(str);
        while (true)
    {
        int key = cv::waitKey(1);
        if (key == 27) // Код 27 соответствует клавише "Escape", выход из цикла
            break;
        
        cv::imshow("Press 'Esc' to exit", det->detect_faces(str));
    }
    cv::destroyWindow("Press 'Esc' to exit");
}  