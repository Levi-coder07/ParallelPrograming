#include <iostream>
#include <random>
#include <chrono>
using namespace std;
const int MAX = 2000;
const int N = 2000;
const int blockSize = 100;
int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];
void modernMulti(){
     for (int i = 0; i < N; i += blockSize) {
        for (int j = 0; j < N; j += blockSize) {
            for (int k = 0; k < N; k += blockSize) {
                for (int i1 = i; i1 < min(i + blockSize, N); i1++) {
                    for (int j1 = j; j1 < min(j + blockSize, N); j1++) {
                        for (int k1 = k; k1 < min(k + blockSize, N); k1++) {
                            C[i1][j1] += A[i1][k1] * B[k1][j1];
                        }
                    }
                }
            }
        }
    }
}
void classicMulti(){
    for(int i = 0 ; i<MAX ; i++ ){
        for(int j= 0 ; j<MAX ; j++ ){
            C[i][j] = 0;
           for(int k= 0;k<MAX;k++){
            C[i][j]+=A[i][k] * B[k][j];
           }
    }
    }
}
int main(){
    srand(time(0));
     for(int i = 0 ; i<MAX ; i++ ){
        for(int j= 0 ; j<MAX ; j++ ){
            A[i][j] = rand()%1000;
            B[i][j] = rand()%1000;
    }
    }
    auto t_start = std::chrono::high_resolution_clock::now();
    classicMulti();
    auto t_end = std::chrono::high_resolution_clock::now();

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout<<"TIEMPO EN MILISEGUNDOS "<<elapsed_time_ms<<std::endl;
    auto t_start1 = std::chrono::high_resolution_clock::now();
    modernMulti();
auto t_end1 = std::chrono::high_resolution_clock::now();

auto elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
    std::cout<<"TIEMPO EN MILISEGUNDOS "<<elapsed_time_ms1;
    

    return 0;
}