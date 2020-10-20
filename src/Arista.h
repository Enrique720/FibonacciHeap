
#ifndef ARISTA_H
#define ARISTA_H

#include <iostream>
#include <vector> 
#include <map>
#include <math.h>
#include "Vectorizar.h"

using namespace std;
class Arista; 
class Graph; 



class Nodo{
private: 
    string name;
    vector <double> carac;
    vector<Arista*> aristas; 
    friend class Arista;
    friend class Graph;

public:
    vector<Arista*> get_aristas(){
        return aristas;
    }
    Nodo(string filename) : name{filename} {
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

    Arista(Nodo* from, Nodo* to, int dist_type, double p = 1){
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
    
    Arista(double val){        
        nodes[0] = nullptr;
        nodes[1] = nullptr;
        value = val;
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
            distance += pow(from->carac[k] -  to->carac[k], p);
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
        for(int i=0; i <nodos.size() ; i++){
            for(int j=0; j < nodos.size(); j++){    
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
    int size(){
        return this->nodos.size();
    }
};

#endif
