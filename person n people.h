#include <iostream>
#include <string>
#include <iomanip>
#include "BST tree.h"

using namespace std;
void re_name(string& str);
void print_menu();
void print_search_menu_1();
void print_search_menu_2();
void print_modify_menu();
void print_credit();
void print_header();
void press_enter_to_continue();


class Person {
protected:
	int for_file = 0;
	string name = "";
	string tel = "";
	string email = "";
public:
	Person(){}
	Person(string a, string b, string c){
		name = a;
		tel = b;
		email = c;
	}
	Person(Person* x){
		name = x->get_name();
		tel = x->get_tel();
		email = x->get_email();
	}
	string get_name(){
		return name;
	}
	string get_tel(){
		return tel;
	}
	string get_email(){
		return email;
	}
	string set_name(string a){
		name = a;
		return a;
	}
	string set_tel(string a){
		tel = a;
		return a;
	}
	string set_email(string a){
		email = a;
		return a;
	}
	int get_int(){
		return for_file;
	}
	int set_int(int x){
		for_file = x;
		return for_file;
	}
	~Person(){
	}
	friend ostream &operator << (ostream &output, const Person o){
		output << "\t\t   " << "|" << o.name;
		output << setw(27 - o.name.length()) << "|" << o.tel;
		output << setw(19 - o.tel.length()) << "|" << o.email;
		output << setw(28 - o.email.length()) << "|";
		return output;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////manager//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Manager {
protected:
	LinkedList<Person*> main_list;
	BST<string,Person*> tree_name;
	BST<string,Person*> tree_tel;
	BST<string,Person*> tree_email;
public:
	~Manager(){
		main_list.forEach([](Person* &p){
			delete p;
		});
	}

	void PrintJustTheMainList(){
		divider();
		cout << "                                              *LIST OF CONTACT* " << endl;
		divider();
		if(!main_list.empty()){
			print_header();
			main_list.forEach([](Person* &p){
				cout << *p << endl;
			});	
		}
		else {
			cout << " 		  ***There isn't any one in here..." << endl; 
			return;
		}
		divider();
	}
	void PrintAllThisManager(){
		divider();
		if(!main_list.empty()){
			PrintJustTheMainList();
			cout << endl << " 		  Tree name: " << endl;
			tree_name.printTree();
			cout << endl << " 		  Tree tel: " << endl;
			tree_tel.printTree();
			cout << endl << " 		  Tree email: " << endl;
			tree_email.printTree();
		}
		else cout << " 		  ***There isn't any one in here..." << endl;
		divider();
	}
	void insert_p(Person* p){
		main_list.insertHead(p);
		tree_name.insert(p->get_name(), p);
		tree_tel.insert(p->get_tel(), p);
		tree_email.insert(p->get_email(), p);
		cout << *p << endl;
	}
	void add_new_person(){
		string a, b, c;

		while(true){
			cout << "              ---------->Please enter your name: ";
			fflush(stdin);
			getline(cin,a);
			re_name(a);
			if(!tree_name.search(a)) break;
			else {
				cout << "              ***This item has existed, please try again!" << endl;
				press_enter_to_continue();
			}
		}
		while(true){
			cout << "              ---------->Please enter your telephone number: ";
			fflush(stdin);
			getline(cin,b);
			if(!tree_tel.search(b)) break;
			else {
				cout << "              ***This item has existed, please try again!" << endl;
				press_enter_to_continue();
			}
		}
		while(true){
			cout << "              ---------->Please enter your email address: ";
			fflush(stdin);
			getline(cin,c);
			if(!tree_email.search(c)) break;
			else {
				cout << "              ***This item has existed, please try again!" << endl;
				press_enter_to_continue();
			}
		}
		Person* p = new Person(a,b,c); 
		insert_p(p);
	}
	void write_main_list_to_file(ofstream &bw){
		int size,i = 0;
		char test = ' ', fin = '\n';
		for (LinkedList<Person*>::Node* p = main_list.gethead(); p!= nullptr; p = p -> next){
			bw.write(&test, sizeof(char));

			size = p->data->get_name().size();
			bw.write((char*)&size, sizeof(size));
			bw.write(p->data->get_name().c_str() , size);

			size = p->data->get_tel().size();
			bw.write((char*)&size , sizeof(size));
			bw.write(p->data->get_tel().c_str() , size);

			size = p->data->get_email().size();
			bw.write((char*)&size , sizeof(size));
			bw.write(p->data->get_email().c_str() , size);

			//assign order number
			p->data->set_int(i);
			i++;
			cout << *(p->data) << endl;
		}
		bw.write(&fin, sizeof(char));
	}

	void write_to_file(ofstream &bw){
		// neu chua co ai
		if( main_list.empty()) return;
		// xay 3 cay moi voi data chi co so thu tu cua moi person
		cout << "Written: " << endl;
		write_main_list_to_file(bw);

		//build
		BTree<int> *tree_name_fin = tree_name.convert_to_another_tree();
		BTree<int> *tree_tel_fin = tree_tel.convert_to_another_tree();
		BTree<int> *tree_email_fin = tree_email.convert_to_another_tree();

		write_a_tree_to_file(bw,tree_name_fin);
		write_a_tree_to_file(bw,tree_tel_fin);
		write_a_tree_to_file(bw,tree_email_fin);
	}
	void read_main_list_from_file(ifstream &bw){
		if(!main_list.empty()) main_list.forEach([](Person* &p){
			delete p;
		});
		string name_, tel_, email_;
		int size;
		char test = ' ';
		bw.read(&test, sizeof(char));
		do{
			bw.read((char*)&size, sizeof(size));
			name_.resize(size);
			bw.read((char*)name_.c_str(), size);

			bw.read((char*)&size, sizeof(size));
			tel_.resize(size);
			bw.read((char*)tel_.c_str(), size);

			bw.read((char*)&size, sizeof(size));
			email_.resize(size);
			bw.read((char*)email_.c_str(), size);

			bw.read(&test, sizeof(char));

			if (bw.fail()) continue; //advoid insert error in mainlist

			Person* p = new Person(name_,tel_,email_); 
			insert_p(p);

		}while (test != '\n');
	}

	void read_from_file(ifstream &bw){
		cout << "Read: " << endl;
		read_main_list_from_file(bw);

		//read the 3 tree
		BTree<int>*tree_name_fin;
		read_a_tree_from_file(bw,tree_name_fin);
		BTree<int>*tree_tel_fin;
		read_a_tree_from_file(bw,tree_tel_fin);
		BTree<int>*tree_email_fin;
		read_a_tree_from_file(bw,tree_email_fin);

		tree_name.convert_back_to("name",tree_name_fin,&main_list);
		tree_tel.convert_back_to("tel",tree_tel_fin,&main_list);
		tree_email.convert_back_to("email",tree_email_fin,&main_list);
	}

	void remove(Person* p){
		main_list.pop(main_list.find(p));
		tree_name.remove(p->get_name());
		tree_tel.remove(p->get_tel());
		tree_email.remove(p->get_email());
		cout << "Deleted: " << endl;
		cout << *p << endl;
	}
	void search(){
		if(main_list.empty()) {
			cout << "              ***There is nothing to search now" << endl;
			return;
		}
		string a;
		Person* p = nullptr;
		int chs;
		print_search_menu_1();
		cin>>chs;
		cout << "              ---------->Enter searching string: ";
		cin.ignore();
		getline(cin,a);
		switch(chs){
		case 1:
			re_name(a);
			p = tree_name.search(a);
			break;
		case 2:
			p = tree_tel.search(a);
			break;
		case 3:
			p = tree_email.search(a);
			break;
		default:
			cout << "              ***Invalid function, please try again" << endl;
			return;
		}
		if(!p){
			cout << "              ***There no such element" << endl;
			return;
		}

		while(true)
		{	system("cls");
				cout << endl;
				cout << "Found: " << endl;
				print_header();
				cout << *p << endl;
				cout << endl;
	
				print_search_menu_2();
				cin >> chs;
				switch(chs){
				case 0:
					return;
				case 1:
					remove(p);
					return;
				case 2:
					p = modify(p);
					press_enter_to_continue();
					break;
				default:
					cout << "              ***Invalid function, please try again" << endl;
					press_enter_to_continue();
					break;
				}}
	}
	Person* modify(Person* p){
		Person* newNode = new Person (p);
		remove(p);
		int chs;
		string a;
		while(true){
			system("cls");
			cout << endl;
			cout << "Modified: " << endl;
			print_header();
			cout << *newNode << endl;
			cout << endl;
			print_modify_menu();
			cin >> chs;
			switch(chs){
			case 0:
				cout << "              ***Done modify, now exit" << endl;
				insert_p(newNode);
				return newNode;
			case 1:
				cout << "              ---------->Enter new name: ";
				fflush(stdin);
				getline(cin,a);
				re_name(a);
				newNode->set_name(a);
				break;
			case 2:
				cout << "              ---------->Enter new telephone number: ";
				fflush(stdin);
				getline(cin,a);
				newNode->set_tel(a);
				break;
			case 3:
				cout << "              ---------->Enter new email address: ";
				fflush(stdin);
				getline(cin,a);
				newNode->set_email(a);
				break;
			default:
				cout << "              ***Invalid function, please try again" << endl;
				press_enter_to_continue();
				continue;
			}
			cout << "Done modify: " << endl;
			print_header();
			cout << *newNode << endl;
			press_enter_to_continue();
		}
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////manager//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void re_name(string& str){ //sua loi viet hoa
    for(unsigned int j=0;j<str.size();j++){
        if(j==0||str[j-1]==' '){
            if(str[j]<='z' && str[j]>='a'){
                str[j]+='A'-'a';}
        }else {
        if(str[j]<='Z' && str[j]>='A'){
                str[j]-='A'-'a';}
    	}
	}
}
void print_menu(){
	system("cls");
	cout << endl;
	cout << "                                      Group 01 - Contact Management System " << endl;
	cout << "                  /****************************/ MENU FUNCTIONS /*****************************/"<< endl;
	cout << "                  /   0.Exit and write all information from current list to toWriteBfile      /"<< endl;
	cout << "                  /   1.Add a new person                                                      /"<< endl;
	cout << "                  /   2.Print all in the list                                                 /"<< endl;
	cout << "                  /   3.Search for someone                                                    /"<< endl;
	cout << "                  /   4.Print all list, all tree (for TRIAL RUN)                              /"<< endl;
	cout << "                  /***************************************************************************/"<< endl;
	cout << "              ---------->Enter the number corresponding with the function you want to use: ";
}
void print_search_menu_1(){
	cout << endl;
	cout << "                                      Group 01 - Contact Management System " << endl;
	cout << "                  /******************************/ SEARCH MENU /******************************/"<< endl;
	cout << "                  /                 --->Which element do you want to find?<---                /"<< endl;
	cout << "                  /   1.Name                                                                  /"<< endl;
	cout << "                  /   2.Phone number                                                          /"<< endl;
	cout << "                  /   3.Email address                                                         /"<< endl;
	cout << "                  /***************************************************************************/"<< endl;
	cout << "              ---------->Enter the number corresponding with the function you want to use: ";
}
void print_search_menu_2(){
	cout << endl;
	cout << "                                      Group 01 - Contact Management System " << endl;
	cout << "                  /******************************/ SEARCH MENU /******************************/"<< endl;
	cout << "                  /                 --->Do you want to :                  <---                /"<< endl;
	cout << "                  /   0.Nothing more                                                          /"<< endl;
	cout << "                  /   1.Delete this person information                                        /"<< endl;
	cout << "                  /   2.Modify this person information                                        /"<< endl;
	cout << "                  /***************************************************************************/"<< endl;
	cout << "              ---------->Enter the number corresponding with the function you want to use: ";
}
void print_modify_menu(){
	cout << endl;
	cout << "                                      Group 01 - Contact Management System " << endl;
	cout << "                  |------------------------------/ MODIFY MENU /------------------------------|"<< endl;
	cout << "                  |                 --->Do you want to modify :           <---                |"<< endl;
	cout << "                  |   0.Nothing                                                               |"<< endl;
	cout << "                  |   1.Their name                                                            |"<< endl;
	cout << "                  |   2.Their telephone number                                                |"<< endl;
	cout << "                  |   3.Their email address                                                   |"<< endl;
	cout << "                  |---------------------------------------------------------------------------|"<< endl;
	cout << "              ---------->Enter the number corresponding with the function you want to use: ";
}
void print_credit(){
	cout << endl;
	cout << "                           			 Group 01 - Contact Management System " << endl;
	cout << "                  /****************************/ GROUP MEMBERS /******************************/" << endl;
	cout << "                  /                    1.Bui Hanh Trang         -   20210851                  /" << endl;
	cout << "                  /                    2.Nguyen Thi Thanh Hang  -   20213570                  /" << endl;
	cout << "                  /                    3.Nguyen Thu Huong       -   20210423                  /" << endl;
	cout << "                  /***************************************************************************/" << endl;
	cout << "                  /  -----------------------------* THANK YOU *-----------------------------  /" << endl;
	cout << "                           --------------------------Exiting------------------------" << endl;
}
void print_header(){
	cout << "\t\t   |-----------Name-----------|-Telephone number-|-------Email address-------|" << endl;
}
void press_enter_to_continue(){
	cout << endl << " 	   	   ------------------------Press Enter to continue!---------------------------" << endl;
	fflush(stdin);
	getchar();
}

