//
// Created by emir on 11/16/24.
//

#include "MainWindow.h"
#include "ArithmeticDialog.h"
#include "TuringSimulationDialog.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>

MainWindow::MainWindow(const int width, const int height, QWidget *parent) {
    setFixedSize(width, height);
    setWindowTitle("Turing Tutor");
    createGraphics();
    createEvents();
}


void MainWindow::createGraphics() {
    setStyleSheet("background-color: lightblue;");

    // Create a central widget
    // A QMainWindow object has already its own layout so this has to be done
    QWidget *centralWidget = new QWidget(this);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    // Add the first picture to the layout
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QLabel *mathLabel = new QLabel;
    QPixmap pixmapMath("../Interface/Images/math.png");
    if (pixmapMath.isNull()) {
        qWarning("Can not load image math.png!");
    } else {
        mathLabel->setPixmap(pixmapMath.scaled(480, 360, Qt::KeepAspectRatio));
    }
    leftLayout->addWidget(mathLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(leftLayout);

    // Add button to the layout
    math_calculator = new QPushButton("Calculator", this);
    math_calculator->setStyleSheet("background-color: blue;");
    math_calculator->setFixedSize(200, 50);
    leftLayout->addWidget(math_calculator, 0, Qt::AlignCenter);

    // Add the second picture to the layout
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QLabel *csLabel = new QLabel;
    QPixmap pixmapCS("../Interface/Images/cs.png");
    if (pixmapCS.isNull()) {
        qWarning("Can not load image cs.png");
    } else {
        csLabel->setPixmap(pixmapCS.scaled(480, 360, Qt::KeepAspectRatio));
    }
    rightLayout->addWidget(csLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(rightLayout);

    // Add button to the layout
    turing_simulator = new QPushButton("TM Simulator", this);
    turing_simulator->setStyleSheet("background-color: blue;");
    turing_simulator->setFixedSize(200, 50);
    rightLayout->addWidget(turing_simulator, 0, Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}


void MainWindow::createEvents() const {
    QObject::connect(math_calculator, SIGNAL(clicked()), this, SLOT(toCalculator()));

    QObject::connect(turing_simulator, SIGNAL(clicked()), this, SLOT(toTMSimulator()));
}

void MainWindow::toCalculator() {
    ArithmeticDialog arithmetic_dialog("../InputFiles/expressionCNF.json", this);
    arithmetic_dialog.exec();
}

void MainWindow::toTMSimulator() {
    TuringSimulationDialog simulation_dialog("../InputFiles/expressionCNF.json", "../InputFiles/expressionCFG.json",
                                             this);
    simulation_dialog.exec();
}
