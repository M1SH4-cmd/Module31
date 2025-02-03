#include <iostream>
#include <string>

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

//    virtual ~Dog() {
//        lovelyToy = nullptr;
//        delete lovelyToy;
//        std::cout << "Dog destructor called" << std::endl;
//    }


//    Dog(const Dog& other)
//    {
//        name = other.name;
//        age = other.age;
//        lovelyToy = new Toy(*other.lovelyToy);
//    }
//
//    Dog& operator=(const Dog& other)
//    {
//        if (this == &other) return *this;
//        name = other.name;
//        age = other.age;
//
//        if (lovelyToy != nullptr) delete lovelyToy;
//        lovelyToy = new Toy(*other.lovelyToy);
//        return *this;
//    }

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

    Animal *d = new Dog(9);

    delete d;
    return 0;
}
