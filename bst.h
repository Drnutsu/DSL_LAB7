
using namespace std;

template <typename T>

class bst;


template<typename T>
class hashTable;


template <typename T>
class node{
	node<T> *next;
	T data;
public:
	node(){next = nullptr;}
	node(T in){
		data = in;
		next = nullptr;
	}
	T getdata(){
		return data;
	}
	void move(){
		*this = *this->next;
	}
	friend class bst<T>;
	friend class hashTable<T>;
};



template <typename T>
class bst{
	node<T> *end;
	node<T> *start;
public:
	friend class hashTable<T>;
	bst(){
		start = new node<T>(); //make Dummy node
		end = start;
	}
	
	void add(T input){
		node<T> *np = new node<T>(input);
		end->next = np;
		end = end->next;
	}
	void print(){
		node<T> *p = start->next;
		cout << "List : ";
		while(p != nullptr){
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	void clear(){
		node<T> *p = start;
		node<T> *temp;
		while(p != nullptr){
			temp = p->next;
			delete p;
			p = temp;
		}
	}

	bool search(string input) {
		node<T> *p = start->next;
		while(p != nullptr){
			if(input.compare(p->data) == 0)return true;
			p = p->next;
		}
		return false;
	}

	void copy(bst<T> *temp){
		bst<T> point*;
		while(point != nullptr){
		}
	}
};

