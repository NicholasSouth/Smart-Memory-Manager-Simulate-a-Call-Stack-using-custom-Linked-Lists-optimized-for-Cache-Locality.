struct Node
{
    stackFrame frame;
    Node *next;

    Node(const stackFrame &curr)
    {
        frame = curr;
        next = nullptr;
    }
};

class LinkedListStack
{
    private:
        Node *top;
    public:
        LinkedListStack()
        {
            top = nullptr;
        }
    
        ~LinkedListStack()
        {
            while (!isEmpty())
                pop();
        }
    
        void push(const stackFrame &frame)
        {
            Node *temp = new Node(frame);
            temp->next = top;
            top = temp;
        }
    
        bool isEmpty() const
        {
            return top == nullptr;
        }
    
        void pop()
        {
            if (isEmpty() )
                return;
        
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    
        stackFrame* peek()
        {
            if (isEmpty())
                return nullptr;
            return &top->frame;
        }
};
