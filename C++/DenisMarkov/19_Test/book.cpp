#include "book.h"

Book::Book() {
    Name      = "Book Name";
    Author    = "Book Author";
    Price     = 0;
    Pages     = 0;
    ReadPages = 0;
}
Book::Book(char* name, char* author, int price, int pages, int readpages) {
    Name      = name;
    Author    = author;
    Price     = price;
    Pages     = pages;
    ReadPages = readpages;
}

void Book::setName(char* name) {
    Name      = name;
}
void Book::setAuthor(char* author) {
    Author    = author;
}
void Book::setPrice(int price) {
    Price     = price;
}
void Book::setPages(int pages) {
    Pages     = pages;
}
void Book::setReadPages(int readpages) {
    if(readpages <= Pages)
        ReadPages = readpages;
}

void Book::addReadPages(int value) {
    if(ReadPages+value <= Pages)
        ReadPages += value;
}

char* Book::getName() {
    return Name;
}
char* Book::getAuthor() {
    return Author;
}
int Book::getPrice() {
    return Price;
}
int Book::getPages() {
    return Pages;
}
int Book::getReadPages() {
    return ReadPages;
}
