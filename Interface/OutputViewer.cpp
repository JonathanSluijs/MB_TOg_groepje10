#include "OutputViewer.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QListWidget>

OutputViewer::OutputViewer(const QString& outputDir, const QStringList& allowedExtensions, QWidget* parent)
    : QDialog(parent), outputDirectory(outputDir), extensions(allowedExtensions) {
    setupUI();
    createEvents();
}

void OutputViewer::setupUI() {
    setWindowTitle("Output Files");
    resize(800, 600);

    fileListView = new QListWidget(this);
    openButton = new QPushButton("Open File", this);
    browseButton = new QPushButton("Open in Browser", this);

    layout = new QVBoxLayout(this);
    layout->addWidget(fileListView);
    layout->addWidget(openButton);
    layout->addWidget(browseButton);
    setLayout(layout);

    // Fill the list view with files
    updateFileList();
}

void OutputViewer::createEvents() {
    connect(openButton, &QPushButton::clicked, this, &OutputViewer::openFile);
    connect(browseButton, &QPushButton::clicked, this, &OutputViewer::browseFile);
}

void OutputViewer::updateFileList() {
    fileListView->clear();
    QDir dir(outputDirectory);
    QStringList files = dir.entryList(extensions, QDir::Files);
    fileListView->addItems(files);
}

void OutputViewer::openFile() {
    // Get the selected file
    QListWidgetItem* selectedItem = fileListView->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No files selected", "Select a file to open.");
        return;
    }

    QString filePath = QDir(outputDirectory).filePath(selectedItem->text());
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();

    if (ext == "txt") {
        // Open the file in the default text editor
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        QMessageBox::warning(this, "Invalid file", "Only .txt files can be opened here!");
    }
}

void OutputViewer::browseFile() {
    QListWidgetItem* selectedItem = fileListView->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No files selected", "Select a file to open in browser!");
        return;
    }

    QString filePath = QDir(outputDirectory).filePath(selectedItem->text());
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();

    if (ext == "html") {
        // Open the file in the default web browser
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        QMessageBox::warning(this, "Invalid file", "Only .html files can be opened in browser!");
    }
}
