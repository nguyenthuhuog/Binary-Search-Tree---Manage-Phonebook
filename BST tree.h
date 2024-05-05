#include <iostream>
#include <fstream>
#include "linkedlist.h"
using namespace std;

void divider(){
	cout << "			   ---------------------------------------------------------" << endl;}

template <typename T>
class BTree{
public:
	T data;
	BTree* left=nullptr;
	BTree* right=nullptr;

	BTree (T data_, BTree* left_ = nullptr , BTree* right_ = nullptr){
		data = data_;
		left = left_;
		right = right_;
	}
	~BTree (){
		if(left) delete left;
		if(right) delete right;
	}
	BTree* setLeft(BTree* left_){
		left=left_;
		return left;
	}
	BTree* setRight(BTree* right_){
		right=right_;
		return right;
	}
	BTree* getLeft(){
		return left;
	}
	BTree* getRight(){
		return right;
	}
	T getData(){
		return data;
	}
	bool isLeaf()const{
		return left == nullptr && right == nullptr;
	}
	BTree* getLeftMost(){
		BTree* p=this;
		for (;p->left != nullptr; p=p->left);
		return p;
	}
	int count(){
		return 1 + (left ? left->count() : 0) + (right ? right->count() : 0);
	}
	int Depth(){
		return max((left ? left->Depth() : 0),(right ? right->Depth() : 0)) + 1;
	}
	bool isFull(){
		if (isLeaf()) return true;
		return (left ? left->isFull() : false) && (right ? right->isFull() : false);
	}
	bool isComplete(){
		if ((right ? right->Depth() : 0) > (left ? left->Depth() : 0)) return false;
		if (left ? !left->isComplete() : false) return false;
		if (right ? !right->isComplete() : false) return false;
		return true;
	}
	void forEach(void (doSmth)(T&) ){
		doSmth(data);
		if (left) left -> forEach(doSmth);
		if (right) right -> forEach(doSmth);
	}
	void printTree(string prefix = "    ", bool isLeft = false){
        cout << prefix;

        if(isLeft) cout << char(195) << char(196) << char(196);
    	else cout << char(192) << char(196) << char(196);

        cout << data << endl;

        if(left) left->printTree( prefix + (isLeft ? "|   " : "    "), true);
        if(right) right->printTree( prefix + (isLeft ? "|   " : "    "), false);

	}

	void mywrite(ostream &bw) {
		char mid = ' ';
		int null = -1;
		bw.write(&mid, sizeof(char));

    	bw.write((char*) &data, sizeof(T));

    	if(left) left->mywrite(bw);
    	else {
    		bw.write(&mid, sizeof(char));
    		bw.write((char*) &null, sizeof(int));
    	}
    	if(right) right->mywrite(bw);
    	else {
    		bw.write(&mid, sizeof(char));
    		bw.write((char*) &null, sizeof(int));
    	}
	}

	void myread(ifstream &bw, BTree *&p) {
	  	char mid;
		T data_;

	  	bw.read((char*)&data_, sizeof(T));
	  	bw.read(&mid, sizeof(char));

	  	if (mid == '\n' || data_ == -1 || bw.fail()) 
	    	return;
		p = new BTree(data_);
		myread(bw, p->left);
		myread(bw, p->right);
	}
	void remove(BTree** parent){
		if(left != nullptr && right != nullptr){
			BTree* temp = right;
			BTree** parent2 = &right;

			while(temp->left!= nullptr){
				parent2 = &temp->left;
				temp = temp->left;
			}

			data = temp->data;
			temp->remove(parent2);
		}
		else{
			*parent = right;
			if(left) *parent = left;
			
			right = nullptr;
			left = nullptr;
			delete this;
		}
	}
};

template <typename T>
void read_a_tree_from_file(ifstream &bw, BTree<T>* &p){
	char x;
	bw.read(&x, sizeof(char));
	p->myread(bw,p);
}

template <typename T>
void write_a_tree_to_file(ofstream &bw, BTree<T>*p){
	char fin = '\n';
    // insert in VLR order
	p->mywrite(bw);
	bw.write(&fin, sizeof(char));
}

template <typename KeyType, typename ValueType>
class BST {
public:
	class Pair{
	public:
		KeyType key;
		ValueType val;
		Pair(){
		}
		Pair(KeyType key_, ValueType val_){
			key = key_;
			val = val_;
		}
		Pair(const Pair &o){
			key = o.key;
			val = o.val;
		}
		friend ostream &operator << (ostream &output, const Pair o){
			output << o.key << '-' << o.val ;
			return output;
		}
	};
protected: 
	using BT = BTree<Pair>; 
	BT* head_tree = nullptr;
public:
	~BST(){
		if(head_tree) delete head_tree;
	}
	BT* getBTree(){
		return head_tree;
	}
	BT* setHead(BT* x){
		head_tree = x;
		return head_tree;
	}
	void printTree(){
		if(head_tree)head_tree->printTree();
		else cout << "No Node yet" << endl;
	}
	void insert(KeyType key_, ValueType val_){
		BT* p = head_tree, *q = nullptr;

		//find suitable leaf
		while (p!=nullptr){
			q = p;

			if (key_ < p->data.key) p = p->left;
			else if ((key_ > p->data.key)) p = p->right;
			else cout << "ERROR IN INSERTING!!!";
		}

		Pair newNodeData(key_, val_);
		BT* newNode = new BT(newNodeData);
		
		//if that tree is empty
		if (q==nullptr){
			head_tree = newNode;
			return;
		}

		//else insert
		if (key_ <= q->data.key) q->setLeft(newNode);
		else q ->setRight(newNode);
	}
	BTree<int>* convert_to_another_tree(){
		if(head_tree)
		return child_convert(head_tree);
		else return nullptr;
	}
	BTree<int>* child_convert( BT* p){
		BTree<int>* result = new BTree<int>(p->data.val->get_int());
		if(p->left) result->left = child_convert(p->left);
		if(p->right) result->right = child_convert(p->right);

		return result;
	}

	void convert_back_to (string component , BTree<int>* p , LinkedList<ValueType>* vec){
		delete head_tree; // in case there are some thing in this tree before
		head_tree = child_convert_back_to_tree(component,p,vec);
	}
	BT* child_convert_back_to_tree (string component , BTree<int>* p , LinkedList<ValueType>* vec){
		ValueType focusPerson = vec->at(p->data)->data;
		Pair newNodeData(focusPerson->get_name(), focusPerson);

		if(component == "tel") newNodeData.key = focusPerson->get_tel();
		else if (component == "email") newNodeData.key = focusPerson->get_email();

		BT* result = new BT(newNodeData);

		if(p->left) result->left = child_convert_back_to_tree(component,p->left, vec);
		if(p->right) result->right = child_convert_back_to_tree(component,p->right, vec);

		return result;
	}

	ValueType search(KeyType key) {
		if (head_tree == nullptr)
		{
			cout << " This Tree is empty! " << endl;
			return nullptr;
		}
		BT* curr = nullptr;
		curr = head_tree;
		while (curr != nullptr) {
			if (curr->data.key == key) {
				return curr->data.val;
			}
			else {
				if (key > curr->data.key) curr = curr->right;
				else curr = curr->left;
			}
		}
		return nullptr;
	}
	void remove(KeyType key_){
		BT* p = head_tree;
		BT** q = nullptr;

		while (p!=nullptr){
			if (key_ < p->data.key) {
				q = &p->left;
				p = p->left;
			}
			else if (key_ > p->data.key) {
				q = &p->right;
				p = p->right;
			}
			else {
				break;
			}
		}
		if (!p) {
			cout << "not found" << endl;
			return;
		}
		p->remove(q);
	}

};