#include <iostream>
#include <vector>
#include <chrono>

void matrixMultiplication(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C){
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < B.size(); j++){
            for(int k = 0; k < C.size(); k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double measureStandard(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    auto start = std::chrono::high_resolution_clock::now();
    matrixMultiplication(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
}

void printMatrix(std::vector<std::vector<int>> matrixRandom){
    for(int i = 0; i < matrixRandom.size(); i++){
        for(int j = 0; j < matrixRandom[i].size(); j++){
            std::cout<<matrixRandom[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

int main(){
    std::vector<std::vector<int>> matrixA(2, std::vector<int>(2, 3));
    std::vector<std::vector<int>> matrixB(2, std::vector<int>(2, 3));
    std::vector<std::vector<int>> matrixC(2, std::vector<int>(2, 0));

    double totalTime = measureStandard(matrixA, matrixB, matrixC);
    printMatrix(matrixC);
    std::cout << "Time: " << totalTime << " microsegundos" <<std::endl;
    return 0;
}
