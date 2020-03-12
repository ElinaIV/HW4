#include <iostream>
#include <set>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include "Timer.cpp"
#include "Hash.h"


void number_one() {
    const int size = 100000;
    Timer t;
    int random_numbers[size];
    std::mt19937 gen;
    gen.seed(time(0));

    for (int i = 0; i < size; ++i) {
        random_numbers[i] = gen();
    }

    {
        std::set<int> set;
        t.restart();
        for (int i = 0; i < size; ++i) {
            set.insert(random_numbers[i]);
        }
        std::cout << "Insert of set: "; t.stop();
    }
    
    {
        std::array<int, size> arr;
        t.restart();
        for (int i = 0; i < size; ++i) {
            arr[i] = random_numbers[i];
        }
        std::sort(arr.begin(), arr.end()); std::cout << "Array: "; t.stop();
    }

    {
        std::vector<int> vec;
        t.restart();
        for (int i = 0; i < size; ++i) {
            vec.push_back(random_numbers[i]);
        }
        std::sort(vec.begin(), vec.end()); std::cout << "Vector: "; t.stop();
    }
}

void number_two() {
    /*
        boost::hash_value();
        хешировать числа с плавающей точкой (float) не есть хорошо, потому что флоаты не обладают
        идеальной точностью, например,
        мы записали в таблицу элемент с ключом sqrt(2), далее считаем sqrt(8)/2 (вроде бы тоже sqrt(2)),
        но элемент с таким ключом найти уже не получится, потому что эти числа неравны при очень хорошем
        приближении. Возможным решением может служить приведение флоатов к интам.
    */
}

void number_three() {
    const int size = 38;
    std::set<size_t> set;
    double delta = 147;

    struct fields {
        std::mt19937 gen { std::random_device()() };
        std::uniform_int_distribution<int> uid;

        int one = 0;
        double two = 0;
        float three = 0;
        long long int four = 0;
    };

    class MyHash {
    public:
        size_t operator()(const fields& f) const {
            size_t h1 = std::hash<int>()(f.one);
            size_t h2 = std::hash<double>()(f.two);
            size_t h3 = std::hash<float>()(f.three);
            size_t h4 = std::hash<long long int>()(f.four);

            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };

    auto str = new fields;
    for (int i = 0; i < size; ++i) {
        str->one += delta;
        for (int j = 0; j < size; ++j) {
            str->two += delta;
            for (int k = 0; k < size; ++k) {
                str->three += delta;
                for (int n = 0; n < size; ++n) {
                    str->four += delta;
                    set.insert(MyHash()(*str));
                }
            }
        }
    }

    std::cout << size*size*size*size - set.size() << std::endl;
}

void number_four() {
    const int size = 20000;
    char* random_chars[size];

    for (int i = 0; i < size; ++i) {
        random_chars[i] = gen_random();
    }

    std::set<unsigned int> setRS;
    std::set<unsigned int> setJS;
    std::set<unsigned int> setPJW;
    std::set<unsigned int> setELF;
    std::set<unsigned int> setBKDR;
    std::set<unsigned int> setSDBM;
    std::set<unsigned int> setDJB;
    std::set<unsigned int> setDEK;
    std::set<unsigned int> setAP;

    for (int i = 0; i < size; ++i) {
        setRS.insert(RSHash(random_chars[i], 6));
        setJS.insert(JSHash(random_chars[i], 6));
        setPJW.insert(PJWHash(random_chars[i], 6));
        setELF.insert(ELFHash(random_chars[i], 6));
        setBKDR.insert(BKDRHash(random_chars[i], 6));
        setSDBM.insert(SDBMHash(random_chars[i], 6));
        setDJB.insert(DJBHash(random_chars[i], 6));
        setDEK.insert(DEKHash(random_chars[i], 6));
        setAP.insert(APHash(random_chars[i], 6));
    }

    std::cout << "RS: " << size - setRS.size() << std::endl;
    std::cout << "JS: " << size - setJS.size() << std::endl;
    std::cout << "PJW: " << size - setPJW.size() << std::endl;
    std::cout << "ELF: " << size - setELF.size() << std::endl;
    std::cout << "BKDR: " << size - setBKDR.size() << std::endl;
    std::cout << "SDBM: " << size - setSDBM.size() << std::endl;
    std::cout << "DJB: " << size - setDJB.size() << std::endl;
    std::cout << "DEK: " << size - setDEK.size() << std::endl;
    std::cout << "AP: " << size - setAP.size() << std::endl;
}

int main() {
    //number_one();
    //number_two();
    number_three();
    //number_four();
}

