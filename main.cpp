#include <iostream>
#include "person n people.h"

using namespace std;

int main (){	
	string Bfile = "group01_01.dat";

	ifstream toReadBfile(Bfile, ios::in | ios::binary);
	if(!toReadBfile) {
	  cout << "Cannot open  file to read!" << endl;
	  return 1;
	}

	int choose;
	Manager sth;

	sth.read_from_file(toReadBfile);
	toReadBfile.close();
	press_enter_to_continue();

	ofstream toWriteBfile(Bfile, ios::out | ios::binary);
	if (!toWriteBfile) {
		cout << "Cannot open file to write!" << endl;
		return 1;
	}

	while(true){
		print_menu();
		fflush(stdin);
		cin >> choose;
		cin.ignore();
		cout << endl;
		
		switch (choose) {
		case 0:
			sth.write_to_file(toWriteBfile);
			press_enter_to_continue();
			system("cls");
			print_credit();
			return 0;
		case 1:
			sth.add_new_person();
			press_enter_to_continue();
			break;
		case 2:
			sth.PrintJustTheMainList();
			press_enter_to_continue();
			break;
		case 4:
			sth.PrintAllThisManager();
			press_enter_to_continue();
			break;
		case 3:
			sth.search();
			press_enter_to_continue();
			break;
		default:
			cout << "              ***Invalid function, please try again" << endl;
			press_enter_to_continue();
			break;
		}
	}
	toWriteBfile.close();
	return 0;
}