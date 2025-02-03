#include <iostream>
#include <string>
#include <memory>

class Toy
{
public:
    Toy(std::string name)
    {
        this -> name = name;
    }
    Toy() : Toy("default_toy_name") {}
private:
    std::string name;
};

class smart_ptr_toy
{
private:
    Toy* obj;
public:
    smart_ptr_toy()
    {
        obj = new Toy("some_name");
    }

    smart_ptr_toy(std::string name)
    {
        obj = new Toy(name);
    }

    smart_ptr_toy(const smart_ptr_toy& other)
    {
        obj = new Toy(*other.obj);
    }

    virtual ~smart_ptr_toy()
    {
        delete obj;
    }

    smart_ptr_toy& operator=(const smart_ptr_toy& other)
    {
        if (this == &other) return *this;
        if (this != nullptr) delete obj;
        obj = new Toy(*other.obj);
        return *this;
    }

};

class Dog
{
private:
    std::string name;
    int age;
    std::shared_ptr<Toy> lovelyToy;
    std::weak_ptr<Dog> bf;

public:
    Dog(std::string name, std::shared_ptr<Toy> toy, int age) : lovelyToy(toy)
    {
        this -> name = name;
        this -> age = age;
    }
    Dog() : Dog ("default_dog_name", std::make_shared<Toy>("default_toy_name"), 0) {}
    Dog(std::string name) : Dog(name, std::make_shared<Toy>("default_toy_name"), 0) {}
    Dog(int age) : Dog("default_dog_name", std::make_shared<Toy>("default_toy_name"), age) {};

    void copyLovelyToy(const Dog& other)
    {
        lovelyToy = other.lovelyToy;
    }

    void setBF(std::shared_ptr<Dog> bf)
    {
        this -> bf = bf;
    }


};


int main() {

    std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");
    std::shared_ptr<Toy> rubberBone = std::make_shared<Toy>("Rubber bone");


    std::shared_ptr<Dog> a = std::make_shared<Dog>("Scharick", ball, 10);
    std::shared_ptr<Dog> b = std::make_shared<Dog>("Bobik", rubberBone, 12);
    std::shared_ptr<Dog> c = std::make_shared<Dog>("Snowie", ball, 17);


    a ->setBF(b);
    b ->setBF(a);




    return 0;
}
