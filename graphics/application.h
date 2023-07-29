#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#include <filesystem>
#include "../obj/detect.h"


using namespace std;

class Application : public QMainWindow
{
    Q_OBJECT
public:
    explicit Application(Detect *det, QWidget *parent = nullptr);

    void create_window();
    virtual ~Application() = default;
    string data_to_send;
    string file_path;

public slots:
    void send_data();
    void recognize();
    void open_browse_dialog();
    void camera_open();

private:
    Detect *det;
    QVBoxLayout *lay;
    QGridLayout *grid;

    QPushButton *resize_butt;
    QPushButton *recognize_butt;
    QPushButton *browse_dirs;
    QPushButton *video_camera;

    QLineEdit *line_edit;

};
#endif // APPLICATION_H