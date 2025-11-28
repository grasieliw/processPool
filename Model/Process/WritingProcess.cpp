#include <fstream>
#include <iostream>
#include <string>

#include "WritingProcess.h"

const string NOME_ARQUIVO = "computation.txt";

WritingProcess::WritingProcess(int pid, string expression) : Process(pid) {
    this->expression = expression;
}

WritingProcess::~WritingProcess(){}

void WritingProcess::execute() {
    ofstream arquivo(NOME_ARQUIVO, ios::app); 

    if (arquivo.is_open()) {
        arquivo << expression << endl;
        cout << "Processo de Gravacao (PID " << getPid() << ") executado com sucesso. Expressao '" << expression << "' adicionada ao " << NOME_ARQUIVO << endl;
        arquivo.close();

    } else {
        cout << "ERRO: Nao foi possivel abrir o arquivo " << NOME_ARQUIVO << " para gravacao. (PID " << getPid() << ")" << endl;
    }
}

TipoProcesso WritingProcess::getTipo() {
    return TIPO_WRITING;
}