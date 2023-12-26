#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#ifdef __cplusplus
extern "C" {
#endif

void __declspec(dllexport) maxmulVector(float *A, float* B, float *C, int size);

#ifdef __cplusplus
}
#endif