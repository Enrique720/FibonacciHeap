
#ifndef ARISTA_H
#define ARISTA_H

#include <iostream>
#include <vector> 
#include <map>
#include <unordered_map>
#include <math.h>
#include "Vectorizar.h"

using namespace std;
class Arista; 
class Graph; 



class Nodo{
private: 

    string name;
    int vz_num;
    vector <double> carac;
    vector<Arista*> aristas; 
    friend class Arista;
    friend class Graph;

public:
    vector<Arista*> get_aristas(){
        return aristas;
    }
    Nodo(string filename) : name{filename}, vz_num{0}{
        carac = Vectorizar(filename, 128, 128);
    }   

    string get_name(){
        return name;
    }

    int get_sizevec(){
        return carac.size();
    }
    void push_edge(Arista* edge){
        aristas.push_back(edge);
    }

};

class Arista{
private: 
    Nodo*  nodes[2];  
    double value;   
    friend class Graph;   
public:
    double get_value(){
        return value;
    }

    Arista(Nodo* from, Nodo* to, int dist_type, double p = 3){
        nodes[0] = from;
        nodes[1] = to;
        switch (dist_type) {
            case 0:
            value = euclidean(from, to);
            break;
            case 1:
            value = manhattan(from, to);
            break;
            case 2:
            value = minkowski(from, to, p);
            break;
        }
    }
    
    Nodo * getFrom(){
        return nodes[0];
    }

    Nodo * getTo(){
        return nodes[1];
    }

    double manhattan(Nodo* from, Nodo* to) {
        double distance = 0;
        for(int k = 0; k < from->get_sizevec(); k++){
            distance += abs(from->carac[k] -  to->carac[k]);
        }
        return distance;
    }

    double euclidean(Nodo* from, Nodo* to) {
        double distance = 0;
        
        for(int k = 0; k < from->get_sizevec(); k++){
            distance += pow(from->carac[k] -  to->carac[k], 2);
        }
    
        return sqrt(distance);
    }

    double minkowski(Nodo* from, Nodo* to, double p) {
        double distance = 0;
        
        for(int k = 0; k < from->get_sizevec(); k++){
            distance += abs(pow(from->carac[k] -  to->carac[k], p));
        }
    
        return pow(distance, 1/p);
    }
  
    bool operator <(double other){
        return this->value < other;
    } 
    
    bool operator >(double other){
        return this->value > other;
    } 

};

class Graph{
private:
    vector<Nodo*> nodos; 

public:
    void insert( string filename ){
        Nodo* newNode = new Nodo(filename);
        nodos.push_back(newNode);
    }
    
    vector<Nodo*> getNodos() {
        return nodos;
    }

    void createEdges(int dist_type){        
        map <Nodo*, bool> visited;
        for(size_t i=0; i <nodos.size() ; i++){
            for(size_t j=0; j < nodos.size(); j++){    
                if(i == j || visited[nodos[j]]) continue;            
                auto newEdge = new Arista(nodos[i], nodos[j],dist_type);
                nodos[i]->push_edge(newEdge);
            }
            visited[nodos[i]] = true;
        }
    }

    void show() {
        for(auto it:this->nodos){
            cout << "Nodo: " << it->name << " \n Edges: \n" ;
             for(auto it2:it->aristas){
                 cout << it2->value << " " << it2->getTo()->get_name() <<endl; 
             }
             cout << endl;
        }
    }

    void PrintGraph(vector<Arista*> aristas){
        cont = 0; 
        int subgraphs = 0;
        map<Nodo*,string> id;
        cout <<  "Graph \"\"" << endl;
        
        cout << "{\n label= \" Graph \" " << endl;
        cout << " layout=neato \n size=\"10\" \n page=\"8.5,11\" \n center=\"\" \n ";
        cout << "subgraph BN" << subgraphs << " \n{ \n";
        cout << "label= " << "subgraph" << subgraphs << endl;
            
        for(auto it:nodos){
            it->vz_num = cont;
            cout << "n" << it->vz_num << " ;\n";
            cout << "n" << it->vz_num << " [image=\"" << it->name  <<  "\" , label=\"\"];" << endl;
            // imgnode[image="apple-touch-icon.png", label=""];
            id[it] = "n" + to_string(it->vz_num);
            cont++;
        }
        for(auto it:aristas){
            cout << id[it->getFrom()] << " -- " << id[it->getTo()] <<" [label = \""<<it->get_value() <<"\"]" <<";" << endl;
        }

        cout << "} \n";
        subgraphs++;
    
        cout << "}\n";
    }

    int size(){
        return this->nodos.size();
    }

    void setEdges(vector <Arista*> aristas){
        for(auto it:nodos){
            it->aristas.clear();
        }
        for(auto it:aristas){
            it->getFrom()->aristas.push_back(it);
        }
    }
};

class DisjointSet { 
   unordered_map <Nodo*, Nodo*> parent;
   public:
   void makeSet(vector<Nodo*> wholeset){
      for (auto i : wholeset) 
        parent[i] = i;
   }
   Nodo* Find(Nodo* l) { 
      if (parent[l] == l) 
         return l;
      return Find(parent[l]); 
   }
   void Union(Nodo* m, Nodo* n){ 
      auto x = Find(m);
      auto y = Find(n);
      parent[x] = y;
   }
};


#endif
