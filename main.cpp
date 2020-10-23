#include <iostream>
#include "src/Fibonacci_heap.h"
#include "src/Arista.h"
using namespace std;

template <typename T>
vector<Arista*> kruskal(FibonacciHeap<T>& FB, Graph& graph)
{
  map <Nodo*, bool> visited;
  //cout << "Graph.size(): " << graph.size() << endl;
  //cout << "FB.size(): " << FB.m_size << endl;

  int nodos = graph.size()-1;
  vector <Arista *> aristas;
  while(nodos){
    auto min = FB.Get_Min();
    FB.ExtractMin();
    
    if(visited[min->getTo()] && visited[min->getFrom()]){
      continue;
    }
    else{
      aristas.push_back(min);
      nodos--;
      visited[min->getTo()] = true;
      visited[min->getFrom()] = true;
    }
  } 
  /*cout << "Aristas Kruskal: " << endl;
  for(auto it:aristas){
    cout << it->get_value() << " ";
  }
  cout << endl;*/
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
  //myGraph.show();
  insertEdges(myFH, myGraph);
  auto vec = kruskal(myFH, myGraph);
  //cout << "------------------------" << endl;
  //cout << "------------------------" << endl;
  //cout << "------------------------" << endl;
  //myGraph.show();
  //myGraph.PrintGraph(vec);
}

int main (){
  prueba("db.txt", 0);
}