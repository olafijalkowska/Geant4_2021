/*
* Kod oblicza objętoć N-wymiarowej kuli o promieniu r
* Wzory analityczne
* n = 0 V=1
* n = 1 V = 2*r
* n = 2 V = pi*r^2
* n = 3 V = 4/3 pi * r^3
* n = 4 V = pi^2/2 * r^4
* n = 5 V = 8*pi^2/15 * r^5
* n = 6 V = pi^3/6 * r^6
* n = 7 V = 16*pi^3/105 * r^7
* ...
* n = 12 V = pi^6/720*r^12
*
* losujemy N n-wymiarowych punktów z prostopadłościanu o boku 2R (czyli każda ze
  współrzędnych mieści się w przedziale (-R, R) )
  zliczamy punkty mieszczące się wewnątrz kuli o promieniu R (M)
  objętość kuli = M/N * V
  gdzie V to objętość prostopadłościanu o boku 2R czyli (2R)^n
*/


#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>

bool isInsideTheSphere(std::vector<double> point, double radius)
{

//fill the code
}

std::vector<double> makeRandomPoint(int size, double radius, std::default_random_engine& engine)
{
    double radiusStat = radius;
    std::uniform_real_distribution<double> dist(-radiusStat, radiusStat);
    std::vector<double> randomPoint;
    for(int i=0; i!=size; ++i)
        randomPoint.push_back(dist(engine));
    return randomPoint;
}

int main()
{
    int nrOfPoints = 100000;
    int size = 2;
    double radius = 1;
    std::random_device rd;
    std::default_random_engine engine(rd());
//fill the code
}


