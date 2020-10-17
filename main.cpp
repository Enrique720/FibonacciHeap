#include <iostream>
#include "Fibonacci_heap.h"
using namespace std;

template <typename T>
void kruskal(FibonacciHeap<T> & A)
{
  
}




int main () {
  FibonacciHeap<int> myFH;
  myFH.ReadFromFile();
  myFH.ExtractMin();
  myFH.PrintHeap();
}