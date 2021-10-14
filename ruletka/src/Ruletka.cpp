#include "Ruletka.h"

Ruletka::Ruletka(std::default_random_engine& engine)
{
    myEngine = engine;
}

Ruletka::~Ruletka() {}

Uczciwa::Uczciwa(std::default_random_engine& engine): Ruletka(engine) {}

Europejska::Europejska(std::default_random_engine& engine): Ruletka(engine) {}

Amerykanska::Amerykanska(std::default_random_engine& engine): Ruletka(engine) {}

int Uczciwa::zakrec()
{
    std::uniform_int_distribution<> distrib(1, 36);
    return distrib(myEngine);
}

int Europejska::zakrec()
{
    std::uniform_int_distribution<> distrib(0, 36);
    return distrib(myEngine);
}

int Amerykanska::zakrec()
{
    std::uniform_int_distribution<> distrib(-1, 36);
    return distrib(myEngine);
}



