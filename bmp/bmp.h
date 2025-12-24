#pragma once
#include <iostream>
#include <fstream>
#include "../parsingFile/parsingFile.h"

const char* path(const char*& path);
void saveBMP(const char*& filename, SandPile& sandpile);