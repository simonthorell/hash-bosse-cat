#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // Define a variable to hold a single hash
    QString singleHash;

    // Define a map to store the file names and paths

    QMap<QString, QString> HashesFilesMap;
    QMap<QString, QString> WordlistFilesMap;

    // Selected Hashing Algorithm & Salt Amount
    QString HashingAlgorithm;
    int saltAmount;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Style GUI
    void styleGUI(QApplication& app);

private slots:
    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    // UI Input Fields
    void setSingleHashFromInput();
    void setHashingAlgorithm(int index); 
    void setSaltAmount(int index);

    // UI Buttons
    void onButtonUploadHashesClicked();
    void onButtonUploadWordlistClicked();
    void onButtonCrackHashesClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
