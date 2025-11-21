#ifndef COMPUTINGPROCESS_H
#define COMPUTINGPROCESS_H

#include "Process.h"

using namespace std;

class ComputingProcess : public Process {

    public:
       ComputingProcess(int pid, string expression);
       ~ComputingProcess();

       string getExpression();

       void execute() override;
       TipoProcesso getTipo() override;
       
    private:
        double operand1;
        double operand2;
        char operador;

        void parseAndStore(string expression);
};
#endif