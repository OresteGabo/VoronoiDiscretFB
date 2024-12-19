#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Diagramme de Voronoï Discret");
    window.resize(500, 500);
    window.show();

    return app.exec();
}
