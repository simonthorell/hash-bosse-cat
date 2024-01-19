#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>    // Add Image

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load the app logo image
    QPixmap pix("assets/black_bosse.png");

    // Set the pixmap to the label
    ui->logoType->setPixmap(pix);

    // Resize the label to fit the image
    ui->logoType->setScaledContents(true);
    ui->logoType->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    // Set logo name style 
    QLabel* logoText = ui->logoText;
    QFont font = logoText->font();        // Get the current font
    font.setFamily("Monospace");          // Set to monospaced font
    font.setStyleHint(QFont::TypeWriter); // Style hint for monospaced
    font.setPointSize(34);                // Set the font size   
    logoText->setFont(font);              // Apply the font to the QLabel

    // Set the alignment of the logo text to center
    logoText->setAlignment(Qt::AlignCenter);

    // Set the text color to white
    QPalette palette = logoText->palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    logoText->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}