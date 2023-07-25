#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
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


public slots:
    void send_data();

private:
    Detect *det;
    QPushButton *browse_butt;
    QLineEdit *line_edit;

};
#endif // APPLICATION_H