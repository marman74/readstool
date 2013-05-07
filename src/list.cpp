#include <iostream>
#include "list.h"
using namespace std;

list::list(){
        lTesta=new nodo;
        lTesta->valore="Salute!";
        lTesta->next=NULL;
    }
    
list::~list(){
        delete lTesta;
    }
    
void list::print(){
        cout<<lTesta->valore<<endl;
    }