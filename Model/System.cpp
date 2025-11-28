#include "System.h"

System::System() {}
System::~System() {}

void System::adicionarProcesso(Process* p) {
    processList.insert(p);
}

void System::executarProcessoPorPid(int pid) {
    Process* processo = processList.removeByPid(pid);
    if (processo == nullptr) {
        return; // Processo não encontrado
    }
    
    processo->execute();
}

void System::executarProximoProcesso() {
    Process* processo = processList.removeNext();
    if (processo == nullptr) {
        cout << "Nenhum processo para executar." << endl;
        return; // Nenhum processo na fila
    }
    
    processo->execute();
}

void System::salvarEstadoSistema(string nomeArquivo) {
    processList.salvarEstado(nomeArquivo);
}

void System::carregarEstadoSistema(string nomeArquivo) {
    processList.carregarEstado(nomeArquivo);
}