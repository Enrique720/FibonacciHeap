g++ -std=c++17 -Wall main.cpp -L/usr/X11R6/lib -lm -lpthread -lX11
./a.out > graph.vz
dot -Tpdf graph.vz -o grafo.pdf
evince grafo.pdf