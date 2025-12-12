#include <QApplication>
#include "UI/LibraryGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LibraryGUI window;
    window.show();

    return app.exec();
}