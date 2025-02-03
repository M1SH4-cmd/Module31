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

class Animal
{
public:
    virtual ~Animal()
    {
        std::cout << "Animal destructor called" << std::endl;
    }

    virtual void voice() = 0;
};

class Dog : public Animal
{
private:
    std::string name;
    int age;
    smart_ptr_toy lovelyToy;

public:
    Dog(std::string name, std::string toyName, int age) : lovelyToy(toyName)
    {
        this -> name = name;
        this -> age = age;
//       this -> lovelyToy = new Toy(toyName);
    }
    Dog() : Dog ("default_dog_name", "default_toy_name", 0) {}
    Dog(std::string name) : Dog(name, "default_toy_name", 0) {}
    Dog(int age) : Dog("default_dog_name", "default_toy_name", age) {};


    void voice() override
    {
        std::cout << "Bark!" << std::endl;
    }

};

class OperaDog : public Dog
{
    void voice() override final
    {
        std::cout << "BaaaAAaAaAAAahhhrk!" << std::endl;
    }
};

int main() {

    std::unique_ptr<Dog> dogptr = std::make_unique<Dog>("Sharick", "Ball", 5);
    return 0;
}
