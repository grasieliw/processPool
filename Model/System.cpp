#include "System.h"
#include "Process/ComputingProcess.h"
#include "Process/WritingProcess.h"
#include "Process/ReadingProcess.h"
#include "Process/PrintingProcess.h"
#include <fstream>

System::System() {
    // Initialize the process list when the system is constructed
    processList = new ProcessList();
}

System::~System() {
    // Clean up and free the process list and any remaining processes
    delete processList;
    processList = nullptr;
}

void System::adicionarProcesso(Process* p) {
    processList->insert(p);
}

void System::executarProcessoPorPid(int pid) {
    Process* processo = processList->removeByPid(pid);
    if (processo == nullptr) {
        return; // Processo não encontrado
    }
    
    processo->execute();
    // The system takes ownership of the removed process pointer and is
    // responsible for deleting it after execution to avoid leaks.
    delete processo;
}

void System::executarProximoProcesso() {
    Process* processo = processList->removeNext();
    if (processo == nullptr) {
        cout << "Nenhum processo para executar." << endl;
        return; // Nenhum processo na fila
    }
    
    processo->execute();
    // Delete the process once executed
    delete processo;
}

void System::salvarEstadoSistema(string nomeArquivo) {
     ofstream ofs(nomeArquivo, ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cerr << "Erro ao abrir arquivo: " << nomeArquivo << endl;
        return;
    }

    Nodo* atual = processList->getFirst();
    while (atual != nullptr) {
        Process* p = atual->valor;
        if (p != nullptr) {
            
            int tipo = static_cast<int>(p->getTipo());
            switch (tipo) {
                case TIPO_COMPUTING: {
                    ComputingProcess* c = dynamic_cast<ComputingProcess*>(p);
                    ofs << p->getPid() << ";COMPUTING;" << c->getOperand1() << ";" << c->getOperador() << ";" << c->getOperand2() << '\n';
                    break;
                }

                case TIPO_WRITING: {
                    WritingProcess* w = dynamic_cast<WritingProcess*>(p);
                    ofs << p->getPid() << ";WRITING;" << w->getExpression() << '\n';
                    break;
                }

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

void System::carregarEstadoSistema(string nomeArquivo) {
    
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

            string expression = to_string(op1) + " " + operador + " " + to_string(op2);

            processList->insert(new ComputingProcess(pid, expression));
        } 
        else if (tipo == "WRITING" && campos.size() >= 3) {
            processList->insert(new WritingProcess(pid, campos[2]));
        } 
        else if (tipo == "READING") {
            processList->insert(new ReadingProcess(pid, processList));
        } 
        else if (tipo == "PRINTING") {
            processList->insert(new PrintingProcess(pid, processList));
        }
    }

    ifs.close();

}