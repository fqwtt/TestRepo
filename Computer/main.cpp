#include <iostream>
#include <string>
using namespace std;

class CPU {
public:
	virtual void calculate() = 0;
};
class GPU {
public:
	virtual void display() = 0;
};
class Memory {
public:
	virtual void storage() = 0;
};

class Intel :public CPU {
public:
	void calculate() {
		cout << "Intel cpu is working!" << endl;
	}
};

class AMD :public CPU {
public:
	void calculate() {
		cout << "AMD cpu is working!" << endl;
	}
};

class NVIDIA :public GPU {
public:
	void display() {
		cout << "NVIDIA gpu is working!" << endl;
	}
};

class Tesla :public GPU {
public:
	void display() {
		cout << "Tesla gpu is working!" << endl;
	}
};

class Samsung :public Memory {
public:
	void storage() {
		cout << "Samsung Memory is working!" << endl;
	}
};

class Kingston :public Memory {
public:
	void storage() {
		cout << "Kingston Memory is working!" << endl;
	}
};

class Computer {
public:
	CPU* cpu = NULL;
	GPU* gpu = NULL;
	Memory* memory = NULL;
	void work() {
		cpu->calculate();
		gpu->display();
		memory->storage();
	}
	~Computer() {
		/*cout << "xigou" << endl;*/
		if (cpu != NULL) {
			delete cpu;
			cpu = NULL;
		}
		if (gpu != NULL) {
			delete gpu;
			gpu = NULL;
		}
		if (memory != NULL) {
			delete memory;
			memory = NULL;
		}
	}
};
void t1(int a) { cout << a << endl; }
int main() {
	int num = 1;
	/*void (*fp[1])(int) = { t1 };
	fp[0](5);*/
	Computer* pc = new Computer[num];
	for (int i = 0; i < num; i++) {
		pc[i].cpu = new AMD();
		pc[i].gpu = new Tesla();
		pc[i].memory = new Kingston();
		pc[i].work();
	}
	cout << rand() << endl;
	delete[] pc;
	return 0;
}