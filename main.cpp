#include <iostream>
#include <vector>

void matrixMultiplication(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, std::vector<std::vector<int>>& C){
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < B.size(); j++){
            for(int k = 0; k < C.size(); k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
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

    matrixMultiplication(matrixA, matrixB, matrixC);
    printMatrix(matrixC);
    return 0;
}
