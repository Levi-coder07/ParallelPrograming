

// Online C++ compiler to run C++ program online
#include <iostream>
#include <chrono>
const int MAX = 10000;
double A[MAX][MAX], x[MAX], y[MAX];
int main() {
    // Write C++ code here
   
    for(int i = 0 ; i<MAX ; i++ ){
        for(int j= 0 ; j<MAX ; j++ ){
            A[i][j] = 2;
    }
    }
    for(int i = 0 ; i<MAX ; i++ ){
        x[i] = i+1;
    }
    for(int i = 0 ; i<MAX ; i++ ){
        y[i] = 0;
    }
    

auto t_start = std::chrono::high_resolution_clock::now();
for(int i = 0 ; i<MAX ; i++ ){
        for(int j= 0 ; j<MAX ; j++ ){
            y[i] += A[i][j]*x[j];
    }
    }
auto t_end = std::chrono::high_resolution_clock::now();

double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout<<"TIEMPO EN MILISEGUNDOS "<<elapsed_time_ms<<std::endl;
    
    for(int i = 0 ; i<MAX ; i++ ){
        y[i] = 0;
    }
     auto t_start1 = std::chrono::high_resolution_clock::now();
    for(int j = 0 ; j<MAX ; j++ ){
        for(int i= 0 ; i<MAX ; i++ ){
            y[i] += A[i][j]*x[j];
    }
    }
auto t_end1 = std::chrono::high_resolution_clock::now();

auto elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
    std::cout<<"TIEMPO EN MILISEGUNDOS "<<elapsed_time_ms1;
    
   
    return 0;
}
