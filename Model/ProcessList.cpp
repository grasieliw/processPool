#include <iostream>
#include <vector>
 

#include "Process/Process.h"
#include "ProcessList.h"
#include "Process/ComputingProcess.h"
#include "Process/WritingProcess.h"
#include "Process/ReadingProcess.h"
#include "Process/PrintingProcess.h"

using namespace std;

ProcessList::ProcessList() {
    first = nullptr;
    last = nullptr;
}

ProcessList::~ProcessList() {
    Nodo* atual = first;
    while (atual != nullptr) {
        Nodo* proxNodo = atual->prox;
        // Delete the process object
        if (atual->valor != nullptr) {
            delete atual->valor;
            atual->valor = nullptr;
        }
        // Delete the node itself
        delete atual;
        atual = proxNodo;
    }
    first = nullptr;
    last = nullptr;
}

void ProcessList::insert(Process* p) {
    if (p == nullptr) return;

    Nodo* newProcess = new Nodo{p, nullptr};

    if (first == nullptr) {
        first = newProcess;
        last = newProcess;
    } else {
        
        last->prox = newProcess; 
        
        last = newProcess; 
    }
}

Process* ProcessList::removeNext() {
    if (first == nullptr) {
        return nullptr; //lista vazia
    }

    Nodo* temp = first;
    Process* removedProcess = temp->valor;

    first = first->prox;

    if (first == nullptr) {
        last = nullptr; //lista ficou vazia
    }

    // Free the node container but not the Process* (caller owns the process)
    delete temp;
    return removedProcess;
}

Process* ProcessList::removeByPid(int pid) {
    if (first == nullptr) {
        return nullptr; // Fila vazia
    }

    if (first->valor->getPid() == pid) {
        return removeNext(); 
    }

    Nodo* nodoAnterior = buscaDoRemove(pid); 
    
    if (nodoAnterior == nullptr) {
        cout << "Processo (PID: " << pid << ") nao encontrado na fila." << endl;
        return nullptr;
    }

    Nodo* nodoRemover = nodoAnterior->prox;
    Process* processoRemovido = nodoRemover->valor; 

    nodoAnterior->prox = nodoRemover->prox; 
    
    if (nodoRemover == last) {
        last = nodoAnterior; 
    } 
    
    // Free the node container, but not the Process* (caller owns the process)
    delete nodoRemover;
    return processoRemovido;
}

vector<Process*> ProcessList::getTodosProcessos() {
    vector<Process*> lista;
    Nodo* atual = first;
    while (atual != nullptr) {
        lista.push_back(atual->valor);
        atual = atual->prox;
    }
    return lista;
}

bool ProcessList::estaVazia() {
    return first == nullptr;
}

int ProcessList::tamanho() {
    int count = 0;
    Nodo* atual = first;
    while (atual) {
        count++;
        atual = atual->prox;
    }
    return count;
}
    
void ProcessList::salvarEstado(string nomeArquivo) { 

   
}

void ProcessList::carregarEstado(string nomeArquivo) { 
    
    

 }

Nodo* ProcessList::buscaDoRemove(int pid) {
    if (first == nullptr) {
        return nullptr;
    }
    return buscaDoRemoveAux(pid, first);
}

Nodo* ProcessList::buscaDoRemoveAux(int pid, Nodo* aux) {
    if (aux == nullptr || aux->prox == nullptr) { 
        return nullptr; 
    }

    if (aux->prox->valor->getPid() == pid) {
        return aux;
    }

    return buscaDoRemoveAux(pid, aux->prox);
}
