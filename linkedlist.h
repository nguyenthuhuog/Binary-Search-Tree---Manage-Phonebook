#include <iostream>
using namespace std;

template <typename T>
class LinkedList{
	public:
		class Node{
		public:
				T data ;
				Node* next = nullptr;
				Node* pre = nullptr ;
			};
	protected:
		Node* headList = nullptr;
		Node* tailList = nullptr;
	public:
		Node* gethead(){
			return headList;
		}
		Node* gettail(){
			return tailList;
		}
		void insertHead(T val){
			Node* e = new Node;

			e -> data = val;
			e -> next = headList;
			e -> pre = nullptr;

			if (empty()) {
				tailList = e;
				headList = e;
			}else{
				headList -> pre = e;	
				headList = e;
			}
		}
		void insertTail(T val){
			Node* e = new Node;
			e -> data = val;
			e -> next = nullptr;
			e -> pre = tailList;
			if (empty()) {
				headList = e;
				tailList = e;}
			else{
				tailList -> next = e;
				tailList = e;
			}
		}
		void insertAfter(T val, Node *p){
			if (p == tailList){
				insertTail(val);
			}else{
				Node* e = new Node;
				e -> data = val;
				e -> next = p -> next;
				p -> next -> pre = e;
				p -> next = e;
				e -> pre = p;
			}
		}
		Node* at(int i){
			if ( i >= 0 ){
				Node* p = headList;
				while ( i > 0 ){
					p = p -> next;
					i -- ;
				}
				return p;
			}
			else{
				Node* p = tailList;
				while ( i < -1 ){
					p = p -> pre;
					i ++;
				}
				return p;
			}
		}
		Node* operator [] (int i){
			return at(i);
		}
		void deleteHead(){
			if ( empty() ){
				return ;
			}else if ( headList == tailList ){
				delete headList;
				headList = nullptr;
				tailList = nullptr;
			}else{
				headList = headList -> next;
				delete headList -> pre;
				headList -> pre = nullptr;
			}
		}
		void deleteTail(){
			if ( empty() ){
				return ;
			}else if ( headList == tailList ){
				delete headList;
				headList = nullptr;
				tailList = nullptr;
			}else{
				tailList = tailList -> pre;
				delete tailList -> next;
				tailList -> next = nullptr;
			}
		}
		void deleteAfter(Node* e){
			if (empty()|| e ->next == nullptr){
				return ;
			}else{
				Node* p = e -> next -> next;
				delete e -> next;
				e -> next = p;
				if(p) p -> pre = e;// xet truong hop xoa ptu cuoi cung, p = null
				else tailList = e;
			}
		}
		void pop(Node* e){
			if (empty()|| e == nullptr){
				return ;
			}else{
				Node* p = e -> next;
				Node* q = e -> pre;
				delete e;
				if(q) q -> next = p;
				else headList = p;
				if(p) p -> pre = q;// xet truong hop xoa ptu cuoi cung, p = null
				else tailList = q;
			}
		}
		Node* find(T data_){
			for (Node* p = headList; p!= nullptr; p = p -> next){
				if (p -> data == data_) return p;
			}
			return nullptr;
		}
		void deleteAll(){
			Node* p = headList, *q;
			while( p != nullptr ){
				q = p -> next;
				delete p;
				p = q;
			}
			headList = nullptr;
			tailList = nullptr;
		}
		int size(){
			Node* p = headList;
			int co = 0;
			while( p != nullptr){
				co++;
				p = p -> next;
			}
			return co;
		}
		void forEach( void (doSmth) (T&)){
			for (Node* p = headList; p!= nullptr; p = p -> next){
				doSmth(p -> data);
			}
		}
		void rforEach( void (doSmth) (T&)){
			for (Node* p = tailList; p!= nullptr; p = p -> pre){
				doSmth(p -> data);
			}
		}
		void swich_(){
			Node* x;
			x = headList;
			headList = tailList;
			tailList = x;
		}
		void push_up(int i){
			if (i==0) return;
			Node* p= at(i);
			Node* x= p->pre, *y = p->next;

			x->pre->next = x->next;
			p->pre=x->pre;
			
			p->next=x;
			x->pre=x->next;

			x->next=y;
			y->pre=x;
		}
		void dllConvert (T * arr, int count){
			for (int i = 0; i< count ; i++){
				insertTail(*(arr + i));
			}
		}
		bool empty(){
			return headList == nullptr;
		}

		virtual ~LinkedList(){
			deleteAll();
		}
};


