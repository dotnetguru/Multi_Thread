// for video5 in Bo Qian c++ multi-threading lessons
#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

using namespace std;

class LogFile{
	std:: mutex _mu;
	ofstream _f;
public:
	LogFile(){
		_f.open("log.txt");
	}// Need destructor to close file later
	void shared_print(string id, int value){
		std::lock_guard<mutex> locker(_mu);
		_f << "From" << id << ": " << value << endl;
	}



};