#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Actividad 8");
    setFixedSize(480,480);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateProcesses(){

    int estimatedTime, num1, num2, signOperator;
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution_time(6,16);
    uniform_int_distribution<int> distribution_numbers(-100,100);
    uniform_int_distribution<int> distribution_sign(0,6);
    auto randomNumber = bind(distribution_numbers, generator);
    auto randomSign = bind( distribution_sign, generator );
    auto randomEstimatedTime = bind( distribution_time, generator );

    for ( int i = 0; i < totalProcess; ) {

        i++;
        Proceso p;
        p.setId(i);
        num1 = randomNumber();
        num2 = randomNumber();
        signOperator = randomSign();
        createOperation( p, num1, num2, signOperator );
        estimatedTime = randomEstimatedTime();
        p.setTiempoEstimado(estimatedTime);
        p.setTiempoMaximoEstimado(estimatedTime);
        p.estado = States::New;
        newProcesses.push_back(p);
        newProcessesCount++;

    }

}

Proceso MainWindow::generarteProcess(int id){

    Proceso p;
    int estimatedTime, num1, num2, signOperator;
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution_time(6,16);
    uniform_int_distribution<int> distribution_numbers(-100,100);
    uniform_int_distribution<int> distribution_sign(0,6);
    auto randomNumber = bind(distribution_numbers, generator);
    auto randomSign = bind( distribution_sign, generator );
    auto randomEstimatedTime = bind( distribution_time, generator );
    p.setId(id);
    num1 = randomNumber();
    num2 = randomNumber();
    signOperator = randomSign();
    createOperation( p, num1, num2, signOperator );
    estimatedTime = randomEstimatedTime();
    p.setTiempoEstimado(estimatedTime);
    p.setTiempoMaximoEstimado(estimatedTime);
    p.estado = States::New;

    return p;

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
        while ( num2 == 0 or num1 < num2 ){
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
        p.estado = States::Ready;
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
    msg.setWindowTitle("Procesos Terminados");
    msg.setText("Todos los procesos han sido ejecutados");
    msg.exec();

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
    readyProcesses[0].estado = States::Executing;
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
        p.estado = States::Finished;
        calculateProcessesTimes(p);
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
            p.estado = States::Ready;
            readyProcesses.push_back(p);
            newProcessesCount--;

        }

    }

}

void MainWindow::interruptProcess(Proceso& p){
    p.estado = States::Blocked;
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
            p.estado = States::Ready;
            readyProcesses.push_back(p);
            blockProcesses.erase(it);
            showReadyProcesses();
        } else{
            it++;
        }
    }
}

void MainWindow::calculateProcessesTimes( Proceso& p ){

    if ( p.estado == States::Finished ){
        p.setTiempoRetorno(p.getTiempoFinalizacion() - p.getTiempoLlegada());
        p.setTiempoServicio(p.getTiempoTranscurrido());
        p.setTiempoEspera( p.getTiempoRetorno() - p.getTiempoServicio() );
    }
    else if ( p.estado != States::New ) {
        p.setTiempoServicio(p.getTiempoTranscurrido());
        p.setTiempoEspera( globalCounter - p.getTiempoTranscurrido() );
    }

}

void MainWindow::createProcessesTable() {

    int i;
    if ( !processesTable.empty() ) {
        processesTable.clear();
    }
    for ( i = 0; i < totalProcess; i++ ) {

        if ( i < (int)readyProcesses.size() ) {
            processesTable.push_back(readyProcesses[i]);
        }
        if ( i < (int)blockProcesses.size() ) {
            processesTable.push_back(blockProcesses[i]);
        }
        if ( i < (int)newProcesses.size() ) {
            processesTable.push_back(newProcesses[i]);
        }
        if ( i < (int)finishedProcesses.size() ) {
            processesTable.push_back(finishedProcesses[i]);
        }

    }
    sort( processesTable.begin(), processesTable.end() );

}

void MainWindow::showProcessesTimes() {

    int row;
    Proceso p;
    QString stateProcess, result, request, arrived, finished, retorn, waiting, service, locked, remaining, operation;

    createProcessesTable();

    ui->timesProcessesTB->setRowCount(0);
    for ( int i = 0; i < (int)processesTable.size(); i++ ) {

        p = processesTable[i];
        calculateProcessesTimes(p);
        row = ui->timesProcessesTB->rowCount();
        ui->timesProcessesTB->insertRow(row);
        ui->timesProcessesTB->setItem(row,ID,new QTableWidgetItem(QString::number(p.getId())));

        switch(p.estado) {
            case States::Finished:
            case States::Ready:
            case States::Blocked:
            case States::Executing:
                arrived  = QString::number(p.getTiempoLlegada());
                service  = QString::number(p.getTiempoServicio());
                operation = QString(p.getOperacion().c_str());
                waiting  = QString::number(p.getTiempoEspera());
                if ( p.getTiempoBloqueado() != 0 ) {
                    locked = QString::number(7-p.getTiempoBloqueado());
                } else {
                    locked = "0";
                }
                if ( tR != 0 ) {
                    remaining = QString::number(p.getTiempoEstimado()-p.getTiempoTranscurrido());
                } else {
                    remaining = "0";
                }

                switch(p.estado) {
                    case States::Finished:
                        finished  = QString::number(p.getTiempoFinalizacion());
                        retorn = QString::number(p.getTiempoRetorno());
                        request = QString::number(p.getTiempoRespuesta());
                        if ( p.getFinalizacion() ) {
                            result = QString::number(p.getResultadoOperacion());
                        } else {
                            result = finished = retorn = arrived = service = request = waiting = locked = remaining = operation ="ERROR";
                        }
                        break;
                default:
                    result = finished = retorn = request = "NULL";
                }
                break;
        default:
            result = finished = retorn = arrived = service = request = waiting = locked = remaining = operation ="NULL";
            break;
        }
        switch(p.estado) {
            case States::Ready: stateProcess = "LISTO"; break;
            case States::New: stateProcess = "NUEVO"; break;
            case States::Executing: stateProcess = "EJECUCIÓN"; break;
            case States::Blocked: stateProcess = "BLOQUEADO"; break;
            case States::Finished: stateProcess = "FINALIZADO"; break;
            default: ;
        }
        ui->timesProcessesTB->setItem(row,STATE,new QTableWidgetItem(stateProcess));
        ui->timesProcessesTB->setItem(row,LOCKED,new QTableWidgetItem(locked));
        ui->timesProcessesTB->setItem(row,OPERATION,new QTableWidgetItem(operation));
        ui->timesProcessesTB->setItem(row,RESULT,new QTableWidgetItem(result));
        ui->timesProcessesTB->setItem(row,ARRIVED,new QTableWidgetItem(arrived));
        ui->timesProcessesTB->setItem(row,FINISH,new QTableWidgetItem(finished));
        ui->timesProcessesTB->setItem(row,RETURN,new QTableWidgetItem(retorn));
        ui->timesProcessesTB->setItem(row,WAITING,new QTableWidgetItem(waiting));
        ui->timesProcessesTB->setItem(row,SERVICE,new QTableWidgetItem(service));
        ui->timesProcessesTB->setItem(row,REMAINING,new QTableWidgetItem(remaining));
        ui->timesProcessesTB->setItem(row,REQUEST,new QTableWidgetItem(request));
    }

}

void MainWindow::createNewProcess() {

    Proceso p;
    p = generarteProcess(totalProcess + 1);

    if ( (int)(readyProcesses.size() + blockProcesses.size() ) < MAX_PROCESSES_IN_MEMORY ) {
        p.estado = States::Ready;
        p.setTiempoLlegada(globalCounter);
        readyProcesses.push_back(p);
        showReadyProcesses();
    } else {
        p.estado = States::New;
        newProcesses.push_back(p);
        newProcessesCount++;
    }
    totalProcess++;

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
       qDebug() <<"Interrupción por entrada-salida";
       interrupted = true;
       tT = ACTION_CODE;

   }
   else if (event->key() == Qt::Key_W and state == RUNNING){
       qDebug() << "Error";
       error = true;
       tT = ACTION_CODE;

   }
   else if (event->key() == Qt::Key_P and state == RUNNING){
       qDebug() << "Pausa";
       state = PAUSED;
       pause.exec();
   }
   else if (event->key() == Qt::Key_C and state == PAUSED){
       qDebug() << "Continuar";
       state = RUNNING;
       if ( ui->stackedWidget->currentIndex() == SHOW_TIMES_PROCESSES ){
           ui->stackedWidget->setCurrentIndex(SHOW_PROCESSES);
       }
       pause.quit();
   }
   else if ( event->key() == Qt::Key_N and state == RUNNING ){
       qDebug() << "Nuevo";
       createNewProcess();
   }
   else if ( event->key() == Qt::Key_B and state == RUNNING ) {
       qDebug() << "Tabla de procesos";
       state = PAUSED;
       ui->stackedWidget->setCurrentIndex(SHOW_TIMES_PROCESSES);
       showProcessesTimes();
       this->setFocus();
       pause.exec();
       this->setFocus();
   }
   else{
       qDebug() << "Nada";
   }
}
