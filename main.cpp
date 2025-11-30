#include "c_app.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");

    CaveApp application;
    application.setupParams();
    application.run();

    return 0;
}