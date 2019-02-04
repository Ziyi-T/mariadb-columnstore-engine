
#ifndef LIST_DIRECTORYTASK_H_
#define LIST_DIRECTORYTASK_H_

#include "PosixTask.h"
#include <string>

namespace storagemanager
{

class ListDirectoryTask : public PosixTask
{
    public:
        ListDirectoryTask(int sock, uint length);
        virtual ~ListDirectoryTask();
        
        bool run();
    
    private:
        ListDirectoryTask();
        
        bool writeString(uint8_t *buf, int *offset, int size, const std::string &str);
};


}
#endif
