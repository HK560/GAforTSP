#include "mainwindow.h"
#include "ui_mainwindow.h"
QT_CHARTS_USE_NAMESPACE//注意要加上这个

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //给lineedit填上默认值
    ui->cycleEdit->setText("100");
    ui->pcEdit->setText("0.5");
    ui->pmEdit->setText("0.3");
    ui->sizeEdit->setText("20");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_resultBtn_clicked()//
{
    try {
        //获取变量信息
        int size=ui->sizeEdit->text().toInt();
        double pc=ui->pcEdit->text().toDouble();
        double pm=ui->pmEdit->text().toDouble();
        int cycletime=ui->cycleEdit->text().toInt();

        if(size<=0||pc<=0||pm<=0||cycletime<=0){
            qDebug()<<"out";
            throw QString("输入值非法");
        }

//        QMessageBox *loadingDialog=new QMessageBox;
//        loadingDialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowStaysOnTopHint);
//        loadingDialog->setModal(false);
//        loadingDialog->exec();

        GA tsp;
        int path;

        tsp.init_races(size,30);//生成随机初始种群
        //    tsp.debugInitRaces();

        QLineSeries *series = new QLineSeries();

        int minPathGlobalValue=INT32_MAX;
        QVector<int> minPathGlobal;//用于存储最小路径
        QTime cTime;//用于计时
        cTime.start();
        int time=cycletime;
        while(time--){
            tsp.tournament(size,30);//选择个体（锦标赛选择）
            tsp.crossover(size,30,pc,pm);//交配
            QVector<int> minPath;
            path=tsp.getMinPathInPool(30,minPath);//取得当前路径
            series->append(cycletime - time,path);//给折线图添加点
            if(path<minPathGlobalValue){//存储最小路径
                minPathGlobalValue=path;
                minPathGlobal=minPath;
            }
            qDebug()<<"PATH:"<<path;
        }
        int runtime=cTime.elapsed();//结束计时
        //打印显示
        ui->runtime->setText(QString("花费时间:%1ms").arg(runtime));
        ui->pathValue->setText(QString::number(minPathGlobalValue));
        ui->path->setText(tsp.outputPath(minPathGlobal));
        //绘制折线图
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->createDefaultAxes();
        chart->setTitle(QString("遗传算法解决旅行商问题 PC:%1 PM:%2").arg(pc).arg(pm));
        QValueAxis *aX=new QValueAxis;
        QValueAxis *aY=new QValueAxis;
        aX->setTitleText("次数");
        aX->setLabelFormat("%d");
        aX->setTitleVisible(true);
        aY->setTitleVisible(true);
        aY->setLabelFormat("%d");
        aY->setTitleText("路径长度");
        chart->addAxis(aX,Qt::AlignBottom);
        chart->addAxis(aY,Qt::AlignLeft);
        chart->addSeries(series);
        series->attachAxis(aX);//需要先addSeries
        series->attachAxis(aY);
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        QMainWindow *chartV=new QMainWindow;
        chartV->setCentralWidget(chartView);
        chartV->resize(800, 500);
        chartV->show();
//        QVector<int>da={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};

//        QMessageBox::warning(this,"",QString::number(tsp.getPathLength(da,30)),QMessageBox::Ok);
        //loadingDialog->close();
    }  catch (QString warningInfo) {
        QMessageBox::warning(this,"警告",warningInfo);
    }

}

