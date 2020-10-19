
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
    Nodo(string filename) : name{filename} {
        carac = Vectorizar(filename, 128, 128);
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
public:
    Arista(Nodo* from, Nodo* to, int dist_type, double p = 0){
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
    

    Arista& operator =(Arista* other){
        this->value = other->value;
        return *this;
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
    void insert( Nodo* node ){
        nodos.push_back(node);
    }

    void createEdges(int dist_type){        
        map <Nodo*, bool> visited;
        for(int i=0; i <nodos.size() ; i++){
            for(int j=0; j < nodos.size(); j++){                
                auto newEdge = new Arista(nodos[i], nodos[j],dist_type);
                nodos[i]->push_edge(newEdge);
            }
            visited[nodos[i]] = true;
        }
    }
};

#endif
