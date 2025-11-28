#include "Model/Process/ComputingProcess.h"
#include "Model/Process/WritingProcess.h"
#include "Model/Process/ReadingProcess.h"
#include "Model/Process/PrintingProcess.h"
#include "Model/ProcessList.h"
#include "Model/System.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

static bool validarExpressaoMain(const std::string &expr) {
    istringstream iss(expr);
    string t1, t2, t3, extra;
    if (!(iss >> t1 >> t2 >> t3)) return false; // não encontrou 3 tokens
    if (iss >> extra) return false; // tokens extras -> inválido

    if (t2.size() != 1) return false;
    char op = t2[0];
    if (std::string("+-*/").find(op) == string::npos) return false;

    try {
        size_t pos = 0;
        stod(t1, &pos);
        if (pos != t1.size()) return false;
        stod(t3, &pos);
        if (pos != t3.size()) return false;
    } catch (...) {
        return false;
    }
    return true;
}

int main() {
   
    System system;
    int choice;

    while (true) {
        cout << "\n=== Process Pool Menu ===" << endl;
        cout << "1. Criar Processo" << endl;
        cout << "2. Executar Proximo" << endl;
        cout << "3. Executar Processo Especifico" << endl;
        cout << "4. Salvar a fila de Processos" << endl;
        cout << "5. Carregar a fila de Processos" << endl;
        cout << "6. Sair" << endl;
        cout << "Sua escolha: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int type;
                cout << "Process type (1:Computing, 2:Writing, 3:Reading, 4:Printing): ";
                cin >> type;
                
                switch(type) {
                    case 1: {
                        string expression;
                        int pid = system.getNextPid();
                        cout << "Escreva a expressao inteira (e.g., 5 + 3): ";
                        cin.ignore();
                        getline(cin, expression);

                        system.adicionarProcesso(new ComputingProcess(pid, expression));
                        cout << "Processo COMPUTING com PID " << pid << " adicionado." << endl;
                        break;
                    }
                    case 2: {
                        string data;
                        int pid = system.getNextPid();
                        cout << "Escreva os dados para escrever: ";
                        cin.ignore();
                        getline(cin, data);

                        if (!validarExpressaoMain(data)) {
                             cout << "[ERRO] Expressao invalida para WRITING (PID " << pid << "): '" << data << "'. Processo ignorado." << endl;
                             break;
                        } else {
                            system.adicionarProcesso(new WritingProcess(pid, data));
                            cout << "Processo WRITING com PID " << pid << " adicionado." << endl;
                        }
                        break;
                    }
                    case 3: {
                        int pid = system.getNextPid();    
                        system.adicionarProcesso(new ReadingProcess(pid, system.getProcessList()));
                        cout << "Processo READING com PID " << pid << " adicionado." << endl;
                        break;
                    }
                    case 4: {
                        int pid= system.getNextPid();

                        system.adicionarProcesso(new PrintingProcess(pid, system.getProcessList()));
                        cout << "Processo PRINTING com PID " << pid << " adicionado." << endl;
                        break;
                    }
                    default:
                        cout << "Tipo de processo invalido!" << endl;
                }

                break;
            }
            case 2: {

                system.executarProximoProcesso();
                break;
            }
            case 3: {
                int id;
                cout << "Escolha o PID para executar: ";
                cin >> id;
                
                system.executarProcessoPorPid(id);
                break;
            }
            case 4: {
                string filename;
                cout << "Escreva a FileName para salvar a lista de processos: ";
                cin >> filename;
                
                system.salvarEstadoSistema(filename);
                break;
            }
            case 5: {
                string nomeArquivo;
                cout << "Escreva a FileName para carregar a lista de processos: ";
                cin >> nomeArquivo;

                system.carregarEstadoSistema(nomeArquivo);
                break;
            }

            case 6:
                cout << "Saindo..." << endl;
                return 0;
            default:
                cout << "Escolha Invalida!" << endl;
        }
    }
    
    return 0;
}
