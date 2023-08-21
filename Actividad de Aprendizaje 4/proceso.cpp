#include "proceso.h"

std::string Proceso::getOperacion() const
{
    return operacion;
}

void Proceso::setOperacion(const std::string &value)
{
    operacion = value;
}

Proceso &Proceso::operator=(const Proceso &p)
{
    this->id = p.getId();
    this->operacion = p.getOperacion();
    this->tiempoEstimado = p.getTiempoEstimado();
    this->tiempoTranscurrido = p.getTiempoTranscurrido();
    this->resultadoOperacion = p.getResultadoOperacion();

    return *this;
}

Proceso::Proceso()
{
    tiempoTranscurrido=0;
}

int Proceso::getId() const
{
    return id;
}

void Proceso::setId(int value)
{
    id = value;
}

int Proceso::getTiempoEstimado() const
{
    return tiempoEstimado;
}

void Proceso::setTiempoEstimado(int value)
{
    tiempoEstimado = value;
}

int Proceso::getTiempoTranscurrido() const
{
    return tiempoTranscurrido;;
}

void Proceso::setTiempoTranscurrido(int value)
{
    tiempoTranscurrido = value;
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
