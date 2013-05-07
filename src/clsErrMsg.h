/*Header file Error message classe clsErrMsg*/

class clsErrMsg{
        private:
            int errNumber;
            void printErrMsg(int err);
        public:
            clsErrMsg(int err);
            ~clsErrMsg();
};
