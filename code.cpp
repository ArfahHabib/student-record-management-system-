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
    UserNode *userHead;     // Head of user linked list
    CourseNode *courseRoot; // Root of course BST

    vector<vector<int>> courseGraph; // 2D vector to store course relationships

public:
    // CourseNode* head;
    ManagementSystem() : userHead(NULL), courseRoot(NULL)
    {
        courseGraph.resize(100); // Initialize the courseGraph with 100 courses
    }

    void registerUser()
    { // LIST
        string username, password, role;

        // Get user details
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (student/faculty/admin): ";
        cin >> role;

        // Create a new user node
        // UserNode* newUser = new UserNode{username, password, role, nullptr};
        UserNode *newUser = new UserNode;
        newUser->username = username;
        newUser->password = password;
        newUser->role = role;
        newUser->next = NULL;

        // Add to linked list
        if (userHead == NULL)
        {
            userHead = newUser; // First user
        }
        else
        {
            UserNode *temp = userHead;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newUser; // Add at the end
        }

        // Save user to file
        ofstream outFile("user_records.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << username << " " << password << " " << role << "\n";
            outFile.close();
            cout << "User registered successfully!\n";
        }
        else
        {
            cout << "Failed to open user file for saving.\n";
        }
    }

    bool loginUser(string &role)
    { // LIST
        string username, password;

        // Login credentials
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Search linked list for the user
        UserNode *temp = userHead;
        while (temp != NULL)
        {
            if (temp->username == username && temp->password == password)
            {
                role = temp->role; // Assign role for subsequent menu logic
                cout << "Login successful!\n";
                return true;
            }
            temp = temp->next;
        }

        cout << "Invalid username or password. Try again.\n";
        return false;
    }

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