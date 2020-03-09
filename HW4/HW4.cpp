#include <iostream>
#include <set>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include "Timer.cpp"

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
    const int size = 300000;
    std::set<size_t> set;
    srand(time(0));

    struct fields {
        int one;
        double two;
        float three;
        long long int four;

        fields() {
            one = rand();
            two = rand() * 0.993431;
            three = rand() * 1.12345;
            four = rand();
        }
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

    std::array<fields*, size> arr_of_structs;
    for (int i = 0; i < size; ++i) {
        arr_of_structs[i] = new fields;
        set.insert(MyHash()(*arr_of_structs[i]));
        delete arr_of_structs[i];
    }

    std::cout << size - set.size() << std::endl;
}

int main() {
    //number_one();
    number_three();
}

