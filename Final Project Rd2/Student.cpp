#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Student.h"
#include "Classes.h"

using namespace std;

//Import class list to vecor of 'Classes'
void Student::import_classes()
{
	//open file containing class list
	fstream classes("AvalibleClasses.txt", ios::beg | ios::in);
	if (classes.fail())
	{
		cout << "Opening class list failed\n";
	}

	//temp place to import file info
	string class_num, class_name, professor, credits, upper_div;


	for(int i = 0; !classes.eof(); i++)
	{
		//imports info from file one line at a time
			classes >> class_num >> class_name >> credits >> upper_div >> professor;
		//creates a temp object then object is added to the vector of classes
			Classes temp(class_num, class_name, credits, upper_div, professor);
			this->vector_of_classes.push_back(temp);
	}

	classes.close();
}

//Create a new file for student
bool Student::new_account()
{
	//get student information
	string last_name;

	//fname
		cout << "Please enter your first name: ";
		cin >> this->fname;
		system("CLS");

	//lname
		cout << "Please enter your last name: ";
		cin >> last_name;
		this->lname = last_name;
		system("CLS");

	//majr
		int choice;
		do{
			cout << "What is your major:\n"
				<< "1. Math\n"
				<< "2. Computer Science\n"
				<< "3. Biology\n"
				<< "4. Chemistry\n"
				<< "5. Business\n"
				<< "6. Art\n"
				<< "\nChoice: ";
			cin >> choice;
			//choose major
			switch (choice){
			case 1: major = "Math"; break;
			case 2: major = "Computer_Science"; break;
			case 3: major = "Biology"; break;
			case 4: major = "Chemistry"; break;
			case 5: major = "Business"; break;
			case 6: major = "Art"; break;
			default: /*error message*/ system("CLS"); system("COLOR c");  cout << "ERROR\n\nInvalid input\n\n"; system("pause"); system("COLOR 7"); system("CLS");
			}
		}while (choice < 1 || choice > 6);
		system("CLS");

	//password	
		cout << "Please create a password for your account: ";
		cin >> this->password;




	//create a new file for the student and export data we have
		last_name.append(".txt");
		ofstream file(last_name);
		if (file.fail())
		{
			cout << "Creating your file did not work.\n";
			return false;
		}
		else
		{
			system("CLS");
			cout << "A file has been created for you.\n\n";
			system("pause");
		}


	//close created file, will not need until the end
		file.close();

	return true;
}

//Lets Students access previous file
bool Student::re_login()
{

	string last_name;
	cout << "Please type in your last name: ";
	cin >> last_name;


	//open student file
		fstream file(last_name + ".txt", ios::in);
		if (file.fail())
		{
			system("CLS");
			system("COLOR c");
			cout << "ERROR:\n\nYour file cannot be opened.\n\n";
			return false;
		}

	//import data from file into class objects
		string line;
		for (int i = 1; !file.eof(); i++)
		{
			switch (i)
			{
			case 1: //import lname
				file >> this->lname;
				break;

			case 2: //import fname
				file >> this->fname;
				break;

			case 3: //import major
				file >> this->major;
				break;

			case 4: // import password
				file >> this->password;
				break;

			case 5: // ignore blank line

				break;

			default: //rest of lines hold class data
				getline(file, line);

				if (!line.empty())
					registered_classes.push_back(line);

				break;
			}
		}

	//confirm student account with password
		string entered_pass;
		cout << "Please enter in your password: ";
		cin >> entered_pass;
		if (entered_pass != this->password)
		{
			system("CLS");
			system("COLOR c");
			cout << "Password incorrect\n\n" << "Goodbye\n\n";
			return false;
		}
		else
		{
			cout << "Login accepted\n";
			return true;
		}
}


/* SWITCH STATEMENT */

//OPTION ONE
//View list of classes available to register for
void Student::see_class_list()
{
	//loop that runs through the vector of classes
	for (int i = 0; i < vector_of_classes.size(); i++)
	{
		Classes temp = vector_of_classes.at(i);
		string tempname = temp.get_class_name(), tempprof = temp.get_professor();

		//remove underscores from all class and professor names
			for (int a = 0; a < tempname.size(); a++)
			{
				if (tempname.at(a) == '_')
					tempname.at(a) = ' ';
			}
			for (int x = 0; x < tempprof.size(); x++)
			{
				if (tempprof.at(x) == '_')
					tempprof.at(x) = ' ';
			}

		//display all objects of each class
			cout << temp.get_class_num() << "  " << tempname << endl << "\t    Credits: " << temp.get_credits() << ", Upper Division: " << temp.get_upper_div() << ", Professor: " << tempprof << endl << endl;
	}
}


//OPTION TWO
//Lets Students add classes
void Student::add_class()
{
	

	//display all classes
	see_class_list();

	//let user choose a class to register for
	string findclass;
	cout << "Type in the class number you would\nlike to register for (ex CS-171): ";
	cin >> findclass;

	//make sure user isn't registered for more than 5 classes
	if (registered_classes.size() == 5)
	{
		system("CLS"); system("COLOR c");
		cout << "ERROR:\n\nYou have reached the max registration of 5 classes, please\nsee your advisor to add more classes.\n\n";
		system("pause"); system("COLOR 7");
		return;
	}

	//make sure user isn't already registered for the class
	for (int i = 0; i < registered_classes.size(); i++)
	{
		if (findclass == registered_classes[i].substr(0, 6))
		{
			system("CLS"); system("COLOR c");
			cout << "ERROR:\n\nYou are already registered for " << findclass << endl << endl;
			system("pause"); system("COLOR 7");
			return;
		}
	}

	//loop going through vector of classes
	for (int i = 0; i < vector_of_classes.size(); i++)
	{
		Classes temp = vector_of_classes.at(i);

		//if user chosen class == class num of current class then import it for the student's file
		if (findclass == temp.get_class_num())
		{		
			findclass = temp.get_class_num() + " " + temp.get_class_name() + " " + temp.get_credits() + " " + temp.get_upper_div() + " " + temp.get_professor();
			this->registered_classes.push_back(findclass);

			system("CLS");
			cout << "You have been registered for " << findclass.substr(0,6) << endl;
			system("pause");
			return;
		}

	}

	//if no class is found
	system("CLS"); system("COLOR c");
	cout << "ERROR:\n\nRegistering for '" << findclass << "' failed.\n\n";
	system("pause"); system("COLOR 7");
}


//OPTION THREE
//Lets Students drop classes
void Student::drop_class()
{
	//show what classes you have registered for
	view_registered_classes();

	//if no registered classes don't let them drop a class
	if (registered_classes.size() == 0){ system("pause"); return; }
	

	cout << "Pease type in the class number (ex CS-171) \nfor the class you would like to drop: ";
	string drop;
	cin >> drop;


	//loop that goes through their registered classes
	for (int i = 0; i < registered_classes.size(); i++)
	{
		//if class wanting to be dropped == current registered class
		if (drop == registered_classes[i].substr(0, 6))
		{
			//delete that part of vector
			registered_classes.erase(registered_classes.begin() + i);

			//inform user of removal
			system("CLS");
			cout << "You have been removed from " << drop << endl << endl;
			system("pause");
			return;
		}
	}

	//if no classes removed say...
	system("CLS"); system("COLOR c");
	cout << "ERROR:\n\nYou cannot be removed from this class because\n"
		<< "-You were not already registered for the class\n"
		<< "-You entered the class number incorrectly (make sure to capitalize \nthe class type (ex. 'CS' not 'cs')\n\n";
	system("pause"); system("COLOR 7");
}


//OPTION FOUR
//Lets Students see what classes they have registered for
void Student::view_registered_classes()
{
	//clear screen
	system("CLS");


	if (registered_classes.size() == 0)
		cout << "You have not registered for any classes yet.";

	else
	{
		cout << "Your currently registered classes are: \n\n";

		//display vector holding class info
		for (int i = 0; i < registered_classes.size(); i++)
		{
			//line from vector
				string demi = this->registered_classes[i];

			//class_num
				string holder = demi.substr(0, 6);

			//locations in string of where every item is
				int end_of_class_name = demi.find(" ", 7);
				int location_of_credits = end_of_class_name + 1;
				int location_of_upperdiv = location_of_credits + 2;
				int location_of_professor = location_of_upperdiv + 2;
				int end_location_of_professor = demi.find("\n", location_of_professor);

			//display class num
				cout << holder << "\t";
			//display class name
				holder = demi.substr(7, end_of_class_name - 7);
				
				//remove underscores
				for (int a = 0; a < holder.size(); a++)
				{
					if (holder.at(a) == '_')
						holder.at(a) = ' ';
				}
				
				cout << holder << "\n\t\t";
			//display credits
				holder = demi.substr(location_of_credits, 1);
				cout << "Credits: " << holder;
			//display upper div
				holder = demi.substr(location_of_upperdiv, 1);
				cout << ", Upperdiv: " << holder;
			//display professor name
				holder = demi.substr(location_of_professor, end_location_of_professor - location_of_professor);

				//remove underscores
				for (int a = 0; a < holder.size(); a++)
				{
					if (holder.at(a) == '_')
						holder.at(a) = ' ';
				}

				cout << ", Professor: " << holder << endl << endl;

		}
	}

	//wait for user permission to continue
	cout << endl << endl;
}


//OPTION FIVE
//Edit major and password
void Student::edit_account_info()
{
	system("CLS");

	cout << "1) Declare new major \n2) Change Password\n\nChoice: ";

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1: //change major
		do{
			system("CLS");
			cout << "What is your new major:\n"
				<< "1. Math\n"
				<< "2. Computer Science\n"
				<< "3. Biology\n"
				<< "4. Chemistry\n"
				<< "5. Business\n"
				<< "6. Art\n"
				<< "\nChoice: ";
			cin >> choice;
			//edit major
			switch (choice){
			case 1: major = "Math"; break;
			case 2: major = "Computer_Science"; break;
			case 3: major = "Biology"; break;
			case 4: major = "Chemistry"; break;
			case 5: major = "Business"; break;
			case 6: major = "Art"; break;
			default: /*error message*/ system("CLS"); system("COLOR c");  cout << "ERROR\n\nInvalid input\n\n"; system("pause"); system("COLOR 7"); return;
			}
		} while (choice < 0 || choice > 6);

		system("CLS"); cout << "Your major has been changed to " << major << endl << endl; system("pause");

		break;


	case 2: //change password
		system("CLS");
		string newpass;
		cout << "Please type in your current password: "; cin >> newpass;
		if (newpass == this->password)
		{
			cout << "Please type in your new password: "; cin >> newpass;
			this->password = newpass;
			system("CLS");
			cout << "New password has been saved.\n\n"; system("pause");
		}
		else
		{
			system("CLS"); system("COLOR c");
			cout << "ERROR\n\nPassword incorrect\n\n";
			system("pause"); system("COLOR 7");
		}
		break;
	}
}


//OPTION SIX
//Saves file and ends program
void Student::file_save()
{
	//opens student file
	fstream student(this->lname + ".txt", ios::out | ios::beg);
	if (student.fail())
	{
		system("CLS"); system("COLOR c");
		cout << "ERROR:\n Could not save information to your file.\n";
		system("pause"); system("COLOR 7");
		return;
	}

	//inserts first 5 lines of their personal information into their file
	student << this->lname << endl << this->fname << endl << this->major << endl << this->password << endl << endl;

	//inserts class list back into file
	for (int i = 0; i < registered_classes.size(); i++)
		student << registered_classes[i] << endl;


	system("CLS");
	cout << "File has been saved.\n\n";
	cout << "Goodbye " << fname << endl;

	cout
		<< "           "; printf("%C", 2); cout << " /" << endl
		<< "           |/  \n"
		<< "          /|   \n"
		<< "          / \\ \n";
	
}