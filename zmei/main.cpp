#include <QApplication>
#include "SnakeWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SnakeWidget window;
    window.setWindowTitle("Розовая змейка");
    window.resize(600, 620);
    window.show();
    return app.exec();
}
