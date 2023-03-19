

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <stdexcept>

#include "Utils.h"



std::string Utils::readFileToString(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::ostringstream content;
    content << inFile.rdbuf();
    return content.str();
}

void Utils::writeBoolVectorToFile(const std::string &filename, const std::vector<bool> &data) {
    std::ofstream outFile(filename, std::ios::binary);
    for (size_t i = 0; i < data.size(); i += 8) {
        char byte = 0;
        for (size_t j = 0; j < 8 && i + j < data.size(); ++j) {
            byte |= data[i + j] << (7 - j);
        }
        outFile.put(byte);
    }
}

std::vector<bool> Utils::readBoolVectorFromFile(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::binary);
    std::vector<bool> data;
    char byte;
    while (inFile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            data.push_back((byte >> i) & 1);
        }
    }
    return data;
}

void Utils::writeStringToFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename, std::ios::binary);
    outFile.write(content.data(), content.size());
}

std::vector<bool> generateRandomBitArray(size_t size) {
    std::vector<bool> bit_array(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (size_t i = 0; i < size; ++i) {
        bit_array[i] = dis(gen);
    }

    return bit_array;
}

void Utils::addIntToBoolVector(std::vector<bool> &bool_vector, int value) {
    for (int i = HEADER_INT_LENGTH - 1; i >= 0; --i) {
        bool bit = (value >> i) & 1;
        bool_vector.push_back(bit);
    }
}


std::string Utils::generateRandomString(size_t length) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    std::string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        result.push_back(alphanum[dis(gen)]);
    }

    return result;
}

std::vector<int> Utils::boolVectorToIntVector(const std::vector<bool> &bool_vector) {
    std::vector<int> int_vec;
    size_t vector_size = bool_vector.size();

    for (size_t i = 0; i < vector_size; i += HEADER_INT_LENGTH) {
        int value = 0;

        for (int j = 0; j < HEADER_INT_LENGTH && i + j < vector_size; ++j) {
            value |= (bool_vector[i + j] << (HEADER_INT_LENGTH - 1 - j));
        }

        int_vec.push_back(value);
    }

    return int_vec;
}


//void testReadWriteBitStreamToFile() {
//    std::vector<bool> bit_stream = generateRandomBitArray(300);
//    std::string output_file = "test_output.bin";
//
//    Utils::writeBitStreamToFile(bit_stream, output_file);
//    std::vector<bool> read_bit_stream = Utils::readBitStreamFromFile(output_file);
//
//    assert(bit_stream == read_bit_stream);
//    std::cout << "Test passed: writeBitStreamToFile and readBitStreamFromFile work correctly." << std::endl;
//}
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//
//    testReadWriteBitStreamToFile();
//
//    return 0;
//}



