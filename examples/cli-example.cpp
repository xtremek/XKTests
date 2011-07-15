#include <iostream>
#include <fstream>

#include <err.h>

#define EXECUTABLE_NAME    "cli-example"

using namespace std;

void print_version()
{
    cout << "CLI Example v0.1" << endl;
}

int main(int argc, char *argv[])
{
    bool debug_mode = false;

    // Check the command line arguments
    if (argc > 0) {
        for (int i = 0; i < argc; i++) {
            string cmd = argv[i];
            if (cmd == "-h" || cmd == "--help") {
                cout << "Usage: " << EXECUTABLE_NAME << " [OPTION]" << endl;
                cout << "Command Line Options: " << endl;
                cout << " -h, --help\tshow this help" << endl;
                cout << " -d, --debug\trun in debug mode (don't run as a service)" << endl;
				return 0;
            } else if (cmd == "-d" || cmd == "--debug") {
                debug_mode = true;
            } else if (cmd == "-v" || cmd == "--version") {
                print_version();
				return 0;
            }
        }
    }

    print_version();

	if (debug_mode) {
		while (1) 
		{
			// Press Ctrl + C to quit this app
		}
	}

    return 0;
}