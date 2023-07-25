#include "application.h"

Application::Application(Detect *det,QWidget *parent) : QMainWindow(parent), det(det)
{
    create_window();
    connect(browse_butt, SIGNAL(clicked()), this, SLOT(send_data()));
}

void Application::create_window()
{
    this->setGeometry(200,100,300,500);
    this->setWindowTitle("OpenCV");
    line_edit = new QLineEdit(this);
    line_edit->setGeometry(10,10,200,30);

    browse_butt = new QPushButton(this);
    browse_butt->setText("Browse");
    browse_butt->setGeometry(10,50,80,40);
}

void Application::send_data()
{
    string data = line_edit->text().toStdString();
    det->get_data(data);
    cout << data << " - data" << endl;
    det->resize_image(det->file_path);
}
