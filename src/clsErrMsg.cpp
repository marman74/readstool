/*Error message classes*/

#include <iostream>
#include "clsErrMsg.h"

using namespace std;

clsErrMsg::clsErrMsg(int err){
    errNumber=err;
    clsErrMsg::printErrMsg(errNumber);
};

clsErrMsg::~clsErrMsg(){
    //cout<<"Obj clsErrMsg Destroyed"<<endl;
};

void clsErrMsg::printErrMsg(int err){
    if(err==1){
        cout<<"Invalid arguments"<<endl;
        cout<<"readsqc <file_name> <cutoff>"<<endl;
    }
    if(err==2) cout<<"File not found"<<endl;
    if(err==3) cout<<"Invalid input string";
}