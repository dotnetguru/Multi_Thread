// for video7 in Bo Qian c++ multi-threading lessons
#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <thread>
#include <deque>
#include <condition_variable>
#include <future>
#include <exception>

using namespace std;

int factorial(std::future<int>& f) {
	int res = 1;

	int N = f.get(); // exception: std::future_errc::broken_promise
	for(int i=N; i>1; i--)
		res *= i;

	cout<< "Result is: " << res << endl;
	return res;
}

int main() {
	int x;

	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

	// do something else
	std::this_thread::sleep_for(chrono::microseconds(20));
	//p.set_exception(std::make_exception_ptr(std::runtime_error("human errors")));
	p.set_value(4);

	x = fu.get();
	cout<< "Get from child: " << x << endl;

	getchar();
	return 0;
}