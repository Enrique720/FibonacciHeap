
#ifndef NODOB_H
#define NODOB_H

#include <string>
#include <vector>
#include <list>
using namespace std;


 int cont;

template<class T>
class NodoB
{
public:

 
  NodoB (T m_key): m_Grado(0), m_key(m_key) , m_pPadre(nullptr) {};


  void show(){
   // cout << "key: " <<m_key << endl;
    cout << "n" << this->m_pPadre->vz_num << " -- " << "n" << this->vz_num  << " ;" << endl;
    cout << "n" << this->vz_num << " [label=\"" << this->m_key << "\"] ;" << endl;
    if(!m_Hijos.empty()){
      for(auto it:m_Hijos){
        cont++;
        it->vz_num= cont;
        it->show();
      }
    }
  }

  void showParent() {
    //cout << "Parent key: " <<m_key << endl;
    this->vz_num = cont;
    cout << "n" << this->vz_num <<" ;\n";
    cout << "n" << this->vz_num << " [label=\"" << this->m_key << "\"] ;" << endl;
    if(!m_Hijos.empty()){
      for(auto it:m_Hijos){
        cont++;
        it->vz_num=cont;
        it->show();
      }
    }
  }

  NodoB<T>* find(T key) {
    if(m_key == key) return this;
    for(auto it: this->m_Hijos){
      
    }
    return nullptr;
  }

  int m_Grado;
  int vz_num;
  string name; 
  bool color = false; // 0 = blanco, 1 = negro
  T m_key;
  list< NodoB<T> * > m_Hijos;
  NodoB<T> * m_pPadre;

private:
  

  

};

#endif // NODOB_H
