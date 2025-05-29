#include "antrastes.h"
#include "strukt_antr.h"
#include "Vector_new.h"

#include <iostream>
#include <iomanip>
#include <Vector>
#include <vector>
#include <chrono>

template <typename Vec>
std::pair<double,int> test_push_back_su(unsigned int sz)
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
    auto trukme=std::chrono::duration_cast<std::chrono::seconds>(pabaiga-pradzia);
    return {trukme, perskirstymai};
}

int main()
{
    double vector_laikas=0.0, mano_vector_laikas=0.0;
    int test_kartai=3;
    int failu_dydziai[5]={10000, 100000, 1000000, 10000000, 100000000};
    std::cout << std::setw(12) << "Size" 
              << std::setw(20) << "std::vector (s)" 
              << std::setw(15) << "Reallocs" 
              << std::setw(20) << "Vector (s)" 
              << std::setw(15) << "Reallocs" << "\n";
    
    for (auto sz : failu_dydziai)
    {
        auto [std_time, std_realloc] = test_push_back_su<std::vector<int>>(sz);
        auto [vec_time, vec_realloc] = test_push_back_su<Vector>(sz);

        std::cout << std::setw(12) << sz 
                  << std::setw(20) << std::fixed << std::setprecision(5) << std_time 
                  << std::setw(15) << std_realloc 
                  << std::setw(20) << std::fixed << std::setprecision(5) << vec_time 
                  << std::setw(15) << vec_realloc << "\n";
    }
    return 0;
}
