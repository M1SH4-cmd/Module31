#include <iostream>
#include <memory>

class Toy
{
public:
    Toy(std::string name)
    {
        this -> name = name;
    }
    Toy() : Toy("default_toy_name") {}

    ~Toy()
    {
        std::cout << "Toy " << name << " was dropped" << std::endl;
    }

    std::string getName() const
    {
        return name;
    }
private:
    std::string name;
};

class Dog
{
private:
    std::string name;
    int age;
    std::shared_ptr<Toy> lovelyToy;
public:
    Dog(std::string name, int age)
    {
        this -> name = name;
        this -> age = age;
    }
    Dog() : Dog ("default_dog_name", 0) {}
    Dog(std::string name) : Dog(name, 0) {}
    Dog(int age) : Dog("default_dog_name", age) {};

    void getToy(std::shared_ptr<Toy> toy) {
        if (lovelyToy == toy) {
            std::cout << "I already have this toy." << std::endl;
        } else if (toy.use_count() > 1) {
            std::cout << "Another dog is playing with this toy." << std::endl;
        } else {
            lovelyToy = toy;
            std::cout << "Dog picked up the toy: " << lovelyToy->getName() << std::endl;
        }
    }

    void dropToy()
    {
        if (!lovelyToy) {
            std::cout << "Nothing to drop" << std::endl;
        } else {
            std::cout << "Dropped toy: " << lovelyToy->getName() << std::endl;
            lovelyToy.reset();
        }
    }
};


int main() {
    auto toy1 = std::make_shared<Toy>("Ball");
    auto toy2 = std::make_shared<Toy>("Frisbee");

    Dog dog1;
    Dog dog2;

    dog1.getToy(toy1);
    dog1.getToy(toy1);
    dog2.getToy(toy1);

    dog1.dropToy();
    dog2.getToy(toy1);

    dog2.dropToy();
    dog2.dropToy();

    return 0;
}