#include "ComputingProcess.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

ComputingProcess::ComputingProcess(int pid, string expression) : Process(pid) {
    parseAndStore(expression);
}

ComputingProcess::~ComputingProcess(){}

void ComputingProcess::parseAndStore(string expression) {
    stringstream ss(expression);
    char op;
    
    if (!(ss >> operand1 >> op >> operand2)) {
        throw std::invalid_argument("Erro ao ler expressao. Formato esperado: 'NUM OPERADOR NUM'");
    }

    if (op != '+' && op != '-' && op != '*' && op != '/') {
        throw std::invalid_argument("Operacao invalida. Use apenas +, -, *, ou /.");
    }
    
    operador = op;
}

string ComputingProcess::getExpression() {
    string result = to_string(operand1) + " " + operador + " " + to_string(operand2);
    return result;
}

void ComputingProcess::execute() {
    double result = 0.0;

    cout << "Executing Computing Process (PID = " << getPid() << ") : ";
    cout << operand1 << " " << operador << " " << operand2 << endl;

    switch (operador) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 == 0) {
                std::cout << "ERRO: Divisao por zero!" << std::endl;
                return; 
            }
            result = operand1 / operand2;
            break;
    }

    cout << "Resultado do Calculo: " << result << endl;
}

TipoProcesso ComputingProcess::getTipo() {
    return TIPO_COMPUTING;
}