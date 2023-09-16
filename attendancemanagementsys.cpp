#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

// prior fxns
string *takeLoginCredentials();
string takePasswordChangeCredentials();
void LoginPage();

// Classes

class Person
{
protected:
public:
    virtual void Login() = 0;
    virtual void Page() = 0;
    virtual void changePassword() = 0;
};

class Admin : public Person
{
private:
    char username[30];
    char password[30];
public:
    Admin() {}
    void setData();
    void write_to_file(string filePath);
    void readFile(string filePath);
    void Login();
    void Page();
    void changePassword();

    bool operator==(Admin &obj)
    {
        string thisUsernameString;
        string thisPasswordString;
        thisUsernameString = username;
        thisPasswordString = password;
        string objUsernameString;
        string objPasswordString;
        objUsernameString = obj.username;
        objPasswordString = obj.password;
        if (thisUsernameString == objUsernameString && thisPasswordString == objPasswordString)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(Admin &obj)
    {
        return !(*this == obj);
    }
};

void Admin ::setData()
{
    string usernameString;
    cout << "Type your username:" << endl;
    fflush(stdin);
    getline(cin, usernameString);
    int i;
    for (i = 0; i < usernameString.length(); i++)
    {
        username[i] = usernameString[i];
    }
    username[i] = '\0';
    string passwordString;
    cout << "Type your password:" << endl;
    fflush(stdin);
    getline(cin, passwordString);
    for (i = 0; i < passwordString.length(); i++)
    {
        password[i] = passwordString[i];
    }
    password[i] = '\0';
}

void Admin::write_to_file(string filePath)
{
    Admin obj;

    ofstream fout;
    fout.open(filePath, ios::app);
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));

    fout.close();
}

void Admin ::readFile(string filePath)
{
    Admin obj;
    string usernameString, passwordString;
    ifstream fin;
    fin.open(filePath, ios::in);
    fin.read((char *)&obj, sizeof(obj));
    while (!fin.eof())
    {
        usernameString = obj.username;
        passwordString = obj.password;
        cout << "username = " << usernameString << endl;
        cout << "password = " << passwordString << endl;
        fin.read((char *)&obj, sizeof(obj));
    }
    fin.close();
}

void Admin ::Login()
{
    setData();
    Admin obj;
    ifstream fin;
    fin.open("admin_list_new.txt", ios::in);
    fin.read((char *)&obj, sizeof(obj));
    while (!fin.eof())
    {
        if (obj == *this) // used operator overloading
        {
            cout << "logged in successfully" << endl;
            this->Page();
            return;
        }
        fin.read((char *)&obj, sizeof(obj));
    }
    fin.close();
    cout << "Please check your details again..." << endl;
    cout << "If you want to go back press 1 and if you want to give another try press 2" << endl;
    char pressed;
    cin >> pressed;
    fflush(stdin);

    switch (pressed)
    {
    case '1':
        LoginPage();
        break;

    case '2':
        this->Login();
        break;

    default:
        cout << "Please give a valid number" << endl;
        LoginPage();
        break;
    }
}

void Admin ::Page()
{
    cout << "Hey " << username << ", Welcome to Attendence Management System" << endl
         << endl;
    cout << "You want to: " << endl;
    cout << "a) Change your password" << endl;
    cout << "b) Add another admin" << endl;
    cout << "c) Add a Teacher" << endl;
    // cout << "d) Remove a Teacher" << endl;
    cout << "d) Add a Student" << endl;
    // cout << "f) Remove a Student" << endl;
    // cout << "g) Grant Attendence" << endl;
    fflush(stdin);
    char AdminOption;
    cin >> AdminOption;
    fflush(stdin);

    switch (AdminOption)
    {
    case 'a':
        this->changePassword();
        break;

    case 'b':
        /* code */
        break;

    case 'c':
        /* code */
        break;

    case 'd':
        /* code */
        break;

    default:
        break;
    }
}

void Admin ::changePassword()
{
    string newPassword = takePasswordChangeCredentials();
    if (!(newPassword == ""))
    {
        string prevPassword = password;

        Admin obj;
        ifstream fin;
        fin.open("admin_list_new.txt", ios::in);
        fin.read((char *)&obj, sizeof(obj));
        ofstream temp;
        temp.open("temp.txt", ios::out);
        while (!fin.eof())
        {
            cout << obj.username << endl;
            cout << obj.password << endl;
            if (!(obj == *this)) // used operator overloading
            {
                temp.write((char *)&obj, sizeof(obj));
            }
            fin.read((char *)&obj, sizeof(obj));
        }
        fin.close();
        temp.close();
        remove("admin_list_new.txt");
        rename("temp.txt", "admin_list_new.txt");
        ofstream fout;
        fout.open("admin_list_new.txt", ios::app);
        strcpy(this->password, newPassword.c_str());
        fout.write((char *)this, sizeof((*this)));
        fout.close();
        // ifstream fin;
        // fin.open("admin_list.txt", ios::in);
        // while (fin)
        // {
        // }
        cout << "Successfully changed the password from " << prevPassword << " to " << newPassword << endl;
    }
    else
    {
        cout << "Password remains the same as it was before." << endl;
    }
}

class Student : public Person
{
private:
public:
    char username[30];
    char password[30];
    Student() {}
    void setData();
    void write_to_file(string filePath);
    void readFile(string filePath);
    void Login();
    void Page();
    void changePassword();

    bool operator==(Student &obj)
    {
        string thisUsernameString;
        string thisPasswordString;
        thisUsernameString = username;
        thisPasswordString = password;
        string objUsernameString;
        string objPasswordString;
        objUsernameString = obj.username;
        objPasswordString = obj.password;
        if (thisUsernameString == objUsernameString && thisPasswordString == objPasswordString)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(Student &obj)
    {
        return !(*this == obj);
    }
};

void Student ::setData()
{
    string usernameString;
    cout << "Type your username:" << endl;
    fflush(stdin);
    getline(cin, usernameString);
    int i;
    for (i = 0; i < usernameString.length(); i++)
    {
        username[i] = usernameString[i];
    }
    username[i] = '\0';
    string passwordString;
    cout << "Type your password:" << endl;
    fflush(stdin);
    getline(cin, passwordString);
    for (i = 0; i < passwordString.length(); i++)
    {
        password[i] = passwordString[i];
    }
    password[i] = '\0';
}

void Student::write_to_file(string filePath)
{
    Student obj;

    ofstream fout;
    fout.open(filePath, ios::app);
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));

    fout.close();
}

void Student ::readFile(string filePath)
{
    Student obj;
    string usernameString, passwordString;
    ifstream fin;
    fin.open(filePath, ios::in);
    fin.read((char *)&obj, sizeof(obj));
    while (!fin.eof())
    {
        usernameString = obj.username;
        passwordString = obj.password;
        cout << "username = " << usernameString << endl;
        cout << "password = " << passwordString << endl;
        fin.read((char *)&obj, sizeof(obj));
    }
    fin.close();
}

void Student ::Login()
{
    setData();
    Student obj;
    ifstream fin;
    fin.open("admin_list_new.txt", ios::in);
    fin.read((char *)&obj, sizeof(obj));
    while (!fin.eof())
    {
        if (obj == *this) // used operator overloading
        {
            cout << "logged in successfully" << endl;
            this->Page();
            return;
        }
        fin.read((char *)&obj, sizeof(obj));
    }
    fin.close();
    cout << "Please check your details again..." << endl;
    cout << "If you want to go back press 1 and if you want to give another try press 2" << endl;
    char pressed;
    cin >> pressed;
    fflush(stdin);

    switch (pressed)
    {
    case '1':
        LoginPage();
        break;

    case '2':
        this->Login();
        break;

    default:
        cout << "Please give a valid number" << endl;
        LoginPage();
        break;
    }
}

void Student ::Page()
{
    cout << "Hey " << username << ", Welcome to Attendence Management System" << endl
         << endl;
    cout << "You want to: " << endl;
    cout << "a) Change your password" << endl;
    cout << "b) Add another admin" << endl;
    cout << "c) Add a Teacher" << endl;
    // cout << "d) Remove a Teacher" << endl;
    cout << "d) Add a Student" << endl;
    // cout << "f) Remove a Student" << endl;
    // cout << "g) Grant Attendence" << endl;
    fflush(stdin);
    char AdminOption;
    cin >> AdminOption;
    fflush(stdin);

    switch (AdminOption)
    {
    case 'a':
        this->changePassword();
        break;

    case 'b':
        /* code */
        break;

    case 'c':
        /* code */
        break;

    case 'd':
        /* code */
        break;

    default:
        break;
    }
}

void Student ::changePassword()
{
    string newPassword = takePasswordChangeCredentials();
    if (!(newPassword == ""))
    {
        string prevPassword = password;

        Student obj;
        ifstream fin;
        fin.open("admin_list_new.txt", ios::in);
        fin.read((char *)&obj, sizeof(obj));
        ofstream temp;
        temp.open("temp.txt", ios::out);
        while (!fin.eof())
        {
            cout << obj.username << endl;
            cout << obj.password << endl;
            if (!(obj == *this)) // used operator overloading
            {
                temp.write((char *)&obj, sizeof(obj));
            }
            fin.read((char *)&obj, sizeof(obj));
        }
        fin.close();
        temp.close();
        remove("admin_list_new.txt");
        rename("temp.txt", "admin_list_new.txt");
        ofstream fout;
        fout.open("admin_list_new.txt", ios::app);
        strcpy(this->password, newPassword.c_str());
        fout.write((char *)this, sizeof((*this)));
        fout.close();
        // ifstream fin;
        // fin.open("admin_list.txt", ios::in);
        // while (fin)
        // {
        // }
        cout << "Successfully changed the password from " << prevPassword << " to " << newPassword << endl;
    }
    else
    {
        cout << "Password remains the same as it was before." << endl;
    }
}

class Teacher : public Person
{
private:
public:
    char username[30];
    char password[30];
    Teacher() {}
    void setData();
    void write_to_file(string filePath);
    void readFile(string filePath);
    void Login();
    void Page();
    void changePassword();

    bool operator==(Teacher &obj)
    {
        string thisUsernameString;
        string thisPasswordString;
        thisUsernameString = username;
        thisPasswordString = password;
        string objUsernameString;
        string objPasswordString;
        objUsernameString = obj.username;
        objPasswordString = obj.password;
        if (thisUsernameString == objUsernameString && thisPasswordString == objPasswordString)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(Teacher &obj)
    {
        return !(*this == obj);
    }
};

void Teacher ::setData()
{
    string usernameString;
    cout << "Type your username:" << endl;
    fflush(stdin);
    getline(cin, usernameString);
    int i;
    for (i = 0; i < usernameString.length(); i++)
    {
        username[i] = usernameString[i];
    }
    username[i] = '\0';
    string passwordString;
    cout << "Type your password:" << endl;
    fflush(stdin);
    getline(cin, passwordString);
    for (i = 0; i < passwordString.length(); i++)
    {
        password[i] = passwordString[i];
    }
    password[i] = '\0';
}

void Teacher::write_to_file(string filePath)
{
    Teacher obj;

    ofstream fout;
    fout.open(filePath, ios::app);
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));
    obj.setData();
    fout.write((char *)&obj, sizeof(obj));

    fout.close();
}

void Teacher ::readFile(string filePath)
{
    Teacher obj;
    string usernameString, passwordString;
    ifstream fin;
    fin.open(filePath, ios::in);
    fin.read((char *)&obj, sizeof(obj));
    while (!fin.eof())
    {
        usernameString = obj.username;
        passwordString = obj.password;
        cout << "username = " << usernameString << endl;
        cout << "password = " << passwordString << endl;
        fin.read((char *)&obj, sizeof(obj));
    }
    fin.close();
}

void Teacher ::Login()
{
    setData();
    Teacher obj;
    ifstream fin;
    fin.open("teacher_list_new.txt", ios::in);
    fin.read((char *)&obj, sizeof(obj));
    while (!fin.eof())
    {
        if (obj == *this) // used operator overloading
        {
            cout << "logged in successfully" << endl;
            this->Page();
            return;
        }
        fin.read((char *)&obj, sizeof(obj));
    }
    fin.close();
    cout << "Please check your details again..." << endl;
    cout << "If you want to go back press 1 and if you want to give another try press 2" << endl;
    char pressed;
    cin >> pressed;
    fflush(stdin);

    switch (pressed)
    {
    case '1':
        LoginPage();
        break;

    case '2':
        this->Login();
        break;

    default:
        cout << "Please give a valid number" << endl;
        LoginPage();
        break;
    }
}

void Teacher ::Page()
{
    cout << "Hey " << username << ", Welcome to Attendence Management System" << endl
         << endl;
    cout << "You want to: " << endl;
    cout << "a) Change your password" << endl;
    // cout << "b) Add another admin" << endl;
    // cout << "c) Add a Teacher" << endl;
    // cout << "d) Remove a Teacher" << endl;
    cout << "b) Add a Student" << endl;
    // cout << "f) Remove a Student" << endl;
    // cout << "g) Grant Attendence" << endl;
    fflush(stdin);
    char AdminOption;
    cin >> AdminOption;
    fflush(stdin);

    switch (AdminOption)
    {
    case 'a':
        this->changePassword();
        break;

    case 'b':
        /* code */
        break;

    case 'c':
        /* code */
        break;

    case 'd':
        /* code */
        break;

    default:
        break;
    }
}

void Teacher ::changePassword()
{
    string newPassword = takePasswordChangeCredentials();
    if (!(newPassword == ""))
    {
        string prevPassword = password;

        Teacher obj;
        ifstream fin;
        fin.open("teacher_list_new.txt", ios::in);
        fin.read((char *)&obj, sizeof(obj));
        ofstream temp;
        temp.open("temp.txt", ios::out);
        while (!fin.eof())
        {
            cout << obj.username << endl;
            cout << obj.password << endl;
            if (!(obj == *this)) // used operator overloading
            {
                temp.write((char *)&obj, sizeof(obj));
            }
            fin.read((char *)&obj, sizeof(obj));
        }
        fin.close();
        temp.close();
        remove("teacher_list_new.txt");
        rename("temp.txt", "teacher_list_new.txt");
        ofstream fout;
        fout.open("teacher_list_new.txt", ios::app);
        strcpy(this->password, newPassword.c_str());
        fout.write((char *)this, sizeof((*this)));
        fout.close();
        // ifstream fin;
        // fin.open("admin_list.txt", ios::in);
        // while (fin)
        // {
        // }
        cout << "Successfully changed the password from " << prevPassword << " to " << newPassword << endl;
    }
    else
    {
        cout << "Password remains the same as it was before." << endl;
    }
}

string *takeLoginCredentials()
{
    static string arr[2];
    cout << "Enter username:" << endl;
    getline(cin, arr[0]);
    fflush(stdin);
    cout << "Enter password:" << endl;
    getline(cin, arr[1]);
    // cin >> arr[1];
    return arr;
}

string takePasswordChangeCredentials()
{
    string newPassword, confirmedPassword;
    cout << "Enter new password:" << endl;
    fflush(stdin);
    getline(cin, newPassword);
    cout << "Confirm password:" << endl;
    fflush(stdin);
    getline(cin, confirmedPassword);
    fflush(stdin);
    if (newPassword == confirmedPassword)
    {
        return confirmedPassword;
    }
    else
    {
        cout << "Both passwords do not match..." << endl;
        cout << "To retry type 1 and to go back type any other key" << endl;
        char ifToChangePasswordRetry;
        fflush(stdin);
        cin >> ifToChangePasswordRetry;
        switch (ifToChangePasswordRetry)
        {
        case '1':
            takePasswordChangeCredentials();
            break;

        default:
            return "";
            break;
        }
    }
}

void LoginPage()
{
    cout << setw(115) << "You want to login as:\na) Admin\nb) Student\nc) Teacher";
    cout << endl;

    char loginChar;
    cin >> loginChar;

    fflush(stdin);

    Person *Pptr = NULL;  //Run time polymorphism

    if (loginChar == 'a')
    {
        // Admin newAdmin;
        // newAdmin.Login();
        Pptr = new Admin;
        Pptr->Login();
        Pptr->Page();
    }
    else if (loginChar == 'b')
    {
        // Student newStudent;
        // newStudent.Login();
        Pptr = new Student;
        Pptr->Login();
        Pptr->Page();
    }
    else if (loginChar == 'c')
    {
        // Teacher newTeacher;
        // newTeacher.Login();
        Pptr = new Teacher;
        Pptr->Login();
        Pptr->Page();
    }
    else
    {
        cout << "Please give a valid input" << endl;
        LoginPage();
    }
}

int main()
{
    // Login Screen
    cout << setfill('-');

    cout << setw(160) << '-';
    cout << endl;
    cout << setfill(' ');
    cout << setw(120) << "***** Welcome To Attendance Management System *****";
    cout << endl;

    cout << setfill('-');
    cout << setw(160) << '-';
    cout << endl;
    cout << setfill(' ');

    LoginPage();
    return 0;
}