#include <iostream>
#include "src/Fibonacci_heap.h"
#include "src/Arista.h"
#include <unordered_map>
using namespace std;

template <typename T>
vector<Arista*> kruskal(FibonacciHeap<T>& FB, Graph& graph)
{  
  DisjointSet disset;
  disset.makeSet(graph.getNodos());  
  int nodos = graph.size()-1;
  vector <Arista *> aristas;
  int cont = 0;
  int n = FB.size();
  while(nodos){
    auto min = FB.Get_Min();
    FB.ExtractMin();
    auto dsTo = disset.Find(min->getTo());
    auto dsFrom = disset.Find(min->getFrom());
    if(dsTo == dsFrom){
      continue;
    }
    else{
      cont++;
      aristas.push_back(min);
      nodos--;
      disset.Union(dsTo,dsFrom);
    }    
  } 
  graph.setEdges(aristas);
  return aristas;
}

template <typename T>
void insertEdges(FibonacciHeap<T> & FB, Graph & graph){
  for(auto it:graph.getNodos()){
    for(auto it2: it->get_aristas()){
      auto newNodeB = new NodoB<Arista*>(it2);
      FB.Insert(newNodeB);
    }
  }
}

void prueba(string data_path, int dist_type){

  
  Graph myGraph;
  FibonacciHeap<Arista*> myFH;

  fstream file (data_path, ios::in);
  string element;
  while (file >> element)
    myGraph.insert(element);


  file.close();

  myGraph.createEdges(dist_type);

  insertEdges(myFH, myGraph);
  auto vec = kruskal(myFH, myGraph);

  int k = 0; 
  for(int i = 0; i < k ; i++){
    vec.pop_back();
  }

  myGraph.PrintGraph(vec);
}

int main (){
  prueba("db.txt", 0);
}