#include "data_structures.hpp"
#include "findley.hpp"
#include "stress.hpp"
#include "tri_hemisphere.hpp"
#include "file_handling.hpp"

#include <Eigen/Core>
#include <boost/program_options.hpp>

#include <iostream>
#include <chrono>

namespace po = boost::program_options;
using Clock = std::chrono::system_clock; 

int main(int argc, const char* argv[]) 
{
    auto start_time = Clock::now();

    try {
        po::options_description description{"Allowed options"};
        description.add_options()
            ("help,h", "Display help message")
            ("input,i", po::value<std::string>(), "Run fatigue calculations on input file");
        po::variables_map vm;
        po::parsed_options parsed = po::command_line_parser(argc, argv)
            .options(description)
            .allow_unregistered()
            .run();
        po::store(parsed, vm);
        po::notify(vm);   
        std::vector<std::string> unrecognized = po::collect_unrecognized(parsed.options, po::include_positional);

        if (vm.count("help")) {
            std::cout << description << "\n";
            return 1;
        }

        if (vm.empty()) {
            std::cout << "Critical plane calculations. See --help for more info.\n";
        } else if (vm.count("input")) {
            std::string const& file = vm["input"].as<std::string>();
            std::cout << "Running on input-file " << file << "\n";
            // TODO
        }
    } catch (const po::error& ex) {
        std::cerr << ex.what() << "\n";
    }

    double elapsed = (double)std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - start_time).count();
    printf("Elapsed: %.3f seconds", elapsed);

    return 0;
}