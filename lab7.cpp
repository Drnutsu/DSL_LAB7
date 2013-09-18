#include<iostream>
#include"hashTable.h"
#include <fstream>
#include <string>

using namespace std;
/*int main() {
	ifstream file("full.txt");
	string line;
	cout << "separate chaining dictation" << endl;
	hashTable<string> list(11);
	if(!file){
		cout << "error" << endl;
	}
	while(!file.eof()){
		file >> line;
		list.insert(line);
	}
	cout << "---------------------finish---------------------------" <<endl;
	string value;
	while(true){
		getline(cin,value);
		if(value == "exit")break;
		else if(value == "show")list.print();
		else list.search(value);
	}

	cout << "---------------------------Statistics---------------------------- " <<endl;
	cout << "CollusionMax : " << list.CollusionMax << endl;
	cout << "number of Token : " << list.getNumToken() << endl;
	cout << "load factor : " << list.getLoadFactor() << endl;
	
}*/