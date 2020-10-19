#include <iostream>
#include "src/Fibonacci_heap.h"
#include "src/Arista.h"
using namespace std;

template <typename T>
void kruskal(FibonacciHeap<T>& FB, Graph& graph)
{
  //map <Arista*, bool> visited;
}

template <typename T>
void insertEdges(FibonacciHeap<T> & FB, Graph & graph){
  for(auto it:graph.nodos){
    for(auto it2: it->aristas){
      auto newNodeB = new NodoB<Arista*>(it2);
      FB.insert(newNodeB);
    }
  }
}

void prueba(){
  Graph grafo;
  auto nodo1 = new Nodo("faces/faces94/malestaff/obeidn/obeidn.12.jpg");
  auto nodo2 = new Nodo("faces/faces94/malestaff/obeidn/obeidn.8.jpg");
  auto nodo3 = new Nodo("faces/faces94/malestaff/obeidn/obeidn.15.jpg");
  grafo.insert(nodo1);
  grafo.insert(nodo2);
  grafo.insert(nodo3);
  grafo.createEdges(0);
  grafo.show();
}


int main (){
  prueba();
}