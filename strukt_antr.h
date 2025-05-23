#ifndef strukt_antr_h
#define strukt_antr_h

#include "Vector_new.h"
#include <iostream>
//#include <vector>
#include <string>

//using std::vector;
using std::string;

class Zmogus
{
    protected:
        string vardas_;
        string pavarde_;
    public:
        Zmogus(string var="", string pav="") : vardas_{var}, pavarde_{pav} {std:: cout << "Zmogaus konstruktorius \n";} // default konstruktorius
        void setVardas(string var) { vardas_ = var; }
        void setPavarde(string pav) { pavarde_ = pav; }
        virtual string vardas() const { return vardas_; }
        virtual string pavarde() const { return pavarde_; }

        //copy konstr
        Zmogus(const Zmogus& other)
            : vardas_(other.vardas_), pavarde_(other.pavarde_) {
        }
        //move konstr
        Zmogus(Zmogus&& other) noexcept
            : vardas_(std::move(other.vardas_)),
            pavarde_(std::move(other.pavarde_)) {
            // Reset the source object
            other.vardas_ = "";
            other.pavarde_ = "";
        }
        virtual void displayInfo() const = 0; // virtual = abstract class
        virtual ~Zmogus() {
            vardas_.clear();
            pavarde_.clear();
            //std::cout << "Destruktorius Zmogus įvykdytas" << std::endl;
        }
};
//isvestine klase
class studentai: public Zmogus
{
    private:
        double egzam_;
        Vector <double> pazymiai_;
        double suma_=0;
        double vidurkis_=0;
        int mediana_=0;
        double gal_med_ = 0, gal_vid_=0;
    public:
        void setVardas(const string& vardas) {
            Zmogus::setVardas(vardas); // Optionally call the base class method
        }

        void setPavarde(const string& pavarde) {
            Zmogus::setPavarde(pavarde); // Optionally call the base class method
        }    
    
    //konstruktoriai:
        studentai() : Zmogus(), egzam_(0) {} // default konstruktorius
        studentai(std::istream& is);  //dis: konstruktorius, realiai inicializacijai

        studentai(const studentai& v); //copy konstruktorius
        studentai(studentai&& v) noexcept; //move konstruktorius
        //studentai(std::initializer_list<double> il); // perduodamas double sarasas
        //kas cia?
        studentai& operator=(const studentai& v); // priskyrimo kopijavimo operatorius
        studentai& operator=(studentai&& v) noexcept; // priskyrimo move operatorius

        using Zmogus::vardas;
        using Zmogus::pavarde;

        void displayInfo() const override {
            std::cout << "Studentas: " << vardas_ << " " << pavarde_ << std::endl;
        }
        // this 

        //get'eriai
        //string vardas() const {return vardas_;}
        //string pavarde() const {return pavarde_;}
        double egzam() const { return egzam_; }
        const Vector<double>& pazymiai() const { return pazymiai_; }
        double suma() const {return suma_;}
        double vidurkis() const;
        int mediana() const;
        double gal_med() const;
        double gal_vid() const;

        std::istream& readStudent(std::istream&);
        //set'eriai
        void setEgzam(double egzam) {egzam_ = egzam;}
        void setPazymiai(const Vector<double>& pazymiai) {pazymiai_ = pazymiai;}
        
        void setSuma(double suma) {suma_ = suma;}
        void setVidurkis(double vidurkis) {vidurkis_ = vidurkis;}
        void setMediana(int mediana) {mediana_ = mediana;}
        void setGalMed(double gal_med) {gal_med_ = gal_med;}
        void setGalVid(double gal_vid) {gal_vid_ = gal_vid;}

        void addPazymys(double pazymys) {pazymiai_.push_back(pazymys);}


        //perdengti operatoriai
        //  i/o operatoriai friend tipo
        friend std::istream& operator>>(std::istream& is, studentai& v);
        friend std::ostream& operator<<(std::ostream& os, const studentai& v);


        //destruktorius:
        ~studentai() override {
            pazymiai_.clear();
            //std::cout << "Destruktorius išvestinės studentai įvykdytas" << std::endl;
        }
        //override - virtualus išvestinės destruktorius
};




/*
class studentai
{
    private:
        string vardas_;
        string pavarde_;
        double egzam_;
        Vector <double> pazymiai_;
        double suma_=0;
        double vidurkis_=0;
        int mediana_=0;
        double gal_med_ = 0, gal_vid_=0;
    public:
        //konstruktoriai:
        studentai() : egzam_(0) {} // default konstruktorius
        studentai(std::istream& is);  //dis: konstruktorius, realiai inicializacijai

        studentai(const studentai& v); //copy konstruktorius
        studentai(studentai&& v) noexcept; //move konstruktorius
        studentai(std::initializer_list<double> il); // perduodamas double sarasas
        //kas cia?
        studentai& operator=(const studentai& v); // priskyrimo kopijavimo operatorius
        studentai& operator=(studentai&& v) noexcept; // priskyrimo move operatorius


        //get'eriai, inline:
        inline string vardas() const {return vardas_;}
        inline string pavarde() const {return pavarde_;}
        inline double egzam() const { return egzam_; }
        inline const Vector<double>& pazymiai() const { return pazymiai_; }
        inline double suma() const {return suma_;}
        inline double vidurkis() const;
        inline int mediana() const;
        double gal_med() const;
        double gal_vid() const;

        //set'eriai:
        std::istream& readStudent(std::istream&); //set'eriai
        void setVardas(string vardas) {vardas_ = vardas;}
        void setPavarde(string pavarde) {pavarde_ = pavarde;}
        void setEgzam(double egzam) {egzam_ = egzam;}
        void setPazymiai(const Vector<double>& pazymiai) {pazymiai_ = pazymiai;}
        
        void setSuma(double suma) {suma_ = suma;}
        void setVidurkis(double vidurkis) {vidurkis_ = vidurkis;}
        void setMediana(int mediana) {mediana_ = mediana;}
        void setGalMed(double gal_med) {gal_med_ = gal_med;}
        void setGalVid(double gal_vid) {gal_vid_ = gal_vid;}

        void addPazymys(double pazymys) {pazymiai_.push_back(pazymys);}


        //perdengti operatoriai
        //  i/o operatoriai friend tipo
        friend std::istream& operator>>(std::istream& is, studentai& v);
        friend std::ostream& operator<<(std::ostream& os, const studentai& v);


        //destruktorius:
        ~studentai() {
            pazymiai_.clear();
            vardas_.clear();
            pavarde_.clear();
            std::cout << "Destruktorius įvykdytas" << std::endl;
        }
};
*/


//bool compare(const studentai&, const studentai&);
/*
bool comparePagalPavarde(const studentai&, const studentai&);
bool comparePagalEgza(const studentai&, const studentai&);
*/

/*
struct studentai
{
    string vardas="var"; //default reiksmes testavimui
    string pavarde="pav";
    Vector<int> pazymiai; //nd tarpiniai rezultatai
    int egzam;
    double suma=0;
    double vidurkis;
    int mediana;
    double gal_vid, gal_med;
};
*/

#endif