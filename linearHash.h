#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
class linearHash;

enum type {ACTIVE,EMPTY,DELETED};

template <typename T>
struct node{
	T data;
	type info;
	node(){
		this->data = "null";
		this->info = EMPTY;
	}
	node(T data,type info = EMPTY){
		this->data = data;
		this->info = info;
	}
};

template <typename T>
class linearHash{
public:
	linearHash(int size){
		numToken = 0;
		arrsize = size;
		maxCollusion = 0;
		list = vector<node<T>>(arrsize);
	}

	bool remove(T input) {
		int pos = hashlinear(input,arrsize);
		while(list.at(pos).info != ACTIVE){
			pos += 1;
			pos %= arrsize;
		}
		if(input.compare(list.at(pos).data) == 0){
			list.at(pos).info = DELETED;
			numToken--;
			return true;
		}else return false;
	}

	bool insert(T data){
		if(numToken/list.size() >= 0.5){
			cout << "rehash at " << numToken << endl;
			rehash();
		}
		int pos = findPos(hashlinear(data,arrsize));
		list.at(pos) = node<T>(data,ACTIVE);
		numToken++;
		return true;
	}

	void rehash(){
		vector<node<T>> oldList = list;
		list.resize(nextPrimeLinear(arrsize * 2));
		arrsize = list.size();
		for(int i = 0; i < oldList.size() ; i++){
			list.at(i).info = EMPTY;
		}

		numToken = 0;
		for(int i = 0;i < oldList.size() ;i++){
			if(oldList.at(i).info == ACTIVE){
				insert(oldList.at(i).data);
			}
		}
	}

	int getNumToken(){
		return numToken;
	}
	int getMaxCollusion(){
		return maxCollusion;
	}
	void print() {
		for(int i = 0;i < list.size();i++){
			cout << "arr [" << i << "]  = " << list.at(i).data << endl;
		}
	}

	bool search(T data) {
		int index = hashlinear(data,arrsize);
		while(list.at(index).info != ACTIVE){
			index += 1;
			index %= arrsize;
		}
		if(data.compare(list.at(index).data) == 0){
			return true;
		}else return false;

	}

	int findPos(int index){
		int collusion = 0;
		while(list.at(index).info != EMPTY && list.at(index).info != DELETED){
			index += 1;
			index %= arrsize;
			collusion++;
		}
		if(collusion > maxCollusion){
			maxCollusion = collusion;
		}
		return index;
	}

	float getLoadFactor(){
		return (float)numToken/arrsize;
	}

private:
	int numToken;
	int arrsize;
	int maxCollusion;
	vector<node<T>> list;
};

int hashlinear(string key,int tableSize){
	int hashVal = 0;
	for(int i = 0;i < key.length();i++){
		hashVal = 37 * hashVal + key[i];
	}
	hashVal %= tableSize; 
	if(hashVal < 0) // มนบางกรณีเมื่อเลขทะลุเกิน int ไปแล้วมันจะเข้าสู่ฝั่งคิดลบ ทำให้อาจทำให้มีผลลัพธ์การ hash เป็นลบได้ เราจึงแปลง complement กลับเป็นบวก
		hashVal += tableSize;
	return hashVal;
}

bool isPrimeLinear(int input){
	for(int i = 2;i < sqrt((float)input);i++){
		if(input % i == 0)return false;
	}
	return true;
}

int nextPrimeLinear(int input){
	while(isPrimeLinear(input) == false){
		input++;
	}
	return input;
}