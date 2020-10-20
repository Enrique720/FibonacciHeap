
#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H
#define MAX_DOUBLE 99999999
#include <string>
#include "NodoB.h"
#include "Arista.h"
#include <math.h>
#include <algorithm>
#include <fstream>
using namespace std;


template<class T>
class FibonacciHeap
{
public:

  FibonacciHeap (): m_size(0) {};
  
//  virtual ~FibonacciHeap ();

  
  void Insert (NodoB<T> * key)
  {
      if (m_heap.empty()) {
        m_heap.push_back(key);
        minElem = m_heap.begin();
      } else {

        m_heap.insert(minElem, key);
        if(key->m_key < min){
          min = key->m_key; 
          minElem--;
        }
      }
   
    this->m_size++;
  }
  
  T Get_Min ()
  {
    return (*minElem)->m_key;
  }

  void ExtractMin ()
  {
    for(auto it:(*minElem)->m_Hijos){
      it->m_pPadre = nullptr;
      m_heap.push_back(it);
    }

    m_heap.remove(*minElem);
    delete *minElem;
    Compactar();
    min = new Arista((double) MAX_DOUBLE);
    for(auto it = m_heap.begin(); it != m_heap.end() ;it++){
      if( (*it)->m_key < min){
        this->minElem = it;
        min = (*minElem)->m_key;
      }
    }

  }

  void PrintHeap(){
    cont = 0; 
    int subgraphs = 0;
    cout <<  "graph \"\"" << endl;
    cout << "{\n label= \" Fibonacci heap \" " << endl;
    for(auto it:m_heap){
      cout << "subgraph BN" << subgraphs << " \n{ \n";
      cout << "label= " << "subgraph" << subgraphs << endl;
      it->showParent();
      cout << "} \n";
      subgraphs++;
      cont++;
    }

    cout << "}\n";
  }
 
  NodoB<T> * find(T key){
    for(auto it:m_heap){
      auto temp = it->find(key);
      if(temp)
        return temp;
    }
    return nullptr;
  }
  
  void Decrease (NodoB<T> * pNodo, T Value)
  {
    pNodo->m_key = Value;
    auto temp = pNodo;
    while(temp->m_pPadre && temp->m_pPadre->m_key > Value){
      swap(temp->m_pPadre->m_key, temp->key);
      temp = temp->m_pPadre;
    }      
    if(Value < min){
      min = Value;
      for(auto it:m_heap){
        if(it->m_key == min){
          minElem = it;
          break;
        }
      } 
    }
  }
  
  void Decrease_key(T original_value, T new_value){
    auto node = find(original_value);
    Decrease(node,new_value);
  }

  NodoB<T> * Unir (NodoB<T> * p1, NodoB<T> * p2)
  {
    if(p1->m_key > p2->m_key){
      p1->m_pPadre = p2;
      p2->m_Hijos.push_front(p1);
      p2->m_Grado++;
      return p2;
    }
    else{
      p2->m_pPadre = p1;
      p1->m_Hijos.push_front(p2);
      p1->m_Grado++;
      return p1;
    }

  }

  
  void Compactar ()
  {   
    vector<NodoB<T>*> tempVec(log2(m_size)+1 ,nullptr);
    for(auto it = m_heap.begin(); it != m_heap.end(); it++){ 
       int grado = (*it)->m_Grado;
        if(!tempVec[grado])
          tempVec[grado] = (*it);
        else{
          auto newNode = Unir(*it,tempVec[grado]);
          tempVec[grado] = nullptr;
          this->m_heap.push_back(newNode);     
        }
    }
    this->m_heap.clear();
    for(auto it:tempVec){
      if((it)){
        this->m_heap.push_back(it);
      }
    }
  }

  void ReadFromFile() {
    string filename;
    cin >> filename;
    fstream f(filename, ios::in);
    T element;
    while (f >> element){
      auto newNodo  = new NodoB<T>(element);
      Insert(newNodo);
    }
    f.close();
  }
  
  int m_size;
  list<NodoB<T> *> m_heap;
  typename list<NodoB<T> *>::iterator minElem = m_heap.end();

  T min = new Arista((double) MAX_DOUBLE);
};

#endif 
