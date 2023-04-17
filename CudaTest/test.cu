#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <string>
#define THREAD_PER_BLOCK 256

using namespace std;

class Person {
public:
	Person() = default;

	Person(int age, double height) {
		this->age = age;
		this->height = height;
	}
	int age = 10;
	double height = 9.9;
};
// Kernel definition
__global__ void PersonAddKernel(Person* A, Person* B, Person* C)
{
	int i = threadIdx.x;
	int j = blockIdx.x;
	int id = j * THREAD_PER_BLOCK + i;
	C[id].age = A[id].age + B[id].age;
	C[id].height = A[id].height + B[id].height;
}

int main()
{
	Person* dev_a = NULL;
	Person* dev_b = NULL;
	Person* dev_c = NULL;

	int block_size = 2;
	int thread_size = THREAD_PER_BLOCK;
	int size = block_size * thread_size;
	cudaSetDevice(0);
	unique_ptr<Person[]> A = make_unique<Person[]>(size);
	unique_ptr<Person[]> B = make_unique<Person[]>(size);
	unique_ptr<Person[]> C = make_unique<Person[]>(size);


	cudaMalloc((void**)&dev_c, size * sizeof(Person));
	cudaMalloc((void**)&dev_a, size * sizeof(Person));
	cudaMalloc((void**)&dev_b, size * sizeof(Person));
	cudaMemcpy(dev_a, A.get(), size * sizeof(Person), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, B.get(), size * sizeof(Person), cudaMemcpyHostToDevice);

	//system("pause");
	// N 个线程的内核调用
	PersonAddKernel << <block_size, thread_size >> > (dev_a, dev_b, dev_c);
	cudaDeviceSynchronize();
	cudaMemcpy(C.get(), dev_c, size * sizeof(Person), cudaMemcpyDeviceToHost);
	for (int i = 0; i < size; i++) {
		cout << C[i].age << " " << C[i].height << endl;
	}
	
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
	cudaDeviceReset();
	return 0;
}