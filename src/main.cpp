#include <Options.hpp>
#include <Lightgrep.hpp>
#include <PathFilter/AlwaysMatchingFilter.hpp>

// This include makes sure that the ICheckAndOutput::create function is defined for all templates
#include "ICheckAndOutput.cpp"

#include "thirdparty/argparse.hpp"

#include <iostream>

std::string getValidRegexCommandFromUser(const std::string &whatToInputMsg);


int main(int argc, char** argv)
{
    argparse::ArgumentParser program("lightgrep");
    {
        program.add_argument("root")
            .help("Root directory starting the search");
        program.add_argument("regex")
            .help("A regex used to match the contents of a file");
        program.add_argument("-w", "--wildcard")
            .default_value<std::string>("*")
            .help("Wildcard used to match filenames: ? represents one character and * represents an arbitrary amount of characters");
        program.add_argument("--dontSkipBinaries")
            .default_value(false)
            .implicit_value(true)
            .help("Binaries are not skipped during search if specified");

        try
        {
            program.parse_args(argc, argv);
        }
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
            std::cerr << program;
            std::exit(1);
        }
    }

	std::ostream_iterator<std::string> oiter{std::cout};

	auto opt = std::make_shared<lg::Options>(program.get<std::string>("root"), 
            program.get<std::string>("--wildcard"), program.get<std::string>("regex"), !program.get<bool>("--dontSkipBinaries"));
	lg::Lightgrep lightgrep(opt, oiter);

	lightgrep.searchAndOutput();

   	
	return 0;
}


// get and return valid regex command from user; can't return regex directly
// because regex has to be constructed differently when the input is empty
std::string getValidRegexCommandFromUser(const std::string &whatToInputMsg) {
	std::regex regex;
	std::string regexStr;
	while (true) {
		std::cout << whatToInputMsg << std::endl;
		std::getline(std::cin, regexStr);

		try {
			regex = std::regex(regexStr);
			break;
		}
		catch (const std::regex_error &e) {
			std::cout << std::endl << e.what() << std::endl;
			std::cout << "Invalid regular expression; Please try again!" << std::endl;
		}
	}

	return regexStr;
}
