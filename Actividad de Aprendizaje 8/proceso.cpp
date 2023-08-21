#include "proceso.h"

Proceso::Proceso()
{
    this->finalizacion = SUCCESSFUL_FINISH;
    this->ejecutado  = false;
}

Proceso::Proceso(int id, string operacion, int resultadoOperacion, bool  finalizacion)
{
    this->id = id;
    this->operacion = operacion;
    this->resultadoOperacion = resultadoOperacion;
    this->finalizacion = finalizacion;
}

Proceso &Proceso::operator=(const Proceso &p)
{
    this->id = p.getId();
    this->operacion = p.getOperacion();
    this->resultadoOperacion = p.getResultadoOperacion();

    this->ejecutado = p.getEjecutado();
    this->finalizacion = p.getFinalizacion();
    this->estado = p.estado;

    this->tiempoMaximoEstimado  = p.getTiempoMaximoEstimado();
    this->times[Times::Estimado] = p.getTiempoEstimado();
    this->times[Times::Transcurrido] = p.getTiempoTranscurrido();
    this->times[Times::Bloqueado] = p.getTiempoBloqueado();
    this->times[Times::Llegada] = p.getTiempoLlegada();
    this->times[Times::Finalizacion] = p.getTiempoFinalizacion();
    this->times[Times::Retorno] = p.getTiempoRetorno();
    this->times[Times::Respuesta] = p.getTiempoRespuesta();
    this->times[Times::Espera] = p.getTiempoEspera();
    this->times[Times::Servicio] = p.getTiempoServicio();

    return *this;
}

int Proceso::getId() const
{
    return id;
}

void Proceso::setId(int value)
{
    id = value;
}

string Proceso::getOperacion() const
{
    return operacion;
}

void Proceso::setOperacion(const string &value)
{
    operacion = value;
}

int Proceso::getResultadoOperacion() const
{
    return resultadoOperacion;
}

void Proceso::setResultadoOperacion(int value)
{
    resultadoOperacion = value;
}

bool Proceso::getFinalizacion() const{
    return finalizacion;
}

void Proceso::setFinalizacion(bool value){
    finalizacion = value;
}

bool Proceso::getEjecutado() const{
    return ejecutado;
}

void Proceso::setEjecutado(bool value){
    ejecutado = value;
}



int Proceso::getTiempoMaximoEstimado() const {
    return tiempoMaximoEstimado;
}

void Proceso::setTiempoMaximoEstimado(int value) {
    tiempoMaximoEstimado = value;
}

int Proceso::getTiempoEstimado() const
{
    return times[Times::Estimado];
}

void Proceso::setTiempoEstimado(int value)
{
    times[Times::Estimado]  = value;
}

int Proceso::getTiempoTranscurrido() const
{
    return times[Times::Transcurrido];
}

void Proceso::setTiempoTranscurrido(int value)
{
    times[Times::Transcurrido] = value;
}

int Proceso::getTiempoBloqueado() const
{
    return times[Times::Bloqueado];
}

void Proceso::setTiempoBloqueado(int value)
{
    times[Times::Bloqueado] = value;
}

int Proceso::getTiempoLlegada() const
{
    return times[Times::Llegada];
}

void Proceso::setTiempoLlegada(int value)
{
    times[Times::Llegada] = value;
}

int Proceso::getTiempoFinalizacion() const
{
    return times[Times::Finalizacion];
}

void Proceso::setTiempoFinalizacion(int value)
{
    times[Times::Finalizacion] = value;
}

int Proceso::getTiempoEspera() const
{
    return times[Times::Espera];
}

void Proceso::setTiempoEspera(int value)
{
    times[Times::Espera] = value;
}

int Proceso::getTiempoRetorno() const
{
    return times[Times::Retorno];
}

void Proceso::setTiempoRetorno(int value)
{
    times[Times::Retorno] = value;
}

int Proceso::getTiempoRespuesta() const
{
    return times[Times::Respuesta];
}

void Proceso::setTiempoRespuesta(int value)
{
    times[Times::Respuesta] = value;
}

int Proceso::getTiempoServicio() const
{
    return times[Times::Servicio];
}

void Proceso::setTiempoServicio(int value)
{
    times[Times::Servicio] = value;
}
