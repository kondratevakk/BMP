#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include "parsingArg/parsingArg.h"
#include "bmp/bmp.h"

int main(int argc, char** argv){

    Arguments arg = {};
    bool d = ParseArguments(argc, argv, arg);
    int count = 0;
    if(!ParseArguments){
        std::cout<<"ERROR";
    }

    SandPile sandpile = ParseFile(arg.input_file);

    while(count!=arg.max_iterations){
        scattering(sandpile);
        if(stability(sandpile)){
            break;
        }
        if(count % arg.frequency == 0){
            saveBMP(arg.output_dir, sandpile);
        }
        count ++;
    }

    saveBMP(arg.output_dir, sandpile);

    for(int i = 0; i < sandpile.height; ++i){
        delete[] sandpile.field[i];
    }
        delete[] sandpile.field;

}
