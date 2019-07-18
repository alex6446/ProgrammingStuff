#include <iostream>
#include "queuelist.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    /*QueueList list;
    list.Push(12);
    list.Push(45);
    list.Push(64);

    cout << list.Pop() << endl;
    cout << list.Pop() << endl;
    list.Push(88);
    list.Push(108);
    cout << list.Pop() << endl;
    cout << list.Pop() << endl;
    cout << list.Pop() << endl;*/

    QueueArray arr(20);
    arr.Push(3);
    arr.Push(15);
    arr.Push(25);

    cout << arr.Pop() << endl;
    cout << arr.Pop() << endl;
    cout << arr.Pop() << endl;

    return 0;
}
