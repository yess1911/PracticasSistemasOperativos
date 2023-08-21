#ifndef PROCESO_H
#define PROCESO_H

#include <iostream>

#define ERROR_FINISH 0
#define SUCCESFUL_FINISH 1
#define ACTION_CODE -1
#define BLOCKED_TIME 7
#define NULL_PROCESS 0
#define PAGES_PER_FRAME 5

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
        Nuevo,
        Listo,
        Ejecutandose,
        Bloqueado,
        Finalizado,
        Count
    };
}

class Proceso
{
private:
    int id;
    std::string operacion;
    int resultadoOperacion;
    bool finalizacion;
    bool ejecutado;
    //Times
    int quantum;
    int tamanio;
    int frames;
    int times[Times::Count] = {0};

public:
    int quantumaux;

    //State could be a public variable
    int estado = 0;
    Proceso();
    Proceso(int id, std::string operacion, int resultadoOperacion,bool finalizacion);
    //Getters and Setters
    int getId() const;
    void setId(int value);
    int getResultadoOperacion() const;
    void setResultadoOperacion(int value);
    std::string getOperacion() const;
    void setOperacion(const std::string &value);
    bool getFinalizacion() const;
    void setFinalizacion(bool value);
    bool getEjecutado() const;
    void setEjecutado(bool value);
    void setTamanio(int value);
    int getTamanio() const;
    int getFrames() const;
    //Times getters and setters
    int getTiempoMaximoEstimado() const;
    void setTiempoMaximoEstimado(int value);
    int getTiempoEstimado() const;
    void setTiempoEstimado(int value);
    int getTiempoTranscurrido() const;
    void setTiempoTranscurrido(int value);
    int getTiempoBloqueado() const;
    void setTiempoBloqueado(int value);
    int getTiempoLlegada() const;
    void setTiempoLlegada(int value);
    int getTiempoFinalizacion() const;
    void setTiempoFinalizacion(int value);
    int getTiempoRetorno() const;
    void setTiempoRetorno(int value);
    int getTiempoRespuesta() const;
    void setTiempoRespuesta(int value);
    int getTiempoEspera() const;
    void setTiempoEspera(int value);
    int getTiempoServicio() const;
    void setTiempoServicio(int value);
    void setQuantum(int value);
    int getQuantum() const;

    //Operators overload
    Proceso &operator=(const Proceso& p);
    bool operator<(const Proceso& p);
    bool operator>(const Proceso& p);
    friend std::ostream& operator<< (std::ostream&,Proceso&);
};

#endif // PROCESO_H
