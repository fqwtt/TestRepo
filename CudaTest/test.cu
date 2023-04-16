
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>

using namespace std;
// Kernel definition
class Person {
public:
	int age = 10;
};
__global__ void VecAdd(int* A, int* B, int* C)
{
	int i = threadIdx.x;
	C[i] = A[i] + B[i];
	printf("%d,%d\n", threadIdx.y, threadIdx.x);
}
__global__ void PersonAdd(Person* A, Person* B, Person* C)
{
	int i = threadIdx.x;
	C[i].age = A[i].age + B[i].age;
	printf("%d,%d\n", threadIdx.y, threadIdx.x);
}
int main()
{
	int* dev_a = 0;
	int* dev_b = 0;
	int* dev_c = 0;
	int size = 3;


	cudaError_t cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		cout << "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?" << endl;
		//exit(0);
	}
	Person A[3];
	Person B[3];
	Person C[3];
	cudaMalloc((void**)&dev_c, size * sizeof(int));
	cudaMalloc((void**)&dev_a, size * sizeof(int));
	cudaMalloc((void**)&dev_b, size * sizeof(int));
	cudaMemcpy(dev_a, A, size * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, B, size * sizeof(int), cudaMemcpyHostToDevice);
	dim3 threadsPerBlock(3, 2);

	// N 个线程的内核调用
	VecAdd << <1, threadsPerBlock >> > (dev_a, dev_b, dev_c);
	cudaDeviceSynchronize();
	cudaMemcpy(C, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
	for (int i = 0; i < size; i++) {
		cout << C[i].age << endl;
	}
	cudaFree(dev_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
	return 0;
}