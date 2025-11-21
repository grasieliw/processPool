#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <iostream>
#include <vector>

#include "Process/Process.h"

using namespace std;

struct Nodo {
    Process* valor;
    Nodo* prox;
};

class ProcessList {

    public:
        ProcessList();
        ~ProcessList();

        void insert(Process* p);
        Process* removeNext();
        Process* removeByPid(int pid);
        vector<Process*> getTodosProcessos();
        bool estaVazia();
        int tamanho();
        void salvarEstado(string nomeArquivo);
        void carregarEstado(string nomeArquivo);    

    private:
        Nodo* first;
        Nodo* last;

        Nodo* buscaDoRemove(int pid);
        Nodo* buscaDoRemoveAux(int pid, Nodo* aux);
};
#endif