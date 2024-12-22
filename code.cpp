//testing
//STUDENT RECORD MANAGENT SYSTEM
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;
// Struct for User Node
struct UserNode
{
    string username;
    string password;
    string role;          // "student", "faculty", "admin"
    list<string> courses; // List of course names
    UserNode *next;
};

// Struct for Course Node (Binary Search Tree)
struct CourseNode
{
    string courseName;
    CourseNode *left;
    CourseNode *right;
    CourseNode *next;
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

     void registerUser(){ // LIST
    string username, password, role;

    // Get user details
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;
    cout<<"Enter role (student/faculty/admin): ";
    cin>>role;

    // Create a new user node
    // UserNode* newUser = new UserNode{username, password, role, nullptr};
    UserNode* newUser = new UserNode;
    newUser->username=username;
    newUser->password=password;
    newUser->role=role;
    newUser->next=NULL;

    // Add to linked list
    if(userHead==NULL)
    {
        userHead=newUser; // First user
    }
    else
    {
        UserNode* temp=userHead;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newUser; // Add at the end
    }

    // Save user to file
    ofstream outFile("user_records.txt", ios::app);
    if(outFile.is_open())
    {
        outFile<<username<<" "<<password<<" "<<role<<"\n";
        outFile.close();
        cout<<"User registered successfully!\n";
    }
    else
    {
        cout<<"Failed to open user file for saving.\n";
    }
}

   bool loginUser(string& role)
{ // LIST
    string username, password;

    // Login credentials
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    // Search linked list for the user
    UserNode* temp=userHead;
    while(temp!=NULL)
    {
        if(temp->username==username && temp->password==password)
        {
            role=temp->role; // Assign role for subsequent menu logic
            cout<<"Login successful!\n";
            return true;
        }
        temp=temp->next;
    }

    cout<<"Invalid username or password. Try again.\n";
    return false;
}

    // Function to add a course to the linked list
void addCourse(CourseNode*& head, const string& courseName)
{
    // Create a new node for the course
    CourseNode* newCourse = new CourseNode;
    newCourse->courseName=courseName;
    newCourse->next=NULL;

    // If the list is empty, new course becomes the head
    if(head==NULL)
    {
        head=newCourse;
    }
    else
    {
        // Traverse to the end and insert the course
        CourseNode* temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newCourse;
    }

    // Save to file
    ofstream file("courses.txt", ios::app);
    if(file.is_open())
    {
        file<<courseName<<endl;
        file.close();
    }
    else
    {
        cout<<"Error opening file."<<endl;
    }
}

// Function to remove a course from the linked list
void removeCourse(CourseNode*& head, const string& courseName)
{
    // After removal, update the file with the new course list
    ofstream file("courses.txt", ios::trunc);
    if(file.is_open())
    {
        CourseNode* current=head;
        while(current!=NULL)
        {
            file<<current->courseName<<endl;
            current=current->next;
        }
        file.close();
        cout<<"Course list updated in file."<<endl;
    }
    else
    {
        cout<<"Error opening file."<<endl;
    }

    // If the list is empty, no course to remove
    if(head==NULL)
    {
        cout<<"The course list is empty."<<endl;
        return;
    }

    // If the course to remove is the first course
    if(head->courseName==courseName)
    {
        CourseNode* temp=head;
        head=head->next; // Move head to the next course
        delete temp;     // Delete the node
        cout<<"Course '"<<courseName<<"' removed."<<endl;
    }
    else
    {
        // Traverse to find the course node to remove
        CourseNode* temp=head;
        CourseNode* prev=NULL;

        while(temp!=NULL&&temp->courseName!=courseName)
        {
            prev=temp;
            temp=temp->next;
        }

        if(temp==NULL)
        {
            cout<<"Course '"<<courseName<<"' not found."<<endl;
            return;
        }

        // Remove the node by adjusting the previous node's next pointer
        prev->next=temp->next;
        delete temp; // Delete the course node
        cout<<"Course '"<<courseName<<"' removed."<<endl;
    }
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