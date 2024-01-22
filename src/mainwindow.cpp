#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>      // Debug
#include <QPixmap>     // Add Image
#include <QFileDialog> // File Dialog
#include <QMessageBox> // Pop-up Window
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize class variables
    singleHash = "";
    HashesFilesMap.clear();
    WordlistFilesMap.clear();
    hashingAlgorithm = HashAlgorithm::SHA256; // Default Hashing Algorithm
    saltAmount = 0;           // Default Salt Amount

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
    font.setPointSize(36);                // Set the font size   
    logoText->setFont(font);              // Apply the font to the QLabel

    // Set the alignment of the logo text to center
    logoText->setAlignment(Qt::AlignCenter);

    // Set the text color to white
    QPalette palette = logoText->palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    logoText->setPalette(palette);

    // Connect the UI InputFields to the slots
    connect(ui->Input_SingleHash, &QLineEdit::textChanged, this, &MainWindow::setSingleHashFromInput);
    connect(ui->comboBox_SelectHashAlgo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &MainWindow::setHashingAlgorithm);
    connect(ui->Slider_SelectSaltAmount, &QSlider::valueChanged, this, &MainWindow::setSaltAmount);

    // Connect the button's clicked() signal to the slots
    connect(ui->Button_UploadHashes, SIGNAL(clicked()), this, SLOT(onButtonUploadHashesClicked()));
    connect(ui->Button_UploadWordlist, SIGNAL(clicked()), this, SLOT(onButtonUploadWordlistClicked()));
    connect(ui->Button_CrackHashes, SIGNAL(clicked()), this, SLOT(onButtonCrackHashesClicked()));
}   

void MainWindow::styleGUI(QApplication& app) {
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
    app.setStyleSheet(
        "QComboBox { background-color: #303030; color: white; }"
        "QToolTip { color: #ffffff; background-color: #000000; border: 1px solid white; }"
        "QPushButton { background-color: #303030; color: white; }"
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

//=========================================================================
// UI Input Fields
//=========================================================================

void MainWindow::setSingleHashFromInput()
{   
    // Get the text from the Input_SingleHash QLineEdit
    singleHash = ui->Input_SingleHash->text().toUtf8().constData();
}

void MainWindow::setHashingAlgorithm(int index)
{
    // Get the text from the combo_HashingAlgorithm QComboBox
    std::string selection = ui->comboBox_SelectHashAlgo->itemText(index).toUtf8().constData();

    if (selection == "MD5") {
        hashingAlgorithm = HashAlgorithm::MD5;
    } else if (selection == "SHA1") {
        hashingAlgorithm = HashAlgorithm::SHA1;
    } else if (selection == "SHA256") {
        hashingAlgorithm = HashAlgorithm::SHA256;
    } else {
        hashingAlgorithm = HashAlgorithm::SHA256;
    }
}

void MainWindow::setSaltAmount(int value)
{
    saltAmount = value;

    // Debug
    qDebug() << "Updated saltAmount: " << saltAmount;
}

//=========================================================================
// UI Buttons
//=========================================================================

void MainWindow::onButtonUploadHashesClicked()
{
    // Open a file dialog for hashes to crack.
    QString filePath = QFileDialog::getOpenFileName(this, "Select Hashes File", "", "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        // Convert QString to std::string
        std::string fileNameStd = QFileInfo(filePath).fileName().toUtf8().constData();
        std::string filePathStd = filePath.toUtf8().constData();

        // Add the file name and path to the std::unordered_map
        HashesFilesMap[fileNameStd] = filePathStd;

        // Add the file name to the QListWidget
        ui->list_UploadedHashlists->addItem(QFileInfo(filePath).fileName());
        
        // Print the filename and path to debug console
        qDebug() << "Added file: " << QString::fromStdString(fileNameStd) << " Path: " << QString::fromStdString(filePathStd);
    }
}


void MainWindow::onButtonUploadWordlistClicked()
{
    // Open a file dialog for wordlist to use.
    QString filePath = QFileDialog::getOpenFileName(this, "Select Wordlist File", "", "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        // Convert QString to std::string
        std::string fileNameStd = QFileInfo(filePath).fileName().toUtf8().constData();
        std::string filePathStd = filePath.toUtf8().constData();

        // Add the file name and path to the std::unordered_map
        WordlistFilesMap[fileNameStd] = filePathStd;

        // Add the file name to the QListWidget
        ui->list_UploadedWordlists->addItem(QFileInfo(filePath).fileName());
        
        // Print the filename and path to debug console
        qDebug() << "Added file: " << QString::fromStdString(fileNameStd) << " Path: " << QString::fromStdString(filePathStd);
    }
}

void MainWindow::onButtonCrackHashesClicked()
{
    ui->list_crackedHashes->clear(); // Clear the cracked hashes list

    int chunkSize = 1000; // TODO: Make this a user input field?
    FileHandler fileHandler(chunkSize);
    size_t totalHashesLines = fileHandler.countFilesLinesInMap(HashesFilesMap);
    size_t totalWordlistLines = fileHandler.countFilesLinesInMap(WordlistFilesMap);

    // Create a set to keep track of cracked hashes to avoid duplicates
    std::set<std::string> crackedHashSet;

    // Iterate over each wordlist file in WordlistFilesMap
    for (const auto& wlEntry : WordlistFilesMap) {
        // Get the wordlist file name and path
        std::string wlName = wlEntry.first;
        std::string wlPath = wlEntry.second;

        // Iterate over each hashed file in HashesFilesMap
        for (const auto& hashEntry : HashesFilesMap) {
            // Get the hashed file name and path
            std::string fileName = hashEntry.first;
            std::string filePath = hashEntry.second;

            // Read the hash set from the hashed file
            std::set<std::string> hashSet = fileHandler.readHashesFromFile(filePath);

            // Crack the hashes
            WordlistProcessor processor(fileHandler, hashSet, hashingAlgorithm, 0, saltAmount);
            bool readyForNextBatch = processor.compareWordlistChunk(wlPath);

            // Add cracked hashes to the set
            for (const auto& pair : processor.crackedHashes) {
                const std::string& hash = pair.first;
                // Check if the hash is not a duplicate
                if (crackedHashSet.find(hash) == crackedHashSet.end()) {
                    crackedHashSet.insert(hash);

                    // Convert std::string to QString
                    QString password = QString::fromStdString(pair.second);

                    // Create the display string for the QListWidgetItem
                    QString displayText = QString::fromStdString(hash) + ": " + password;

                    // Add the item to the list
                    ui->list_crackedHashes->addItem(displayText);
                }
            }
        }
    }

    QMessageBox::information(this, "Cracked" , "Cracked " + QString::number(crackedHashSet.size()) + " out of " + QString::number(totalHashesLines) + " hashes using " + QString::number(totalWordlistLines) + " words.");
    // TODO: Ask user to save result in a file

    // Display the QString in a QMessageBox
    // QMessageBox::information(this, "Single Hash", "The single hash is: " + QString::fromStdString(singleHash)
    //                                             + "\nHashing Algorithm: " + QString::fromStdString(hashingAlgorithm)
    //                                             + "\nSalt Amount: " + QString::number(saltAmount)
    //                                             + "\nTotal Hashes Lines: " + QString::number(totalHashesLines)
    //                                             + "\nTotal Wordlist Lines: " + QString::number(totalWordlistLines)
    //                                             );

}