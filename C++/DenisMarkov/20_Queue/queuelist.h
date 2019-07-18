#pragma once

struct Steck {
    int     key;
    Steck   *next;
};

class QueueList {
    private:
        Steck   *next;

    public:
        QueueList();
        void    Push(int);
        int     Pop();
};

class QueueArray {
    private:
        int*    arr;
        int     Max;
        int     index;
    public:
        QueueArray(int);
        ~QueueArray();
        bool    Push(int);
        int     Pop();
        bool    Is_empty();
        bool    Is_full();
};
