g++ -std=c++17 -O2 -Wall main.cpp
./a.out > graph.vz
dot -Tpdf graph.vz -o grafo.pdf
evince grafo.pdf