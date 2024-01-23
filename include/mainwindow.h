#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <unordered_map>
#include <set>

#include "file_handler.h"
#include "wordlist_processor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::string singleHash;
    std::unordered_map<std::string, std::string> HashesFilesMap;
    std::unordered_map<std::string, std::string> WordlistFilesMap;
    HashAlgorithm hashingAlgorithm;
    int saltAmount;
    // UI style variables
    QString greyStyle;
    QString neonGreenStyle;

public:
    // Constructor and Destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Style GUI (call this after creating a new MainWindow object)
    void styleGUI(QApplication& app);

private slots:
    // UI Input Fields
    void setSingleHashFromInput();
    void setHashingAlgorithm(int index); 
    void setSaltAmount(int index);
    void setProgressBarValue(int progressPercentage);

    // UI Buttons
    void onButtonUploadHashesClicked();
    void onButtonRemoveHashesClicked();
    void onButtonUploadWordlistClicked();
    void onButtonRemoveWordlistClicked();
    void onButtonCrackHashesClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
