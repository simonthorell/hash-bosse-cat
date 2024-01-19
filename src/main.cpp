//==============================================================================
// Program: HashBosseCat - Advanced Password Recovery Tool
// Author: Simon Thorell
// Date: 2024-01-17
// Version: 1.0
// Description: Using the GUI to upload a file of hashes to crack, the program
//              will attempt to crack the hashes using a dictionary attack.
//              The program will also allow the user to enter a hash to crack
//              manually.
//==============================================================================
#include <QApplication>
#include "mainwindow.h"     // GUI

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.styleGUI(app);
    MainWindow w;
    w.show();
    return app.exec();
}