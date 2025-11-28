#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>

#include "Process/Process.h"
#include "ProcessList.h"

using namespace std;

class System {

    public:
        System();
        ~System();

        void adicionarProcesso(Process* p);
        void executarProcessoPorPid(int pid);
        void executarProximoProcesso();
        void salvarEstadoSistema(string nomeArquivo);
        void carregarEstadoSistema(string nomeArquivo);

    private:
        ProcessList processList;

};
#endif