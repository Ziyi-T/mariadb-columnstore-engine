
#ifndef S3STORAGE_H_
#define S3STORAGE_H_

#include <string>
#include "CloudStorage.h"
#include "libmarias3/marias3.h"

namespace storagemanager
{

class S3Storage : public CloudStorage
{
    public:
        S3Storage();
        virtual ~S3Storage();

        int getObject(const std::string &sourceKey, const std::string &destFile, size_t *size = NULL);
        int getObject(const std::string &sourceKey, boost::shared_array<uint8_t> *data, size_t *size = NULL);
        int putObject(const std::string &sourceFile, const std::string &destKey);
        int putObject(const boost::shared_array<uint8_t> data, size_t len, const std::string &destKey);
        void deleteObject(const std::string &key);
        int copyObject(const std::string &sourceKey, const std::string &destKey);
        int exists(const std::string &key, bool *out);

    private:
        ms3_st *creds;
        std::string bucket;   // might store this as a char *, since it's only used that way
};




}

#endif
