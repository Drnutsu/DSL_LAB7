#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "bst.h"

using namespace std;

template <typename T>
class hashTable{
public :
	int CollusionMax;
	int CollusionCount;
	int lastHash;
	explicit hashTable(int size = 11){// explicit ป้องกันการใช้สลับกันใน function ที่มี parameter หลายชนิด
		tablesize = size;
		numToken  = 0;
		table = new vector<bst<T>>(size);
		lastHash = CollusionMax = CollusionCount = 0;
	}

	void rehash(){ 
		vector<bst<T>> *newTable = new vector<bst<T>>(nextPrime(table->size()*2));
		tablesize = newTable->size();
		numToken = lastHash = CollusionMax = CollusionCount = 0; // reset stat
		for(int i = 0;i < table->size();i++){
			node<T> *point = table->at(i).start;
			if(point->next != nullptr){ //ตรวจสอบว่าช่องนั้นว่างใช่หรือไม่ ถ้าว่างแสดงว่าไม่มีข้อมูลอยู่ตั้งแต่แรก
				point = point->next;
				while(point != nullptr){ //วนจนครบ chain
					int index = hashfunc(point->data,tablesize);  // เริ่มทำการใส่ข้อลงไปใน vector ใหม่โดยเอามาจาก vector เก่าผ่านสมการ hash เดิม
					newTable->at(index).add(point->data); 
					if(index == lastHash)CollusionCount++; //detect Collusion and Count
					else{
						if(CollusionCount > CollusionMax)
							CollusionMax = CollusionCount;
					}
					numToken++;
					point = point->next; // เลื่อนไปเรื่อยๆ จนหมด chain
				}
			}
		}
		for(int i =0;i < table->size() ;i++){ // clear old vector
			table->at(i).clear();
		}
		table = newTable;
	}

	void insertfunc(T input){
		insert(input);
	}
	void insert(T input){
		if((numToken/table->size()) >= 0.5){
			cout << "rehash at : " << numToken <<endl;
			rehash();
		}
		int index = hashfunc(input,tablesize);
		if(index == lastHash)CollusionCount++; //detect Collusion and Count
		else{
			if(CollusionCount > CollusionMax)
				CollusionMax = CollusionCount;
		}

		table->at(index).add(input);
		numToken++;
	}
	void insert(node<T> &input){
		insert(input.getdata());
		numToken++;
	}

	bool remove(T input){
		int index = hashfunc(input,tablesize);
		if(table->at(index).search(input)){
			node<T> *old = table->at(index).start;
			while(old->next->getdata() != input){
				if(old == table->at(index).end && old->getdata() != input)return false;
				old = old->next;
			}
			node<T> *temp = old->next;
			if(temp->next != table->at(index).end){
			old->next = temp->next;
			delete temp;
			numToken--;
			return true;
			}else return false;
		}else return false;
	}

	void print(){
		for(int i =0;i < tablesize ;i++){
			cout << "-----------------------------------------------------" << endl;
			table->at(i).print();
			cout << "-----------------------------------------------------" << endl;
		}
	}

	void search(T input){
		int index = hashfunc(input,tablesize);
		if(table->at(index).search(input)){ // ทำการเรียกฟังก์ชั่น search ของ bst อีกที
			cout << input << " is collectly spell" << endl;
		}else cout << input << " is not in the dictionary" << endl;
	}

	void clear(){
		cout << "table clear" << endl;
		for(int i =0;i < table->size() ;i++){
			table->at(i).clear();
		}
	}

	~hashTable(){
		for(int i =0;i < tablesize ;i++){
			table->at(i).clear();
		}
	}

	long getNumToken(){
		return numToken;
	}

	float getLoadFactor(){
		return (float)numToken / table->size();
	}
private:
	vector<bst<T>> *table;
	int tablesize;
    long numToken;
};


int hashfunc(string key,int tableSize){
	int hashVal = 0;
	for(int i = 0;i < key.length();i++){
		hashVal = 37 * hashVal + key[i];
	}
	hashVal %= tableSize; 
	if(hashVal < 0) // มนบางกรณีเมื่อเลขทะลุเกิน int ไปแล้วมันจะเข้าสู่ฝั่งคิดลบ ทำให้อาจทำให้มีผลลัพธ์การ hash เป็นลบได้ เราจึงแปลง complement กลับเป็นบวก
		hashVal += tableSize;
	return hashVal;
}

bool isPrime(int input){

	for(int i =2;i < sqrt((float)input);i++){
		if(input%i == 0)return false;
	}return true;
}

int nextPrime(int input){
	while(true){
		if(isPrime(input))return input;
		input++;
	}
}
