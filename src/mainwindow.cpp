#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>    // Add Image
// #include <QToolBar>   // Customize toolbar

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load the app logo image
    QPixmap pix("assets/black_bosse.png");

    // Set the pixmap to the label
    ui->label->setPixmap(pix);

    // If you want to resize the label to fit the image
    ui->label->setScaledContents(true);
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    // // Create and add a toolbar
    // QToolBar *toolBar = addToolBar(tr("Tools"));
    
    // // Set the stylesheet for the toolbar
    // toolBar->setStyleSheet("QToolBar { background-color: #333333; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

