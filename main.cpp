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

std::vector<std::vector<int>> add(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B){
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

std::vector<std::vector<int>> subtract(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B){
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

std::vector<std::vector<int>> matrixStrassen(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n){
    if(A.size() <= 32){
        matrixMultiplication(A, B, C);
        return C;
    }
    int subSize = n/2;

    std::vector<std::vector<int>> submatrixA_11(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixA_12(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixA_21(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixA_22(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_11(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_12(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_21(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixB_22(subSize, std::vector<int>(subSize, 0));
    
    for(int i = 0; i < subSize; i++){
        for(int j = 0; j < subSize; j++){
            submatrixA_11[i][j] = A[i][j];
            submatrixA_12[i][j] = A[i][j+subSize];
            submatrixA_21[i][j] = A[i+subSize][j];
            submatrixA_22[i][j] = A[i+subSize][j+subSize];
        }
    }

    for(int i = 0; i < subSize; i++){
        for(int j = 0; j < subSize; j++){
            submatrixB_11[i][j] = B[i][j];
            submatrixB_12[i][j] = B[i][j+subSize];
            submatrixB_21[i][j] = B[i+subSize][j];
            submatrixB_22[i][j] = B[i+subSize][j+subSize];
        }
    }
    std::vector<std::vector<int>> P_1(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxSubtract_1 = subtract(submatrixB_12, submatrixB_22);
    matrixStrassen(submatrixA_11, auxSubtract_1, P_1, subSize);
    
    std::vector<std::vector<int>> P_2(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxAdd_2 = add(submatrixA_11, submatrixA_12);
    matrixStrassen(auxAdd_2, submatrixB_22, P_2, subSize);

    std::vector<std::vector<int>> P_3(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxAdd_3 = add(submatrixA_21, submatrixA_22);
    matrixStrassen(auxAdd_3, submatrixB_11, P_3, subSize);

    std::vector<std::vector<int>> P_4(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxSubtract_4 = subtract(submatrixB_21, submatrixB_11);
    matrixStrassen(submatrixA_22, auxSubtract_4, P_4, subSize);

    std::vector<std::vector<int>> P_5(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxAdd_5A = add(submatrixA_11, submatrixA_22);
    std::vector<std::vector<int>> auxAdd_5B = add(submatrixB_11, submatrixB_22);
    matrixStrassen(auxAdd_5A, auxAdd_5B, P_5, subSize);

    std::vector<std::vector<int>> P_6(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxSubtract_6 = subtract(submatrixA_12, submatrixA_22);
    std::vector<std::vector<int>> auxAdd_6 = add(submatrixB_21, submatrixB_22);
    matrixStrassen(auxSubtract_6, auxAdd_6, P_6, subSize);

    std::vector<std::vector<int>> P_7(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> auxSubtract_7 = subtract(submatrixA_11, submatrixA_21);
    std::vector<std::vector<int>> auxAdd_7 = add(submatrixB_11, submatrixB_12);
    matrixStrassen(auxSubtract_7, auxAdd_7, P_7, subSize);

    std::vector<std::vector<int>> submatrixC_11(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixC_12(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixC_21(subSize, std::vector<int>(subSize, 0));
    std::vector<std::vector<int>> submatrixC_22(subSize, std::vector<int>(subSize, 0));
    for(int i = 0; i < subSize; i++){
        for(int j = 0; j < subSize; j++){
            submatrixC_11[i][j] = P_5[i][j] + P_4[i][j] - P_2[i][j] + P_6[i][j];
            submatrixC_12[i][j] = P_1[i][j] + P_2[i][j];
            submatrixC_21[i][j] = P_3[i][j] + P_4[i][j];
            submatrixC_22[i][j] = P_5[i][j] + P_1[i][j] - P_3[i][j] - P_7[i][j];
        }
    }

    for(int i = 0; i < subSize; i++){
        for(int j = 0; j < subSize; j++){
            C[i][j] = submatrixC_11[i][j];
            C[i][j+subSize] = submatrixC_12[i][j];
            C[i+subSize][j] = submatrixC_21[i][j];
            C[i+subSize][j+subSize] = submatrixC_22[i][j];
        }
    }
    
    return C;
}

double measureStrassen(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    matrixStrassen(A, B, C, n);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
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
    int n = 256;
    for(int i = 2; i <= n; i = i * 2){
        std::vector<std::vector<int>> matrixA(i, std::vector<int>(i, 3));
        std::vector<std::vector<int>> matrixB(i, std::vector<int>(i, 3));
        std::vector<std::vector<int>> matrixC(i, std::vector<int>(i, 0));

        double totalTimeStandard = measureStandard(matrixA, matrixB, matrixC);
        double totalTimeStrassen = measureStrassen(matrixA, matrixB, matrixC, i);
        std::cout << i << " " << totalTimeStandard << " " << totalTimeStrassen << std::endl;
    }
    return 0;
}
