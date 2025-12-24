#include "bmp.h"

const char* path(const char*& path) {
    static int pictures = 0;
    pictures++;

    size_t path_len = std::strlen(path);
    size_t suffix_len = std::snprintf(nullptr, 0, "/picturs_%d.bmp", pictures);

    static char new_path[1024];  
    if (path_len + suffix_len + 1 > sizeof(new_path)) {
        std::cout << "Path is too long!" << std::endl;
        return nullptr;
    }

    std::strcpy(new_path, path);

    std::sprintf(new_path + path_len, "/picturs_%d.bmp", pictures);

    return new_path;
}

void saveBMP(const char*& output_file, SandPile& sandpile){

    std::ofstream bmp_file;
    bmp_file.open(path(output_file), std::ios_base::binary);

    if(!bmp_file){
        std::cout<<"ERROR";
    }

    uint8_t bmp_file_info_long[4]; 
    uint8_t bmp_file_info[2];

    const int32_t file_header = 14; 
    const int32_t info_header = 40;
    const int32_t colour_table = 20; 
    const int32_t number_of_bits = 4;
    const int32_t number_of_colours = 5;

    bmp_file_info[0] = 'B'; 
    bmp_file_info[1] = 'M';
    bmp_file << bmp_file_info[0] << bmp_file_info[1];

    uint16_t image_height = sandpile.height;
    if (image_height % 8 != 0) {
        image_height = image_height + 8 - (image_height % 8);
    }

    int64_t size = file_header + info_header + colour_table + (image_height * sandpile.width) / 2; 
    bmp_file_info_long[3] = static_cast<uint8_t>(size >> 24);
    size = size % (256 * 256 * 256);
    bmp_file_info_long[2] = static_cast<uint8_t>(size >> 16);
    size = size % (256 * 256);
    bmp_file_info_long[1] = static_cast<uint8_t>(size >> 8);
    size = size % (256 * 256);
    bmp_file_info_long[0] = static_cast<uint8_t>(size);
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info[0] = 0;
    bmp_file_info[1] = 0;
    bmp_file << bmp_file_info[0] << bmp_file_info[1]; 
    bmp_file << bmp_file_info[0] << bmp_file_info[1]; 

    bmp_file_info_long[0] = static_cast<uint8_t>(file_header + info_header + colour_table);
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = static_cast<uint8_t>(info_header); 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    int32_t tmp;
    tmp = sandpile.height;
    bmp_file_info_long[3] = static_cast<uint8_t>(tmp >> 24);
    tmp = tmp % (256 * 256 * 256);
    bmp_file_info_long[2] = static_cast<uint8_t>(tmp >> 16);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[1] = static_cast<uint8_t>(tmp >> 8);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[0] = static_cast<uint8_t>(tmp);
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    tmp = sandpile.width;
    bmp_file_info_long[3] = static_cast<uint8_t>(tmp >> 24);
    tmp = tmp % (256 * 256 * 256);
    bmp_file_info_long[2] = static_cast<uint8_t>(tmp >> 16);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[1] = static_cast<uint8_t>(tmp >> 8);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[0] = static_cast<uint8_t>(tmp);
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info[0] = 1;
    bmp_file_info[1] = 0;
    bmp_file << bmp_file_info[0] << bmp_file_info[1];

    bmp_file_info[0] = static_cast<uint8_t>(number_of_bits); 
    bmp_file_info[1] = 0;
    bmp_file << bmp_file_info[0] << bmp_file_info[1];

    bmp_file_info_long[0] = 0; 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = 0; 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = 0; 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = 0; 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = static_cast<uint8_t>(number_of_colours); 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = static_cast<uint8_t>(number_of_colours); 
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    uint8_t white[] = {255, 255, 255, 0};
    bmp_file << white[0] << white[1] << white[2] << white[3];
    uint8_t green[] = {0, 255, 0, 0};
    bmp_file << green[0] << green[1] << green[2] << green[3];
    uint8_t yellow[] = {0, 255, 255, 0};
    bmp_file << yellow[0] << yellow[1] << yellow[2] << yellow[3];
    uint8_t purple[] = {128, 0, 128, 0};
    bmp_file << purple[0] << purple[1] << purple[2] << purple[3];
    uint8_t black[] = {0, 0, 0, 0};
    bmp_file << black[0] << black[1] << black[2] << black[3];

    uint8_t two_pixels;
    uint8_t first;
    uint8_t second;

    for (int i = static_cast<int16_t>(sandpile.width - 1); i >= 0; --i) {
        for (uint16_t j = 0; j < image_height; j += 2) {
            if (j >= sandpile.height) {
                first = 0;
                second = 0;
            } else if ((j + 1 >= sandpile.height)) {
                if (sandpile.field[i][j] > 4) { 
                    first = 4;
                } else {
                    first = sandpile.field[i][j];
                }
                second = 0;
            } else {
                if (sandpile.field[i][j] > 4) {
                    first = 4;
                } else {
                    first = sandpile.field[i][j];
                }
                if (sandpile.field[i][j + 1] > 4) {
                    second = 4;
                } else {
                    second = sandpile.field[i][j + 1];
                }
            }
            two_pixels = (first << 4) + second;  
            bmp_file << two_pixels;
        }
    }

}