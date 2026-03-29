#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct PhoneBook{
  long Number;
  string Surname;
};

void StartMenu(vector<PhoneBook> &book);
void AddNumber(vector<PhoneBook> &book);
void SortNumbers(vector<PhoneBook> &book);
void Table(vector<PhoneBook> &book);

int main()
{
  vector<PhoneBook> Book1;
  StartMenu(Book1);
  return 0;
}

void StartMenu(vector<PhoneBook> &book)
{
  int command;
  bool IsOk = true;
  while(IsOk){
    cout << "Enter 1 for adding a new phone number" << endl;
    cout << "Enter 2 for sorting phone numbers by surname" << endl;
    cout << "Enter 3 for exit" << endl;
    cin >> command;
    switch(command){
      case 1: AddNumber(book); break;
      case 2: SortNumbers(book); Table(book); break;
      case 3: cout << "Goodbye!" << endl; return;
      default: cout << "Error." << endl; IsOk = false; break; 
    }
  }
}

void AddNumber(vector<PhoneBook> &book)
{
  PhoneBook newNumber;
  cout << "Adding a new phone number." << endl;
  cout << "Enter the phone number: "; cin >> newNumber.Number; cin.ignore(10000,'\n');
  cout << "Enter the surname: "; getline(cin, newNumber.Surname);
  book.push_back(newNumber);
  cout << "Successful!" << endl;
}

void SortNumbers(vector<PhoneBook> &book)
{
  sort(book.begin(), book.end(), [](const PhoneBook &a, const PhoneBook &b){ return a.Surname < b.Surname; });
}

void Table(vector<PhoneBook> &book)
{
  for (size_t i = 0; i < book.size(); i++){
    cout << "#" << i+1 << endl;
    cout << "Number: " << book[i].Number << endl;
    cout << "Surname: " << book[i].Surname << endl;
    cout << "====================================" << endl;
  }
}