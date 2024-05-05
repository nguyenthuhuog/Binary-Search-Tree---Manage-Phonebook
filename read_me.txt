---------------------------------------------------------------------------
void Manager::insert_p(Person* p);
	insert Person* p to manager's memory
---------------------------------------------------------------------------
void Manager::remove(Person* p);
	remove Person* p from manager's memory
---------------------------------------------------------------------------
void Manager::add_new_person();
	start adding opperation
	user add a new person into the manager
---------------------------------------------------------------------------
void Manager::write_to_file(ofstream &bw);
	write the whole manager into binary file bw
	(old infomation will be remove)
---------------------------------------------------------------------------
void Manager::read_from_file(ifstream &bw);
	read a manager from binary file bw
---------------------------------------------------------------------------
void Manager::search();
	start searching opperation
	user search for a person
---------------------------------------------------------------------------
Person* Manager::modify(Person* p);
	start modify opperation
	user modify a person info
---------------------------------------------------------------------------
void BST<KeyType,ValueType>::insert(KeyType key_, ValueType val_);
	insert a node with data is (key_,val_) into the BST
---------------------------------------------------------------------------
ValueType BST<KeyType,ValueType>::search(KeyType key_);
	search for node with key = key_
	return that node pointer
	if cannot find return nullptr
---------------------------------------------------------------------------
void BST<KeyType,ValueType>::remove(KeyType p);
	remove the node with key = p
---------------------------------------------------------------------------
void re_name(string& str);
	fix any wrong upcase and downcase in a full name
---------------------------------------------------------------------------
void press_enter_to_continue();
	stop the system temporary
---------------------------------------------------------------------------
void Manager::PrintJustTheMainList();
	print the list of contact in that manager
---------------------------------------------------------------------------
void Manager::PrintAllThisManager();
	in that manager
	print the list of contact
	print all 3 tree name, tel and email
---------------------------------------------------------------------------