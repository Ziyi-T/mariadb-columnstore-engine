
#include "AppendTask.h"
#include "messageFormat.h"
#include <errno.h>

using namespace std;

namespace storagemanager
{

AppendTask::AppendTask(int sock, uint len) : PosixTask(sock, len)
{
}

AppendTask::~AppendTask()
{
}

#define check_error(msg, ret) \
    if (!success) \
    { \
        handleError(msg, errno); \
        return ret; \
    }
    
#define min(x, y) (x < y ? x : y)

bool AppendTask::run()
{
    bool success;
    uint8_t cmdbuf[1024] = {0};
    int err;
    
    success = read(cmdbuf, sizeof(append_cmd));
    check_error("AppendTask read", false);
    append_cmd *cmd = (append_cmd *) cmdbuf;
    
    if (cmd->flen > 1023 - sizeof(*cmd))
    {
        handleError("AppendTask", ENAMETOOLONG);
        return true;
    }
    success = read(&cmdbuf[sizeof(*cmd)], cmd->flen);
    check_error("AppendTask read", false);
    
    size_t readCount = 0, writeCount = 0;
    vector<uint8_t> databuf;
    uint bufsize = min(1 << 20, cmd->count);   // 1 MB
    databuf.resize(bufsize);
    
    while (readCount < cmd->count)
    {
        uint toRead = min(cmd->count - readCount, bufsize);
        success = read(&databuf[0], toRead);
        check_error("AppendTask read data", false);
        readCount += toRead;
        uint writePos = 0;
        while (writeCount < readCount)
        {
            int err = ioc->append(cmd->filename, &databuf[writePos], toRead - writePos);
            if (err <= 0)
                break;
            writeCount += err;
            writePos += err;
        }
        if (readCount != writeCount)
            break;
    }
    
    uint8_t respbuf[sizeof(sm_msg_resp) + 4];
    sm_msg_resp *resp = (sm_msg_resp *) respbuf;
    resp->type = SM_MSG_START;
    if (cmd->count != 0 && writeCount == 0)
    {
        resp->payloadLen = 8;
        resp->returnCode = -1;
        *((int *) &resp[1]) = errno;
        success = write((uint8_t *) respbuf, sizeof(sm_msg_resp) + 4);
    }
    else
    {
        resp->payloadLen = 4;
        resp->returnCode = writeCount;
        success = write((uint8_t *) respbuf, sizeof(sm_msg_resp));
    }
    return success;
}

}
