#ifndef PROCESO_H
#define PROCESO_H

#include <iostream>

#define ERROR_FINISH 0
#define SUCCESSFUL_FINISH 1
#define ACTION_CODE -1
#define BLOCKED_TIME 7
#define NULL_PROCESS 0

using namespace std;

namespace Times{

    enum {
        Estimado,
        Transcurrido,
        Bloqueado,
        Llegada,
        Finalizacion,
        Retorno,
        Respuesta,
        Espera,
        Servicio,
        Count
    };

}

namespace States {

    enum {
        New,
        Ready,
        Executing,
        Blocked,
        Finished,
        Count
    };

}

class Proceso
{
private:
    int id;
    string operacion;
    int resultadoOperacion;
    bool finalizacion;
    bool ejecutado;
    int quantum;
    int times[Times::Count] = {0};

public:
    int quantumaux;

    int estado = 0;
    Proceso();
    Proceso( int id, string operacion, int resultadoOperacion, bool  finalizacion );

    void setNombre(const string &value);
    int getId() const;
    void setId(int value);
    int getResultadoOperacion() const;
    void setResultadoOperacion(int value);
    string getOperacion() const;
    void setOperacion(const string &value);

    bool getFinalizacion() const;
    void setFinalizacion(bool value);
    bool getEjecutado() const;
    void setEjecutado(bool value);

    int getTiempoEstimado() const;
    void setTiempoEstimado(int value);

    int getTiempoTranscurrido() const;
    void setTiempoTranscurrido(int value);

    int getTiempoLlegada() const;
    void setTiempoLlegada(int value);

    int getTiempoRetorno() const;
    void setTiempoRetorno(int value);

    int getTiempoServicio() const;
    void setTiempoServicio(int value);

    int getTiempoFinalizacion() const;
    void setTiempoFinalizacion(int value);

    int getTiempoEspera() const;
    void setTiempoEspera(int value);

    int getTiempoBloqueado() const;
    void setTiempoBloqueado(int value);

    int getTiempoRespuesta() const;
    void setTiempoRespuesta(int value);

    int getQuantum() const;
    void setQuantum(int value);

    Proceso &operator=(const Proceso& p);
    bool operator<(const Proceso &p) {
        return this->id < p.id;
    }

    bool operator>(const Proceso &p) {
        return this->id > p.id;
    }

    friend ostream &operator<<(std::ostream &o, Proceso &p) {
        o << p.getId() << ",";
        o << p.getOperacion() << ",";
        o << p.getResultadoOperacion() << ",";
        o << p.getTiempoEstimado() << ",";
        o << p.getTiempoTranscurrido() << ",";
        o << p.getTiempoBloqueado() << ",";
        o << p.getTiempoLlegada() << ",";
        o << p.getTiempoFinalizacion() << ",";
        o << p.getTiempoRetorno() << ",";
        o << p.getTiempoEspera() << ",";
        o << p.getTiempoServicio();

        return o;
    }
};

#endif // PROCESO_H
