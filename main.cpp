#include <iostream>
#include "src/Fibonacci_heap.h"
#include "src/Arista.h"
using namespace std;

template <typename T>
void kruskal(FibonacciHeap<T,>& FB, Graph& graph)
{
  
}

template <typename T>
void insertEdges(FibonacciHeap<T> & FB, Graph & graph){
  for(auto it:graph.nodos){
    for(auto it2: it->aristas){
      auto newNodeB = new NodoB(it2);
      FB.insert(newNodeB);
    }
  }
}

void prueba(){
  Graph grafo;
  auto nodo1 = new Nodo("faces/faces94/malestaff/obeidn/obeidn.12.jpg");
}


int main () {
  FibonacciHeap<int> myFH;
  myFH.ReadFromFile();
  myFH.ExtractMin();
  myFH.PrintHeap();
}