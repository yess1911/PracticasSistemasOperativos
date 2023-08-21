#ifndef PROCESO_H
#define PROCESO_H

#include <iostream>

#define ERROR_FINISH 0
#define SUCCESSFUL_FINISH 1
#define ACTION_CODE -1

using namespace std;

class Proceso
{
private:
    string operacion;
    int id;
    int tiempoEstimado;
    int tiempoTranscurrido;
    int resultadoOperacion;
    bool finalizacion;

public:
    Proceso();
    void setNombre(const string &value);
    int getId() const;
    void setId(int value);
    int getTiempoEstimado() const;
    void setTiempoEstimado(int value);
    int getTiempoTranscurrido() const;
    void setTiempoTranscurrido(int value);
    int getResultadoOperacion() const;
    void setResultadoOperacion(int value);
    string getOperacion() const;
    void setOperacion(const string &value);
    bool getFinalizacion() const;
    void setFinalizacion(bool value);

    Proceso &operator=(const Proceso& p);
};

#endif // PROCESO_H
