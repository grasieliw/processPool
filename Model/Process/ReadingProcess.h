#ifndef READINGPROCESS_H
#define READINGPROCESS_H

#include <string>

#include "Process.h"
#include "ComputingProcess.h"
#include "Model/ProcessList.h"

using namespace std;

class ReadingProcess : public Process {

    public:
       ReadingProcess(int pid, ProcessList* fila);
       ~ReadingProcess();

       void execute() override;
       TipoProcesso getTipo() override;

       ProcessList* getProcessList() const { return processList; }
       
    private:
        const string NOME_ARQUIVO = "computation.txt";
        ProcessList* processList;
};
#endif