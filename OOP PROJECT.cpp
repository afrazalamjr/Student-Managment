#include<iostream>

#include<iomanip>

#include<fstream>

using namespace std;
void afraz(string s, string s1, string s2) //function to edit any input fileH. Inputs 3 parameters, first parameter is the name of the file, second parameter is what to edit, third is what to replace with.
{
  ifstream fin;
  fin.open(s.c_str()); //file opened by name of parameter s
  ofstream fot;
  int a, b, c;
  fot.open("temp.txt"); //temporary output file opened to store data temporarily
  string line;
  string hmm;
  while (getline(fin, line)) { //while loop running until all lines of a file have been input
    a = line.find(s1); //finding desired word from parameter s1
    if (a == -1) {
      fot << line << endl; //until desired word is not found, line is output to temp.txt as is
    } else //when desired word found, replace it with replacement word
    {
      fot << s1 << " " << s2 << endl;
    }
  }
  fot.close(); //close temp.txt
  fin.close(); //close input file
  fin.open("temp.txt"); //use temp as input file
  fot.open(s.c_str()); //use parameter s as output file
  while (getline(fin, line)) {
    fot << line << endl; //output data from temp to output file
  }
}
string encrypt(string a) { //simple encryption function to change values of any input string and return same string 
  int temp;
  int offset[28] = {
    20,
    11,
    23,
    12,
    5,
    6,
    12,
    6,
    7,
    5,
    3,
    0,
    1,
    1,
    9,
    19,
    17,
    25,
    24,
    4,
    19,
    22,
    2,
    1,
    7,
    12,
    3,
    0
  };
  for (int i = 0; i < a.length(); i++) {
    a[i] = char(int(a[i]) + offset[i]);
  }
  return a;
}

string decrypt(string a) { //simple decryption function to change bacl values of any input string and return decrypted string
  int offset[28] = {
    20,
    11,
    23,
    12,
    5,
    6,
    12,
    6,
    7,
    5,
    3,
    0,
    1,
    1,
    9,
    19,
    17,
    25,
    24,
    4,
    19,
    22,
    2,
    1,
    7,
    12,
    3,
    0
  };
  for (int i = 0; i < a.length(); i++) {
    a[i] = char(int(a[i]) - offset[i]);
  }
  return a;
}

class person { //Master class person, parent to student, faculty and management. Grandparent to HOD class
  private: // private variables
    int age;
  string email;
  string address;
  string name;
  string password;

  protected: //protected ID, needed in child classes
    string ID;

  public:
    person() //defualt constructor
  {
    age = 0;
    email = "";
    address = "";
    name = "";
    password = "";
    ID = "";
  }
  friend string encrypt(string a); //encrypting the password string to hide from people accessing file directly
  string IDfile;
  string passfile;

  void setIDfile() { //adding .txt to the file name to store data as txt files
    IDfile = ID + ".txt";
  }
  void setpassfile() { //adding .txt to the password file name to store data as txt files
    passfile = ID + "pass.txt";
  }

  void setID(string a) { //setter for ID
    ID = a;
  }

  void input() { //input member function to enter all Relevant values
    cout << "Enter name: " << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Enter Age: " << endl;
    cin >> age;
    while (age < 0 || age > 120) {
      cout << "Error. Age incorrect." << endl;
      cin >> age;
    }
    cout << "Enter Email: " << endl;
    cin >> email;
    cout << "Enter Address: " << endl;
    cin.ignore();
    getline(cin, address);
    cout << "Enter Password: " << endl;
    cin >> password;
  }

  void savepassword() { //savepassword to a file
    ofstream paa;
    paa.open(passfile.c_str());
    paa << encrypt(password); //encrypt password before outputting to file
    paa.close();
  }
  ofstream dataout;
  void savetofile() { //save data in a file
    dataout.open(IDfile.c_str());
    dataout
      <<
      "Name: " << name << endl <<
      "ID: " << ID << endl <<
      "Age: " << age << endl <<
      "Email: " << email << endl <<
      "Address: " << address << endl;
  }

  string getpass() { //getter for password
    return password;
  }

  void viewdata(string n) { //display function to access data from a file
    string m;
    m = n + ".txt";
    ifstream datain;
    datain.open(m.c_str());
    string line;
    while (getline(datain, line)) {
      cout << line << endl;
    }
  }
  friend void afraz(string, string, string); //function decalred as friend function
};

class student: public virtual person { //child class student, specialized for students
  private: string department;
  float cgpa,
  gpa[140];
  int clearedcredits = 0; 
   int credit[140];
  string subjects[140];
  int subjectcount = 0;
  public: student() //default constructor
  {
    department = "";
    cgpa = 0;
    for (int i = 0; i < 140; i++) {
      gpa[i] = 0;
      credit[i] = 0;
    }

  }
  void inputs() { //input function for extra inputs of student
    cout << "Enter department: " << endl;
    cin.ignore();
    getline(cin, department);
    char subchoice = 'N';
    cout << "Enter (Y) to add a subject you have studied: " << endl;
    cin >> subchoice;
    while (subchoice == 'Y' || subchoice == 'y') {
      cout << "Enter subject " << subjectcount + 1 << ": " << endl;
      cin.ignore();
      getline(cin, subjects[subjectcount]);
      cout << "Enter Subject credit hours: " << endl;
      cin >> credit[subjectcount];
      while (credit[subjectcount] <= 0 || credit[subjectcount] > 4) {
        cout << "Error. Enter credit hours between 1 and 4: " << endl;
        cout << "Enter Subject credit hours: " << endl;
        cin >> credit[subjectcount];
      }
      cout << "Enter Subject attained GPA: " << endl;
      cin >> gpa[subjectcount];
      while (gpa[subjectcount] < 0 || gpa[subjectcount] > 4) {
        cout << "Error. Enter GPA between 0 and 4: " << endl;
        cout << "Enter Subject GPA: " << endl;
        cin >> gpa[subjectcount];
      }
      cgpa = (cgpa + gpa[subjectcount]);
      clearedcredits = clearedcredits + credit[subjectcount];
      cout << "Enter (Y) to add another subject you have studied: " << endl;
      cin >> subchoice;
      subjectcount++;
    }
    cgpa = cgpa / (subjectcount);
  }

  void savetofiles() { //saving data to a file
    dataout
      <<
      "Department: " << department << endl <<
      "CGPA: " << cgpa << endl <<
      "Cleared Credits: " << clearedcredits << endl << endl <<
      left << setw(30) << "Subjects" << right << setw(30) << "Credit hours" << right << setw(30) << "GPA" << endl << endl;
    for (int i = 0; i < subjectcount; i++) {
      dataout << left << setw(30) << subjects[i] << right << setw(30) << credit[i] << right << setw(30) << gpa[i] << endl << "******************************" << endl;
    }
  }
};

class faculty: public virtual person { //child class faculty
  private: string subject;
  int yearsemployed;
  float salary;
  public: faculty() //default constructor for faculty class
  {
    subject = "";
    yearsemployed = 0;
    salary = 0;
  }
  void inputf() { //input function for extra inputs of faculty
    cout << "Enter Taught Subject: " << endl;
    cin.ignore();
    getline(cin, subject);
    cout << "Enter Years employed: " << endl;
    cin >> yearsemployed;
    cout << "Enter Salary: " << endl;
    cin >> salary;
  }

  void savetofilef() { //saving to file
    dataout
      <<
      "Taught Subject: " << subject << endl <<
      "Years employed: " << yearsemployed << endl <<
      "Salary: " << salary << endl;
  }

  void findstudents(string s) //function for a teacher to find a student
  {
    ifstream f;
    string line;

    f.open(s.c_str());
    if (!f) {
      cout << "No students with the entered ID." << endl;
    } else {
      cout << "Student data: " << endl;
      while (getline(f, line)) {
        cout << line << endl;
      }
    }
  }

};

class management: public virtual person { //child class management
  private: string role;
  int yearsemployed;
  float salary;
  public: management() //default constructor for management class
  {
    role = "";
    salary = 0;
  }
  void inputm() { //input funtion for extra memebers of management class
    cout << "Enter Role in management: " << endl;
    cin.ignore();
    getline(cin, role);
    cout << "Enter Years employed: " << endl;
    cin >> yearsemployed;
    cout << "Enter Salary: " << endl;
    cin >> salary;
  }

  void savetofilem() { //save all data to a file
    dataout
      <<
      "Taught Role in management: " << role << endl <<
      "Years employed: " << yearsemployed << endl <<
      "Salary: " << salary << endl;
  }

  void findfaculty(string s) //find specific faculty members
  {
    ifstream f;
    string line;
    f.open(s.c_str());
    if (!f) {
      cout << "No faculty with the entered ID." << endl;
    } else {
      cout << "Faculty data: " << endl;
      while (getline(f, line)) {
        cout << line << endl;
      }
    }
  }

};

class HOD: public faculty, public management, public student //class HOD, child of student, faculty and management. Grandchild of Person
{
  public: void deletefile() //function to let HOD delete someones record from database
  {
    string b;
    cout << "Welcome, HOD. Enter an employment or student ID to remove from database: " << endl;
    cin >> b;
    b = b + ".txt";
    remove(b.c_str());
    system("cls");
    cout << "Deleted." << endl << endl;
  }
};

int main() { //main function 
  student s; //objects initialized for all 4 classes
  faculty f;
  management m;
  HOD h;
  int meh = 0;
  char ed = 'K';
  string s1;
  char cond = 'K';
  string b, filecheck, pass, getpass, dummypass;
  do {
    cout << "Welcone to University Manager Portal"<<endl<<
	       "Enter: " << endl << //menu to let user decide Their category
      "(S) for Student." << endl <<
      "(F) for Faculty." << endl <<
      "(M) for Management." << endl <<
      "(H) for HOD." << endl <<
      "(E) to Exit." << endl;
    char choice;
    cin >> choice;
    system("cls");
    switch (choice) { //switch function used to choose between options

    case 'S': { // case S, for students
      cout << "Enter Student Roll number: " << endl;
      cin >> b;
      filecheck = b + ".txt";
      pass = b + "pass.txt";
      s.setID(b);
      ifstream maindata;
      maindata.open(filecheck.c_str());
      ifstream passcheck;
      passcheck.open(pass.c_str());
      passcheck >> getpass;
      getpass = decrypt(getpass);
      if (maindata.is_open()) { //checks if file already exists, if does, asks for password and displays data

        cout << "Welcome back!" << endl;
        cout << "Enter password for ID '" << b << "' : " << endl;
        cin >> dummypass;
        while (dummypass != getpass) {
          cout << "Incorrect password. Retry." << endl;
          cout << "Enter password for ID '" << b << "' : " << endl;
          cin >> dummypass;
        }
        system("cls");
        s.viewdata(b);
        maindata.close();
      } else { //if file is not present, asks user to input new data to register new student
        cout << "Welcome New student!" << endl;
        s.input();
        s.inputs();
        s.setIDfile();
        s.setpassfile();
        s.savetofile();
        s.savetofiles();
        s.savepassword();
      }
    }
    break;

    case 'F': { //case F, for faculty
      cout << "Enter Faculty ID number: " << endl;
      cin >> b;
      filecheck = b + ".txt";
      pass = b + "pass.txt";
      f.setID(b);
      ifstream maindata;
      maindata.open(filecheck.c_str());
      ifstream passcheck;
      passcheck.open(pass.c_str());
      passcheck >> getpass;
      getpass = decrypt(getpass);
      system("CLS");
      if (maindata.is_open()) { //checks if file already exists, if does, asks for password and displays data
        cout << "Welcome back!" << endl;
        cout << "Enter password for ID '" << b << "' : " << endl;
        cin >> dummypass;
        while (dummypass != getpass) {
          cout << "Incorrect password. Retry." << endl;
          cout << "Enter password for ID '" << b << "' : " << endl;
          cin >> dummypass;
        }
        system("cls");
        f.viewdata(b);
        maindata.close();
        cout << "Do you want to view data of a student? (Y/N)" << endl; //asks if teachers wants too see data of student
        cin >> cond;
        while (cond == 'Y' || cond == 'y') {
          cout << "Enter ID of student: " << endl;
          cin >> b;
          b = b + ".txt";
          f.findstudents(b);
          cout << "Enter: " << endl //options to change different aspects of a students data
            <<
            "(1) to change age of student." << endl <<
            "(2) to change email of student." << endl <<
            "(3) to change address of student." << endl <<
            "(4) to change department of student." << endl <<
            "(5) to add another subject for student." << endl <<
            "(0) to make no changes." << endl;

          cin >> ed;
          switch (ed) {
          case '1':
            cout << "Enter age of student: " << endl;
            cin >> s1;
            afraz(b, "Age: ", s1);
            break;
          case '2':
            cout << "Enter email of student: " << endl;
            cin.ignore();
            getline(cin, s1);
            afraz(b, "Email: ", s1);
            break;
          case '3':
            cout << "Enter address of student: " << endl;
            cin.ignore();
            getline(cin, s1);
            afraz(b, "Address: ", s1);
            break;
          case '4':
            cout << "Enter department of student: " << endl;
            cin.ignore();
            getline(cin, s1);
            afraz(b, "Department: ", s1);
            break;
          case '0':
            cout << "Exiting student editing menu." << endl;
            break;
          default:
            cout << "Error. Enter number from 0 to 5 only. Retry. " << endl;
            break;
          }
          cout << "Do you want to view data of a student? (Y/N)" << endl;
          cin >> cond;
        }
      } else { //if file is not present, asks user to input new data to register new student
        cout << "Welcome New Faculty member!" << endl;
        f.input();
        f.inputf();
        f.setIDfile();
        f.setpassfile();
        f.savetofile();
        f.savetofilef();
        f.savepassword();
      }
      cout << "******************************" << endl;
    }
    break;

    case 'M': { //case M, for management
      cout << "Enter Management ID number: " << endl;
      cin >> b;
      filecheck = b + ".txt";
      pass = b + "pass.txt";
      m.setID(b);
      ifstream maindata;
      maindata.open(filecheck.c_str());
      ifstream passcheck;
      passcheck.open(pass.c_str());
      passcheck >> getpass;
      getpass = decrypt(getpass);
      system("CLS");
      if (maindata.is_open()) { //checks if file already exists, if does, asks for password and displays data
        cout << "Welcome back!" << endl;
        cout << "Enter password for ID '" << b << "' : " << endl;
        cin >> dummypass;
        while (dummypass != getpass) {
          cout << "Incorrect password. Retry." << endl;
          cout << "Enter password for ID '" << b << "' : " << endl;
          cin >> dummypass;
        }
        system("cls");
        m.viewdata(b);
        cout << "Do you want to find a faculty member? (Y/N)" << endl;
        cin >> cond;
        while (cond == 'Y' || cond == 'y') {
          cout << "Enter faculty member ID: " << endl;
          cin >> b;
          b = b + ".txt";
          m.findfaculty(b);
          cout << "Enter: " << endl //various options to change different aspects of a faculty member data
            <<
            "(1) to change faculty age: " << endl <<
            "(2) to change faculty email: " << endl <<
            "(3) to change faculty address: " << endl <<
            "(4) to change faculty taught subject: " << endl <<
            "(5) to change faculty years employed: " << endl <<
            "(6) to change faculty salary: " << endl <<
            "(0) to make no changes. " << endl;
          cin >> ed;
          switch (ed) {
          case '1':
            cout << "Enter age of faculty: " << endl;
            cin >> s1;
            afraz(b, "Age: ", s1);
            break;
          case '2':
            cout << "Enter email of faculty: " << endl;
            cin.ignore();
            getline(cin, s1);
            afraz(b, "Email: ", s1);
            break;
          case '3':
            cout << "Enter address of faculty: " << endl;
            cin.ignore();
            getline(cin, s1);
            afraz(b, "Address: ", s1);
            break;
          case '4':
            cout << "Enter taught subject of faculty: " << endl;
            cin.ignore();
            getline(cin, s1);
            afraz(b, "Taught Subject: ", s1);
            break;
          case '5':
            cout << "Years employed of faculty: " << endl;
            cin >> s1;
            afraz(b, "Years employed: ", s1);
            break;
          case '6':
            cout << "Enter salary of faculty: " << endl;
            cin >> s1;
            afraz(b, "Salary: ", s1);
            break;
          case '0':
            cout << "Exiting faculty editing menu." << endl;
            break;
          default:
            cout << "Error. Enter number from 0 to 5 only. Retry. " << endl;
            break;
          }
          cout << "Do you want to find a faculty member? (Y/N)" << endl;
          cin >> cond;
        }
      } else { //if file is not present, asks user to input new data to register new student
        cout << "Welcome New Faculty member!" << endl;
        m.input();
        m.inputm();
        m.setIDfile();
        m.setpassfile();
        m.savetofile();
        m.savetofilem();
        m.savepassword();
      }
      maindata.close();
      break;

      cout << "******************************" << endl;
    }

    case 'H': //case H, for HOD
    {
      cout << "Enter HOD ID: " << endl;
      cin >> b;
      filecheck = b + ".txt";
      pass = b + "pass.txt";
      h.setID(b);
      ifstream maindata;
      maindata.open(filecheck.c_str());
      ifstream passcheck;
      passcheck.open(pass.c_str());
      passcheck >> getpass;
      getpass = decrypt(getpass);
      system("CLS");
      if (maindata.is_open()) { //checks if file already exists, if does, asks for password and displays data
        cout << "Welcome back!" << endl;
        cout << "Enter password for ID '" << b << "' : " << endl;
        cin >> dummypass;
        while (dummypass != getpass) {
          cout << "Incorrect password. Retry." << endl;
          cout << "Enter password for ID '" << b << "' : " << endl;
          cin >> dummypass;
        }
        system("cls");
        h.viewdata(b);
        cout << endl << "Do you want to delete someone from the database? (Y/N)" << endl; //asks if wants to delete someones file
        cin >> ed;
        if (ed == 'Y') {
          h.deletefile();
        }
      } else { //if file is not present, asks user to input new data to register new student
        cout << "Welcome New HOD!" << endl;
        h.input();
        h.setIDfile();
        h.setpassfile();
        h.savetofile();
        h.savetofilem();
        h.savepassword();
      }
      break;
    }

    case 'E': {
      cond = 'E';
      break;
    }
    default:
      system("cls");
      cout << "Please enter (S), (F), (M) or (E) only." << endl;
      cout << "******************************" << endl;
    }
  }
  while (cond != 'E');
  system("cls");
  cout << "Thank you for using our program. Goodbye." << endl;
  return 0;
}
