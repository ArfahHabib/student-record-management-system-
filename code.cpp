#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

// BSTnode structure to store course names and grades
struct BSTNode
{
    string course; 
    float grade;   
    BSTNode *left;
    BSTNode *right;

    BSTNode(string c, float g) : course(c), grade(g), left(NULL), right(NULL) {}
};

// Simple Hash Map structure for storing users and their courses
struct HashMapTable
{
    list<pair<string,string>> *table; 
    int table_size;

    
    HashMapTable(int ts)
    {
        table_size=ts;
        table=new list<pair<string,string>>[table_size];
    }

  
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
    string role;          
    list<string> courses; 
    UserNode *next;
};


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
    UserNode *userHead;     
    CourseNode *courseRoot; 

    vector<vector<int>> courseGraph; 

public:
   
    ManagementSystem() : userHead(NULL), courseRoot(NULL)
    {
        courseGraph.resize(100); 
    }

     void registerUser(){
    string username, password, role;

    
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;
    cout<<"Enter role (student/faculty/admin): ";
    cin>>role;

    
    UserNode* newUser = new UserNode;
    newUser->username=username;
    newUser->password=password;
    newUser->role=role;
    newUser->next=NULL;

    if(userHead==NULL)
    {
        userHead=newUser; 
    }
    else
    {
        UserNode* temp=userHead;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newUser; 
    }

 
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
{ 
    string username, password;

    
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

   
    UserNode* temp=userHead;
    while(temp!=NULL)
    {
        if(temp->username==username && temp->password==password)
        {
            role=temp->role; 
            cout<<"Login successful!\n";
            return true;
        }
        temp=temp->next;
    }

    cout<<"Invalid username or password. Try again.\n";
    return false;
}

    
void addCourse(CourseNode*& head, const string& courseName)
{
    
    CourseNode* newCourse = new CourseNode;
    newCourse->courseName=courseName;
    newCourse->next=NULL;

   
    if(head==NULL)
    {
        head=newCourse;
    }
    else
    {
        
        CourseNode* temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newCourse;
    }

 
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


void removeCourse(CourseNode*& head, const string& courseName)
{
    
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

    
    if(head==NULL)
    {
        cout<<"The course list is empty."<<endl;
        return;
    }

    
    if(head->courseName==courseName)
    {
        CourseNode* temp=head;
        head=head->next; 
        delete temp;     
        cout<<"Course '"<<courseName<<"' removed."<<endl;
    }
    else
    {
        
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

        
        prev->next=temp->next;
        delete temp; 
        cout<<"Course '"<<courseName<<"' removed."<<endl;
    }
}


    
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
        allCourses.push_back(course); 
    }

    file.close();
}


void displayAvailableCoursesBFS(const vector<string>& allCourses)
{
    if(allCourses.empty())
    {
        cout<<"No courses available.\n";
        return;
    }

    cout<<"Available Courses (BFS):\n";

    list<string> courseQueue; 

    
    courseQueue.push_back(allCourses[0]);

    
    bool visited[allCourses.size()]={false};

    visited[0]=true; 

    while(!courseQueue.empty())
    {
        string currentCourse=courseQueue.front(); 
        courseQueue.pop_front();

        cout<<currentCourse<<endl; 

        
        int courseIndex=-1;
        for(int i=0;i<allCourses.size();++i)
        {
            if(allCourses[i]==currentCourse)
            {
                courseIndex=i;
                break;
            }
        }

        
        if(courseIndex!=-1)
        {
            
            for(int i=0;i<allCourses.size();++i)
            {
                if(!visited[i])
                {
                    visited[i]=true;                    
                    courseQueue.push_back(allCourses[i]); 
                }
            }
        }
    }
}

    
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

   
bool registerCourse(vector<string>& registeredCourses, const vector<string>& availableCourses)
{
    int courseIndex;
    cout<<"Enter the course number (starting from 0) you want to register for: ";
    cin>>courseIndex;

    
    if(courseIndex<0||courseIndex>=availableCourses.size())
    {
        cout<<"Invalid course selection.\n";
        return false;
    }

    string courseToRegister = availableCourses[courseIndex];

    
    for(const auto& course : registeredCourses)
    {
        if(course==courseToRegister)
        {
            cout<<"You are already registered for this course.\n";
            return false;
        }
    }

    registeredCourses.push_back(courseToRegister);
    cout<<"You have successfully registered for "<<courseToRegister<<".\n";
    return true;
}

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

    cout<<"Select a course to assign a grade:"<<endl;
    for(int i=0; i<courses.size(); ++i)
    {
        cout<<i+1<<". "<<courses[i]<<endl;
    }

    
    int courseChoice;
    cout<<"Enter the number of the course: ";
    cin>>courseChoice;

    if(courseChoice<1||courseChoice>courses.size())
    {
        cout<<"Invalid course choice!"<<endl;
        return;
    }

    
    cout<<"Enter the grade for the course "<<courses[courseChoice-1]<<": ";
    cin>>grade;

    
    gradeStack.push(grade);

    
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
            userFound=true; 
            continue;       
        }
        outputFile<<line<<endl;
    }

   
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

    if(!file.is_open())
    {
        cout<<"No existing file found. Creating a new file."<<endl;
        file.close();
        ofstream newFile("user_records.txt");
        newFile.close(); // Close after creating
        return;
    }

  
    int userCount=0;
    string line;
    while(getline(file, line))
    {
        userCount++;
    }

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

        while(line[j]!=' '&&j<line.length())
        {
            username+=line[j]; 
            j++;
        }
        j++; 

        while(line[j]!=' '&&j<line.length())
        {
            password+=line[j];
            j++;
        }
        j++; 

        while(j<line.length())
        {
            role+=line[j]; 
            j++;
        }

        userArray[i].username=username;
        userArray[i].password=password;
        userArray[i].role=role;

        i++; 
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

    delete[] userArray;
}


    // Function to search for a user by username
UserNode* searchUserByUsername(const string& username)
{
    UserNode* temp = userHead;
    while(temp!=NULL)
    {
        if(temp->username==username)
        {
            return temp; // Return the found user
        }
        temp = temp->next;
    }
    return NULL; // User not found
}

// Function to generate a student report with courses and grades
void generateStudentReport(BSTNode* root, vector<string>& courses)
{
    
    cout<<"Student Report - Courses and Grades:" << endl;
    
    if(root==NULL)
    {
        cout<<"No courses or grades available!" << endl;
        return;
    }

    inOrderTraversal(root);

    cout<<"\nCourses List (without grades):" << endl;
    for(int i=0;i<courses.size();++i)
    {
        cout<<i+1<<". "<<courses[i] << endl;
    }
}

void studentMenu(const string& username)
{
    string filename="courses.txt"; 
    vector<string> allCourses;       
    vector<string> registeredCourses; 

    loadCoursesFromFile(filename, allCourses);

    bool registrationSuccess=false;

    while(true)
    {
        int choice;
        cout<<"\n1. Display available courses\n2. Register for a course\n3. View registered courses\n4. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            displayAvailableCoursesBFS(allCourses);
            break;

        case 2:
            registrationSuccess=registerCourse(registeredCourses, allCourses);
            if(registrationSuccess)
            {
                cout<<"Registration successful.\n";
            }
            else
            {
                cout<<"Registration failed.\n";
            }
            break;

        case 3:
            displayRegisteredCourses(registeredCourses);
            break;

        case 4:
            cout<<"Exiting...\n";
            return; 

        default:
            cout<<"Invalid choice. Please try again.\n";
            break;
        }
    }
}

   void facultyMenu(const string& username)
{
    // Declare and initialize the stack and root
    stack<float> gradeStack;         // Stack to hold grades
    BSTNode* root=NULL;              // Root of the Binary Search Tree (BST)
    string courseName;               // Declare the courseName variable here
    string filename="courses.txt";   // File with course data
    vector<string> allCourses;       // All available courses
    // Load the courses from the file
    loadCoursesFromFile(filename, allCourses);

    while(true)
    {
        cout<<"\n===== Faculty Menu =====\n";
        cout<<"1. Assign Grades\n";
        cout<<"2. Add Course\n";
        cout<<"3. Remove Course\n";
        cout<<"4. View Course List\n";
        cout<<"5. Logout\n";
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;

        switch(choice)
        {
        case 1:
            // Get the grade to assign
            float grade;
            cout<<"Enter grade to assign: ";
            cin>>grade;
            assignGrade(gradeStack, root, grade, allCourses);
            break;

        case 2:
            cout<<"Enter course name to add: ";
            cin>>courseName;
            addCourse(courseRoot, courseName); // Now passing the course name
            break;
        case 3:
        {
            cout<<"Enter course name to remove: ";
            cin>>courseName;
            removeCourse(courseRoot, courseName);
            break;
        }
        case 4:
            displayAvailableCoursesBFS(allCourses);
            break;
        case 6:
            cout<<"Logging out...\n";
            return;
        default:
            cout<<"Invalid choice! Try again.\n";
        }
    }
}

void adminMenu()
{
    string filename="courses.txt";   
    vector<string> allCourses;       
    BSTNode* root;

    loadCoursesFromFile(filename, allCourses);
    while(true)
    {
        cout<<"\n===== Admin Menu =====\n";
        cout<<"1. Register New User\n";
        cout<<"2. Remove User\n";
        cout<<"3. View User List\n";
        cout<<"4. View All Courses\n";
        cout<<"5. Generate Reports\n";
        cout<<"6. Logout\n";
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;

        switch(choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
        {
            string username;
            cout<<"Enter the username to delete: ";
            getline(cin, username);
            removeUser(username);
            break;
        }
        case 3:
            viewAllRecords();
            break;
        case 4:
            displayAvailableCoursesBFS(allCourses);
            break;
        case 5:
        {
            string username;
            cout<<"Enter the username for the report: ";
            cin>>username;
            generateStudentReport(root, allCourses); // Pass the username to generate the report
        }
        break;

        case 6:
            cout<<"Logging out...\n";
            return;
        default:
            cout<<"Invalid choice! Try again.\n";
        }
    }
}
};

int main()
{
    ManagementSystem system;
    int choice;

    do
    {
        cout<<"1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            system.registerUser();
            break;
        case 2:
        {
            string role;
            if(system.loginUser(role))
            {
                if(role=="student")
                {
                    system.studentMenu(role);
                }
                else if(role=="faculty")
                {
                    system.facultyMenu(role);
                }
                else if(role=="admin")
                {
                    system.adminMenu();
                }
            }
            break;
        }
        case 3:
            cout<<"Exiting..."<<endl;
            break;
        default:
            cout<<"Invalid choice! Please try again."<<endl;
        }
    } while(choice!=3);

    return 0;
}