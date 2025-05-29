#ifndef ANTRASTES_H
#define ANTRASTES_H

#include "strukt_antr.h"
#include "Vector_new.h"

#include <iostream>
#include <iomanip>
//#include <vector>
#include <string>
#include <algorithm> // kad veiktu sort
#include <ctime> //rand
#include <random>
#include <fstream>
#include <sstream>
#include <chrono> //laiko skaiciavimui
#include <ctime>
#include <numeric> //accumulate
#include <iterator> //istream_iterator

//using std::vector;
using std::string;

void vartotojo_pasirinkimas(int &nr_meniu, int a, int b);
bool ar_beda(int x, int pr, int pb);
bool ar_beda_bendras(int x, int pr, int pb);
int rand_pazymys();
void failo_generavimas(string failo_pavadinimas, int nr_failo_dydis, int paz_kiekis);
int mediana_skaiciavimas(Vector <int> &pazymiai, studentai &temp);
string vardo_generavimas();
string pavardes_generavimas();

void spausdinimas(Vector<studentai> grupe);
void spausdinimas_faile(Vector <studentai> grupe, const string& outputo_pavadinimas);

void rikiavimas(int nr_rikiavimas, Vector<studentai> &grupe);
void spausdinimo_parinkimas(Vector<studentai> grupe, int nr_spausdinimas, int nr_rikiavimas);


int sumos_skaiciavimas(Vector <int> &pazymiai, studentai &temp);
double vidurkio_skaiciavimas(Vector <int> &pazymiai, studentai &temp);
double galutinis_vid_sk(studentai &temp, double &vidurkis);
double galutinis_med_sk(studentai &temp, int &mediana);

/*
template <typename Container>
void spausdinimas_faile(const Container& grupe, const std::string& outputo_pavadinimas);
template <typename Container>
void nuskaitymas(const std::string& failo_pavadinimas, Container& grupe, int &n);
template <typename Container>
void skaiciavimas(Container& grupe, int n);
*/

void nuskaitymas(const string& failo_pavadinimas, Vector<studentai>& grupe, int &n);
void skaiciavimas(Vector<studentai>& grupe, int n);


#endif // ANTRASTES_H