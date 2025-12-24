#include "parsingArg.h"

bool ParseUint64(const char* str, uint64_t& result) {
    result = 0;
    while (*str) {
        if (*str < '0' || *str > '9') {
            return false; 
        }
        uint64_t prev_result = result;
        result = result * 10 + (*str - '0');
 
        if (result < prev_result) {
            return false;
        }
        ++str;
    }
    return true;
}

bool PrintError(const char* message) {
    std::cerr << message << std::endl;
    return false;
}

bool ParseArguments(int argc, char** argv, Arguments& args) {
    args = {nullptr, nullptr, UINT64_MAX, 0};

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-i") || !strncmp(argv[i], "--input=", 8)) {
            if (!strcmp(argv[i], "-i")) {  
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    args.input_file = argv[i + 1];
                    ++i;
                } else {
                    return PrintError("Error");
                }
            } else { 
                args.input_file = argv[i] + 8;
            }

        } else if (!strcmp(argv[i], "-o") || !strncmp(argv[i], "--output=", 9)) {
            if (!strcmp(argv[i], "-o")) {  
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    args.output_dir = argv[i + 1];
                    ++i;
                } else {
                    return PrintError("Error");
                }
            } else { 
                args.output_dir = argv[i] + 9;
            }

        } else if (!strcmp(argv[i], "-m") || !strncmp(argv[i], "--max-iter=", 11)) {
            if (!strcmp(argv[i], "-m")) { 
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    if (!ParseUint64(argv[i + 1], args.max_iterations)) {
                        return PrintError("Error");
                    }
                    ++i;
                } else {
                    return PrintError("Error");
                }
            } else { 
                if (!ParseUint64(argv[i] + 11, args.max_iterations)) {
                    return PrintError("Error");
                }
            }

        } else if (!strcmp(argv[i], "-f") || !strncmp(argv[i], "--freq=", 7)) {
            if (!strcmp(argv[i], "-f")) { 
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    if (!ParseUint64(argv[i + 1], args.frequency)) {
                        return PrintError("Error");
                    }
                    ++i;
                } else {
                    return PrintError("Error");
                }
            } else { 
                if (!ParseUint64(argv[i] + 7, args.frequency)) {
                    return PrintError("Error");
                }
            }
        }
    }

    if (args.input_file == nullptr) {
        return false;
    }
    if (args.output_dir == nullptr) {
        return false;
    }

    return true;  
}
