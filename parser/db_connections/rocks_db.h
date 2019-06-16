#ifndef ANALYSIS_LIBRARY_CONNECTION_H
#define ANALYSIS_LIBRARY_CONNECTION_H

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#include <iostream>
#include <assert.h>
#include <pwd.h>
#include <zconf.h>
#include "rocksdb/db.h"

using namespace std;

namespace rocksdb_mapping {

    class connectDB {

        //Attributes
        string parserDirectoryName;
        string rocksDBDataDirectoryName;
        string elementDirectory;
        rocksdb::DB* db;
        rocksdb::Options options;
        rocksdb::Status status;

    public:

        connectDB(string homePath, string subDir, string storeDir) {
            parserDirectoryName = homePath;
            rocksDBDataDirectoryName = subDir;
            elementDirectory = storeDir;

            options.create_if_missing = true;

            string folderPathName = parserDirectoryName  + PATH_SEPARATOR + rocksDBDataDirectoryName + PATH_SEPARATOR;
            string path = folderPathName + elementDirectory;

            // open a database with a name which corresponds to a file system directory
            status = rocksdb::DB::Open(options, path, &db);
            // check status
            if (!status.ok()) cerr << status.ToString() << endl;
        }

        string getValueFromKey(string key) {
            rocksdb::Slice keyVal = key;
            std::string value;
            status = db->Get(rocksdb::ReadOptions(), keyVal, &value);
            if (!status.ok()){
                value = "null";
            }

            return value;
        }

        string isKeyExist(string key) {

            rocksdb::Slice keyVal = key;
            std::string value;
            status = db->Get(rocksdb::ReadOptions(), keyVal, &value);

            if (value.empty()){
                value = "null";
            }

            return value;
        }

        void close() {
            // close the database
            delete db;
        }
    };
}

#endif //ANALYSIS_LIBRARY_CONNECTION_H