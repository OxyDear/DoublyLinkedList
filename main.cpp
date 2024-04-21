#include <iostream>

using namespace std;

struct Spisok {
    int inf;
    Spisok *left;
    Spisok *right;
};

// создание списка
void newSpisok (Spisok **spl, Spisok **spr) {
    *spl = new Spisok;
    *spr = new Spisok;

    (*spl)->left = NULL;
    (*spl)->right = *spr;

    (*spr)->left = *spl;
    (*spr)->right = NULL;
}

// добавить элемент после заданного
void addElementRight (Spisok *sp, int inf) { // sp - элемент после которого задаётся значение
    Spisok *spt = new Spisok;
    spt->inf = inf;
    spt->left = sp;
    spt->right = sp->right;
    sp->right = spt;
    spt->right->left = spt;
}

// добавить элемент перед заданным
void addElementLeft (Spisok *sp, int inf) { // sp - элемент перед которым задаётся значение
    Spisok *spt = new Spisok;
    spt->inf = inf;
    spt->left = sp->left;
    spt->right = sp;
    spt->left->right = spt;
    sp->left = spt;
}

// удаление заданного элемента
int deleteElement (Spisok *sp) {
    int inf = sp->inf;
    sp->left->right = sp->right;
    sp->right->left = sp->left;
    delete sp;
    return inf;
}

// удаление списка
void deleteSpisok (Spisok **spl, Spisok **spr) {
    Spisok *spt = (*spl)->right;

    while (spt != *spr) {
        cout << deleteElement(spt) << endl;
        spt = (*spl)->right;
    }

    delete *spl, *spl = NULL;
    delete *spr, *spr = NULL;
    return;
}

// разделить список на два по очередно
void divideSpisokIntoTwo (Spisok *spl, Spisok *spr,
                          Spisok **splLeft, Spisok **sprLeft,
                          Spisok **splRight, Spisok **sprRight) {

    newSpisok(splLeft, sprLeft);
    newSpisok(splRight, sprRight);

    Spisok *spt = spl->right;

    while (spt != spr) {
        addElementLeft(*sprLeft, deleteElement(spt));
        spt = spl->right;

        if (spt != spr) {
            addElementLeft(*sprRight, deleteElement(spt));
            spt = spl->right;
        }
    }

    delete spl;
    delete spr;
}

// удаляет отрицательные элементы из первого списка и переносит их во второй
void searchNegative (Spisok *spl, Spisok *spr, Spisok *sprRight) {
    Spisok* spt = spl->right;

    while (spt != spr) {
        if (spt->inf < 0) {
            Spisok* next = spt->right;
            addElementLeft(sprRight, deleteElement(spt));
            spt = next;
        } else {
            spt = spt->right;
        }
    }
}

Spisok *addochd(Spisok *sp, int inf) {
    Spisok *spt = new Spisok;
    spt->inf = inf;
}

// выводит список
void printSpisok (Spisok *spl) {

    cout.width(2);

    if (spl->right == NULL) {
        cout << endl;
        return;
    } else if (spl->left == NULL) {
        return printSpisok(spl->right);
    }

    cout << spl->inf << " ";
    return printSpisok(spl->right);
}

int main() {

    Spisok *spl = new Spisok, *spr = new Spisok;
    Spisok *splLeft = new Spisok, *sprLeft = new Spisok;
    Spisok *splRight = new Spisok, *sprRight = new Spisok;

    spl->inf = 1;
    spr->inf = 2;
    splLeft->inf = 3;
    sprLeft->inf = 4;
    splRight->inf = 5;
    sprRight->inf = 6;

    newSpisok(&spl, &spr);
    addElementLeft(spr, 1); // left
    addElementLeft(spr, -4); // right
    addElementLeft(spr, -6); // left
    addElementLeft(spr, 8); // right
    addElementLeft(spr, 0); // left
    addElementLeft(spr, -10); // right

    cout <<"\033[1;31m" << "all elements: ";
    printSpisok(spl);
    cout << "\033[1;37m";

    divideSpisokIntoTwo(spl, spr, &splLeft, &sprLeft, &splRight, &sprRight);

    cout << "\033[1;32m" << "all elements in first: ";
    printSpisok(splLeft);
    cout << "all elements in second: ";
    printSpisok(splRight);
    cout << "\033[1;37m";

    searchNegative(splLeft, sprLeft, sprRight);

    cout << "\033[1;33m" << "all elements after function in first: ";
    printSpisok(splLeft);
    cout << "all elements after function in second: ";
    printSpisok(splRight);
    cout << "\033[1;37m";
    deleteSpisok(&splLeft, &sprLeft);
    deleteSpisok(&splRight, &sprRight);

    return 0;
}
