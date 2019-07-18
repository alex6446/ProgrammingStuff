#pragma once

class Book {
    private:
        char*   Name;
        char*   Author;
        int     Price;
        int     Pages;
        int     ReadPages;

    public:
        Book();
        Book(char*, char* author="Book Author", int price=0, int pages=0, int readpages=0);
        void    setName(char*);
        void    setAuthor(char*);
        void    setPrice(int);
        void    setPages(int);
        void    setReadPages(int);

        void    addReadPages(int);

        char*   getName();
        char*   getAuthor();
        int     getPrice();
        int     getPages();
        int     getReadPages();
};
