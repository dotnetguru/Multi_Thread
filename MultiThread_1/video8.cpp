// for video8 in Bo Qian c++ multi-threading lessons
#include <iostream>
#include <thread>
#include <exception>

using namespace std;

class A {
public:
	void f(int x, char c){}
	long g(double x) {return 0;}
	int operator()(int N) {return 0;}
};

int main() {
	A a;
	std::thread t1(a, 6);
}