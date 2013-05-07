/*Header file clsReadsQC*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class clsReadsQC{

        private:
                static const int _MAXBUF=256;//reading buffer size;
                static const int _SCORE=10;//number of field containing read score string
                static const int _RNAME=2;//number of field containing read name
                
                const char* currentRead;//memory location storing the current read
                char* fileName;//file open
                char** readFields;//Bidimensional matrix in which read fields are stored
                int fieldNumbers;//number of field in a read
		int readQScore;//quality score of a read
                int readsCount;//reads counter
                int countCutOff;//reads count cut off;
		ifstream readsFile;//file pointer to reads file
                
                struct node {   
                        string key;//key string
                        int count;//reads count
                        float nCount;//normalized count
                        node *next;//pointer to next node
                };
                
                typedef node *linknode;//type pointer to node
                
                linknode lHead;//list head pointer
                linknode lP;//list pointer 
                
                int normalization();//Nomralization of reads counts as counts per million of reads
                int applyCutOff(int cOff);//Reads counts threshold
                
                int outFile(int norm);//write out reads cont file
		int startComputation();//manage the computation
		int readLine();//Read a line from the file
		int checkIfHeader();//Check if the line is an header line
		int getFields();//gtet fields from read and put in readFields structure
		int meanQualityScore(char* readsQField);//calculate the mean qualityt score of a read
		int openStream();//open file stream
                int updateList(char* readsName);//update key table list;
                
        public:
                void printCurrentRead();//print current read
                void printFields();//print each field of the read
                clsReadsQC(char* fn, int cco);//class constructor fn=filename 
                ~clsReadsQC();//class destructor
};
