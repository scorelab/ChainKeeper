#include "src/page.h"
#include "src/parser.h"
#include "ext/crow/crow.h"
#include "src/CmdLineOptions.h"
#include <thread>
#include <vector>
#include <ctime>
#include <stdlib.h>

using boost::filesystem::path;

using namespace parse;
using namespace std;

int main(int ac, const char* av[]) {
    // get command line options
    core::CmdLineOptions opts {ac, av};

    auto bc_path_opt = opts.get_option<string>("bc-path");

    uint32_t log_level = 0;
    mlog_configure("", true);

    cout << "" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Welcome to the ChainParser - Analysing ang Exploring Tool for Bitcoin Blockchain" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "" << endl;

    // get blockchain path
    path blockchain_path;

    if (!core::get_blockchain_path(bc_path_opt, blockchain_path, nettype))
    {
        cerr << "Error getting blockchain path." << endl;
        return EXIT_FAILURE;
    }

    cout << "Connect with Bitcoin blockchain data in path - " << blockchain_path << endl;

    cryptonote::Blockchain* core_storage;
    string deamon_url {*deamon_url_opt};
    uint64_t mempool_info_timeout {5000};

    // initialize mcore and core_storage
    if (!core::init_blockchain(blockchain_path.string(), mcore, core_storage,nettype))
    {
        cerr << "Error accessing blockchain." << endl;
        return EXIT_FAILURE;
    }


    //get current block-height
    uint64_t current_blockchain_height =  core_storage->get_current_blockchain_height();
    cout << "Current blockchain Height - " << current_blockchain_height << endl;
    // run the crow http server

    //check the last saved block height
    string last_block = parse::getLastSavedBlockHeight();
    int start_block_height = atoi(last_block.c_str()) + 1;
    int end_block_height = 10000;

    cout << "ChainParser currently parsed block height - "<< last_block<< endl;
    string userInputBlock;
//    cout << "Enter how many blocks need to parse: ";
//    cin >> userInputBlock;
//    end_block_height = atoi(userInputBlock.c_str());

    cout << "ChainParser started to parse blocks range of "<<start_block_height<<" to "<< end_block_height<< endl;
    if(start_block_height>=end_block_height){
        cout << "ChainParser has parsed upto "<<last_block<<" blocks already";
        cout <<" "<< endl;
        cout << "The ChainParser is terminating." << endl;
        return EXIT_SUCCESS;
    }

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "Started Time -" << std::put_time(std::localtime(&now_c), "%c") << '\n';
    cout << "" <<endl;
    time_t Start, End;
    time (& Start);

    //iterate parser through the blockchain
    auto thread1 = std::thread(parse::mainFunction, start_block_height,end_block_height,current_blockchain_height);
    auto thread2 = std::thread(parse::runBlockMainThread);
    auto thread3 = std::thread(parse::runTxMainThread);
    auto thread4 = std::thread(parse::runKeyImageMainThread);

    auto thread5 = std::thread(parse::runSAIdHashMappingThread);
    auto thread6 = std::thread(parse::runSAIndexStoreThread);
    auto thread7 = std::thread(parse::runSaDataStoreThread);

    auto thread8 = std::thread(parse::runRMIdHashMappingThread);
    auto thread9 = std::thread(parse::runRMIndexStoreThread);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();

    //store last saved block height
    parse::storeLastSavedBlockHeight(end_block_height);

    //end date and time
    time (& End);
    double dif = difftime (End, Start);
    cout << "\nParsing completed IN " << dif << " SECOND(s)." << endl;

    now = std::chrono::system_clock::now();
    now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "\nEnded Time - " << std::put_time(std::localtime(&now_c), "%c") << '\n';

    cout << "The Chain-parser is terminating." << endl;

    return EXIT_SUCCESS;
}