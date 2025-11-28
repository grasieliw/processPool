#ifndef WRITINGPROCESS_H
#define WRITINGPROCESS_H

#include "Process.h"

using namespace std;

class WritingProcess : public Process {

    public:
       WritingProcess(int pid, string expression);
       ~WritingProcess();

      void setExpression(const string& expr) { expression = expr; }
      string getExpression() const { return expression; }

       void execute() override;
       TipoProcesso getTipo() override;
       
    private:
        string expression;
};
#endif