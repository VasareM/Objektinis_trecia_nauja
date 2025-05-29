//#include "antrastes.h"
#include "strukt_antr.h"
#include "Vector_new.h"
//#include "antrastes_spartai.h"
//#include "kodas_vektoriai.cpp"

#include <iostream>
#include <iomanip>
#include <Vector>
#include <vector>
#include <chrono>
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

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::setw;
using std::ifstream;
using std::ofstream;
using std::string;
using std::sort;



//konstruktoriaus realizacija:
studentai::studentai(std::istream& is) {
    readStudent(is);
}
//copy constructor 
studentai::studentai(const studentai& v) 
    : Zmogus(v), //base klasės kopijavimas
    egzam_(v.egzam_), pazymiai_(v.pazymiai_),
    suma_(v.suma_), vidurkis_(v.vidurkis_), mediana_(v.mediana_), gal_med_(v.gal_med_), gal_vid_(v.gal_vid_) 
    {
}

//move constructor
studentai::studentai(studentai&& v)noexcept
    : Zmogus(std::move(v)), 
    egzam_(v.egzam_), pazymiai_(std::move(v.pazymiai_)),
    suma_(v.suma_), vidurkis_(v.vidurkis_), mediana_(v.mediana_), gal_med_(v.gal_med_), gal_vid_(v.gal_vid_) 
    {
    // resetinama
    v.egzam_ = 0;
    v.suma_ = 0;
    v.vidurkis_ = 0;
    v.mediana_ = 0;
    v.gal_med_ = 0;
    v.gal_vid_ = 0;
}

//copy assignment operator
studentai& studentai::operator=(const studentai& v)
{
    if (&v != this) // check for self-assignment
    {
        vardas_ = v.vardas_;
        pavarde_ = v.pavarde_;
        egzam_ = v.egzam_;
        pazymiai_ = v.pazymiai_;
        suma_ = v.suma_;
        vidurkis_ = v.vidurkis_;
        mediana_ = v.mediana_;
        gal_med_ = v.gal_med_;
        gal_vid_ = v.gal_vid_;
    }
    return *this;
}
//move assignment operator
studentai& studentai::operator=(studentai&& v) noexcept
{
    if (&v != this) // check for self-assignment
    {
        vardas_ = std::move(v.vardas_);
        pavarde_ = std::move(v.pavarde_);
        egzam_ = v.egzam_;
        pazymiai_ = std::move(v.pazymiai_);
        suma_ = v.suma_;
        vidurkis_ = v.vidurkis_;
        mediana_ = v.mediana_;
        gal_med_ = v.gal_med_;
        gal_vid_ = v.gal_vid_;
        
        // resettinama
        v.egzam_ = 0;
        v.suma_ = 0;
        v.vidurkis_ = 0;
        v.mediana_ = 0;
        v.gal_med_ = 0;
        v.gal_vid_ = 0;

        //return *this;
    }
    return *this;
}
// noexcept - nemeta exception'ų, kai transferinami duomenys

// input operator
std::istream& operator>>(std::istream& is, studentai& v)
{
    std::string line;
    if (!std::getline(is, line)) 
    {
        return is;
    }
    std::istringstream iss(line);
    v.pazymiai_.clear();
    iss >> v.vardas_ >> v.pavarde_;
    double paz_laik;
    while (iss >> paz_laik)
    {
        v.pazymiai_.push_back(paz_laik);
    }
    if (!v.pazymiai_.empty()) 
    {
        v.egzam_=v.pazymiai_.back();
        v.pazymiai_.pop_back();
    }
    else
    {
        v.egzam_=0;
    }

    //skaičiavimai:
    v.vidurkis_ = v.vidurkis();
    v.mediana_ = v.mediana();
    v.gal_vid_ = v.gal_vid();
    v.gal_med_ = v.gal_med();
    return is;
}
//output operator
std::ostream& operator<<(std::ostream& os, const studentai& v)
{
    os << std::left << setw(25) << v.pavarde_ << setw(20) << v.vardas_;
    os << setw(20) << std::fixed << std::setprecision(2) << v.gal_vid_ << setw(20) << v.gal_med_ << endl;
    return os;
}
//studentai::gal_balas realizacija
double studentai::gal_med() const 
{
    if (pazymiai_.empty()) return 0;
    return 0.4*mediana() + 0.6*egzam_;
}
double studentai::gal_vid() const{
    if (pazymiai_.empty()) return 0;
    return 0.4*vidurkis() + 0.6*egzam_;
}
int studentai::mediana() const {
    if (pazymiai_.empty()) return 0;
    Vector<double> temp = pazymiai_;
    std::sort(temp.begin(), temp.end());
    size_t size = temp.size();
    if (size%2==0)
    {
        return (temp[size/2-1]+temp[size/2])/2;
    }
    else 
    {
        return temp[size/2];
    }
}
double studentai::vidurkis() const {
    if (pazymiai_.empty()) return 0;
    double suma = 0;
    for (const auto& pazymys : pazymiai_)
    {
        suma += pazymys;
    }
    return suma/pazymiai_.size();
}
//studentai::readStudent realizacija
std::istream& studentai::readStudent(std::istream& is)
{
    // Member funkcijos realizacija paremta ankstesniojo 2-ojo darbo funkcija: 
    // std::istream& readStudent(std::istream&, Studentas&)
    pazymiai_.clear(); 
    is >> vardas_ >> pavarde_;

    double paz;
    while (is >> paz) {
        pazymiai_.push_back(paz);
    }
    // If stream failed but not at end, clear error for further use
    if (!is.eof()) is.clear();

    if (!pazymiai_.empty()) 
    {
        egzam_=pazymiai_.back();
        pazymiai_.pop_back();
    }
    else
    {
        egzam_=0;
    }
    //skaičiavimai:
    vidurkis_ = vidurkis();
    mediana_ = mediana();
    gal_vid_ = gal_vid();
    gal_med_ = gal_med();

    return is;
}

template <typename Vec>
void nuskaitymas(const string& failo_pavadinimas, Vec& grupe, int &n) 
{
    std::ios::sync_with_stdio(false); // Optimize input speed
    ifstream in;
    try {
        in.open(failo_pavadinimas);
        if (!in.is_open()) {
            throw std::runtime_error("Problema failo nuskaityme");
        }
    } 
    catch (const std::exception& e) {
        cout << e.what() << endl;
        return;
    }
    string eilute;
    n=-3;
    if (getline(in, eilute)) {
        std::istringstream ss(eilute);
        n = std::distance(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()) - 3;
    }
    while (getline(in, eilute)) 
    {
        std::istringstream iss(eilute);
        studentai temp;
        temp.readStudent(iss);
        grupe.push_back(std::move(temp)); // to optimize Vector insertion
    }
    in.close();
}

template <typename Vec>
void skaiciavimas(Vec& grupe, int n)
{
    for (auto& m:grupe)
    {
        m.setSuma(std::accumulate(m.pazymiai().begin(), m.pazymiai().end(), 0.0));
        m.setVidurkis(m.vidurkis());
        m.setMediana(m.mediana());
        m.setGalVid(m.gal_vid());
        m.setGalMed(m.gal_med());
    }
}

template <typename Vec>
void rikiavimas(int nr_rikiavimas, Vec &grupe)
{
    if (nr_rikiavimas==1) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.vardas()<b.vardas();});
    else if (nr_rikiavimas==2) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.pavarde()<b.pavarde();});
    else if (nr_rikiavimas==3) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.gal_vid()<b.gal_vid();});
    else if (nr_rikiavimas==4) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.gal_med()<b.gal_med();});
    else 
    {
        cout << "Tokio rikiavimo būdo nėra" << endl;
        return;
    }
}

template <typename Vec>
void spausdinimas_faile(const Vec& grupe, const string& outputo_pavadinimas)
{
    ofstream out (outputo_pavadinimas);
    out << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << string(85, '-') << endl;
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        out << std::left << setw(25) << m.pavarde() << setw(20) << m.vardas();
        out << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid() << setw(20) << m.gal_med() << endl;
    }
}
template <typename Vec>
void studentu_skaiciavimas(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    Vec grupe;
    nuskaitymas(failo_pavadinimas, grupe, n);

    skaiciavimas(grupe, n);
    Vec galvociai, nelaimingi;
    if (strategijos_nr==3)
    {
        rikiavimas(nr_rikiavimas, grupe);
        
        auto perskyrimas = std::stable_partition(grupe.begin(), grupe.end(), [&](const studentai& s) {
            return (nr_rikiavimas == 3 && s.gal_vid() < 5) || (nr_rikiavimas == 4 && s.gal_med() < 5);
        });
        nelaimingi.assign(grupe.begin(), perskyrimas);
        galvociai.assign(perskyrimas, grupe.end());
    } 
    spausdinimas_faile(nelaimingi, "nelaimingi_benchmarko.txt");
    spausdinimas_faile(galvociai, "galvociai_benchmarko.txt");
}



int main()
{
    int failu_dydziai[3]={100000, 1000000, 10000000};
    int test_kartai=1;

    std::cout << std::setw(20) << "Dydis"
              << std::setw(30) << "std::vector laikas (s)" 
              << std::setw(30) << "Vector laikas (s)" << std::endl;

    for (int i=0; i<3; i++)
    /////////// su vienu failu tik
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
            std_laikas+=trukme;
            
            auto pradzia2=std::chrono::high_resolution_clock::now();
            studentu_skaiciavimas<Vector<studentai>>(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
            auto pabaiga2=std::chrono::high_resolution_clock::now();
            auto trukme2=std::chrono::duration<double>(pabaiga2-pradzia2).count();
            Vector_laikas += trukme2;
            
        }
        std::cout << std::setw(20) << nr_failo_dydis
                  << std::setw(30) << std::fixed << std::setprecision(5) << (std_laikas / test_kartai)
                  << std::setw(30) << std::fixed << std::setprecision(5) << (Vector_laikas / test_kartai)
                  << std::endl;
    } 
    return 0;
}