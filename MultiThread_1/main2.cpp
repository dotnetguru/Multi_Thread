//this code is modified from the second video from Bo Qian's c++ multi-thread series

#include <iostream>
#include <thread>
#include <string>

using namespace std;


class Factor{
public:
	void operator()(std::string &msg){
			cout<< "from t1: " << msg <<endl;
			msg = "msg changed";
			cout<< endl;
	}
};

int main() {
	string s = "string example ";
	cout<< this_thread::get_id()<<endl;
	std:: thread t1((Factor()), ref(s));

	cout<<thread::hardware_concurrency()<<endl;
	//try{
	//	//for ( int i=0 ; i<50 ; i++ )
	//		cout << "from main: " << s << endl;
	//} catch(...){
	//	t1.join();
	//	throw;
	//}

	t1.join();
	cout << "from main: " << s << endl;
	getchar();
	return 0;
}