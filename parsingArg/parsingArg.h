#pragma once
#include <iostream>

struct Arguments {
    const char* input_file;    
    const char* output_dir;     
    uint64_t max_iterations;    
    uint64_t frequency;       
};

bool ParseUint64(const char* str, uint64_t& result);
bool PrintError(const char* message);
bool ParseArguments(int argc, char** argv, Arguments& args);
