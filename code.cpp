//testing
//STUDENT RECORD MANAGENT SYSTEM
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

// BSTNode structure to store course names and grades
struct BSTNode
{
    string course; // Course name
    float grade;   // Grade for the course
    BSTNode *left;
    BSTNode *right;

    BSTNode(string c, float g) : course(c), grade(g), left(NULL), right(NULL) {}
};

// Simple Hash Map structure for storing users and their courses
struct HashMapTable
{
    list<pair<string,string>> *table; // Array of lists to store user-course pairs
    int table_size;

    // Constructor to initialize the hash table
    HashMapTable(int ts)
    {
        table_size=ts;
        table=new list<pair<string,string>>[table_size];
    }

    // Simple hash function to map usernames to the table
    int hashFunction(const string& key)
    {
        int hashValue=0;
        for (char c:key)
        {
            hashValue+=c;
        }
        return hashValue%table_size;
    }

    // Register a user with a course
    void registerUser(const string& username,const string& course)
    {
        int index=hashFunction(username);
        table[index].push_back(make_pair(username,course));
    }

    // Display courses registered by the user
    void displayUserCourses(const string& username)
    {
        int index=hashFunction(username);
        for (auto& entry:table[index])
        {
            if (entry.first==username)
            {
                cout<<"Course: "<<entry.second<<endl;
            }
        }
    }
};
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
 // Function to load courses from a file
void loadCoursesFromFile(const string& filename, vector<string>& allCourses)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cout<<"Error opening file:"<<filename<<endl;
        return;
    }

    string course;
    while(file>>course)
    {
        allCourses.push_back(course); // Add course to the available courses list
    }

    file.close();
}


/ Function to display available courses using BFS (Breadth First Search)
void displayAvailableCoursesBFS(const vector<string>& allCourses)
{
    if(allCourses.empty())
    {
        cout<<"No courses available.\n";
        return;
    }

    cout<<"Available Courses (BFS):\n";

    list<string> courseQueue; // Queue for BFS traversal

    // Start from the first course in the list
    courseQueue.push_back(allCourses[0]);

    // Visited array to track which courses have been displayed
    bool visited[allCourses.size()]={false};

    visited[0]=true; // Mark the first course as visited

    while(!courseQueue.empty())
    {
        string currentCourse=courseQueue.front(); // Dequeue
        courseQueue.pop_front();

        cout<<currentCourse<<endl; // Display the current course

        // Find the index of the current course
        int courseIndex=-1;
        for(int i=0;i<allCourses.size();++i)
        {
            if(allCourses[i]==currentCourse)
            {
                courseIndex=i;
                break;
            }
        }

        // If we have a valid index, let's proceed with the BFS traversal
        if(courseIndex!=-1)
        {
            // In this case, all courses are considered neighbors for simplicity
            for(int i=0;i<allCourses.size();++i)
            {
                if(!visited[i])
                {
                    visited[i]=true;                    // Mark the neighbor course as visited
                    courseQueue.push_back(allCourses[i]); // Enqueue the neighbor course
                }
            }
        }
    }
}

    // Function to display registered courses by a student
    void displayRegisteredCourses(const vector<string> &registeredCourses)
    {
        if (registeredCourses.empty())
        {
            cout << "No courses registered yet.\n";
        }
        else
        {
            cout << "Registered Courses:\n";
            for (const auto &course : registeredCourses)
            {
                cout << course << endl;
            }
        }
    }

   // Function to register a course for the student
bool registerCourse(vector<string>& registeredCourses, const vector<string>& availableCourses)
{
    int courseIndex;
    cout<<"Enter the course number (starting from 0) you want to register for: ";
    cin>>courseIndex;

    // Check if the course index is valid
    if(courseIndex<0||courseIndex>=availableCourses.size())
    {
        cout<<"Invalid course selection.\n";
        return false;
    }

    string courseToRegister = availableCourses[courseIndex];

    // Check for duplicate registration
    for(const auto& course : registeredCourses)
    {
        if(course==courseToRegister)
        {
            cout<<"You are already registered for this course.\n";
            return false;
        }
    }

    // Add the course to the registered courses list
    registeredCourses.push_back(courseToRegister);
    cout<<"You have successfully registered for "<<courseToRegister<<".\n";
    return true;
}

  // Binary Search Tree to store and display grades
void insertGrade(BSTNode*& root, const string& course, float grade)
{
    if(root==NULL)
    {
        root=new BSTNode(course, grade);
    }
    else
    {
        if(course<root->course)
        {
            insertGrade(root->left, course, grade);
        }
        else
        {
            insertGrade(root->right, course, grade);
        }
    }
}

// Helper function to perform an in-order traversal of the BST and display courses and grades
void inOrderTraversal(BSTNode* root)
{
    if(root==NULL)
    {
        return;
    }
    inOrderTraversal(root->left);
    cout<<"Course: "<<root->course<<" - Grade: "<<root->grade<<endl;
    inOrderTraversal(root->right);
}


    void assignGrade(stack<float>& gradeStack, BSTNode*& root, float grade, vector<string>& courses)
{
    // Display available courses
    cout<<"Select a course to assign a grade:"<<endl;
    for(int i=0; i<courses.size(); ++i)
    {
        cout<<i+1<<". "<<courses[i]<<endl;
    }

    // Ask user to choose a course
    int courseChoice;
    cout<<"Enter the number of the course: ";
    cin>>courseChoice;

    if(courseChoice<1||courseChoice>courses.size())
    {
        cout<<"Invalid course choice!"<<endl;
        return;
    }

    // Ask for grade input
    cout<<"Enter the grade for the course "<<courses[courseChoice-1]<<": ";
    cin>>grade;

    // Assign grade by pushing onto the stack
    gradeStack.push(grade);

    // Insert grade into the BST (passing both course and grade)
    insertGrade(root, courses[courseChoice-1], grade);

    cout<<"Grade assigned to "<<courses[courseChoice-1]<<" successfully!"<<endl;
}

void removeUser(const string& username, const string& filename="user_records.txt")
{
    // Open the file in read mode
    ifstream inputFile(filename);
    if(!inputFile)
    {
        cerr<<"Error opening file!"<<endl;
        return;
    }

    // Read all lines into a vector
    vector<string> lines;
    string line;
    while(getline(inputFile, line))
    {
        lines.push_back(line);
    }
    inputFile.close();

    // Open the file in write mode to overwrite it
    ofstream outputFile(filename);
    if(!outputFile)
    {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }

    bool userFound = false;

    // Write all lines back to the file except the line containing the exact username
    for(const auto& line : lines)
    {
        // Check for exact match of the username (you can adjust this based on the format)
        if(line.substr(0, username.length())==username)
        {
            userFound=true; // Found the user
            continue;       // Skip this line
        }
        outputFile<<line<<endl;
    }

    // Notify if the user was found and deleted
    if(userFound)
    {
        cout<<"User '"<<username<<"' has been deleted."<<endl;
    }
    else
    {
        cout<<"User '"<<username<<"' not found."<<endl;
    }

    outputFile.close();
}


  // Function to perform selection sort based on username
void selectionSort(UserNode* arr, int size)
{
    for(int i=0; i<size-1; i++)
    {
        int minIndex=i;
        for(int j=i+1; j<size; j++)
        {
            if(arr[j].username<arr[minIndex].username)
            {
                minIndex=j;
            }
        }
        // Swap the found minimum element with the first element
        if(minIndex!=i)
        {
            UserNode temp=arr[i];
            arr[i]=arr[minIndex];
            arr[minIndex]=temp;
        }
    }
}

// Function to display records (recursive)
void displayRecords(UserNode* arr, int left, int right)
{
    if(left<=right)
    {
        cout<<"Username: "<<arr[left].username<<", Role: "<<arr[left].role<<endl;
        displayRecords(arr, left+1, right);
    }
}

// Function to view all user records, sort them, and display
void viewAllRecords()
{
    ifstream file("user_records.txt");

    // If file doesn't exist, create it
    if(!file.is_open())
    {
        cout<<"No existing file found. Creating a new file."<<endl;
        file.close();
        ofstream newFile("user_records.txt");
        newFile.close(); // Close after creating
        return;
    }

    // Count the number of users in the file
    int userCount=0;
    string line;
    while(getline(file, line))
    {
        userCount++;
    }

    // Create an array to store the user records
    UserNode* userArray=new UserNode[userCount];

    // Reset the file pointer to the beginning of the file
    file.clear();
    file.seekg(0, ios::beg);

    // Parse each user record from the file
    int i=0;
    while(getline(file, line))
    {
        int j=0; // Used to keep track of position in the string
        string username="", password="", role="";

        // Extract the username
        while(line[j]!=' '&&j<line.length())
        {
            username+=line[j]; // Add character to username until we hit a space
            j++;
        }
        j++; // Skip the space after username

        // Extract the password
        while(line[j]!=' '&&j<line.length())
        {
            password+=line[j]; // Add character to password until we hit a space
            j++;
        }
        j++; // Skip the space after password

        // Extract the role (everything remaining after the second space)
        while(j<line.length())
        {
            role+=line[j]; // Add remaining characters to role
            j++;
        }

        // Store the values in the array
        userArray[i].username=username;
        userArray[i].password=password;
        userArray[i].role=role;

        i++; // Move to the next index in the array
    }

    // Sort the user records by username using Selection Sort
    selectionSort(userArray, userCount);

    // Display the sorted records using recursion
    cout<<"Displaying all user records:\n";
    displayRecords(userArray, 0, userCount-1);

    // Write the updated records back to the file
    ofstream outFile("user_records.txt");
    if(outFile.is_open())
    {
        for(int i=0; i<userCount; i++)
        {
            outFile<<userArray[i].username<<" "<<userArray[i].password<<" "<<userArray[i].role<<"\n";
        }
        outFile.close();
    }

    // Clean up
    delete[] userArray;
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