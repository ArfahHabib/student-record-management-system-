//testing
//STUDENT RECORD MANAGENT SYSTEM
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;
struct UserNode
{
    string username;
    string password;
    string role;
    list<string> courses; // List of course names
    UserNode *next;
};
// Class to manage the student management system
class ManagementSystem
{
private:
    UserNode *userHead;

public:
    // CourseNode* head;
    ManagementSystem() : userHead(NULL) {}

    void studentMenu(const string &username)
    {
        // student function
    }

    void facultyMenu(const string &username)
    {
        // faculty function
    }

    void adminMenu()
    {
        // admin function
    }
};

int main()
{
    ManagementSystem system;
    int choice;

    do
    {
        cout << "1. Register:" << endl;
        cout << " 2. Login:" << endl;
        cout << "3. Exit:" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.registerUser();
            break;
        case 2:
        {
            string role;
            if (system.loginUser(role))
            {
                if (role == "student")
                {
                    system.studentMenu(role);
                }
                else if (role == "faculty")
                {
                    system.facultyMenu(role);
                }
                else if (role == "admin")
                {
                    system.adminMenu();
                }
            }
            break;
        }
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}