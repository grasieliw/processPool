#ifndef PRINTINGPROCESS_H
#define PRINTINGPROCESS_H

#include <string>

#include "Process.h"
#include "Model\ProcessList.h"

using namespace std;

class PrintingProcess : public Process {

    public:
        PrintingProcess(int pid, ProcessList* fila); 
        ~PrintingProcess();

        void execute() override; 
        
        TipoProcesso getTipo() override;
        ProcessList* getProcessList() const { return processList; }

    private:
        ProcessList* processList; 
};
#endif


