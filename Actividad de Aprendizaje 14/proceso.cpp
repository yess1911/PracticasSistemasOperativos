#include "proceso.h"

Proceso::Proceso()
{
    this->finalizacion = SUCCESFUL_FINISH;
    this->ejecutado = false;
}

Proceso::Proceso(int id, std::string operacion, int resultadoOperacion, bool finalizacion)
{
    this->id = id;
    this->operacion = operacion;
    this->resultadoOperacion = resultadoOperacion;
    this->finalizacion = finalizacion;
}

//Getters and setters

int Proceso::getId() const
{
    return id;
}

void Proceso::setId(int value)
{
    id = value;
}

std::string Proceso::getOperacion() const
{
    return operacion;
}

void Proceso::setOperacion(const std::string &value)
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

bool Proceso::getFinalizacion() const
{
    return finalizacion;
}

void Proceso::setFinalizacion(bool value)
{
    finalizacion = value;
}

bool Proceso::getEjecutado() const
{
    return ejecutado;
}

void Proceso::setEjecutado(bool value)
{
    ejecutado = value;
}

void Proceso::setTamanio(int value)
{
    tamanio = value;
    frames = (tamanio / PAGES_PER_FRAME) + (tamanio % PAGES_PER_FRAME == 0 ? 0 : 1);
}

int Proceso::getTamanio() const
{
    return tamanio;
}

int Proceso::getFrames() const
{
    return frames;
}

//Times

int Proceso::getTiempoEstimado() const
{
    return times[Times::Estimado];
}

void Proceso::setTiempoEstimado(int value)
{
    times[Times::Estimado] = value;
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

void Proceso::setQuantum(int value)
{
    quantum = value;
}

int Proceso::getQuantum() const
{
    return quantum;
}

//Operators

Proceso &Proceso::operator=(const Proceso &p)
{
    this->id = p.getId();
    this->operacion = p.getOperacion();
    this->resultadoOperacion = p.getResultadoOperacion();
    this->finalizacion = p.getFinalizacion();
    //Times
    this->times[Times::Estimado] = p.getTiempoEstimado();
    this->times[Times::Transcurrido] = p.getTiempoTranscurrido();
    this->times[Times::Bloqueado] = p .getTiempoBloqueado();
    this->times[Times::Llegada] = p.getTiempoLlegada();
    this->times[Times::Finalizacion] = p.getTiempoFinalizacion();
    this->times[Times::Retorno] = p.getTiempoRetorno();
    this->times[Times::Respuesta] = p.getTiempoRespuesta();
    this->times[Times::Espera] = p.getTiempoEspera();
    this->times[Times::Servicio] = p.getTiempoServicio();
    this->quantum = p.getQuantum();
    //State
    this->ejecutado = p.getEjecutado();
    this->estado = p.estado;
    //Memory
    this->tamanio = p.getTamanio();
    this->frames = p.getFrames();

    return *this;
}

bool Proceso::operator<(const Proceso &p)
{
    return this->id < p.id;
}

bool Proceso::operator>(const Proceso &p)
{
    return this->id > p.id;
}

std::ostream &operator<<(std::ostream &o, Proceso &p)
{
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
    o << p.getTiempoServicio() << ",";
    o << p.getQuantum();
    return o;
}
