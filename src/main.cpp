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
#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include "hash_generator.h" // MD5, SHA1, SHA256
#include "salt_generator.h" // Add salt to strings

void styleGUI(QApplication& app);    // Style the GUI
void testClasses(); // For testing purposes

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    styleGUI(app);
    MainWindow w;
    w.show();

    // testClasses(); // For testing classes in console
    return app.exec();
}

void styleGUI(QApplication& app) {
    // Dark color palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(00, 00, 00));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    
    app.setPalette(darkPalette);

    // STYLE SHEET FOR QCOMBOBOX
    app.setStyleSheet("QComboBox { background-color: #303030; color: white; }");
    app.setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 1px solid white; }");
    app.setStyleSheet("QPushButton { background-color: #303030; color: white; }");
}

void testClasses() {
    HashGenerator hashGen; // Create a HashGenerator object
    SaltGenerator saltGen; // Create a SaltGenerator object

    // Prompt user to enter a string to hash
    std::cout << "Please enter a string to hash: ";
    std::string input_string;
    std::cin >> input_string;

    // Example of random salt generation
    std::string salt = saltGen.generateSalt(10);
    std::cout << "Salt: " << salt << std::endl;
    std::string salted_string = input_string + salt;
    std::cout << "Salted String: " << salted_string << std::endl;
    
    /* As salt is random, the salted string will be different each time
       we will not be able to compare the hash of the salted string to
       a hash we have already cracked. */

    // Compute MD5 hash
    std::string hash = hashGen.computeMD5(input_string);
    
    // Output the hash
    std::cout << "MD5 Hash: " << hash << std::endl;

    // Logic Test to compare two hashes (hashToCrack is the hash of "stefan")
    std::string hashToCrack = "2e970e822e1a8834203d06abb60f59ec";
    
    if (hash == hashToCrack) {
        std::cout << "Hashes Match!" << std::endl;
    } else {
        std::cout << "Hashes Do Not Match! Try again..." << std::endl;
    }
}