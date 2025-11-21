#include "Process.h"

Process::Process(int pid) : pid(pid) {}
Process::~Process(){}

void Process::setPid(int pid) {
    this->pid = pid;
}

int Process::getPid() {
    return this->pid;
}