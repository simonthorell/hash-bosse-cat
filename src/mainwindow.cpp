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

    // Set window to fixed size
    this->setFixedSize(this->size()); // This sets the fixed size to the current size

    // Load the app logo image
    QPixmap pix(":/images/black_bosse.png");

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
    connect(ui->Button_RemoveHashes, SIGNAL(clicked()), this, SLOT(onButtonRemoveHashesClicked()));
    connect(ui->Button_UploadWordlist, SIGNAL(clicked()), this, SLOT(onButtonUploadWordlistClicked()));
    connect(ui->Button_RemoveWordlist, SIGNAL(clicked()), this, SLOT(onButtonRemoveWordlistClicked()));
    connect(ui->Button_CrackHashes, SIGNAL(clicked()), this, SLOT(onButtonCrackHashesClicked()));

    // Force UI to update and process any pending events
    QApplication::processEvents();
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

    app.setStyleSheet(
        // STYLE SHEET FOR QCOMBOBOX
        "QComboBox { background-color: #303030; color: white; }"
        "QToolTip { color: #ffffff; background-color: #000000; border: 1px solid white; }"
        "QPushButton { background-color: #303030; color: white; }"
        // STYLE SHEET FOR PROGRESS BAR
         "QProgressBar {"
        "    border: 2px solid grey;"
        "    border-radius: 5px;"
        "    background-color: #f0f0f0;"  // Light grey background
        "    text-align: center;"  // Center-align the text
        "    color: black;"  // Set the text color to black
        "}"
        "QProgressBar::chunk {"
        "    background-color: rgba(57, 255, 20, 128);"  // 50% transparent neon green
        "    width: 10px;"  // Width of the 'chunk'
        "    margin: 0.5px;"  // Optional: add slight spacing between chunks
        "}"
    );

    // Set the initial value of the progress bar to 0%
    setProgressBarValue(0);

    // STYLE SHEET FOR QSLIDER
    greyStyle = "QSlider::groove:horizontal {"
                "    border: 1px solid #999999;"
                "    height: 8px;"  // Groove thickness
                "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b1b1b1, stop:1 #c4c4c4);"
                "}"
                "QSlider::handle:horizontal {"
                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #f6f7fa);"
                "    border: 1px solid #5c5c5c;"
                "    width: 18px;"  // Handle width
                "    margin: -2px 0;"  // Handle margin
                "    border-radius: 3px;"  // Handle border radius
                "}"
                "QSlider::sub-page:horizontal {"
                "    background: grey;"  // Color for the filled part of the groove
                "}";

    neonGreenStyle = "QSlider::groove:horizontal {"
                    "    border: 1px solid #999999;"
                    "    height: 8px;"  // Groove thickness
                    "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b1b1b1, stop:1 #c4c4c4);"
                    "}"
                    "QSlider::handle:horizontal {"
                    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #f6f7fa);"
                    "    border: 1px solid #5c5c5c;"
                    "    width: 18px;"  // Handle width
                    "    margin: -2px 0;"  // Handle margin
                    "    border-radius: 3px;"  // Handle border radius
                    "}"
                    "QSlider::sub-page:horizontal {"
                    "    background: rgb(42, 130, 218);"  // Neon green color for the filled part of the groove
                    "}";

    // Initialize slider value from saltAmount variable
    ui->Slider_SelectSaltAmount->setValue(saltAmount);
    // Set the initial style of the slider based on the saltAmount value
    setSaltAmount(saltAmount);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    if (value == 0) {
        ui->Slider_SelectSaltAmount->setStyleSheet(greyStyle);
    } else {
        ui->Slider_SelectSaltAmount->setStyleSheet(neonGreenStyle);
    }

    // Force the widget to repaint itself
    ui->Slider_SelectSaltAmount->repaint();

    // Debug
    // qDebug() << "Updated saltAmount: " << saltAmount;
}

void MainWindow::setProgressBarValue(int progressPercentage)
{
    // Set the progress bar value (10 = 10%)
    ui->progressBar_CrackProgess->setValue(progressPercentage);

    // Force the widget to repaint itself
    ui->progressBar_CrackProgess->repaint();
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

        setProgressBarValue(0); // Reset the progress bar value
        
        // qDebug() << "Added file: " << QString::fromStdString(fileNameStd) << " Path: " << QString::fromStdString(filePathStd);
    }
}

void MainWindow::onButtonRemoveHashesClicked()
{
    // Get the selected item from the QListWidget
    QListWidgetItem* item = ui->list_UploadedHashlists->currentItem();

    // Check if an item is selected
    if (item) {
        // Get the item text
        QString itemText = item->text();
        // Remove the item from the QListWidget
        ui->list_UploadedHashlists->takeItem(ui->list_UploadedHashlists->row(item));
        // Remove the item from the std::unordered_map
        HashesFilesMap.erase(itemText.toUtf8().constData());

        setProgressBarValue(0); // Reset the progress bar value

        // qDebug() << "Removed file: " << itemText;
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

        setProgressBarValue(0); // Reset the progress bar value
        
        // qDebug() << "Added file: " << QString::fromStdString(fileNameStd) << " Path: " << QString::fromStdString(filePathStd);
    }
}

void MainWindow::onButtonRemoveWordlistClicked()
{
    // Get the selected item from the QListWidget
    QListWidgetItem* item = ui->list_UploadedWordlists->currentItem();

    // Check if an item is selected
    if (item) {
        // Get the item text
        QString itemText = item->text();
        // Remove the item from the QListWidget
        ui->list_UploadedWordlists->takeItem(ui->list_UploadedWordlists->row(item));
        // Remove the item from the std::unordered_map
        WordlistFilesMap.erase(itemText.toUtf8().constData());

        setProgressBarValue(0); // Reset the progress bar value

        // qDebug() << "Removed file: " << itemText;
    }
}

void MainWindow::onButtonCrackHashesClicked()
{
    ui->list_crackedHashes->clear(); // Clear the cracked hashes list

    int chunkSize = 50; // TODO: Make this a user input field?
    FileHandler fileHandler(chunkSize);
    size_t totalHashesLines = singleHash.empty() ? fileHandler.countFilesLinesInMap(HashesFilesMap) : 1;
    size_t totalWordlistLines = fileHandler.countFilesLinesInMap(WordlistFilesMap);

    // Create a set to keep track of cracked hashes to avoid duplicates
    std::set<std::string> crackedHashSet;
    // Create a hash set for processing
    std::set<std::string> hashSet;

    if (!singleHash.empty()) {
        // If singleHash is not empty, use only the singleHash for processing
        hashSet.insert(singleHash);
    } else {
        // If singleHash is empty, read hashes from files in HashesFilesMap
        for (const auto& hashEntry : HashesFilesMap) {
            // Get the hashed file name and path
            std::string filePath = hashEntry.second;
            // Merge the hashes from the file into hashSet
            std::set<std::string> fileHashSet = fileHandler.readHashesFromFile(filePath);
            hashSet.insert(fileHashSet.begin(), fileHashSet.end());
        }
    }

    // Progress bar variables
    int currentIndex = 0; // Initialize a counter for the current index
    int totalWordlists = WordlistFilesMap.size(); // Get the total number of wordlists

    // Process the hashes in hashSet against each wordlist in WordlistFilesMap
    for (const auto& wlEntry : WordlistFilesMap) {
        // Get the wordlist file name and path
        std::string wlPath = wlEntry.second;

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

        // Update the progress bar
        currentIndex++; // Increment the current index
        int progressPercentage = static_cast<int>(static_cast<double>(currentIndex) / totalWordlists * 100);
        setProgressBarValue(progressPercentage);
    }

    QMessageBox::information(this, "Cracked", "Cracked " + QString::number(crackedHashSet.size()) + " out of " + QString::number(totalHashesLines) + " hashes using " + QString::number(totalWordlistLines) + " words.");
    // TODO: Ask user to save result in a file
}
