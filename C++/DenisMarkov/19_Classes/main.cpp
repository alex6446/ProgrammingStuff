#include <iostream>
#include "book.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    Book chara("Undertale", "Toby Fox", 78, 51, 12);
    /*chara.setName      ("Undertale");
    chara.setAuthor    ("Toby Fox");
    chara.setPrice     (78);
    chara.setPages     (51);
    chara.setReadPages (12);*/

    cout << chara.getName()      << endl;
    cout << chara.getAuthor()    << endl;
    cout << chara.getPrice()     << endl;
    cout << chara.getPages()     << endl;
    cout << chara.getReadPages() << endl;

    chara.addReadPages (35);
    cout << chara.getReadPages() << endl;

    chara.addReadPages (35);
    cout << chara.getReadPages() << endl;

    return 0;
}
