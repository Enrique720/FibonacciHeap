
#ifndef ARISTA_H
#define ARISTA_H

#include <iostream>
#include <vector> 
#include <map> 
#include <math.h>
#include "Vectorizar.h"

template <class T>
class Nodo{
private: 
    std::string name;
    std::vector<T> carac;
    std::vector<Arista<T>*>aristas; 
public:
    Nodo(std::string filename) : name{filename} {
        carac = Vectorizar<float>(filename, 128, 128);
    }


    int get_sizevec(){
        return carac.size()
    }
    void push_edge(Edge<T>* edge){
        aristas.push_back(edge);
    }

};

template <class T>
class Arista{
private: 
    Nodo <T>*  nodes[2];
    T value;
public:
    Arista(Nodo <T> * from, Nodo <T> * to, T val){
        nodes[0] = from;
        nodes[1] = to; 
        value = val; 
    }
    Arista& operator =(Arista other){
        this->value = other->value;
        return *this;
    }
    bool operator <(T other){
        return this->value < other;
    } 
    
    bool operator >(T other){
        return this->value > other;
    } 

};
template <class T>
class Graph{
private:
    std::vector<Nodo<T>* > nodos; 

public:
    void insert( Nodo <T>* node ){
        nodos.push_back(node);
    }

    void createEdges(){
        float dist;
        std::map <Nodo<T>*, bool> visited;
        for(int i=0; i <nodos.size() ; i++){
            for(int j=0; j < nodos.size(); j++){
                dist=0;
                if(i == j || visited[nodos[j]]) continue;
                /* Distancia Euclideana */
                for(int k = 0; k < nodos[i].get_sizevec(); k++){
                    dist += pow(nodos[i].carac[k] -  nodos[j].carac[k], 2);
                }
                auto newEdge = new Arista(nodos[i], nodos[j], sqrt(dist));
                nodos[i].push_edge(newEdge);
            }
            visited[nodos[i]] = true;
        }
    }
};

#endif
