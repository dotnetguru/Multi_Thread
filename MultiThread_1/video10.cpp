// this file is used for video 10 of Bo Qian's multi-threading C++

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <deque>


using namespace std;

std::mutex mu;
std::condition_variable cond;
std::deque<std::packaged_task<int()>> task_q;

int factorial(int n)
{
	if( 0==n || 1== n )
		return 15;
	else
		return n*factorial(n-1);
}

int main() {
	/**/
	std:: thread t1(factorial, 6);
	std::this_thread::sleep_for(chrono::microseconds(3));
	chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
	std::this_thread::sleep_until(tp);


	//Mutex
	std::mutex mu;
	std::lock_guard<mutex> locker(mu);
	std::unique_lock<mutex> ulocker(mu);
	ulocker.try_lock();
	ulocker.try_lock_for(chrono::nanoseconds(500));
	ulocker.try_lock_until(tp);

	//condition variable
	std::condition_variable cond;
	cond.wait_for(ulocker, chrono::microseconds(2));
	cond.wait_until(ulocker, tp);

	//futuer and promise
	std::promise<int> p;
	std::future<int> f = p.get_future();
	f.get();
	f.wait();
	f.wait_for(chrono::microseconds(2));
	f.wait_until(tp);

	// async()
	std::future<int> fu = async(factorial, 6);

	// Packaged Task
	std::packaged_task<int(int)> t(factorial);
	std::future<int> fu2 = t.get_future(); 
	t(6);

}