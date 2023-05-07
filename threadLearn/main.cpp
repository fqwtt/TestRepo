#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

template<typename Iter, typename T>
struct accumulate_block {
	void operator()(Iter begin, Iter end, T& result) {
		for (Iter it = begin; it != end; it++) {
			result += *it;
		}
		//result = accumulate(begin, end, result);
	}
};

template<typename Iter, typename T>
T parallel_accumulate(Iter begin, Iter end, T init) {
	const int length = distance(begin, end);
	if (length < 1)
		return init;
	const int min_per_thread = 25;
	const int max_threads = (length + min_per_thread - 1) / min_per_thread;
	const int hardware_threads = thread::hardware_concurrency();
	const int num_thread = min(hardware_threads, max_threads);
	const int block_size = length / num_thread; //ÓÐÎÊÌâ

	Iter begin_block = begin;
	vector<T> result(num_thread);
	vector<thread> threads(num_thread - 1);
	for (int i = 0; i < num_thread - 1; i++) {
		thread t(accumulate_block<Iter, T>(), begin_block, begin_block + block_size, ref(result[i]));
		threads[i] = move(t);
		//begin_block += block_size;
		advance(begin_block, block_size);
	}
	accumulate_block<Iter, T> tmp;
	tmp(begin_block, end, result[num_thread - 1]);
	for (thread& t : threads)
		t.join();
	T res = accumulate(result.begin(), result.end(), init);
	return res;
}
int main() {
	vector<int> v(100);
	for (int i = 0; i < 100; i++)
		v[i] = i + 1;
	int res = parallel_accumulate(v.begin(), v.end(), 0);
	cout << res << endl;
	return 0;
}