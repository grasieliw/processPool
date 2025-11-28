#include <iostream>
#include <vector>
 #include <fstream>

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

ProcessList::~ProcessList() {}

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

    ofstream ofs(nomeArquivo, ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cerr << "Erro ao abrir arquivo: " << nomeArquivo << endl;
        return;
    }

    Nodo* atual = first;
    while (atual != nullptr) {
        Process* p = atual->valor;
        if (p != nullptr) {
            
            int tipo = static_cast<int>(p->getTipo());
            switch (tipo) {
                case TIPO_COMPUTING:
                    ComputingProcess* c = dynamic_cast<ComputingProcess*>(p);
                    ofs << p->getPid() << ";COMPUTING;" << c->getOperand1() << ";" << c->getOperador() << ";" << c->getOperand2() << '\n';
                    break;

                case TIPO_WRITING:
                    WritingProcess* c = dynamic_cast<WritingProcess*>(p);
                    ofs << p->getPid() << ";WRITING;" << c->getExpression() << '\n';
                    break;

                case TIPO_READING:
                    ofs << p->getPid() << ";READING" << '\n';
                    break;
                case TIPO_PRINTING:
                    ofs << p->getPid() << ";PRINTING" << '\n';
                    break;
                default:
                    ofs << "UNKNOWN" << '\n';
                    break;
            }
        }
        atual = atual->prox;
    }

    ofs.close();
}

void ProcessList::carregarEstado(string nomeArquivo) { 
    
    ifstream ifs(nomeArquivo, ios::in);
    if (!ifs.is_open()) {
        cerr << "Erro ao abrir arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    while (getline(ifs, linha)) {
        size_t pos = 0;
        vector<string> campos;
        string campo;
        
        while ((pos = linha.find(';')) != string::npos) {
            campo = linha.substr(0, pos);
            campos.push_back(campo);
            linha.erase(0, pos + 1);
        }
        campos.push_back(linha);
        
        if (campos.size() < 2) continue;
        
        int pid = stoi(campos[0]);
        string tipo = campos[1];
        
        if (tipo == "COMPUTING" && campos.size() >= 5) {
            int op1 = stoi(campos[2]);
            char operador = campos[3][0];
            int op2 = stoi(campos[4]);
            insert(new ComputingProcess(pid, op1, operador, op2));
        } 
        else if (tipo == "WRITING" && campos.size() >= 3) {
            insert(new WritingProcess(pid, campos[2]));
        } 
        else if (tipo == "READING") {
            insert(new ReadingProcess(pid));
        } 
        else if (tipo == "PRINTING") {
            insert(new PrintingProcess(pid));
        }
    }

    ifs.close();

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
