

#ifndef WRITETASK_H_
#define WRITETASK_H_

#include "PosixTask.h"

namespace storagemanager
{

class WriteTask : public PosixTask
{
    public:
        WriteTask(int sock, uint length);
        virtual ~WriteTask();
        
        bool run();
    
    private:
        WriteTask();
};

}
#endif
