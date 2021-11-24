#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GA tsp;
    tsp.init_races(20,30);
    tsp.debugInitRaces();
    tsp.tournament(20,30);
    tsp.crossover(20,30,0.3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

