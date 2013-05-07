/*Test program*/
#include <iostream>
#include <cstdlib>
#include "clsReadsQC.h"
#include "clsErrMsg.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc>=2){
        int cco;
        if(argv[2]) cco=atoi(argv[2]);
        else cco=0;
        clsReadsQC rQC(argv[1], cco);
        //rQC.printFields();
        return(0);
    }
    else{
        clsErrMsg error(1);
    }
    return(0);
}
