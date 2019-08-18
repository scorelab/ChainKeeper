#ifndef ANALYSIS_LIBRARY_BLOCK_DB_H
#define ANALYSIS_LIBRARY_BLOCK_DB_H

#include <iostream>
#include <stdio.h>
#include <sqlitecon.hpp>

namespace Block {
    template <class K, class V>
    boost::python::dict toPythonDict(std::map<K, V> map) {
        typename std::map<K, V>::iterator iter;
        boost::python::dict dictionary;
        for (iter = map.begin(); iter != map.end(); ++iter) {
            dictionary[iter->first] = iter->second;
        }
        return dictionary;
    }

    class Block: public sqlite_db::conenction {
        sqlite3 *db;
        sqlite3_stmt *stmt;

    public:

        Block(string homeDirPath, string subDir, string storeDir) :
                sqlite_db::conenction(homeDirPath, subDir, storeDir) {}

        map<string, string> getBlockDetails(int height) {

            std::map<string, string> blockMap;
            char const *sqlQuery = "select * from BLOCK_DATA where DATA_ID=?;";
            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);

            sqlite3_bind_int(stmt, 1, height);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int i;
                int num_cols = sqlite3_column_count(stmt);

                for (i = 0; i < num_cols; i++) {
                    blockMap.insert(
                            pair<string, string>(
                                    std::string(reinterpret_cast<const char *>(sqlite3_column_name(stmt, i))),
                                    std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)))));
                }

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return blockMap;
        }

        std::vector<std::map<string, string>> getBlockDetailsRange(int heightFrom, int heightTo) {
            char *errorMessage;
            std::vector<std::map<string, string>> rangeData;

            char const *sqlQuery = "select * from BLOCK_DATA where DATA_ID >= ? AND DATA_ID <= ?;";
            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);

            sqlite3_bind_int(stmt, 1, heightFrom);
            sqlite3_bind_int(stmt, 2, heightTo);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                std::map<string, string> blockMap;
                int i;
                int num_cols = sqlite3_column_count(stmt);

                for (i = 0; i < num_cols; i++) {
                    blockMap.insert(
                            pair<string, string>(
                                    std::string(reinterpret_cast<const char *>(sqlite3_column_name(stmt, i))),
                                    std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)))));
                }

                rangeData.push_back(blockMap);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return rangeData;
        }

        boost::python::list getTxOfBlock(int height) {
            boost::python::list blockTxIdList;
            char const *sqlQuery = "select DATA_ID FROM TX_INDEX WHERE BLOCK_ID=?;";

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, height);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++) {
                    blockTxIdList.append(sqlite3_column_int(stmt, i));
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return blockTxIdList;

        }

        std::vector <std::map<string,string>> getBlockTxData(int blk_height){
            std::vector <std::map<string,string>> txCoinbaseHashList;

            std::string query = "select * from TX_DATA WHERE HEIGHT=?";
            char const *sqlQuery = query.c_str();

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, blk_height);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                std::map<string, string> txMap;

                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++) {
                    txMap.insert(pair<string, string>(
                            std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i))),
                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)))));
                }

                txCoinbaseHashList.push_back(txMap);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return txCoinbaseHashList;
        }

    };
}

#endif //ANALYSIS_LIBRARY_BLOCK_DB_H
