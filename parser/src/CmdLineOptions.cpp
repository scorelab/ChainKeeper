#include "CmdLineOptions.h"


namespace xmreg
{
    CmdLineOptions::CmdLineOptions(int acc, const char *avv[]) {

        positional_options_description p;

        p.add("txhash", -1);

        options_description desc(
                "monerosci, Onion Monero Blockchain Explorer");

        desc.add_options()
                ("bc-path,b", value<string>(), "path to lmdb folder of the blockchain, e.g., ~/.bitmonero/lmdb");

        store(command_line_parser(acc, avv)
                          .options(desc)
                          .positional(p)
                          .run(), vm);

        notify(vm);

        if (vm.count("help"))
        {
            if (vm["help"].as<bool>())
                cout << desc << "\n";
        }
    }

    template<typename T>
    boost::optional<T>
    CmdLineOptions::get_option(const string & opt_name) const
    {

        if (!vm.count(opt_name))
        {
            return boost::none;
        }

        return vm[opt_name].as<T>();
    }

    template  boost::optional<string>
            CmdLineOptions::get_option<string>(const string & opt_name) const;

    template  boost::optional<bool>
            CmdLineOptions::get_option<bool>(const string & opt_name) const;

    template  boost::optional<size_t>
            CmdLineOptions::get_option<size_t>(const string & opt_name) const;

}