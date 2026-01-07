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