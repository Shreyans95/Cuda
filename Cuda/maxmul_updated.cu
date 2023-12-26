#include <stdio.h>
#include <cuda.h>
#include "maxmul.h"
 
//This file is being created for experiment purpose, in case we decide to do
//some testing our the main logic. To be removed later.
__global__ void matrixMultiplication(float *A, float *B, float *C, int size) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < size && col < size) {
        float sum = 0.0;
        for (int k = 0; k < size; k++) {
            // printf("row = %d, col = %d", row * size + k, k * size + col);
            sum += A[row * size + k] * B[k * size + col];
        }
        C[row * size + col] = sum;
    }
}

extern "C" {

   void maxmulVector(float *A, float *B, float *C, int size) {
    float *d_A, *d_B, *d_C;
    clock_t startTime = clock();
    // printf("Point1");
    // Allocate memory on the GPU for A, B, and C
    cudaMalloc((void**)&d_A, size * size * sizeof(float));
    cudaMalloc((void**)&d_B, size * size * sizeof(float));
    cudaMalloc((void**)&d_C, size * size * sizeof(float));
    // printf("Point2");
    // Copy A and B from host to device
    cudaMemcpy(d_A, A, size * size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size * size * sizeof(float), cudaMemcpyHostToDevice);
    // printf("Point3");
    // Set grid and block dimensions
    dim3 dimGrid((size + 15) / 16, (size + 15) / 16);
    dim3 dimBlock(16, 16);

    // printf("Point1=4");
    // Launch the CUDA kernel to perform matrix multiplication

    
    matrixMultiplication<<<dimGrid, dimBlock>>>(d_A, d_B, d_C, size);
    
    // printf("Point5");
    // Copy the result C from device to host
    cudaMemcpy(C, d_C, size * size * sizeof(float), cudaMemcpyDeviceToHost);

    // Free GPU memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaDeviceSynchronize();
        clock_t endTime = clock();
        double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("\nGPU Execution Time: %f seconds\n", elapsedTime);
}

}