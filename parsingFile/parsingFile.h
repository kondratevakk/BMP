#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

struct SandPile {
    uint64_t** field;
    int16_t width;
    int16_t height;

    SandPile(int16_t _width = 0, int16_t _height = 0) : width(_width), height(_height), field(nullptr) {}
};

struct Point { 
    int16_t x;
    int16_t y;
    uint64_t sand;
};

SandPile ParseFile(const char*& input_filename);

bool stability(SandPile& sandpile);

uint64_t** AddLineAbove(uint64_t**& matrix, int16_t width, int16_t height);

uint64_t** AddLineBelow(uint64_t**& matrix, int16_t width, int16_t height);

uint64_t** AddColumnRigth (uint64_t**& matrix, int16_t width, int16_t height);

uint64_t** AddColumnLeft (uint64_t**& matrix, int16_t width, int16_t height);

void scattering (SandPile& sandpile);