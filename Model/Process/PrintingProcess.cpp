#include <iostream>
#include <vector>

#include "Model/ProcessList.h"
#include "Process.h"
#include "PrintingProcess.h"
#include "ComputingProcess.h"
#include "WritingProcess.h"
#include "ReadingProcess.h"

PrintingProcess::PrintingProcess(int pid, ProcessList* fila) : Process(pid), processList(fila) {}
PrintingProcess::~PrintingProcess(){}

void PrintingProcess::execute() {
    cout << "\n========================================================" << endl;
    cout << "  RELATORIO DO POOL DE PROCESSOS (PID: " << getPid() << ")" << endl;
    cout << "========================================================" << endl;
    
    vector<Process*> processos = processList->getTodosProcessos(); 

    if (processos.empty()) {
        cout << "A fila de processos esta vazia." << endl;
        return;
    }

    cout << "Total de processos na fila: " << processos.size() << endl;
    cout << "--------------------------------------------------------" << endl;
    
    int indice = 0;
    for (Process* p : processos) {
        if (p == nullptr) continue;

        cout << "[" << indice++ << "] PID: " << p->getPid();

        switch (p->getTipo()) {
            case TIPO_COMPUTING:
                cout << " | TIPO: CALCULO";
                cout << " | Detalhe: Expressao Aritmetica.";
                break;
            case TIPO_WRITING:
                cout << " | TIPO: GRAVACAO";
                cout << " | Detalhe: Gravar em computation.txt.";
                break;
            case TIPO_READING:
                cout << " | TIPO: LEITURA";
                cout << " | Detalhe: Ler e Limpar computation.txt.";
                break;
            case TIPO_PRINTING:
                cout << " | TIPO: IMPRESSAO";
                cout << " | Detalhe: Imprimir o estado atual da fila.";
                break;
            default:
                cout << " | TIPO: Desconhecido";
                break;
        }
        cout << endl; // Nova linha para o próximo processo
    }
    
    cout << "========================================================" << endl;
}

TipoProcesso PrintingProcess::getTipo() {
    return TIPO_PRINTING;
}


