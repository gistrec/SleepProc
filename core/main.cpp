#include "../ui/main_window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
        printf("5 5 5");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
