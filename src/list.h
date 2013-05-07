#include <iostream>
using namespace std;

class list{
private:
        struct nodo{
                string valore;
                nodo *next;
        };

        typedef nodo *nodolista;
        nodolista lTesta;
public:
    list();
    ~list();
    void print();
};