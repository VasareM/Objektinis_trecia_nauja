#include "antrastes.h"
#include "strukt_antr.h"
#include "Vector_new.h"

#include <iostream>
#include <iomanip>
#include <Vector>
#include <vector>
#include <chrono>

template <typename Vec>
std::pair<double,double> test_push_back_su(unsigned int sz, int test_kartai)
{
    double bendras_laikas=0.0, bendri_perskirstymai=0.0;
    for (int k=0; k<test_kartai; ++k)
    {
        auto pradzia=std::chrono::high_resolution_clock::now();
        Vec v;
        int perskirstymai=0;
        for (int i = 1; i <= sz; ++i) 
        {
            if (v.size()==v.capacity()) perskirstymai++;
            v.push_back(i);
        }
        auto pabaiga=std::chrono::high_resolution_clock::now();
        auto trukme=std::chrono::duration<double>(pabaiga-pradzia).count();

        bendras_laikas+=trukme;
        bendri_perskirstymai+=perskirstymai;
    }
    return {bendras_laikas/test_kartai, bendri_perskirstymai/test_kartai};
}

int main()
{
    int test_kartai=3;
    int failu_dydziai[5]={10000, 100000, 1000000, 10000000, 100000000};
    std::cout << std::setw(12) << "Dydis" 
              << std::setw(20) << "std::vector (s)" 
              << std::setw(15) << "Perskirstymai" 
              << std::setw(20) << "Vector (s)" 
              << std::setw(15) << "Perskirstymai" << "\n";
    
    for (auto sz : failu_dydziai)
    {
        auto [std_time, std_realloc] = test_push_back_su<std::vector<int>>(sz, test_kartai);
        auto [vec_time, vec_realloc] = test_push_back_su<Vector<int>>(sz, test_kartai);

        std::cout << std::setw(12) << sz 
                  << std::setw(20) << std::fixed << std::setprecision(5) << std_time 
                  << std::setw(15) << std::fixed << std::setprecision(0) << std_realloc 
                  << std::setw(20) << std::fixed << std::setprecision(5) << vec_time 
                  << std::setw(15) << std::fixed << std::setprecision(0) << vec_realloc << "\n";
    }
    return 0;
}
