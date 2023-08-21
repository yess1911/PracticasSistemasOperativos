#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <random>
#include <functional>

#include <QTimer>
#include <QTime>
#include <QThread>
#include <QMessageBox>
#include <QKeyEvent>
#include <QtDebug>
#include <QMutex>
#include <QEventLoop>

#include "proceso.h"

#define MAX_PROCESSES_IN_MEMORY 3
#define NUMBER_TO_DELAY 500000000

enum Pages{CAPTURE_DATA, SHOW_PROCESSES, SHOW_TIMES_PROCESSES};
enum Operations{ADD, SUB, MULT, DIV, MOD, POW};
enum States{PAUSED, RUNNING};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateProcesses();
    void createOperation(Proceso &p, int num1, int num2, int signOperator);
    void loadProcessesMemory();
    void startProcesses();
    void showReadyProcesses();
    void runProcess();
    void showFinishedProcesses(bool finishedType, Proceso& p);
    void interruptProcess(Proceso& p);
    void showBlockedProcesses();
    void incrementBlockedTimes();
    void calculateProcessesTimes();
    void showProcessesTimes();
    void delay();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

    void on_processNumberSP_valueChanged(int arg1);

    void on_processAcountPB_clicked();

    void on_startRunPB_clicked();

private:
    Ui::MainWindow *ui;
    QEventLoop pause;

    int capturedProcess = 0;
    int totalProcess;
    int globalCounter = 0;
    int newProcessesCount = 0;
    int tT;
    int tR;
    bool state =  RUNNING;
    bool error = false;
    bool interrupted = false;

    vector<Proceso> newProcesses;
    vector<Proceso> readyProcesses;
    vector<Proceso> blockProcesses;
    vector<Proceso> finishedProcesses;
};
#endif // MAINWINDOW_H
