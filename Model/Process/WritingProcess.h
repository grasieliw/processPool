#ifndef WRITINGPROCESS_H
#define WRITINGPROCESS_H

#include "Process.h"

using namespace std;

class WritingProcess : public Process {

    public:
       WritingProcess(int pid, string expression);
       ~WritingProcess();

       void execute() override;
       TipoProcesso getTipo() override;
       
    private:
        string expression;
};
#endif