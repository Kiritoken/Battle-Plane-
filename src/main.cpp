#include <iostream>
#include "viewer/viewer.h"


int main() {
    Viewer viewer("EBattle-Plane");
    viewer.init();
    viewer.start();
    return 0;
}