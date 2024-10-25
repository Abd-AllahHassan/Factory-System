#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

// Interface
template <typename T>
class List
{
protected:
    int size;

public:
    List() : size(0) {}

    friend class SmartManufacturing;

    virtual size_t getSize() const
    {
        return size;
    }

    virtual bool isEmpty() const
    {
        return size == 0;
    }

    virtual void clear() {}
    virtual void display() const {}
    virtual T& operator[](int index) {}
    virtual size_t indexOf(const T& item) const {}
    virtual void push(const T& value) {}
    virtual void enqueue(const T& value) {}
    virtual void pop() {}
    virtual void dequeue() {}
    virtual T& topElement() {}

};

template <typename T>
class Stack
{
private:
    T* array;
    int capacity;
    int top;
    int size;

public:

    Stack() : capacity(2), top(-1), size(0)
    {
        array = new T[capacity];
    }

    ~Stack()
    {
        delete[] array;
    }

    void push(T value)
    {
        if (size == capacity)
        {
            resize();
        }

        array[++top] = value;
        size++;
    }

    void pop()
    {
        if (isEmpty())
        {
            std::cerr << "Error: Stack is empty. Cannot pop.\n";
            return;
        }

        if (size * 3 < capacity)
        {
            resize();
        }

        top--;
        size--;
    }

    T& topElement() const
    {
        if (isEmpty())
        {
            std::cerr << "Error: Stack is empty. No top element.\n";
            static T kh;
            return kh;
        }

        return array[top];
    }

    void resize()
    {
        size_t new_capacity = std::max(2 * (int)size, 2);
        T* brr = new T[new_capacity];
        for (int i = 0; i < size; i++)
            brr[i] = array[i];
        delete[] array;
        array = brr;
        capacity = new_capacity;
    }

   void display() const {
        if (top == -1) {
            cerr << "The stack is empty!" << endl;
            return;
        }

        for (int i = top; i >= 0; --i) {
                cout<<"any thing stack";
            cout << array[i].stepName << ": " << array[i].stepNum << " ";
        }
        cout << endl;
    }

    T& getIndex(const int& j)
    {
        if(j > size || j < 0)
        {
            cerr << "Invalid Index!" << endl;
        }

        return array[j];
    }

    int getTop() const
    {
        return top;
    }

    bool isEmpty() const
    {
        return top == -1;
    }

};

struct Step
{
    string stepName;
    int stepNum;

    Step(): stepName("Unknown"), stepNum(0) {}

    void set(const int& number)
    {
        stepNum = number;
        cout << "Enter Operation Name: ";
        getline(cin >> ws, stepName);

    }

    void print()
    {
        cout << "Operation -> " << stepName << " Number -> " << stepNum << endl;
    }
};

template <typename T>
class Queue
{
private:
    T* array;
    int front;
    int rear;
    int size;

public:

    friend class SmartManufacturing;

    Queue() : front(-1), rear(-1), size(0)
    {
        array = new T[4];
    }

    void enqueue(const T& value)
    {

        if (size == 4)
        {
            throw out_of_range("Queue out of limit");
        }

        if (front == -1)
        {
            front = rear = 0;
        }

        else
        {
            rear = (rear + 1) % 4;
        }

        array[rear] = value;
        size++;
    }

    void dequeue()
    {
        if (front == -1 && rear == -1)
        {
            std::cerr << "Error: Queue is empty. Cannot dequeue.\n";
            return;
        }

        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % 4;
        }

        size--;
    }

    T& topElement() const
    {
        if (front == -1 && rear == -1)
        {
            throw std::out_of_range("Error: Queue is empty. No front element.\n");
        }

        return array[front];
    }

    int getFront()
    {
        return front;
    }

    T& firstElement()
    {
        return array[front];
    }

    T& operator[](size_t index)
    {
        if (index >= List<T>::size)
        {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    Stack<Step>& operator[](int index)
    {
        if (index >= List<Stack<Step>>::size)
        {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

     void display() const {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        int current = front;
        while (current != rear) {
                cout<<"queue display";
            array[current].display(); // Assuming Stack has a display method
            current = (current + 1) % 4;
        }
        array[current].display(); // Display the last element
        cout << endl;
    }
    T& traversing()
    {
        if (front == -1)
        {
            std::cout << "Queue is empty." << std::endl;
        }
        else
        {
            for (int i = front; i != rear; i = (i + 1) % 4)
            {
                return array[i];
            }
        }
    }

    int getRear() const
    {
        return rear;
    }

    bool isEmpty() const
    {
        return rear == -1 && front == -1;
    }

    int getSize() const
    {
        return size;
    }
};


template <typename T>
struct Node
{
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList
{
protected:
    Node<T>* head;
    int size;

public:

    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    void push(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (head ==  nullptr)
        {
            head = newNode;
            size++;
            return;
        }

        Node<T>* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
        size++;
    }

     void display() const {
        Node<T>* current = head;
        while (current) {
                cout<<"linkedlist display";
            current->data.display(); // Assuming Queue has a display method
            current = current->next;
        }
        cout << endl;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T& topElement()
    {
        if (head == nullptr)
        {
            throw std::out_of_range("List is empty");
        }

        Node<T>* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        return current -> data;
    }


    void pop()
    {
        if (head == nullptr)
        {
            return;
        }

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            size--;
            return;
        }

        Node<T>* current = head;
        while (current->next->next != nullptr)
        {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
        size--;
    }

    bool isEmpty() const
    {
        return size == 0;
    }
};


class SmartManufacturing
{
private:
    LinkedList<Queue<Stack<Step>>> data;

public:

    void addProduct()
    {
         Stack<Step> newStack;
            int stepCount;

            cout << "How Many Manufacturing Steps For This Product: \n";
            cin >> stepCount;

            for(int i = 0; i < stepCount; i++)
            {
                Step newStep;
                cout<<"Enter name :";
                cin>>newStep.stepName;
                newStack.push(newStep);
            }
        if (data.isEmpty() || data.topElement().getSize() == 4)
        {
            Queue<Stack<Step>> newQueue;
            newQueue.enqueue(newStack);
            data.push(newQueue);
        }
        else
        {
           data.topElement().enqueue(newStack);
        }
    }

    void displayAllSteps()
    {
        cout << "Displaying Manufacturing List ..." << endl;
        data.display();
    }

};

int main()
{
    SmartManufacturing smartfactory;

    char ch;
    do
    {
        system("cls");
        system("color 0A");

        cout << "\t\t\t------------------------------------"<<endl;
        cout << "\t\t\t|--    SMART FACTORY SYSTEM    ----|"<<endl;
        cout << "\t\t\t------------------------------------"<<endl;
        cout << "\t\t\t[1] Add A Product"<<endl;
        cout << "\t\t\t[2] Display Product Sequence"<<endl;
        cout << "\t\t\t[3] Process A Product"<<endl;
        cout << "\t\t\t[0] Exit"<<endl;
        cout << "Enter Your Choice: ";
        cin >> ch;

        switch(ch)
        {
        case '1':
        {

            smartfactory.addProduct();
            break;

        }

        case '2':
            smartfactory.displayAllSteps();
            break;

        case '3':

            break;

        case '0':
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            sleep(3);
        }
    }
    while(ch != '0');

    cout << "\t\t\t\tTHANK YOU!\n";
    return 0;
}
