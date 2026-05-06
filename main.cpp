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

std::vector<std::vector<int>> matrixStrassen(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n){
    if(A.size() == 1 && B.size() == 1){
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    subSize = n/2;

    std::vector<std::vector<int>> submatrixA_11(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixA_12(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixA_21(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixA_22(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_11(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_12(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vectro<int>> submatrixB_21(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_22(subSize, std::vector<int>(subSize, 0));

    return matrixStrassen(A, B, C, n/2);
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
    int n = 32;
    for(int i = 2; i <= n; i = i * 2){
        std::vector<std::vector<int>> matrixA(i, std::vector<int>(i, 3));
        std::vector<std::vector<int>> matrixB(i, std::vector<int>(i, 3));
        std::vector<std::vector<int>> matrixC(i, std::vector<int>(i, 0));

        double totalTime = measureStandard(matrixA, matrixB, matrixC);
        std::cout << i << " " << totalTime <<std::endl;
    }
    return 0;
}
