#include "Model/Process/ComputingProcess.h"
#include "Model/Process/WritingProcess.h"
#include "Model/Process/ReadingProcess.h"
#include "Model/Process/PrintingProcess.h"
#include "Model/ProcessList.h"
#include "Model/System.h"
#include <iostream>
#include <vector>
using namespace std;

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
                        int pid;
                        string expression;
                        cout << "Enter PID: ";
                        cin >> pid;
                        cout << "Enter full expression (e.g., 5 + 3): ";
                        cin.ignore();
                        getline(cin, expression);

                        system.adicionarProcesso(new ComputingProcess(pid, expression));
                        break;
                    }
                    case 2: {
                        int pid;
                        string data;
                        cout << "Enter PID: ";
                        cin >> pid;
                        cout << "Enter data to write: ";
                        cin.ignore();
                        getline(cin, data);

                        system.adicionarProcesso(new WritingProcess(pid, data));
                        break;
                    }
                    case 3: {
                        int pid;
                        cout << "Enter PID: ";
                        cin >> pid;

                        system.adicionarProcesso(new ReadingProcess(pid, system.getProcessList()));
                        break;
                    }
                    case 4: {
                        int pid;
                        cout << "Enter PID: ";
                        cin >> pid;

                        system.adicionarProcesso(new PrintingProcess(pid, system.getProcessList()));
                        break;
                    }
                    default:
                        cout << "Invalid process type!" << endl;
                }

                break;
            }
            case 2: {

                system.executarProximoProcesso();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Process ID to execute: ";
                cin >> id;
                
                system.executarProcessoPorPid(id);
                break;
            }
            case 4: {
                string filename;
                cout << "Enter filename to save the process list: ";
                cin >> filename;
                
                system.salvarEstadoSistema(filename);
                break;
            }
            case 5: {
                string nomeArquivo;
                cout << "Enter filename to save the process list: ";
                cin >> nomeArquivo;

                system.carregarEstadoSistema(nomeArquivo);
                break;
            }

            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
