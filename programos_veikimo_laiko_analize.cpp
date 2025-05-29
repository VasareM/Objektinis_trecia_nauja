#include "antrastes.h"
#include "strukt_antr.h"
#include "Vector_new.h"
#include "kodas_vektoriai.cpp"

#include <iostream>
#include <iomanip>
#include <Vector>
#include <vector>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::setw;

template <typename Vec>
void studentu_skaiciavimas(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    Vec <studentai> grupe;
    auto failo_nuskaitymo_pradzia=std::chrono::high_resolution_clock::now();
    nuskaitymas(failo_pavadinimas, grupe, n);
    auto failo_nuskaitymo_pabaiga = std::chrono::high_resolution_clock::now();
    auto failo_nuskaitymo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_nuskaitymo_pabaiga - failo_nuskaitymo_pradzia);
    cout << "Failo iš " << nr_failo_dydis << " įrašų nuskaitymo laikas: " << std::fixed << std::setprecision(5) << failo_nuskaitymo_trukme.count() << "s" << endl;
    ///
    skaiciavimas(grupe, n);
    Vec <studentai> galvociai, nelaimingi;
    if (strategijos_nr==3)
    {
        auto failo3_sort_pradzia=std::chrono::high_resolution_clock::now();
        rikiavimas(nr_rikiavimas, grupe);
        auto perskyrimas = std::stable_partition(grupe.begin(), grupe.end(), [&](const studentai& s) {
            return (nr_rikiavimas == 3 && s.gal_vid() < 5) || (nr_rikiavimas == 4 && s.gal_med() < 5);
        });
        auto failo3_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo3_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo3_sort_pabaiga - failo3_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su stable_partition funkcija: " << std::fixed << std::setprecision(5) << failo3_sort_trukme.count() << "s" << endl;
        auto failo3_dalijimo_pradzia=std::chrono::high_resolution_clock::now();

        nelaimingi.assign(grupe.begin(), perskyrimas);
        galvociai.assign(perskyrimas, grupe.end());
        auto failo3_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo3_dalijimo_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo3_dalijimo_pabaiga - failo3_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo3_dalijimo_trukme.count() << "s" << endl;
    } 
    spausdinimas_faile(nelaimingi, "nelaimingi_benchmarko.txt");
    spausdinimas_faile(galvociai, "galvociai_benchmarko.txt");
    cout << endl;
    auto pilna_pabaiga = std::chrono::high_resolution_clock::now();
    auto pilna_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(pilna_pabaiga - failo_nuskaitymo_pradzia);
    cout << nr_failo_dydis << " įrašų testo laikas: " << std::fixed << std::setprecision(5) << pilna_trukme.count() << "s" << endl;
    cout << endl << endl;
}



int main()
{
    int failu_dydziai[3]={100000, 1000000, 10000000};
    int test_kartai=1;

    std::cout << std::setw(12) << "Dydis"
              << std::setw(20) << "Vid. laikas (s)" << std::endl;

    for (int i=0; i<3; i++)
    {
        int nr_failo_dydis=failu_dydziai[i];
        double std_laikas=0.0, Vector_laikas=0.0;
        for (int k=0; k<test_kartai; ++k)
        {
            std::string failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
            int n=0;
            int nr_rikiavimas=3;
            int strategijos_nr=3;
            
            auto pradzia=std::chrono::high_resolution_clock::now();
            studentu_skaiciavimas<std::vector<studentai>>(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
            auto pabaiga=std::chrono::high_resolution_clock::now();
            auto trukme=std::chrono::duration<double>(pabaiga-pradzia).count();
            std_laikas+-trukme;

            auto pradzia2=std::chrono::high_resolution_clock::now();
            studentu_skaiciavimas<Vector<studentai>>(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
            auto pabaiga2=std::chrono::high_resolution_clock::now();
            auto trukme2=std::chrono::duration<double>(pabaiga2-pradzia2).count();
            Vector_laikas += trukme2;
        }
        std::cout << std::setw(12) << nr_failo_dydis
                  << std::setw(20) << std::fixed << std::setprecision(5) << (std_laikas / test_kartai)
                  << std::setw(20) << std::fixed << std::setprecision(5) << (Vector_laikas / test_kartai)
                  << std::endl;
    } 
    return 0;
}