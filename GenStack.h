#include<iostream>
using namespace std;

template <class T>
class GenStack
{
  public:
    GenStack();
    GenStack(int maxSize);
    ~GenStack();

    void push(T data);
    T& pop();
    T& peek();

    int getSize();
    int isEmpty();
    int isFull();

    int max;
    int top;
    int size;//use this too and increment and decrement throughout

    T *myArray;
};

template <class T>
GenStack<T>::GenStack()
{
  myArray = new T[10];
  max = 10;
  top = -1;
  cout<< "GenStack created"<<endl;
}

template <class T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize];
  max = maxSize;
  top = -1;
  cout<< "GenStack created"<<endl;
}

template <class T>
GenStack<T>::~GenStack()
{
  delete myArray;
  cout<< "GenStack deleted"<<endl;
}

template <class T>
void GenStack<T>::push(T data)
{

  if (!isFull())
  {
    myArray[++top] = data;
  }
}

template <class T>
T& GenStack<T>::pop()
{
  //make necessary checks, is empty??
  if (isEmpty())
  {
    throw range_error("Cannot pop empty stack");
  }
  else
  {
    return myArray[top--];
  }
  //might have to change the point of top for this too, oh maybe not with --
}


template <class T>
T& GenStack<T>::peek()
{
  if (isEmpty())
  {
    cout<<"Error, cannot peek"<<endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    return myArray[top];
  }
}

template <class T>
int GenStack<T>::isFull()
{
  return (top == max-1);
}

template <class T>
int GenStack<T>::isEmpty()
{
  return (top == -1);
}

template <class T>
int GenStack<T>::getSize()
{
  return (top+1);
}
