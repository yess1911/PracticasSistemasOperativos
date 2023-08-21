#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <thread>
#include <chrono>
#include <random>
#include <functional>

#include <QTimer>
#include <QTime>
#include <QThread>
#include <QMessageBox>
#include <QKeyEvent>
#include <QtDebug>
#include <QEventLoop>
#include <QCloseEvent>

#include "proceso.h"

#define PAGES 5
#define FRAMES 49
#define FREE_PAGE 0
#define SO -4
#define FILE_NAME "suspended.txt"
#define TMP_FILE "tmp.txt"

enum Pages{CAPTURE_DATA,SHOW_PROCESSES,SHOW_TIMES_PROCESSES,SHOW_MEMORY_TABLE};
enum Operations{ADD, SUB, MULT, DIV, MOD, POW};
enum TableColumns{ID,STATE,LOCKED,OPERATION,RESULT,ARRIVED,FINISH,RETURN,WAITING,SERVICE,REMAINING,REQUEST};
enum ProgramStates{PAUSED,RUNNING};

struct Frame{
    int freePages = 5;
    int usedBy = FREE_PAGE;
    int state = FREE_PAGE;
};

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
    Proceso generarteProcess(int id);
    void createOperation(Proceso &p,int num1,int num2,int signOperator);
    void loadProcessesMemory();
    void startProcesses();
    void showReadyProcesses();
    void runProcess();
    void showFinishedProcesses(bool finishedType, Proceso& p);
    void interruptProcesss(Proceso& p);
    void showBlockedProcesses();
    void incrementBlockedTimes();
    void calculateProcessTimes(Proceso& p);
    void createProcessesTable();
    void showProcessesBcp();
    void createNewProcess();
    void delay();

    bool filledMemory();
    int availableFrames();
    void fillFrames(int size, int frames, int id, int state);
    void showMemoryTable();
    void updateFramesById(int id, int state);
    void deleteFramesById(int id, int state);

    void suspendProcess();
    void returnProcess();
    void updateFile();
    void updateNextSuspendLabel();

protected:

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

private slots:

    void on_processNumberSP_valueChanged(int arg1);

    void on_processAcountPB_clicked();

    void on_startRunPB_clicked();

    void enable_initialButton();

    void on_quantumSP_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QEventLoop pause;

    int capturedProcess = 0;
    int totalProcess;
    int globalCounter = 0;
    int newProcessesCount = 0;
    int quantum;
    int tT;
    int tR;
    bool state = RUNNING;
    bool interrupted = false;
    bool error = false;

    //Memory
    Frame memory[FRAMES];

    std::fstream file;
    int suspendedProcesses;

    std::vector<Proceso> newProcesses;
    std::vector<Proceso> readyProcesses;
    std::vector<Proceso> blockProcesses;
    std::vector<Proceso> finishedProcesses;
    std::vector<Proceso> processesTable;
};
#endif // MAINWINDOW_H
