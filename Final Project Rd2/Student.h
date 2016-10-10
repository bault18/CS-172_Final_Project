#include "Classes.h"
using namespace std;

class Student
{
private:

	string fname;
	string lname;
	string password;
	string major;
	vector<string> registered_classes;
	vector<Classes> vector_of_classes;
	


public:
	
	void see_class_list();

	bool new_account();
	bool re_login();

	void add_class();
	void drop_class();


	void view_registered_classes();

	void import_classes();

	void file_save();

	void edit_account_info();



};