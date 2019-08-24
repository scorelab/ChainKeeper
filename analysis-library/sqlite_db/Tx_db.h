#ifndef ANALYSIS_LIBRARY_TX_DB_H
#define ANALYSIS_LIBRARY_TX_DB_H

#include <iostream>
#include <stdio.h>
#include "sqlitecon.hpp"

namespace TxData {
    template<class K, class V>
    boost::python::dict toPythonDict(std::map<K, V> map) {
        typename std::map<K, V>::iterator iter;
        boost::python::dict dictionary;
        for (iter = map.begin(); iter != map.end(); ++iter) {
            dictionary[iter->first] = iter->second;
        }
        return dictionary;
    }

    class TxData : public sqlite_db::conenction {
        sqlite3 *db;
        sqlite3_stmt *stmt;

    public:

        TxData(string homeDirPath, string subDir, string storeDir) :
                sqlite_db::conenction(homeDirPath, subDir, storeDir) {}

        map<string, string> getTxDetails(int index){

            std::map<string, string> txMap;
            char const *sqlQuery = "select * from TX_DATA where DATA_ID=?;";
            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);

            sqlite3_bind_int(stmt, 1, index);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++)
                {
                    txMap.insert(pair<string, string>(
                            std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i))),
                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)))));
                }

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return txMap;
        }

        std::vector<int> getOutputsOfTX(int tx_index){
            std::vector<int> outputTxIdList;
            char const *sqlQuery = "select HASH_ID FROM SA_INDEX WHERE TX_ID=?;";

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, tx_index);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++)
                {
                    outputTxIdList.push_back(sqlite3_column_int(stmt, i));
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return outputTxIdList;
        }

        boost::python::list getOutputsFromTxIndex(boost::python::list sa_ids){
            boost::python::list txOutputList;
            int idLength = boost::python::len(sa_ids);
            string temp = "";
            for(int x=0; x< idLength; x++){
                int id = boost::python::extract<int>(sa_ids[x]);
                temp += to_string(id);
                if(x != idLength-1){
                    temp +=",";
                }
            }
            std::string q1 = "select P_KEY from SA_DATA WHERE DATA_ID IN (";
            std::string q2 = ");";
            std::string query = q1+temp+q2;
            char const *sqlQuery = query.c_str();

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++)
                {
                    txOutputList.append(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return txOutputList;
        }

        boost::python::list getInputsFromTxIndex(boost::python::list ki_ids, boost::python::list ki_mixins){
            boost::python::list txInputList;
            boost::python::list txKIHashList;

            string temp = "";
            int idLength = boost::python::len(ki_mixins);
            for(int x=0; x< idLength; x++){
                int id = boost::python::extract<int>(ki_ids[x]);
                temp += to_string(id);
                if(x != idLength-1){
                    temp +=",";
                }
            }

            std::string q1 = "select K_HASH from KI_DATA WHERE DATA_ID IN (";
            std::string q2 = ");";
            std::string query = q1+temp+q2;
            char const *sqlQuery = query.c_str();

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++)
                {
                    txKIHashList.append(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
                }

            }

            for (int i = 0; i < idLength; i++) {
                std::map<string, string> inputMap;
                inputMap.insert(pair<string, string>(std::string("KEY_IMAGE"),
                        std::string(boost::python::extract<string>(txKIHashList[i]))));
                inputMap.insert(pair<string, string>(std::string("MIXIN_COUNT"),
                        std::string(to_string(boost::python::extract<int>(ki_mixins[i])))));

                boost::python::dict input_tx_dict = toPythonDict(inputMap);
                txInputList.append(input_tx_dict);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return txInputList;
        }

        map<string, string> getOutputIDs(int index, int txId){

            std::map<string, string> outputMap;
            char const *sqlQuery = "select * from SA_INDEX where TX_ID=? AND HASH_ID=?;";
            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);

            sqlite3_bind_int(stmt, 1, txId);
            sqlite3_bind_int(stmt, 2, index);

            while (sqlite3_step(stmt) != SQLITE_DONE) {

                int num_cols = sqlite3_column_count(stmt);
                for (int i = 0; i < num_cols; i++)
                {
                    outputMap.insert(pair<string, string>(
                            std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i))),
                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)))));
                }

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return outputMap;
        }

        int nonCoinbaseCount() {
            char const *sqlQuery = "select count(*) FROM TX_DATA WHERE COIN_BASE=?;";
            int count;

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, 0);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++){
                    count = sqlite3_column_int(stmt, i);
                }

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return count;
        }

        int getBlockIndexFromTxIndex(int txIndex) {
            char const *sqlQuery = "select BLOCK_ID FROM TX_INDEX WHERE HASH_ID=?;";
            int blk_id;

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, txIndex);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++){
                    blk_id = sqlite3_column_int(stmt, i);
                }

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return blk_id;
        }

        std::vector <std::map<string,string>> getTxesTimestamps(int startBlk, int endBlk) {
            std::vector <std::map<string,string>> txes;

            std::string query = "select DATA_ID,TIMESTAMP FROM TX_DATA where HEIGHT>=? AND HEIGHT<=?;";
            char const *sqlQuery = query.c_str();

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, startBlk);
            sqlite3_bind_int(stmt, 2, endBlk);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                std::map<string, string> txMap;

                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++) {
                    txMap.insert(pair<string, string>(
                            std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i))),
                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)))));
                }

                txes.push_back(txMap);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return txes;
        }

        std::vector <std::map<string,string>> getTxFilterData(int start, int end, string enterQuery){
            std::vector <std::map<string,string>> txes;

            std::string query = "select * FROM TX_DATA where HEIGHT>=? AND HEIGHT<=? AND "+enterQuery+" ;";
            char const *sqlQuery = query.c_str();

            sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, start);
            sqlite3_bind_int(stmt, 2, end);

            while (sqlite3_step(stmt) != SQLITE_DONE) {
                std::map<string, string> txMap;

                int num_cols = sqlite3_column_count(stmt);

                for (int i = 0; i < num_cols; i++) {
                    txMap.insert(pair<string, string>(
                            std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i))),
                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)))));
                }

                txes.push_back(txMap);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return txes;
        }
    };
}



#endif //ANALYSIS_LIBRARY_TX_DB_H
