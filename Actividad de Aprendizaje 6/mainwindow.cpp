#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Actividad 6");
    setFixedSize(480,480);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateProcesses(){

    Proceso p;
    int estimatedTime, num1, num2, signOperator, i;
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution_time(6,16);
    uniform_int_distribution<int> distribution_numbers(-100,100);
    uniform_int_distribution<int> distribution_sign(0,6);
    auto randomNumber = bind(distribution_numbers, generator);
    auto randomSign = bind( distribution_sign, generator );
    auto randomEstimatedTime = bind( distribution_time, generator );

    i = 0;
    while ( i < totalProcess ) {

        i++;
        p.setId(i);
        num1 = randomNumber();
        num2 = randomNumber();
        signOperator = randomSign();
        createOperation( p, num1, num2, signOperator );
        estimatedTime = randomEstimatedTime();
        p.setTiempoEstimado(estimatedTime);
        p.setTiempoMaximoEstimado(estimatedTime);
        newProcesses.push_back(p);
        newProcessesCount++;

    }

}

void MainWindow::createOperation(Proceso &p, int num1, int num2, int signOperator){

    int result;
    string operation = "";
    char sign;

    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution_numbers(-100,100);
    uniform_int_distribution<int> distribution_sign(0,6);
    auto randomNumber = bind(distribution_numbers, generator);

    switch(signOperator) {
        case ADD:
            while ( num2 < 0 ){
                num2 = randomNumber();
            }
            result = num1 + num2;
            sign = '+';
            break;
        case SUB:
            while ( num2 < 0 ){
                num2 = randomNumber();
            }
            result = num1 - num2;
            sign = '-';
            break;
        case MULT:
            result = num1 * num2;
            sign = '*';
            break;
        case DIV:
            while ( num2 == 0 or num1 < num2 ){
                num2 = randomNumber();
            }
            result = num1 / num2;
            sign = '/';
            break;
        case MOD:
            while ( num2 == 0 or num1 < num2){
                num2 = randomNumber();
            }
            result = num1 % num2;
            sign = '%';
            break;
        case POW:
            while ( num2 < 0 ){
                num2 = randomNumber();
            }
            result = pow(num1, num2);
            sign = '^';
            break;
        default:
            sign = '+';
            result = num1 + num2;
            break;
        }
    operation = to_string(num1) + sign + to_string(num2);
    p.setOperacion(operation);
    p.setResultadoOperacion(result);

}

void MainWindow::loadProcessesMemory(){
    for ( int i = 0; i < MAX_PROCESSES_IN_MEMORY and i < totalProcess; i++ ){
        Proceso p;
        p = newProcesses[0];
        p.setTiempoLlegada(globalCounter);
        newProcesses.erase(newProcesses.begin());
        readyProcesses.push_back(p);
    }
    totalProcess > MAX_PROCESSES_IN_MEMORY
            ? newProcessesCount = newProcessesCount - MAX_PROCESSES_IN_MEMORY
             : newProcessesCount = 0;
}

void MainWindow::startProcesses(){

    ui->newProcessesLCD->display(newProcessesCount);
    loadProcessesMemory();
    while ( readyProcesses.size() ){

        showReadyProcesses();
        runProcess();
        if ( readyProcesses.size() == 0 and blockProcesses.size() > 0 ){
            Proceso nullP( 0, "NULL", 0, false );
            readyProcesses.push_back(nullP);
        }

    }
    QMessageBox msg;
    msg.setWindowTitle("Proceso Finalizado");
    msg.setText("Todos los procesos han sido ejecutados");
    msg.exec();

    calculateProcessesTimes();
    ui->stackedWidget->setCurrentIndex(SHOW_TIMES_PROCESSES);
    setFixedSize(1320,720);
    showProcessesTimes();

}

void MainWindow::showReadyProcesses(){

    int rows = 0;
    int i = 1;
    Proceso p;
    ui->readyProcessesTB->setRowCount(0);
    while ( i < (int)readyProcesses.size() ) {

        p = readyProcesses[i];
        ui->readyProcessesTB->insertRow( ui->readyProcessesTB->rowCount() );
        ui->readyProcessesTB->setItem( rows, 0, new QTableWidgetItem( QString::number(p.getId()) ) );
        ui->readyProcessesTB->setItem( rows, 1, new QTableWidgetItem( QString::number(p.getTiempoEstimado()) ) );
        ui->readyProcessesTB->setItem( rows, 2, new QTableWidgetItem( QString::number(p.getTiempoTranscurrido()) ) );
        rows++;
        i++;

    }

}

void MainWindow::runProcess()
{
    qDebug() << "Ejecutado: " << readyProcesses[0].getEjecutado();

    readyProcesses[0].setFinalizacion(SUCCESSFUL_FINISH);
    if ( !readyProcesses[0].getEjecutado() ){
        readyProcesses[0].setEjecutado(true);
        qDebug() << "ID: " << readyProcesses[0].getId();
        qDebug() << "Tiempo llegada: " << readyProcesses[0].getTiempoLlegada();
        readyProcesses[0].setTiempoRespuesta( globalCounter - readyProcesses[0].getTiempoLlegada() );
        qDebug() << "Tiempo Respuesta: " << readyProcesses[0].getTiempoRespuesta();
    }

    tT = readyProcesses[0].getTiempoTranscurrido();
    tR = readyProcesses[0].getTiempoEstimado() - tT;
    interrupted = error = false;

    ui->processRuningTB->setItem(0,0,new QTableWidgetItem(QString::number(readyProcesses[0].getId())));
    ui->processRuningTB->setItem(1,0,new QTableWidgetItem(QString(readyProcesses[0].getOperacion().c_str())));
    ui->processRuningTB->setItem(2,0,new QTableWidgetItem(QString::number(readyProcesses[0].getTiempoEstimado())));
    ui->processRuningTB->setItem(3,0,new QTableWidgetItem(QString::number(readyProcesses[0].getTiempoTranscurrido())));
    ui->processRuningTB->setItem(4,0,new QTableWidgetItem(QString::number(tR)));

    if ( readyProcesses[0].getId() != NULL_PROCESS ) {

        while (tT < readyProcesses[0].getTiempoEstimado() and tT != ACTION_CODE ){
            tR--;
            tT++;
            readyProcesses[0].setTiempoTranscurrido(tT);
            ui->processRuningTB->setItem(3,0,new QTableWidgetItem(QString::number(readyProcesses[0].getTiempoTranscurrido())));
            ui->processRuningTB->setItem(4,0,new QTableWidgetItem(QString::number(tR)));

            if ( !blockProcesses.empty() ) {
                incrementBlockedTimes();
            }
            showBlockedProcesses();
            globalCounter++;
            ui->globalCountLCD->display(globalCounter);
            ui->newProcessesLCD->display(newProcessesCount);
            delay();
        }
        if ( interrupted ){
            interruptProcess(readyProcesses[0]);
        }
        else if ( error ) {
            showFinishedProcesses(ERROR_FINISH, readyProcesses[0]);
        } else {
            showFinishedProcesses(SUCCESSFUL_FINISH, readyProcesses[0]);
        }

    } else {

        while ( readyProcesses.size() < 2 ) {
            incrementBlockedTimes();
            globalCounter++;
            showBlockedProcesses();
            ui->globalCountLCD->display(globalCounter);
            ui->newProcessesLCD->display(newProcessesCount);
            delay();
        }

    }
    readyProcesses.erase(readyProcesses.begin());
    ui->stackedWidget->repaint();
    ui->processRuningTB->clearContents();

}

void MainWindow::showFinishedProcesses(bool finishedType, Proceso& p){

    if ( p.getId() != NULL_PROCESS ) {

        p.setTiempoFinalizacion(globalCounter);
        p.setFinalizacion(finishedType);
        finishedProcesses.push_back(p);

        int rowsFinished( ui->finishedTB->rowCount() );
        ui->finishedTB->insertRow(rowsFinished);
        ui->finishedTB->setItem( rowsFinished, 0, new QTableWidgetItem(QString::number(p.getId())) );
        ui->finishedTB->setItem( rowsFinished, 1, new QTableWidgetItem(QString(p.getOperacion().c_str())) );

        if ( finishedType == ERROR_FINISH ) {
            ui->finishedTB->setItem( rowsFinished, 2, new QTableWidgetItem(QString("ERROR")) );
        } else {
            ui->finishedTB->setItem( rowsFinished, 2, new QTableWidgetItem(QString::number(p.getResultadoOperacion())) );
        }
        if ( newProcesses.size() ) {
            Proceso p;
            p = newProcesses[0];
            newProcesses.erase(newProcesses.begin());
            p.setTiempoLlegada(globalCounter);
            readyProcesses.push_back(p);
            newProcessesCount--;
        }

    }

}

void MainWindow::interruptProcess(Proceso& p){
    blockProcesses.push_back(p);
    showBlockedProcesses();
}

void MainWindow::showBlockedProcesses() {

    Proceso p;
    int i = 0, row = 0;
    ui->blockTB->setRowCount(0);
    while ( i < (int)blockProcesses.size() ) {

        p = blockProcesses[i];
        ui->blockTB->insertRow(ui->blockTB->rowCount());
        ui->blockTB->setItem( row, 0, new QTableWidgetItem(QString::number( p.getId() )) );
        ui->blockTB->setItem( row, 1, new QTableWidgetItem(QString::number( p.getTiempoBloqueado() )) );
        i++;
        row++;

    }

}

void MainWindow::incrementBlockedTimes()
{
    for (auto it = blockProcesses.begin(); it != blockProcesses.end();){
        (*it).setTiempoBloqueado((*it).getTiempoBloqueado() + 1);

        if ((*it).getTiempoBloqueado() == BLOCKED_TIME){
            Proceso p;
            p = *it;
            p.setTiempoBloqueado(0);
            readyProcesses.push_back(p);
            blockProcesses.erase(it);
            showReadyProcesses();
        }
        else{
            it++;
        }
    }
}

void MainWindow::calculateProcessesTimes(){
    for (int i  = 0; i < (int)finishedProcesses.size(); i++ ) {
        Proceso& p = finishedProcesses[i];
        p.setTiempoRetorno(p.getTiempoFinalizacion() - p.getTiempoLlegada());
        p.setTiempoServicio(p.getTiempoTranscurrido());
        p.setTiempoEspera(p.getTiempoRetorno() - p.getTiempoServicio());
    }
}

void MainWindow::showProcessesTimes() {

    int row;
    Proceso p;

    ui->timesProcessesTB->setRowCount(0);
    for ( int i = 0; i < (int)finishedProcesses.size(); i++ ) {

        p = finishedProcesses[i];
        row = ui->timesProcessesTB->rowCount();
        ui->timesProcessesTB->insertRow(row);
        ui->timesProcessesTB->setItem( row, 0, new QTableWidgetItem( QString::number(p.getId()) ) );
        ui->timesProcessesTB->setItem( row, 1, new QTableWidgetItem( QString(p.getOperacion().c_str()) ) );
        if ( p.getFinalizacion() ) {
            ui->timesProcessesTB->setItem( row, 2, new QTableWidgetItem(QString::number(p.getResultadoOperacion())));
        } else {
            ui->timesProcessesTB->setItem( row, 2, new QTableWidgetItem( QString("ERROR") ) );
        }
        ui->timesProcessesTB->setItem(row,3,new QTableWidgetItem(QString::number(p.getTiempoMaximoEstimado())));
        ui->timesProcessesTB->setItem(row,4,new QTableWidgetItem(QString::number(p.getTiempoLlegada())));
        ui->timesProcessesTB->setItem(row,5,new QTableWidgetItem(QString::number(p.getTiempoFinalizacion())));
        ui->timesProcessesTB->setItem(row,6,new QTableWidgetItem(QString::number(p.getTiempoRetorno())));
        ui->timesProcessesTB->setItem(row,7,new QTableWidgetItem(QString::number(p.getTiempoRespuesta())));
        ui->timesProcessesTB->setItem(row,8,new QTableWidgetItem(QString::number(p.getTiempoEspera())));
        ui->timesProcessesTB->setItem(row,9,new QTableWidgetItem(QString::number(p.getTiempoServicio())));

    }


}

void MainWindow::delay()
{
    QTime delayTime = QTime::currentTime().addSecs(1);
    while ( QTime::currentTime() < delayTime ){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::on_processNumberSP_valueChanged(int arg1)
{
    if (arg1 > 0){
        ui->processAcountPB->setEnabled(true);
    }
    else{
        ui->processAcountPB->setEnabled(false);
    }
}

void MainWindow::on_processAcountPB_clicked()
{
    ui->processNumberSP->setEnabled(false);
    totalProcess = ui->processNumberSP->value();
    generateProcesses();
    ui->stackedWidget->setCurrentIndex(SHOW_PROCESSES);
    setFixedSize(1280,720);
}

void MainWindow::on_startRunPB_clicked()
{
    startProcesses();
    ui->startRunPB->setEnabled(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_E and state == RUNNING){
       qDebug() <<"Interrupcion";
       interrupted = true;
       tT = ACTION_CODE;
       //interruptProcess();
   }
   else if (event->key() == Qt::Key_W and state == RUNNING){
       qDebug() << "Error";
       error = true;
       tT = ACTION_CODE;
       //showFinishedProcesses(ERROR_FINISH);
   }
   else if (event->key() == Qt::Key_P and state == RUNNING){
       qDebug() << "Pause";
       state = PAUSED;
       pause.exec();
   }
   else if (event->key() == Qt::Key_C and state == PAUSED){
       qDebug() << "Continue";
       state = RUNNING;
       pause.quit();
   }
   else{
       qDebug() << "Nothing";
   }
}
