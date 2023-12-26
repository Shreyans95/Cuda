#include "maxmul_wrapper.h"
#include "maxmul.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <iostream>
#include <cmath>
#include <vector>

void multiplyUsingCPU(float *a, float* b, int size) {
    // float *C = [size][size];
    int rows_a = size;
    int cols_a = size;
    int rows_b = size;
    int cols_b = size;
    int c ;
    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; ++j) {
            for (int k = 0; k < cols_a; ++k) {
                int x = i * cols_b + j;
                int y = i * cols_a + k;
                int z = k * cols_b + j;
                // printf("x = %d, y = %d, z = %d\n",x,y,z);
                c += a[y] * b[z];
            }
        }
    }
    printf("mul executed\n");
}

extern "C" {
    
    void maxmul(float *A, float* B, float *C, int size){
        
        // CPU execution
    std::thread cpuThread([&] {
        clock_t startTime = clock();
        // float *D = (float *)malloc(sizeof(float) * size);
        // float *a = (float *)malloc(sizeof(float) * size);
        // float *b = (float *)malloc(sizeof(float) * size);

        // for(int index = 0 ; index < size; index++) {
        //     a[index] = A[index];
        //     b[index] = B[index];
        // }
        printf("size in cpu = %d\n", size);
        multiplyUsingCPU(A, B, size);
        clock_t endTime = clock();
        double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("CPU Execution Time: %f seconds\n", elapsedTime);
        // std::cout << "Matrix C:" << std::endl;
        // for (int i = 0; i < size; ++i) {
        //     for (int j = 0; j < size; ++j) {
        //         std::cout << D[i * size + j] << " ";
        //     }
        //     // std::cout << std::endl;
        // }
        // printf("exeuted1\n");
        // free(a);
        // printf("exeuted2\n");
        // free(b);
        // printf("exeuted3\n");
        // free(D);
        // printf("exeuted4\n");
    });
    printf("exeuted\n");
    // GPU execution
    std::thread gpuThread([&] {
        maxmulVector(A, B, C, size);
    });
    cpuThread.join();
    gpuThread.join();
    }
}