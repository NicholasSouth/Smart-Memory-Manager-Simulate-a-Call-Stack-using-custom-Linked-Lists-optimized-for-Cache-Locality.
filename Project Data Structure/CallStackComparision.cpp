#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

//structure for a frame
struct stackFrame
{
    int address;//address of the frame to go back to
    int local[8];//to store local variables of the frame, expected max 8 variables/frame
//constructor to defaulty clear the frame
    stackFrame()
    {
        address = 0;
        for(int &counter : local)
            counter = 0;
    }
};
//using array for a call stack
class ArrayStack
{
    private:
        static const int CAPACITY = 10000000;
        stackFrame *data;
        int top;
    public:
    //constructor to clear the array before running
        ArrayStack()
        {
            data = new stackFrame[CAPACITY];
            top = 0;
        }
    //destructor to delete data afterward
        ~ArrayStack()
        {
            delete[] data;
        }
    //check if array is empty
        bool isEmpty() const
        {
            return top == 0;
        }
    //check if array is full to advoid overflow
        bool isFull() const
        {
            return top == CAPACITY;
        }
    //push function
        void push(const stackFrame& frame)
        {
        //stop appending when array is full
            if (isFull())
                return;
            data[top++] = frame;
        }
    //pop function       
        void pop()
        {
        //makes program quite early if array is empty
            if (isEmpty())
                return;
        //the actual pop function
            top--;
        }
    //peek function
        stackFrame *peek()
        {
            if (isEmpty())
                return nullptr;
            return &data[top - 1];
        }
};
//node structure for linked list, each node is a frame
struct Node
{
    stackFrame frame;
    Node *next;
//constructor to initialize the frame to the node
    Node(const stackFrame &curr)
    {
        frame = curr;
        next = nullptr;
    }
};
//using linked list for a call stack
class LinkedListStack
{
    private:
        Node *top;
    public:
    //constructor to defaultly clear the list before running
        LinkedListStack()
        {
            top = nullptr;
        }
    //detructor to defaultly clear the list after running
        ~LinkedListStack()
        {
            while (!isEmpty())
                pop();
        }
    //push function
        void push(const stackFrame &frame)
        {
            Node *temp = new Node(frame);
            temp->next = top;
            top = temp;
        }
    //check if list is empty
        bool isEmpty() const
        {
            return top == nullptr;
        }
    //pop function
        void pop()
        {
        //makes program quite early if list is empty
            if (isEmpty() )
                return;
        //the actual pop function logic
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    //peek function
        stackFrame* peek()
        {
            if (isEmpty())
                return nullptr;
            return &top->frame;
        }
};
//create more optimal node structure called block
struct Block
{
    stackFrame frames[32];//store stacked frame instead of local variables
    int top;
    Block *prev;       
//contructor to  initialize the frame to the node
    Block()
    {
        top = 0;
        prev = nullptr;
    }
};
//develope a smart stack
class SmartStack
{
    private:
        Block *front;
    public:
    //constructor to defaultly create a block
        SmartStack()
        {
            front = new Block();
        }
    //detructor to defaultly delete the list
        ~SmartStack()
        {
            while (front)
            {
                Block *temp = front;
                front = front->prev;
                delete temp;
            }
        }
    //push function
        void push(const stackFrame& frame)
        {
        //check if block is full to create new block
            if (front->top == 32)
            {
                Block *temp = new Block();
                temp->prev = front;
                front = temp;
            }
        //the actual append function code logic
            front->frames[front->top++] = frame;
        }
    //check if list is empty
        bool isEmpty() const
        {
            return front->top == 0 && front->prev == nullptr;
        }
    //pop function
        void pop()
        {
        //ends program early if block is empty
            if (isEmpty())
                return;
        //the actual pop function logic
            front->top--;
        // If block is empty, check for previous block and delete current block
            if (front->top == 0 && front->prev != nullptr)
            {
                Block *curr = front;
                front = front->prev;
                delete curr;
            }
        }
    //peek dunction
        stackFrame *peek()
        {
            if (isEmpty())
                return nullptr;
            return &front->frames[front->top - 1];
        }
};
//benchmarking
static const int N = 10'000'000;
//benchmark for array stack
void benchmarkArrayStack()
{
    ArrayStack stack;
    stackFrame frame;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        stack.push(frame);
    for (int i = 0; i < N; i++)
        stack.pop();
    auto end = high_resolution_clock::now();
    cout << "ArrayStack time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;
}
//benchmark for linked list stack
void benchmarkLinkedListStack()
{
    LinkedListStack stack;
    stackFrame frame;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        stack.push(frame);
    for (int i = 0; i < N; i++)
        stack.pop();
    auto end = high_resolution_clock::now();
    cout << "LinkedListStack time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;
}
//benchmark for smart stack
void benchmarkSmartStack()
{
    SmartStack stack;
    stackFrame frame;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        stack.push(frame);
    for (int i = 0; i < N; i++)
        stack.pop();
    auto end = high_resolution_clock::now();
    cout << "SmartStack time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;
}
int main()
{
    cout << "Stack Benchmark (10 million push/pop)\n\n";
    benchmarkArrayStack();
    benchmarkLinkedListStack();
    benchmarkSmartStack();
    return 0;
}