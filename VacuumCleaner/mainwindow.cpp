#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000")),
    game(new GameWidget(this))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(currentColor);
    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(startGame()));
    connect(ui->stopButton, SIGNAL(clicked()), game,SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game,SLOT(clear()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(setInterval(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(setCellNumber(int)));
    connect(game,SIGNAL(environmentChanged(bool)),ui->cellsControl,SLOT(setDisabled(bool)));
    connect(game,SIGNAL(gameEnds(bool)),ui->cellsControl,SLOT(setEnabled(bool)));

    ui->mainLayout->setStretchFactor(ui->gameLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);
    game->dustRemoved = ui->DustRemoved;
    game->jewelPicks = ui->JewelsPicks;
    game->jewelRemoved = ui->JewelsDestroyed;
    game->energyPerActions = ui->SpentEnergyPerActions;
    game->MachineSearch = ui->MachineSearch;
}

MainWindow::~MainWindow()
{
    delete ui;
}
