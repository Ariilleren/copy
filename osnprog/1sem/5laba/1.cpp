#include <iostream>
using namespace std;

struct list {
    char x;
    int size = 0;
    list *Next,*Head;
};
 
void add(char x, list *&MyList) {
    list *temp = new list;
    temp->x = x;
    temp->Next = MyList->Head;
    MyList->Head = temp;
    MyList->size++;
}
 
void show(list *MyList) {
    list *temp = MyList->Head;

    while (temp != NULL) {
        cout << temp->x << " ";
        temp = temp->Next;
    }
}
 
void clear(list *MyList) {
    while (MyList->Head != NULL) {

        list *temp = MyList->Head->Next;
        delete MyList->Head;
        MyList->Head = temp;
    }
    MyList->size = 0;
}

char at(int position, list *MyList) {
    list *temp = MyList->Head;
    for (int i = 0; i < position; i++) {
        temp = temp->Next;
    }
    return temp->x;
}
 
int main() {
    list *MyList = new list;

    MyList->Head = NULL;

    for (int i='z'; i>='a'; i--) {
        add(i,MyList);
    }
    show(MyList);
    cout << endl << endl;
    for (int i = 0; i < MyList->size; i++) {
        char elem = at(i, MyList);
        if (elem >= 'f' && elem <= 'q') {
            cout << elem << " ";
        }
    }
    clear(MyList);
    delete MyList->Head;
    delete MyList;
    return 0;
}