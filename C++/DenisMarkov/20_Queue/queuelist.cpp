#include "queuelist.h"

/////   QueueList   //////////////////////////////////////////////////////////

QueueList::QueueList(){
    next  = nullptr;
}

void QueueList::Push(int num) {
    Steck *pv   = new Steck;
    pv->key     = num;
    pv->next    = next;
    next        = pv;
}

int QueueList::Pop() {
    /*int temp    = next->key;
    Steck *pv   = next;
    next        = next->next;
    delete pv;
    return temp;*/

    Steck *pv   = next;

    int temp;
    if(pv->next != nullptr) {
        while(pv->next->next != nullptr)
            pv = pv->next;
        temp = pv->next->key;
        delete pv->next;
        pv->next = nullptr;

    } else {
        temp = pv->key;
        delete  pv;
        next = nullptr;
    }

    return temp;
}

/////   QueueArray   //////////////////////////////////////////////////////////

QueueArray::QueueArray(int number) {
    Max     = 1000;
    index   = 0;
    if(number <= Max) {
        arr = new int[number];
        Max = number;
    }
}

QueueArray::~QueueArray() {
    delete [] arr;
};

bool QueueArray::Push(int num) {
    if(index == Max)
        return false;
    else {
        arr[index] = num;
        index++;
        return true;
    }
}

int QueueArray::Pop() {
    if(index < 0)
        return 0;
    else {
        int temp = arr[0];
        for(int i = 0; i < index-1; i++) {
            arr[i] = arr[i+1];
        }
        index--;
        return temp;
    }
}

bool QueueArray::Is_empty() {
    if(index <= 0)
        return true;
    else
        return false;
}

bool QueueArray::Is_full() {
    if(index == Max)
        return true;
    else
        return false;
}


















