// this file is used for video 9 of Bo Qian's multi-threading C++

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
		return 1;
	else
		return n*factorial(n-1);
}

void thread_1() {
	std::packaged_task<int()> t;
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker,[](){return !task_q.empty();});
		t = std::move(task_q.front());
		task_q.pop_front();		
	}
	
	t();
}

int main() {
	std::thread t1(thread_1);
	std::packaged_task<int()> t(bind(factorial, 6));
	std::future<int> fu = t.get_future();
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(t));
	}
	cond.notify_one();

	cout << fu.get();

	t1.join();
	getchar();
	return 0;
}

/*
	3 ways to get a future:
	-- promise::get_future()
	-- package_task::get_future()
	-- async() returns a future

*/