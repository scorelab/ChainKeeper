#ifndef SQLITE_CON_H
#define SQLITE_CON_H

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <boost/python/dict.hpp>
#include <map>

using namespace std;

namespace sqlite_db {

    class conenction {
        sqlite3 *db;
        sqlite3_stmt *stmt;
        string homeDirName;

    public:
        conenction(string homeDirPath, string subDir, string storeDir) {
            homeDirName = homeDirPath;
            string subDirName = subDir;
            string storeDirName = storeDir + ".db";

            string folderPathName = homeDirName + "/" + subDirName + "/";
            string path = folderPathName;
            string finalPath = path;
            string dbPath = path + storeDirName;

            sqlite3_open(dbPath.c_str(), &db);

            if (db == NULL) {
                printf("Failed to open DB\n");
            }

        }
    };
}

#endif //SQLITE_CON_H