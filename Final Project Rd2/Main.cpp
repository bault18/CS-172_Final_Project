#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Classes.h"
#include "Student.h"

using namespace std;

int main()
{
	
	Student student;
	student.import_classes();
	int switch1;

//login loop
	do{
		cout << "1) Create new account" << endl << "2) Login to existing account" << endl << endl << "Choice: ";
		cin >> switch1;

		system("CLS");

		switch (switch1)
		{
		case 1: //new account

			if (student.new_account() == false)
			{	//if creating a new account failed
				return 0;	}
			break;

		case 2: //Existing account

			if (student.re_login() == false)
			{	//if password wrong close program
				return 0;	}
			break;

		default: //wrong input
			cout << "Invalid input.\n";
			break;
		}
	} while (switch1 != 2 && switch1 != 1);

//actual action loop
	do{
		system("CLS");

		cout << "Welcome to Whitnet\n\n"
			<< "1) View availible class list\n"
			<< "2) Register for a class\n"
			<< "3) Drop a class\n"
			<< "4) See currently registered classes\n"
			<< "5) Edit acount information\n"
			<< "6) Save and Exit\n"
			<< "\nChoice: ";
		cin >> switch1;


		system("CLS");

		switch (switch1)
			{
			case 1: //see class list
			
				student.see_class_list();
				system("pause");
				break;

			case 2: //register for classes
				student.add_class();
				break;

			case 3: //drop class
				student.drop_class();
				break;

			case 4: //see student file
				student.view_registered_classes();
				system("pause");
				break;
			case 5: //edit account info
				student.edit_account_info();
				break;
			case 6: //save info and exit program
				student.file_save();
				return 0;
				break;

			default: //invalid entry
				cout << "Invalid entry. Please select an action with the numbers 1-5.\n\n";
				system("pause");
				break;
			}
	} while (switch1 != 6);
}