#include "person.cpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip> 
using namespace std;

void readData(vector <Person> &emp);
void getCompanies(vector<Person> &emp,vector<string> &names);
void printHightestPaid(vector<Person> &emp);
void separateAndSave(vector<Person> &emp,vector<string> &names);

int main(){
  vector<Person> employees;
  vector<string> companyNames;

  readData(employees);
  getCompanies(employees,companyNames);
  printHightestPaid(employees);
  separateAndSave(employees,companyNames);

  return 0;
}

void readData(vector<Person> &emp){
  string fname, lname,comp, trash;
  int id;
  float hours, pay;

  ifstream input;
  input.open("input.txt");
  while(!input.eof()){
    Person info;
    input >> fname >> lname >> id >> comp >> hours >> pay;
    getline(input,trash);
    info.setFirstName(fname);
    info.setLastName(lname);
    info.setEmployeeId(id);
    info.setCompanyName(comp);
    info.setHoursWorked(hours);
    info.setPayRate(pay);
    emp.push_back(info);
  }

  input.close();
}

void getCompanies(vector<Person> &emp,vector<string> &names){
  string company = " ";
  int i = 0;
  for(int i; i < emp.size(); ++i){
    company = emp[i].getCompanyName();
    names.push_back(company);
  }
}

void printHightestPaid(vector<Person> &emp){
  float highest = 0.0;
  int location = 0;
  for(int j = 0; j < emp.size(); ++j){
    if(emp[j].totalPay() > highest){
      highest = emp[j].totalPay();
      location = j;
    }
  }
  cout << "Highest paid: " << emp[location].fullName() << endl;
  cout << "Employee ID: " << emp[location].getEmployeeId() << endl;
  cout << "Employer: " << emp[location].getCompanyName() << endl;
  cout << "Total Pay: $" << highest << endl;

}

void separateAndSave(vector<Person> &emp,vector<string> &names){
  for(int k = 0; k < names.size(); ++k){
    float total = 0.0;
     ofstream output;
     output.open(names[k]);
    for(int l = 0; l < emp.size(); ++l){
      if(names[k] == emp[l].getCompanyName()){
	output<< left << setw(19) << emp[l].fullName() << right << setw(10) << emp[l].getEmployeeId() << setw(10) << names[k] << setw(10) << "$" << emp[l].totalPay() << endl;
	total += emp[l].totalPay();
      }
    }
    
    output << "Total: $" << total << endl;
    output.close();
  }
}
