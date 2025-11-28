#include <fstream>
#include <iostream>
#include <stdexcept>

#include "ReadingProcess.h"

ReadingProcess::ReadingProcess(int pid, ProcessList* fila) : Process(pid), processList(fila) {}
ReadingProcess::~ReadingProcess(){}

void ReadingProcess::execute() {
    ifstream arquivoLeitura(NOME_ARQUIVO);
    string linha;
    int processosCriados = 0;

    cout << "\nProcesso de Leitura (PID " << getPid() << ") iniciado." << endl;

    if (arquivoLeitura.is_open()) {
        
        while (getline(arquivoLeitura, linha)) {
            if (!linha.empty()) {    
                int novoPid = getPid();

                Process* novoProcesso = new ComputingProcess(novoPid, linha); 
                
                processList->insert(novoProcesso);
                processosCriados++;

                cout << "[SUCESSO] Expressao lida '" << linha << "'. Criado ComputingProcess com PID " << novoPid << "." << endl; 
            }
        }
        arquivoLeitura.close();
        
        cout << "Leitura concluida. " << processosCriados << " novos processos de calculo adicionados a fila." << endl;

        ofstream arquivoLimpeza(NOME_ARQUIVO, ios::trunc); 
        
        if (arquivoLimpeza.is_open()) {
            cout << "Arquivo de computacao ('" << NOME_ARQUIVO << "') limpo com sucesso." << endl;
            arquivoLimpeza.close();
        } else {
            cout << "[ERRO]: Nao foi possivel limpar o arquivo " << NOME_ARQUIVO << "." << endl;
        }

    } else {
        cout << "[ERRO]: Nao foi possivel abrir o arquivo " << NOME_ARQUIVO << " para leitura. Certifique-se de que ele existe." << endl;
    }
}

TipoProcesso ReadingProcess::getTipo() {
    return TIPO_READING;
}