#include "parsingFile.h"

SandPile ParseFile(const char*& input_filename) {

    SandPile sandpile{};
    std::ifstream file(input_filename);
    if (!file.is_open()) {
        std::cout << "Error";
        return sandpile;
    }

    Point current{};

    auto** tmp = new uint64_t*[INT16_MAX];
    for (uint16_t i = 0; i < INT16_MAX; i++) {
        tmp[i] = new uint64_t [INT16_MAX];
    }
    for (int16_t i = 0; i < INT16_MAX; i++) {
        for (int16_t j = 0; j < INT16_MAX; j++) {
            tmp[i][j] = 0;
        }
    }

    while (file >> current.x >> current.y >> current.sand) {
        if (current.x + 1 > sandpile.width) {
            sandpile.width += current.x;
        }
        if (current.y + 1 > sandpile.height) {
            sandpile.height += current.y;
        }
        tmp[current.x][current.y] = current.sand;
    }

    if (sandpile.width < 1) {
        sandpile.width = 1;
    }
    if (sandpile.height < 1) {
        sandpile.height = 1;
    }

    sandpile.field = new uint64_t*[sandpile.width];
    for (int16_t i = 0; i < sandpile.width; i++) {
        sandpile.field[i] = new uint64_t[sandpile.height];
    }
    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            sandpile.field[i][j] = tmp[i][j];
        }
    }

    for (int16_t i = 0; i < INT16_MAX; i++) {
        delete[] tmp[i];
    }
    delete[] tmp;

    file.close();


    return sandpile;
}

bool stability(SandPile& sandPile) {

    for (int16_t j = 0; j < sandPile.height; j++) {
        for (int16_t i = 0; i < sandPile.width; i++) {
                if (sandPile.field[i][j] >= 4) {
                    return false;
                }
            }
        }

    return true;
}

uint64_t** AddColumnLeft(uint64_t**& matrix, int16_t width, int16_t height) {

    width = static_cast<int16_t>(width + 1);

    auto** new_matrix = new uint64_t*[width];

    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }

    for (int16_t i = 1; i < width; i++) {
        for (int16_t j = 0; j < height; j++) {
            new_matrix[i][j] = matrix[i - 1][j];
        }
    }

    for (int16_t j = 0; j < height; j++) {
        new_matrix[0][j] = 0;
    }

    for (int16_t i = 0; i < width - 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

uint64_t** AddColumnRigth(uint64_t**& matrix, int16_t width, int16_t height) {

    width = static_cast<int16_t>(width + 1);

    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }

    for (int16_t i = 0; i < width - 1; i++) {
        for (int16_t j = 0; j < height; j++) {
            new_matrix[i][j] = matrix[i][j];
        }
    }
    for (int16_t j = 0; j < height; j++) {
        new_matrix[width - 1][j] = 0;
    }

    for (int16_t i = 0; i < width - 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

uint64_t** AddLineAbove(uint64_t**& matrix, int16_t width, int16_t height) {

    height = static_cast<int16_t>(height + 1);

    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }

    for (int16_t i = 0; i < width; i++) {
        for (int16_t j = 1; j < height; j++) {
            new_matrix[i][j] = matrix[i][j - 1];
        }
    }

    for (int16_t i = 0; i < width; i++) {
        new_matrix[i][0] = 0;
    }

    for (int16_t i = 0; i < width; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;

    return new_matrix;
}

uint64_t** AddLineBelow(uint64_t**& matrix, int16_t width, int16_t height) {

    height = static_cast<int16_t>(height + 1);

    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }

    for (int16_t i = 0; i < width; i++) {
        for (int16_t j = 0; j < height - 1; j++) {
            new_matrix[i][j] = matrix[i][j];
        }
    }

    for (int16_t i = 0; i < width; i++) {
        new_matrix[i][height - 1] = 0;
    }

    for (int16_t i = 0; i < width; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

void scattering(SandPile& sandpile) {

    auto** matrix = new uint64_t*[sandpile.width];
    for (int16_t i = 0; i < sandpile.width; i++) {
        matrix[i] = new uint64_t[sandpile.height];
    }

    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            matrix[i][j] = sandpile.field[i][j];
        }
    }

    int32_t width_left = 0;
    int32_t height_up = 0;
    int32_t width_right = 0;
    int32_t height_down = 0;

    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            if (sandpile.field[i][j] >= 4) {
                if (i + 1 >= sandpile.width + width_right) {
                    matrix = AddColumnRigth(matrix, static_cast<int16_t>(sandpile.width + width_left + width_right), 
                                            static_cast<int16_t>(sandpile.height + height_up + height_down));
                    width_right++;
                }
                if (j + 1 >= sandpile.height + height_down) {
                    matrix = AddLineBelow(matrix, static_cast<int16_t>(sandpile.width + width_left + width_right), 
                                            static_cast<int16_t>(sandpile.height + height_up + height_down));
                   height_down++;
                }
                if (j - 1 + height_up < 0) {
                    matrix = AddLineAbove(matrix, static_cast<int16_t>(sandpile.width + width_left + width_right), 
                                            static_cast<int16_t>(sandpile.height + height_up + height_down));
                    height_up++;
                }
                if (i - 1 + width_left < 0) {
                    matrix = AddColumnLeft(matrix, static_cast<int16_t>(sandpile.width + width_left + width_right), static_cast<int16_t>(sandpile.height + height_up + height_down));
                    width_left++;
                }
                matrix[i + width_left][j + height_up] -= 4;
                matrix[i + 1 + width_left][j + height_up]++;
                matrix[i + width_left][j - 1 + height_up]++;
                matrix[i - 1 + width_left][j + height_up]++;
                matrix[i + width_left][j + 1 + height_up]++;
            }
        }
    }

    sandpile.width = static_cast<int16_t>(sandpile.width + width_left + width_right);
    sandpile.height = static_cast<int16_t>(sandpile.height + height_up + height_down);

    for (int16_t i = 0; i < static_cast<int16_t>(sandpile.width - width_left - width_right); i++) {
        delete[] sandpile.field[i];
    }
    delete[] sandpile.field;

    sandpile.field = new uint64_t*[sandpile.width];
    for (int16_t i = 0; i < sandpile.width; i++) {
        sandpile.field[i] = new uint64_t[sandpile.height];
    }

    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            sandpile.field[i][j] = matrix[i][j];
        }
    }

    for (int16_t i = 0; i < sandpile.width; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}