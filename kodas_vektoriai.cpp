#include "antrastes.h"
#include "strukt_antr.h"
#include "Vector_new.h"


#include <exception>
#include <limits>

#include <iostream>
#include <Vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <list>
#include <deque>
#include <cassert>


using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::setw;
using std::ifstream;
using std::ofstream;
using std::sort;
using std::list;
using std::deque;


//konstruktoriaus realizacija:
studentai::studentai(std::istream& is) {
    readStudent(is);
}
//copy constructor 
//manau reikės pakeisti pagal situaciją
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
/*
studentai::studentai(std::initializer_list<double> il) {
    pazymiai_ = il;
}
    */
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
    //std::cout << "Parsed vardas: " << v.vardas_ << ", pavarde: " << v.pavarde_ << std::endl;
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
    /*
    std::cout << "Parsed pazymiai: ";
    for (const auto& paz : v.pazymiai_) {
        std::cout << paz << " ";
    }
    std::cout << "\nEgzam: " << v.egzam_ << std::endl;
    */
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
/*
double mediana_skaiciavimas(const Vector<double>& pazymiai_) 
{
    if (pazymiai_.empty()) return 0;
    Vector<double> temp = pazymiai_;
    std::sort(temp.begin(), temp.end());
    size_t size=temp.size();
    if (size%2==0)
    {
        return (temp[size/2-1]+temp[size/2])/2;
    }
    else 
    {
        return temp[size/2];
    }
}
double vidurkis_skaiciavimas(const Vector<double>& pazymiai_)
{
    if (pazymiai_.empty()) return 0;
    double suma=0;
    for (const auto& pazymys : pazymiai_)
    {
        suma += pazymys;
    }
    return suma/pazymiai_.size();
}
*/
void skaiciavimas(Vector <studentai>& grupe, int n)
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
  
// Ne Studentas member funkcija, bet dirba su Studentas objektais, todėl realizacija čia
/*
bool comparePagalVid(const studentai& a, const studentai& b) {
    return a.gal_vid() < b.gal_vid();
}
bool comparePagalMed(const studentai& a, const studentai& b) {
    return a.gal_med() < b.gal_med();
}
*/

void septintas_meniu(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    Vector <studentai> grupe;
    auto failo_nuskaitymo_pradzia=std::chrono::high_resolution_clock::now();
    nuskaitymas(failo_pavadinimas, grupe, n);
    auto failo_nuskaitymo_pabaiga = std::chrono::high_resolution_clock::now();
    auto failo_nuskaitymo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_nuskaitymo_pabaiga - failo_nuskaitymo_pradzia);
    cout << "Failo iš " << nr_failo_dydis << " įrašų nuskaitymo laikas: " << std::fixed << std::setprecision(5) << failo_nuskaitymo_trukme.count() << "s" << endl;
    ///
    skaiciavimas(grupe, n);
    Vector <studentai> galvociai, nelaimingi;
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
    
    else 
    {
        auto failo_sort_pradzia=std::chrono::high_resolution_clock::now();
        rikiavimas(nr_rikiavimas, grupe);
        auto failo_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo_sort_pabaiga - failo_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su sort funkcija: " << std::fixed << std::setprecision(5) << failo_sort_trukme.count() << "s" << endl;
        
        auto failo_dalijimo_pradzia=std::chrono::high_resolution_clock::now();
        if (strategijos_nr==1)
        {
            for (int i=0; i<grupe.size(); i++)
            {
                if (nr_rikiavimas==3 && grupe[i].gal_vid()<5 || nr_rikiavimas==4 && grupe[i].gal_med()<5) nelaimingi.push_back(grupe[i]);
                else galvociai.push_back(grupe[i]);
            }
        }
        if (strategijos_nr == 2)
        {
            auto it = grupe.begin();
            while (it != grupe.end() &&
                ((nr_rikiavimas == 3 && it->gal_vid() < 5) || (nr_rikiavimas == 4 && it->gal_med() < 5)))
            {
                ++it;
            }

            // (grupe.begin(), it) - nelaimingi
            nelaimingi.insert(nelaimingi.end(), grupe.begin(), it);
            // Remove elements from begin to it
            grupe.erase(grupe.begin(), it); // <-- FIXED: use the new erase method
        }
        
        auto failo_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_dalijimo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_dalijimo_pabaiga - failo_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo_dalijimo_trukme.count() << "s" << endl;    
    }

    spausdinimas_faile(nelaimingi, "nelaimingi.txt");
    if (strategijos_nr==1 || strategijos_nr==3) spausdinimas_faile(galvociai, "galvociai.txt");
    else if (strategijos_nr==2) spausdinimas_faile(grupe, "galvociai.txt");
    cout << endl;
    auto pilna_pabaiga = std::chrono::high_resolution_clock::now();
    auto pilna_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(pilna_pabaiga - failo_nuskaitymo_pradzia);
    cout << nr_failo_dydis << " įrašų testo laikas: " << std::fixed << std::setprecision(5) << pilna_trukme.count() << "s" << endl;
    cout << endl << endl;
    
}
void nuskaitymas_list(const string& failo_pavadinimas, list <studentai>& grupe, int &n) 
{
    std::ios::sync_with_stdio(false); // Optimize input speed
    ifstream in;
    try {
        in.open(failo_pavadinimas);
        if (!in.is_open()) {
            throw std::runtime_error("Problema failo nuskaityme");
        }
    } catch (const std::exception& e) {
        cout << e.what() << endl;
        return;
    }
    string eilute;

    n=-3; // 3 - vardas, pavarde, egzamino pazymys
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
void skaiciavimas_list(list <studentai> &grupe, int n)
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
bool maziau_listui(const studentai& a, const studentai& b, int nr_rikiavimas)
{
    if (nr_rikiavimas==3) return a.gal_vid()<b.gal_vid();
    else if (nr_rikiavimas==4) return a.gal_med()<b.gal_med();
    else return false;
}
void spausdinimas_faile_list(list <studentai> grupe, const string& outputo_pavadinimas, int nr_rikiavimas)
{
    ofstream out (outputo_pavadinimas);
    out << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << string(85, '-') << endl;
    grupe.sort([&](const studentai& a, const studentai& b) {
        return maziau_listui(a, b, nr_rikiavimas);
    });
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        out << std::left << setw(25) << m.pavarde() << setw(20) << m.vardas();
        out << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid() << setw(20) << m.gal_med() << endl;
        //for(const auto&n:m.pazymiai) cout << n << " "               //cout << endl;
    }
}
void list_veiksmai(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    list <studentai> grupe;
    auto failo_nuskaitymo_pradzia=std::chrono::high_resolution_clock::now();
    nuskaitymas_list(failo_pavadinimas, grupe, n);
    auto failo_nuskaitymo_pabaiga = std::chrono::high_resolution_clock::now();
    auto failo_nuskaitymo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_nuskaitymo_pabaiga - failo_nuskaitymo_pradzia);
    cout << "Failo iš " << nr_failo_dydis << " įrašų nuskaitymo laikas: " << std::fixed << std::setprecision(5) << failo_nuskaitymo_trukme.count() << "s" << endl;
    skaiciavimas_list(grupe, n);
    list <studentai> galvociai, nelaimingi;
    if (strategijos_nr==3)
    {
        auto failo3_sort_pradzia=std::chrono::high_resolution_clock::now();
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

    else 
    {
        auto failo_sort_pradzia=std::chrono::high_resolution_clock::now();
        //rikiavimas(nr_rikiavimas, grupe);
        grupe.sort([&](const studentai& a, const studentai& b) {
            return maziau_listui(a, b, nr_rikiavimas);
        });
        auto failo_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo_sort_pabaiga - failo_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su sort funkcija: " << std::fixed << std::setprecision(5) << failo_sort_trukme.count() << "s" << endl;
        
        auto failo_dalijimo_pradzia=std::chrono::high_resolution_clock::now();
        
        if (strategijos_nr==1)
        {
            for (auto it = grupe.begin(); it != grupe.end(); ++it)
            {
                if ((nr_rikiavimas == 3 && it->gal_vid() < 5) || (nr_rikiavimas == 4 && it->gal_med() < 5))
                    nelaimingi.push_back(*it);
                else
                    galvociai.push_back(*it);
            }
        }
        if (strategijos_nr == 2)
        {
            auto it = grupe.begin();
            while (it != grupe.end() &&
                ((nr_rikiavimas == 3 && it->gal_vid() < 5) || (nr_rikiavimas == 4 && it->gal_med() < 5)))
            {
                ++it;
            }

            // (grupe.begin(), it) - nelaimingi
            nelaimingi.insert(nelaimingi.end(), grupe.begin(), it);
            // Remove elements from begin to it
            grupe.erase(grupe.begin(), it); // <-- FIXED: use the new erase method
        }        
        auto failo_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_dalijimo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_dalijimo_pabaiga - failo_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo_dalijimo_trukme.count() << "s" << endl;    
    }

    spausdinimas_faile_list(nelaimingi, "nelaimingi.txt", nr_rikiavimas);
    if (strategijos_nr==1 || strategijos_nr==3) spausdinimas_faile_list(galvociai, "galvociai.txt", nr_rikiavimas);
    else if (strategijos_nr==2) spausdinimas_faile_list(grupe, "galvociai.txt", nr_rikiavimas);

    cout << endl;
    auto pilna_pabaiga = std::chrono::high_resolution_clock::now();
    auto pilna_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(pilna_pabaiga - failo_nuskaitymo_pradzia);
    cout << nr_failo_dydis << " įrašų testo laikas: " << std::fixed << std::setprecision(5) << pilna_trukme.count() << "s" << endl;
    cout << endl << endl;
}
void nuskaitymas_deque(const string& failo_pavadinimas, deque <studentai>& grupe, int &n) 
{
    std::ios::sync_with_stdio(false); // Optimize input speed
    ifstream in;
    try {
        in.open(failo_pavadinimas);
        if (!in.is_open()) {
            throw std::runtime_error("Problema failo nuskaityme");
        }
    } catch (const std::exception& e) {
        cout << e.what() << endl;
        return;
    }
    string eilute;

    n=-3; // 3 - vardas, pavarde, egzamino pazymys
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
void skaiciavimas_deque(deque <studentai> &grupe, int n)
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
void spausdinimas_faile_deque(deque <studentai> grupe, const string& outputo_pavadinimas, int nr_rikiavimas)
{
    ofstream out (outputo_pavadinimas);
    out << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << string(85, '-') << endl;
    std::sort(grupe.begin(), grupe.end(), [&](const studentai& a, const studentai& b) {
        return maziau_listui(a, b, nr_rikiavimas);
    });
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        out << std::left << setw(25) << m.pavarde() << setw(20) << m.vardas();
        out << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid() << setw(20) << m.gal_med() << endl;
        //for(const auto&n:m.pazymiai) cout << n << " "               //cout << endl;
    }
}
void deque_veiksmai(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    deque <studentai> grupe;
    auto failo_nuskaitymo_pradzia=std::chrono::high_resolution_clock::now();
    nuskaitymas_deque(failo_pavadinimas, grupe, n);
    auto failo_nuskaitymo_pabaiga = std::chrono::high_resolution_clock::now();
    auto failo_nuskaitymo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_nuskaitymo_pabaiga - failo_nuskaitymo_pradzia);
    cout << "Failo iš " << nr_failo_dydis << " įrašų nuskaitymo laikas: " << std::fixed << std::setprecision(5) << failo_nuskaitymo_trukme.count() << "s" << endl;
    skaiciavimas_deque(grupe, n);
    deque <studentai> galvociai, nelaimingi;
    if (strategijos_nr==3)
    {
        auto failo3_sort_pradzia=std::chrono::high_resolution_clock::now();
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

    else 
    {
        auto failo_sort_pradzia=std::chrono::high_resolution_clock::now();
        std::sort(grupe.begin(), grupe.end(), [&](const studentai& a, const studentai& b) {
            return maziau_listui(a, b, nr_rikiavimas);
        });
        auto failo_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo_sort_pabaiga - failo_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su sort funkcija: " << std::fixed << std::setprecision(5) << failo_sort_trukme.count() << "s" << endl;
        
        auto failo_dalijimo_pradzia=std::chrono::high_resolution_clock::now();
        
        if (strategijos_nr==1)
        {
            for (auto it = grupe.begin(); it != grupe.end(); ++it)
            {
                if ((nr_rikiavimas == 3 && it->gal_vid() < 5) || (nr_rikiavimas == 4 && it->gal_med() < 5))
                    nelaimingi.push_back(*it);
                else
                    galvociai.push_back(*it);
            }
        } 
        if (strategijos_nr == 2)
        {
            auto it = grupe.begin();
            while (it != grupe.end() &&
                ((nr_rikiavimas == 3 && it->gal_vid() < 5) || (nr_rikiavimas == 4 && it->gal_med() < 5)))
            {
                ++it;
            }
            nelaimingi.insert(nelaimingi.end(), grupe.begin(), it);
            grupe.erase(grupe.begin(), it);
        }         
        auto failo_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_dalijimo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_dalijimo_pabaiga - failo_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo_dalijimo_trukme.count() << "s" << endl;    
    }

    spausdinimas_faile_deque(nelaimingi, "nelaimingi.txt", nr_rikiavimas);
    if (strategijos_nr==1 || strategijos_nr==3) spausdinimas_faile_deque(galvociai, "galvociai.txt", nr_rikiavimas);
    else if (strategijos_nr==2) spausdinimas_faile_deque(grupe, "galvociai.txt", nr_rikiavimas);

    cout << endl;
    auto pilna_pabaiga = std::chrono::high_resolution_clock::now();
    auto pilna_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(pilna_pabaiga - failo_nuskaitymo_pradzia);
    cout << nr_failo_dydis << " įrašų testo laikas: " << std::fixed << std::setprecision(5) << pilna_trukme.count() << "s" << endl;
    cout << endl << endl;
}

#ifndef RUN_TESTS
int main()
{
    try {
        srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
        cout << "Meniu (įveskite pasirinktos programos eigos nr.):" << endl;
        cout << "1 - ranka įveskite duomenis, 2 - generuoti pažymius, 3 - generuoti pažymius ir studentų vardus, 4 - baigti darbą;" << endl;
        cout << "5 - nuskaityti duomenis iš failo, 6 - failų generatorius;" << endl;
        cout <<  "7 - testavimas su Vector \n8 - testavimas su list \n9 - testavimas su deque" << endl;
        cout << "10 - testavimas su visais konteineriais" << endl;
        cout << "11 - testavimas su rule of five ir i/o operatoriais" << endl;
        string vardas, pavarde;
        int nr_meniu;
        cin >> nr_meniu;
        vartotojo_pasirinkimas(nr_meniu, 1, 11);
        if (nr_meniu==4)
        {
            cout << "Darbas baigtas" << endl;
            return 0;
        }
        if (nr_meniu==6)
        {
            cout << "Kokio dydžio failą generuosime? (įveskite eilučių kiekį)" << endl;
            int failu_dydziai[5];
            for (int i=0; i<5; i++) {
                cin >> failu_dydziai[i];
            }
            for (int i=0; i<5; i++) {
                int nr_failo_dydis=failu_dydziai[i];
                auto kurimo_pradzia=std::chrono::high_resolution_clock::now();
                //cin >> nr_failo_dydis;
                string failo_pavadinimas;
                //int paz_kiekis=rand()%15+1; //galimas, bet visus failus bus vienodas
                int paz_kiekis=7;
                failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                failo_generavimas(failo_pavadinimas, nr_failo_dydis, paz_kiekis);
                auto kurimo_pabaiga = std::chrono::high_resolution_clock::now();
                auto kurimo_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(kurimo_pabaiga - kurimo_pradzia);
                cout << "Failo " << failo_pavadinimas << " kūrimo laikas: " << std::fixed << std::setprecision(4) << kurimo_trukme.count() << "s" << endl;
                
            }
            return 0;
        }
        if (nr_meniu>=7 && nr_meniu<=10)
        {
            cout << "Kaip išrikiuoti studentus? Pagal... \n 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
            int nr_rikiavimas;
            cin >> nr_rikiavimas;
            vartotojo_pasirinkimas(nr_rikiavimas, 3, 4);
            cout << "Įveskite strategijos nr." << endl;
            cout << "1 - įprastas, dvi grupės, 2 - šalinami nelaimingi, 3 - efektyvūs metodai" << endl;
            int strategijos_nr;
            cin >> strategijos_nr;
            vartotojo_pasirinkimas(strategijos_nr, 1, 3);
            int n=0, nr_failo_dydis, failu_dydziai[5]={1000, 10000, 100000, 1000000, 10000000};
            string failo_pavadinimas;
            ///////////////
            /////////
            int kiek_failu=3;
            /////////
            ///////////////
            for (int i=0; i<kiek_failu; i++)
            {
                nr_failo_dydis=failu_dydziai[i];
                failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                
                if (nr_meniu==7)
                {
                    septintas_meniu(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                if (nr_meniu==8)
                {
                    list_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                if (nr_meniu==9)
                {
                    deque_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
            }
            if (nr_meniu==10)
            {
                cout << "Vector" << endl;
                for (int i=0; i<kiek_failu; i++)
                {
                    nr_failo_dydis=failu_dydziai[i];
                    failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                    septintas_meniu(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                cout << endl;
                cout << "list" << endl;
                for (int i=0; i<kiek_failu; i++)
                {
                    nr_failo_dydis=failu_dydziai[i];
                    failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                    list_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                cout << endl;
                cout << "deque" << endl;
                for (int i=0; i<kiek_failu; i++)
                {
                    nr_failo_dydis=failu_dydziai[i];
                    failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                    deque_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                cout << endl;
            }

            return 0;
        }
        if (nr_meniu==11)
        {
            // testuojama ar veikia abstrakti Zmogus klasė
            // Zmogus z("Vardas", "Pavarde");
            // cout << z << endl;
            
            cout << endl << "Testuojami rule of five ir i/o operatoriai" << endl << endl;
            studentai s1;
            
            //čia gal --
            cout << "Default konstruktoriaus testas: \n" << s1 << endl;
            
            // output operator test to console
            cout << "Išvedimo operatoriaus testas į ekraną: \n" << s1 << endl;
            
            // manual input operator
            
            cout << "Įveskite studento vardą, pavardę, pažymius, egzamino balą: \n" << endl;
            cin >> s1;
            if (!(cin >> s1)) {
                std::cerr << "Nuskaitymas nepavyko" << endl;
            }
            else cout << "Rankiniu būdu įvesti duomenys: \n" << s1 << endl;
            
            /*
            // automatic input operator
            std::stringstream ss;
            ss << "Jonas Jonaitis 8 9 10 7";
            studentai s9;
            ss >> s9;
            std::stringstream output;
            output << s9;
            std::string expected = "Jonaitis               Jonas               9.00                9.00";
            assert(output.str().find(expected) != std::string::npos);
            cout << "Automatinio įvedimo operatoriaus testas: \n" << s9 << endl;
            */

            // copy constructor
            studentai s2(s1);
            cout << "Copy konstruktoriaus testas: \n" << s2 << endl;
            
            // move constructor
            cout << "Įveskite studento vardą, pavardę, pažymius, egzamino balą: \n" << endl;
            if (!(cin >> s1)) {
                std::cerr << "Nuskaitymas nepavyko" << endl;
            }
            else cout << "Rankiniu būdu įvesti duomenys (s1): \n" << s1 << endl;
            studentai s3(std::move(s1));
            cout << "Move konstruktoriaus testas (s3): \n" << s3 << endl;
            cout << "Move konstruktoriaus testas (s1): \n" << s1 << endl;
            
            // copy assignment operator
            cout << "Įveskite studento vardą, pavardę, pažymius, egzamino balą: \n" << endl;
            if (!(cin >> s1)) {
                std::cerr << "Nuskaitymas nepavyko" << endl;
            }
            else cout << "Rankiniu būdu įvesti duomenys (s1): \n" << s1 << endl;
            studentai s4;
            s4=s1;
            cout << "Copy priskyrimo operatoriaus testas: \n" << s4 << endl;
            
            // move assignment operator
            cout << "Įveskite studento vardą, pavardę, pažymius, egzamino balą: \n" << endl;
            if (!(cin >> s1)) {
                std::cerr << "Nuskaitymas nepavyko" << endl;
            }
            else cout << "Rankiniu būdu įvesti duomenys (s1): \n" << s1 << endl;
            studentai s5;
            s5=std::move(s1);
            cout << "Move priskyrimo operatoriaus testas (s5): \n" << s5 << endl;
            cout << "Move priskyrimo operatoriaus testas (s1): \n" << s1 << endl;

            // input operator test from file
            ifstream in("kursiokai copy.txt");
            studentai s6;
            if (in.is_open())
            {
                
                in >> s6;
                cout << "Failo įvedimo operatoriaus testas: \n" << s6 << endl;
                in.close();
            }
            else 
            {
                cout << "Nepavyko atidaryti failo" << endl;
                return 0;
            }
            
            // output operator test to file
            ofstream out("kursiokai_out_test.txt");
            if (out.is_open())
            {
                out << s6;
                cout << "Failo išvedimo operatoriaus testas --> duomenys faile *kursiokai_out_test.txt*" << endl;
                out.close();
            }
            else 
            {
                cout << "Nepavyko atidaryti failo" << endl;
                return 0;
            }
            // destructor test
            studentai s7; //sukuriami ir sunaikinami i6 karto
            cout << "Destruktoriaus testas: sukuriami objektai iš karto sunaikinami" << endl;
            

            cout << "Testavimas baigtas" << endl;
            return 0;
        }

        //////
        cout << "Kaip išrikiuoti studentus? Pagal... \n 1 - vardą, 2 - pavardę, 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
        int nr_rikiavimas;
        cin >> nr_rikiavimas;
        vartotojo_pasirinkimas(nr_rikiavimas, 1, 4);
        cout << "Kaip norėsite išvesti duomenis? \n 1 - į ekraną, 2 - į failą" << endl;
        int nr_spausdinimas;
        cin >> nr_spausdinimas;
        vartotojo_pasirinkimas(nr_spausdinimas, 1, 2);
        int m=0, n=0; //m-studentai, n-nd
        int paz, egz;
        Vector <studentai> grupe;     //grupes studentu pazymiai
        if (nr_meniu==5)
        {
            cout << "Išsirinkite darbinį failą: \n 1 - kursiokai.txt, 2 - studentai10000.txt, 3 - studentai100000.txt, 4 - studentai1000000.txt" << endl;
            int nr_failas=1; //default reiksme
            cin >> nr_failas;
            string failo_pavadinimas;
            if (nr_failas == 1) failo_pavadinimas = "kursiokai.txt";
            else if (nr_failas == 2) failo_pavadinimas = "studentai10000.txt";
            else if (nr_failas == 3) failo_pavadinimas = "studentai100000.txt";
            else if (nr_failas == 4) failo_pavadinimas = "studentai1000000.txt";
            else {
                cout << "Tokio failo nėra" << endl;
                return 0;
            }
            auto pradzia=std::chrono::high_resolution_clock::now();
            auto pradzia_pilna=std::chrono::high_resolution_clock::now();
            nuskaitymas(failo_pavadinimas, grupe, n);
            auto pabaiga = std::chrono::high_resolution_clock::now();
            auto trukme = std::chrono::duration_cast<std::chrono::seconds>(pabaiga - pradzia);
            cout << "Nuskaitymo vykdymo laikas: " << trukme.count() << "s" << endl;
            skaiciavimas(grupe, n);
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
            auto pabaiga_pilna = std::chrono::high_resolution_clock::now();
            auto trukme_pilna = std::chrono::duration_cast<std::chrono::seconds>(pabaiga_pilna - pradzia_pilna);
            cout << "Programos vykdymo laikas: " << trukme_pilna.count() << "s" << endl;
        }

        else if (nr_meniu==1)
        {
            cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
            char ats;
            m=0;
            cin >> ats;
            if (ats=='n')
            {
                cout << "Darbas baigtas" << endl;
                return 0;
            }
            while (ats=='T')
            {
                studentai temp;
                cout << "Įveskite studento vardą ir pavardę" << endl;
                temp.readStudent(cin); // Use class method
                grupe.push_back(temp);
                m++;
                cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
                cin >> ats;
                if (ats=='n')
                {
                    break;
                }
            }
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
        }
        else if (nr_meniu==2)
        {
            cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
            char ats;
            m=0;
            cin >> ats;
            while (ats=='T')
            {
                studentai temp;
                cout << "Įveskite studento vardą ir pavardę" << endl;
                cin >> vardas >> pavarde;
                temp.setVardas(vardas);
                temp.setPavarde(pavarde);
                while (temp.vardas().size()>19 || temp.pavarde().size()>19)
                {
                    cout << "Vardas arba pavardė per ilgi" << endl;
                    cout << "Įveskite studento vardą ir pavardę" << endl;
                    cin >> vardas >> pavarde;
                    temp.setVardas(vardas);
                    temp.setPavarde(pavarde);
                }
                /*
                cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
                cin >> n;
                while (ar_beda(n, 1, 15))
                {
                    cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
                    cin >> n;
                }
                */
                n=rand()%15+1;
                for (int y=0; y<n; y++)
                {
                    paz=rand_pazymys();
                    temp.setSuma(temp.suma()+paz);
                    temp.addPazymys(paz);
                }
                temp.setVidurkis(temp.vidurkis());
                temp.setMediana(temp.mediana());
                temp.setEgzam(rand_pazymys());
                /*
                temp.setGalVid(0.4 * temp.vidurkis() + 0.6 * temp.egzam()); 
                temp.setGalMed(0.4 * temp.mediana() + 0.6 * temp.egzam());
                */
                grupe.push_back(temp);
                m++;
                cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
                cin >> ats;
                if (ats=='n')
                {
                    break;
                }
            }
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
        }
        else if (nr_meniu==3)
        {
            cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
            char ats;
            m=0;
            cin >> ats;
            while (ats=='T')
            {
                studentai temp;

            ////////////////////////
                temp.setVardas(vardo_generavimas());
                temp.setPavarde(pavardes_generavimas());
            ////////////////////////

                n=rand()%15+1;
                for (int y=0; y<n; y++)
                {
                    paz=rand_pazymys();
                    temp.setSuma(temp.suma()+paz);
                    temp.addPazymys(paz);
                }
                temp.setVidurkis(temp.vidurkis());
                temp.setMediana(temp.mediana());
                temp.setEgzam(rand_pazymys());
                /*
                temp.setGalVid(0.4 * temp.vidurkis() + 0.6 * temp.egzam()); 
                temp.setGalMed(0.4 * temp.mediana() + 0.6 * temp.egzam());
                */
                grupe.push_back(temp);
                m++;
                cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
                cin >> ats;
                if (ats=='n')
                {
                    break;
                }
            }
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
        }
        cout << endl << "Darbas baigtas" << endl;
    } 
    catch (const std::exception& e)
    {
        cout << "Įvyko klaida: " << e.what() << endl;
    }
    catch (...) 
    {
        cout << "Įvyko nežinoma klaida" << endl;
    }
    return 0;
}
#endif