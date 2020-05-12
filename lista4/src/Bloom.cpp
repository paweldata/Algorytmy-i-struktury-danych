#include <random>
#include <utility>
#include <fstream>

#include "Bloom.h"

struct Hash {
    std::vector<uint32_t> numbers;

    explicit Hash(std::vector<uint32_t> numbers) {
        this->numbers = std::move(numbers);
    }

    Hash() = default;

    uint32_t hash(std::string str) {
        uint32_t result = 0;
        int size = this->numbers.size();
        int stringSize = str.size();

        for (int i = 0; i < size; i++)
            result += numbers[i] * str[i % stringSize];

        return result;
    }
};

Bloom::Bloom() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint32_t > rand(0, UINT32_MAX);

    this->hashFunctions = std::vector<Hash>(this->hashAmount);

    for (int i = 0; i < this->hashAmount; i++) {
        std::vector<uint32_t> numbers(32);

        for (int j = 0; j < 32; j++)
            numbers[j] = rand(generator);

        this->hashFunctions[i] = Hash(numbers);
    }
}

void Bloom::insert(std::string elem) {
    elem = this->cleanElem(elem);

    if (elem.empty())
        return;

    for (Hash hash : this->hashFunctions)
        this->array.set(hash.hash(elem) % Bloom::arraySize);

    this->maxSize = std::max(++this->size, this->maxSize);
}

void Bloom::load(std::string filename) {
    std::ifstream file(filename);
    std::string elem;

    if (!file.is_open()) {
        printf("File %s not exists\n", filename.c_str());
        return;
    }

    while (file >> elem)
        this->insert(elem);
}

void Bloom::deleteElem(std::string elem) {}

bool Bloom::find(std::string elem) {
    for (Hash hash : this->hashFunctions)
         if (!this->array.test(hash.hash(elem) % Bloom::arraySize))
             return false;

     return true;
}

std::string Bloom::min() {
    return "";
}

std::string Bloom::max() {
    return "";
}

std::string Bloom::successor(std::string elem) {
    return "";
}

void Bloom::inorder() {
    printf("\n");
}

int Bloom::getSize() {
    int result = 0;

    for (int i = 0; i < Bloom::arraySize; i++)
        result += this->array.test(i);

    return result;
}

int Bloom::getMaxSize() {
    int result = 0;

    for (int i = 0; i < Bloom::arraySize; i++)
        result += this->array.test(i);

    return result;
}
