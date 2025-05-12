#include <iostream>
#include <string>
#include <vector>                // Needed for using std::vector

using namespace std;             // Prevents us from having to use "std::"

class Diet {
public:
    vector<string> food;

    Diet(const vector<string>& foodList) : food(foodList) {}                     // Constructor to intitialize object diet
                                                                                 // modify vector with foodlist; call with food
};
class Habitat {
public:
    vector<string> landscaping;

    Habitat(const vector<string>& terrain) : landscaping(terrain) {}             // constructor to intitialize obj habitat
};

class Animal {
protected:                                                                      // protected so derived classes can access but outside ones cant
    string name;
    int age;
    string species;                                                              // intitialized as a const string down in constructor
    Diet diet;                                                                    // composition invoking the obj diet
    Habitat habitat;                                                               // composition invoking the obj habitat

    Animal(string name, int age, const string& species, const Diet& dietObj, const Habitat& habitatObj)   // Constructor to inntitalize and can reference using this pointer
    : diet(dietObj), habitat(habitatObj) {                                                                // composition invoking the obj habitat and diet
    this->name = name;
    this->age = age;
    this->species = species;
}     
                              

public:
    virtual void makeSound() const = 0;                                                                        // virtual functions that can be over ridden in derived class to have its own sound
    virtual void eat() const = 0;                                                                       // problems later in code requred to update to const=0 to fix

    virtual void displayInfo() final {                                                                  // displays all the animal infromation and stops derived classes from overiding anything
      cout << "Name: " << this->name << endl;
      cout << "Age: " << this->age << endl;
      cout << "Species: " << this->species << endl;

      cout << "Diet: ";                                                                                  // stolen from the car example for loop to iterate through vector string in diet
      for (const auto& item : this->diet.food) {
          cout << item << ", ";
      }
      cout << endl;

      cout << "Habitat: ";                                                                               // stolen from the car example, for loop to iterate through vector string of habitat
      for (const auto& item : this->habitat.landscaping) {
          cout << item << ", ";
      }
      cout << endl;
  }

                                                                          
};

class Elephant : public Animal {                                                              // derived class of Elephant
public:
    Elephant(string name, int age, const Diet& diet, const Habitat& habitat)
        : Animal(name, age, "Elephant", diet, habitat) {}

    void makeSound() const override {                                                               // calls function makesound and defiens it for elephants
        cout << "VRRRRRRRRRRR" << endl;
    }

    void eat() const override {                                                                    // calls function eats and tells you what time elephants eat at
        cout << "This animal eats at 12:01 pm." << endl;
    }
};

class Lion : public Animal {                                                                  //derived class from animal base class
public:
    Lion(string name, int age, const Diet& diet, const Habitat& habitat)
        : Animal(name, age, "Lion", diet, habitat) {}

    void makeSound() const override {
        cout << "ROOOOAAR" << endl;
    }

    void eat() const override {
        cout << "This animal eats at 8:00 am and 5:30 pm." << endl;
    }
};
void makeAllAnimalsSound(const vector<Animal*>& zoo) {
  cout << "\nAll animals making their sound:\n";                          
  for (const Animal* animal : zoo) {
      animal->makeSound();
  }
}

int main() {                                                                                    // Finally the main function
    // Elephants
    vector<string> elephantFood1 = { "hay", "watermelon", "bamboo" };                             // couldnt get to work with jsut string made a vector for diet and habitat from car example
    vector<string> elephantTerrain1 = { "pond", "large rocks" };                                  // defines what elephant 1 eats and lives in if seperate animals of the same species eat differently or are in different enclosures
                                                                                                  
    vector<string> elephantFood2 = { "grass", "leaves", "bananas" };
    vector<string> elephantTerrain2 = { "mud pit", "trees", "shade area" };

    Elephant* dumbo =  new Elephant("Dumbo", 35, Diet(elephantFood1), Habitat(elephantTerrain1));        // a pointer to a new elphant namesd dumbo with attributes
    Elephant* horton = new Elephant("Horton", 28, Diet(elephantFood2), Habitat(elephantTerrain2));      // a pointer to the 2nd elephant named horton with his attributes

    // Lions
    vector<string> lionFood1 = { "meat", "bones" };                                                    // same as elephant just with lions
    vector<string> lionTerrain1 = { "savannah", "tall grass","moat" };

    vector<string> lionFood2 = { "chicken", "beef" };
    vector<string> lionTerrain2 = { "rock ledge", "dry plains","moat" };

    Lion* simba = new Lion("Simba", 7, Diet(lionFood1), Habitat(lionTerrain1));                       // use of class* was difficult to understant the syntax at first
    Lion* nala = new Lion("Nala", 6, Diet(lionFood2), Habitat(lionTerrain2));                         // could not get  use of a new object

    
    vector<Animal*> animals = { dumbo, horton, simba, nala };                                       // Store all animals in a polymorphic vector

    for (Animal* animal : animals) {                                                               // iterates through each pointer in the vector and runs the 3 functions
        animal->displayInfo();
        animal->makeSound();
        animal->eat();
      
    }

    makeAllAnimalsSound(animals);                                                           // calls polymorphic function

    return 0;
}


// This was an absolute nightmare fueled by caffeine and regret at procrastinating. I still dont quite understand the class* obj to point to stuff, but I worked out the syntax through examples
//