//
// Created by emir on 11/16/24.
//

#include "MainWindow.h"
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent, int width, int height) {
    setFixedSize(width, height);
    setWindowTitle("Turing Tutor");
    createGraphics();
    createEvents();
}

MainWindow::~MainWindow() {
}

void MainWindow::createGraphics() {
    setStyleSheet("background-color: lightblue;");

    // Load the first image
    QLabel *math = new QLabel;
    QPixmap pixmap_math("../Images/math.png");
    if (pixmap_math.isNull()) {
        qWarning("Can not load image math.png!");
        return;
    }
    math->setPixmap(pixmap_math);

    //Load the second image
    QLabel *computer_science = new QLabel;
    QPixmap pixmap_cs("../Images/cs.png");
    if (pixmap_cs.isNull()) {
        qWarning("Can not load image cs.png!");
        return;
    }
    computer_science->setPixmap(pixmap_cs);

    // Position the images
}

void MainWindow::createEvents() const {
}

void MainWindow::toElementaryStudent() {
}

void MainWindow::toCSStudent() {
}
