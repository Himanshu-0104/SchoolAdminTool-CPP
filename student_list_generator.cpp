#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

// prior fxns
string *takeLoginCredentials();
string takePasswordChangeCredentials();
void LoginPage();
void TeacherPage(){};
void StudentPage(){};

// Classes

class Person
{
protected:
public:
    virtual void Login() = 0;
    virtual void Page() = 0;
    virtual void changePassword() = 0;
};

class Student : public Person
{
private:
    char username[30];
    char password[30];

public:
    Student() {}
        void setData()
    {
        string nameString;
        cout << "Type your username:" << endl;
        fflush(stdin);
        getline(cin, nameString);
        int i;
        for (i = 0; i < nameString.length(); i++)
        {
            username[i] = nameString[i];
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

    void write_to_file(string filePath)
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

    void readFile(string filePath)
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

    void Login(){};
    void Page(){};
    void changePassword(){};
};

int main()
{
    Student a;
    a.write_to_file("student_list_new.txt");
    // a.readFile("admin_list_new.txt");
}