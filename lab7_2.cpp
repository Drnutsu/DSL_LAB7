#include <iostream>
#include "linearHash.h"
#include <string>
#include <fstream>

using namespace std;

int main() {
	ifstream file("full.txt");
	string line;
	linearHash<string> linear(11);
	while(!file.eof()){
		file >> line;
		linear.insert(line);
	}
	cout << "---------------------finish---------------------------" <<endl;
	string opt;
	while(true){
		getline(cin,opt);
		if(opt == "exit")break;
		else if(opt == "show")linear.print();
		else if(opt == "stat"){
			cout << "numToken = " << linear.getNumToken() << endl;
			cout << "maxCollusion = " << linear.getMaxCollusion() << endl;
			cout << "loadFactor = " << linear.getLoadFactor() << endl;
		}else{
			if(linear.search(opt))cout << "Found !!" << endl;
			else cout << "not found !!" << endl;
		}
	}

}