#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMessageBox>
#include <QMainWindow>
#include <QLineSeries>
#include <QValueAxis>
#include <QChartView>
#include <QChart>
#include<QDebug>
#include<QTime>
#include<QDialog>
#include <exception>
#include"location.h"
#include"ga.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_resultBtn_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
