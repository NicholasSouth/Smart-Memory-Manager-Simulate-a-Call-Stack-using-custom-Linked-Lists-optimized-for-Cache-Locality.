#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

//Frame strcut
struct stackFrame{
    int add; //address of the frame to go back to
    int local[8]; //to store local variables of the frame, expected max 8 variables/frame

//constructor to defaulty clear the frame
    stackFrame(){
        add = 0;
        for(int &counter : local){
            counter = 0;
        }
    }
};

//using array for a call stack
class ArrayStack{
    private:
        static const int CAP = 10000000; //capacity 
        stackFrame *data;
        int top;
    public:
    //constructor to clear the array before running
        ArrayStack(){
            data = new stackFrame[CAP];
            top = 0;
        }
    //destructor to delete data afterward
        ~ArrayStack(){
            delete[] data;
        }
    //check if array is empty
        bool isEmpty() const{
            return top == 0;
        }
    //check if array is full to advoid overflow
        bool isFull() const{
            return top == CAP;
        }
    //push function
        void push(const stackFrame& frame){
        //stop appending when array is full
            if (isFull()){
                return;
            }
            data[top++] = frame;
        }
    //pop function       
        void pop(){
        //makes program quite early if array is empty
            if (isEmpty()){
                return;
            }
        //the actual pop function
            top--;
        }
    //peek function
        stackFrame *peek(){
            if (isEmpty()){
                return nullptr;
            }
            return &data[top - 1];
        }
};

int main(){}