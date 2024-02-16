//==============================================================================
// Program: HashBosseCat - Advanced Password Recovery Tool
// Author: Simon Thorell
// Date: 2024-02-16
// Version: 1.0
// Description: Using the GUI to upload a file of hashes to crack, the program
//              will attempt to crack the hashes using a dictionary attack.
//              The program will also allow the user to enter a hash to crack
//              manually.
//==============================================================================
#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"     // GUI

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    MainWindow mainWindow;
    mainWindow.styleGUI(app);
    mainWindow.show();
    
    return app.exec();
}