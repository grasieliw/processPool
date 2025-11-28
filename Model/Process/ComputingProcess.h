#ifndef COMPUTINGPROCESS_H
#define COMPUTINGPROCESS_H

#include "Process.h"

using namespace std;

class ComputingProcess : public Process {

    public:
        ComputingProcess(int pid, string expression);
        ~ComputingProcess();

        string getExpression();

        void setOperand1(double op1) { operand1 = op1; }
        void setOperand2(double op2) { operand2 = op2; }
        void setOperador(char op) { operador = op; }

        double getOperand1() const { return operand1; }
        double getOperand2() const { return operand2; }
        char getOperador() const { return operador; }
        TipoProcesso getTipo() override;


        void execute() override;
       
    private:
        double operand1;
        double operand2;
        char operador;

        void parseAndStore(string expression);
};
#endif