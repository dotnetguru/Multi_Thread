// for video6 in Bo Qian c++ multi-threading lessons
#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <thread>
#include <deque>
#include <condition_variable>


using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function_1(){
	int count = 10;
	while (count>0){
		std::unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();		
		cout<< "t1 put a valut to queue: " << count << endl;
		cond.notify_one(); // Notify one waiting thread, if there is one.
		cond.notify_all();
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function_2(){
	int data=0;
	while (data!= 1){
		std::unique_lock<mutex> locker(mu);
		cond.wait(locker, [](){return !q.empty();}); // spurious wake
		data = q.back();
		q.pop_back();
		locker.unlock();
		cout<< "t2 get a value from t1:  "<< data << endl;
	}
}

int main() {
	std::thread t1(function_1);
	std::thread t2(function_2);
	t1.join();
	t2.join();
	getchar();
	return 0;

}