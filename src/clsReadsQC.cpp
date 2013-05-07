#include <iostream>
#include <fstream>
#include <string>
#include "clsReadsQC.h"
#include "clsErrMsg.h"

using namespace std;

int clsReadsQC::outFile(int norm){
    //if norm is set to 1  normalized counts will be written in the out files
    int bufSize;
    ofstream outFile;
    string outFileName(fileName);
    string outFileExt (".out");
    outFileName+=outFileExt;
    const char* outFName=outFileName.c_str();
    outFile.open(outFName);
    if (outFile){
        outFile<<"miR";
        outFile<<"\t";
        outFile<<"Counts";
        if (norm==1){
                outFile<<"\t";
                outFile<<"Normalized";}
        outFile<<"\n";
        for(lP=lHead; lP!=NULL; lP=lP->next){
            outFile<<lP->key;
            outFile<<"\t";
            outFile<<lP->count;
            if (norm==1){
                outFile<<"\t";
                outFile<<lP->nCount;}
            outFile<<"\n";
        }
        outFile.close();
    }
    return(0);
}

int clsReadsQC::normalization(){
    float norm=readsCount/1.0e+6;
    //cout<<"norm: "<<norm;
    if (lHead!=NULL){
        for(lP=lHead; lP!=NULL; lP=lP->next) {
                lP->nCount=(float)lP->count/norm;
        }
    return(0);
    }
}

int clsReadsQC::applyCutOff(int cOff){
    int cco=cOff;
    if (cco!=0){
        //cout<<cco<<endl;
        if (lHead!=NULL){
            linknode lPrev=lHead;
                for(lP=lHead; lP!=NULL; lP=lP->next) {
                        if (lP->count<cco){
                            if (lP==lHead) lHead=lP->next;
                            else if(lP->next==NULL) lPrev->next=NULL;
                            else {
                                lPrev->next=lP->next;
                                //linknode del=lP;                         
                                delete lP;
                            }
                        }
                        else lPrev=lP;
                }
        }
    return(0);
    }
}

int clsReadsQC::readLine(){
	//This method reads  a line and put it in a mamory block pointed by
	//class variable currentRead. It also set the value of the global variable readQScore by calling the method
	//meanQualityScore
	//Exit status 0 ok, exit status 1 if file not found.
        //reading buffer
        string buffer;
        getline(readsFile, buffer);//reads first line of the file
        if (buffer.size()>2){
		currentRead=buffer.c_str();//class variable currentRead set to pointer to string conatining read line
                if(checkIfHeader()==0){//check if the line is an header line
                        if(getFields()==0) {
                                //printFields();//print read fields
				readQScore=22;//meanQualityScore(readFields[_SCORE]);//set readQScore
                                //updateList(readFields[_RNAME]);//update key table counts
				}
				//else return(3);
			}
                return (0);
        }
        else return (1);
}

int clsReadsQC::openStream(){
    //this method open a file stream and set the global variable readsFile if exit code=0. Exit code = 1 if file not found
	readsFile.open(fileName);
    if(!readsFile){
            clsErrMsg error(2);
			return(1);//exit code 1 from method readLine if file not found
    }
    else return(0);
}

int clsReadsQC::checkIfHeader(){
    //check if the current line is an header line. Exit code = 1 if true, exit code=0 if no headr line
    const char* _CURRENT="@";
    if(currentRead[0]==*_CURRENT) return(1);//if the first char of the line is @ the line would be an header line exit code=1
    else return(0);//if not header line exit code=0
};

int clsReadsQC::getFields(){
    
    //extract substrings from currentReads and set class variable readFields which point to an array of character array (c-string)
    //global variable fieldNUmbers setted to the number of field of the current read
    int p, prev, i, j, count;//iterators and counters
    p=0;//current position
    prev=0;//previous position
    count=1;//subbstring counter
    //string scanning to detrmine the numeber of substrings
    for(p; currentRead[p]!='\0'; p++) {
        if (currentRead[p]=='\t') count++;
    }
	fieldNumbers=count;
	if (count>1) {
    	readFields=new char* [count];//dinamyc allocation of a char buffer
		count=0;
		for(p=0;currentRead[p]!='\0'; p++){//scanning of the sunbstrings
			if (currentRead[p]=='\t') {
				int dim=p-prev+1;
				readFields[count]=new char [dim];//allocation of a char buf for the substring
				for(i=prev, j=0; i<p; i++, j++){//copy of the substring in the char buf
					readFields[count][j]=currentRead[i];
				}
			readFields[count][dim]='\0';//add string terminator
			//iterators update
			prev=p+1;
			count++;
			}
		}
		int dim=p-prev+1;//copy of the last substring
		readFields[count]=new char [dim];
		for(i=prev, j=0; i<p; i++, j++){
			readFields[count][j]=currentRead[i];
		}
		readFields[count][dim]='\0';//string terminator
		return(0);
	}
	else return(3);
	}

int clsReadsQC::meanQualityScore(char* rQF){
    //calculate qualityt score and set the global variable readQScore
    int size;
    int totalScore=0;
    int meanScore=0;
    string strQF(rQF);
    size=strQF.length();
    for(int i=0; i<size;i++){
        int score=((int)strQF[i])-33;
        totalScore+=score;
        //cout<<strQF[i]<<" :"<<score<<endl;
    }
    meanScore=totalScore/size;
    //cout<<"Mean Q Score: "<<meanScore<<endl;
	//readQScore=meanScore;
    return(meanScore);
}

int clsReadsQC::updateList(char* rName){
    int chkd=0;
    if (lHead!=NULL){
        lP=lHead;
        linknode lPos=lHead;
        while ((lPos!=NULL) && (chkd!=1)) {
                if (lPos->key==rName) {
                        chkd=1;
                        lPos->count++;
                }
                lP=lPos;
                lPos=lPos->next;
        }
        if (chkd!=1){
            linknode t=new node;
            t->key=rName;
            t->count=1;
            t->nCount=0.0;
            t->next=NULL;
            lP->next=t;
        }
    }
    else {
        lHead=new node;
        lHead->key=rName;
        lHead->count=1;
        lHead->nCount=0.0;
        lHead->next=NULL;
    }
    return(1);
}

void clsReadsQC::printCurrentRead(){
    //print current read, global variable currentRead
    if(currentRead!=NULL) cout<<currentRead<<endl;
    else cout<<"No current read available"<<endl;
}

void clsReadsQC::printFields(){
    //print each field of the current read
    //for(int i=0; i<fieldNumbers; i++) cout<<&readFields[i]<<endl;
    for(int i=0; i<fieldNumbers; i++) cout<<readFields[i]<<endl;
}

int clsReadsQC::startComputation(){
		//control the flux of the program
                const char* _NOTALIGNED="*";
		int ret=openStream();//open file stream
		if(ret==0){
			while(readsFile.good()){//while not EOF
                                if(readLine()==0) {//read current line
                                        if (readQScore>20) {//score threshold
                                                //cout<<"QScore :"<<readQScore<<endl;//print QScore
                                                if(readFields[_RNAME][0]!=*_NOTALIGNED) updateList(readFields[_RNAME]);
                                                readsCount++;
                                                }
                                        }              
				}
		readsFile.close();//if no errors
                int cco_flag=applyCutOff(countCutOff);
                int norm_flag=normalization();
                //for(lP=lHead; lP!=NULL; lP=lP->next) cout<<lP->key<<" "<<lP->count<<endl;
                outFile(0);
		}
		return(0);
}

clsReadsQC::clsReadsQC(char* fn, int cco){
    //class constructor
    //class variable initialization
        int ret;
        countCutOff=cco;
        fileName=fn;
        currentRead=NULL;
        readFields=NULL;
     	readQScore=0;
        readsCount=0;
        fieldNumbers=0;
        lHead=NULL;
        lP=NULL;
        ret=startComputation();//start computation
}

clsReadsQC::~clsReadsQC(){
    //if(lHead) for (lP=lHead; lP!=NULL; lP=lP->next){
    //    delete lP;
        //cout<<"DELETED"<<endl;
    //};
    //delete readFields;
    //cout<<"Obj clsReadsQC Destroyed"<<endl;
}
