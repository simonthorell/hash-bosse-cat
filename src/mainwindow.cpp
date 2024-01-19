#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap> // Add Image

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load the app logo image
    QPixmap pix("assets/cat.png");

    // Set the pixmap to the label
    ui->label->setPixmap(pix);

    // If you want to resize the label to fit the image
    ui->label->setScaledContents(true);
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

