#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include   <string>
#include <sstream>
#include	"BST.h"
#include    "Student.h"

using namespace std;

//function
bool readFile(const char *, BST *);
int menu();


int main() {

  
	 menu();
	
	system("pause");
	return 0;
}


//function

bool readFile(const char* filename, BST* t1) {
    string line;
    Student student;
    ifstream file;

    file.open(filename);

    if (!file) {
        cout << "Error: Unable to open file." << endl;
        return false;
    }

    while (getline(file, line)) {
        if (line.find("Student Id = ") != string::npos) {
            istringstream iss(line.substr(line.find('=') + 2));
            iss >> student.id;
        }
        else if (line.find("Name = ") != string::npos) {
            strncpy_s(student.name, line.substr(line.find('=') + 2).c_str(), sizeof(student.name));
        }
        else if (line.find("Address = ") != string::npos) {
            strncpy_s(student.address, line.substr(line.find('=') + 2).c_str(), sizeof(student.address));
        }
        else if (line.find("DOB = ") != string::npos) {
            strncpy_s(student.DOB, line.substr(line.find('=') + 2).c_str(), sizeof(student.DOB));
        }
        else if (line.find("Phone Number = ") != string::npos) {
            strncpy_s(student.phone_no, line.substr(line.find('=') + 2).c_str(), sizeof(student.phone_no));
        }
        else if (line.find("Course = ") != string::npos) {
            strncpy_s(student.course, line.substr(line.find('=') + 2).c_str(), sizeof(student.course));
        }
        else if (line.find("CGPA = ") != string::npos) {
            istringstream iss(line.substr(line.find('=') + 2));
            iss >> student.cgpa;
            if (file) {
                t1->insert(student);
            }
            cout << student.name << " record successfully read.\n";
        }
       
    }
	cout << "\n\n";
    file.close();
    return true;
}


int menu()
{
	BST t2;
    BST* t1 = new BST;
	int choice = 0, source = 1, order = 1;
	bool menuRepeat = true;
	type item;

	do
	{

		cout << "Menu" << endl;
		cout << "1. Read data to BST\n"
			<< "2. Print deepest nodes\n"
			<< "3. Display student \n"
			<< "4. Clone Subtree\n"
			<< "5. Print Level Nodes\n"
			<< "6. Print Path\n "
			<< "7. Exit \n";

		cout << "Enter your selection :";
		cin >> choice;
		cout << "\n\n";

		switch (choice)
		{
		case 1:
			readFile("student.txt", t1);

			break;
		case 2:
			t1->deepestNodes();

			break;
		case 3:

			t1->display(order,source);

			break;
		case 4:
		{
			bool success = t1->CloneSubtree(t2, item);

			if (success) {
				cout << "Cloning successful." << endl;
			}
			else {
				cout << "Cloning failed." << endl;
			}

			break;
		}
			
		case 5:
			t1->printLevelNodes();
			
			break;
		case 6:
			t1->printPath();
			break;
		case 7:
			return 0;

		default:
			cout << "Your selection must be between 1 to 7 " << endl;
		}
	} while (menuRepeat == true);

	return 0; // Indicate successful completion
}


