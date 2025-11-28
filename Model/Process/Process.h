#ifndef PROCESS_H 
#define PROCESS_H

#pragma once

#include <string>
#include <iostream>

using namespace std;

enum TipoProcesso {
    TIPO_COMPUTING,
    TIPO_WRITING,
    TIPO_READING,
    TIPO_PRINTING
};

class Process {
    public:
        Process(int pid);
        ~Process();

        void setPid(int pid);
        
        int getPid();
        virtual TipoProcesso getTipo() = 0;

        virtual void execute() = 0;
    
    private:
        int pid;
};
#endif