#include <iostream>
#include <string>

class Toy {
public:
    Toy(const std::string& name) : name(name) {}

    std::string getName() {
        return name;
    }

    ~Toy() {
        std::cout << "Toy " << name << " was dropped." << std::endl;
    }

private:
    std::string name;
};

class shared_ptr_toy {
public:
    shared_ptr_toy(Toy* ptr = nullptr) {
        this->ptr = ptr;
        this->count = (ptr ? new int(1) : nullptr);
    }

    shared_ptr_toy(const shared_ptr_toy& other) {
        this->ptr = other.ptr;
        this->count = other.count;

        if (count) {
            ++(*count);
        }
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& other) {
        if (this != &other) {
            reset();
            this->ptr = other.ptr;
            this->count = other.count;
            if (count) {
                ++(*count);
            }
        }
        return *this;
    }

    ~shared_ptr_toy() {
        reset();
    }

    Toy* get() const {
        return ptr;
    }

    std::string getToyName() const {
        return ptr ? ptr->getName() : "No Toy";
    }

    int use_count() const {
        return count ? *count : 0;
    }

    void reset() {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
        }
        ptr = nullptr;
        count = nullptr;
    }

private:
    Toy* ptr;
    int* count;
};

shared_ptr_toy make_shared_toy(const std::string& name) {
    return shared_ptr_toy(new Toy(name));
}

class Dog {
public:
    void getToy(shared_ptr_toy toy) {
        if (this->toy.getToyName() == toy.getToyName()) {
            std::cout << "I already have this toy." << std::endl;
        } else if (toy.use_count() > 1) {
            std::cout << "Another dog is playing with this toy." << std::endl;
        } else {
            this->toy = toy;
            std::cout << "Dog picked up the toy: " << toy.getToyName() << std::endl;
        }
    }

    void dropToy() {
        if (!toy.get()) {
            std::cout << "Nothing to drop." << std::endl;
        } else {
            std::cout << "Dog dropped the toy: " << toy.get()->getName() << std::endl;
            toy.reset();
        }
    }

private:
    shared_ptr_toy toy;
};

int main() {
    shared_ptr_toy toy_01 = make_shared_toy("ball");
    shared_ptr_toy toy_02(toy_01);
    shared_ptr_toy toy_03 = make_shared_toy("duck");

    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links: " << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links: " << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links: " << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links: " << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links: " << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links: " << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    toy_01.reset();
    std::cout << toy_01.getToyName() << " links: " << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links: " << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links: " << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    return 0;
}