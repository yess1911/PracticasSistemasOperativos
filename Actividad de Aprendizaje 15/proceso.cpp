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

std::istream &operator>>(std::istream &i, Proceso &p)
{
    std::string str;
    i >> p.id;
    i.get();
    getline(i,p.operacion,FIELD_SEPARATOR);
    getline(i,str,FIELD_SEPARATOR);
    p.resultadoOperacion = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.finalizacion = atoi(str.c_str()) == 1 ? true : false;
    getline(i,str,FIELD_SEPARATOR);
    p.estado = atoi(str.c_str()) == 1 ? true : false;
    getline(i,str,FIELD_SEPARATOR);
    p.quantum = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.tamanio = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.frames = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Estimado] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Transcurrido] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Bloqueado] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Llegada] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Finalizacion] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Retorno] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Respuesta] = atoi(str.c_str());
    getline(i,str,FIELD_SEPARATOR);
    p.times[Times::Espera] = atoi(str.c_str());
    getline(i,str);
    p.times[Times::Servicio] = atoi(str.c_str());

    return i;
}

std::ostream &operator<<(std::ostream &o, Proceso &p)
{
    o << p.getId() << FIELD_SEPARATOR;
    o << p.getOperacion() << FIELD_SEPARATOR;
    o << p.getResultadoOperacion() << FIELD_SEPARATOR;
    o << (p.getFinalizacion() ? 1 : 0) << FIELD_SEPARATOR;
    o << (p.estado ? 1 : 0) << FIELD_SEPARATOR;
    o << p.getQuantum() << FIELD_SEPARATOR;
    o << p.getTamanio() << FIELD_SEPARATOR;
    o << p.getFrames() << FIELD_SEPARATOR;
    o << p.getTiempoEstimado() << FIELD_SEPARATOR;
    o << p.getTiempoTranscurrido() << FIELD_SEPARATOR;
    o << p.getTiempoBloqueado() << FIELD_SEPARATOR;
    o << p.getTiempoLlegada() << FIELD_SEPARATOR;
    o << p.getTiempoFinalizacion() << FIELD_SEPARATOR;
    o << p.getTiempoRetorno() << FIELD_SEPARATOR;
    o << p.getTiempoRespuesta() << FIELD_SEPARATOR;
    o << p.getTiempoEspera() << FIELD_SEPARATOR;
    o << p.getTiempoServicio() << std::endl;

    return o;
}
