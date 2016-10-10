#ifndef CLASSES
#define CLASSES

using namespace std;

class Classes
{
private:
	string class_num, class_name, professor, credits, upper_div;
	

public:
	Classes(string class_num, string class_name, string credits, string upper_div, string professor)
	{
		this->class_num = class_num;
		this->class_name = class_name;
		this->credits = credits;
		this->upper_div = upper_div;
		this->professor = professor;
	}

	string get_class_num() { return class_num; }
	string get_class_name() { return class_name; }
	string get_professor() { return professor; }
	string get_upper_div() { return upper_div; }
	string get_credits(){ return credits; }
};

#endif