#include <home_animal_factory.h>
#include <wild_animal_factory.h>
#include <gtest/gtest.h>


TEST(AnimalTest, WildAnimalFactoryHorse) {
  WildAnimalFactory factory;
  Animal* animal = factory.create("horse");
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("horse") == 1);
  EXPECT_TRUE(animal->type() == "wild");
  EXPECT_EQ(animal->count(), 1);
  EXPECT_EQ(animal->say(), "I am a wild horse, I have 4 legs and I feeded 0 kg");
  animal->eat(100);
  EXPECT_EQ(animal->say(), "I am a wild horse, I have 4 legs and I feeded 100 kg");
  delete animal;
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("horse") == 0);
}

TEST(AnimalTest, WildAnimalFactoryKenguru) {
  WildAnimalFactory factory;
  Animal* animal = factory.create("kenguru");
  Animal* animal2 = factory.create("kenguru");
  animal2->eat(1);
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("horse") == 0);
  EXPECT_EQ(animal->count(), 1);
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("kenguru") == 2);  
  EXPECT_EQ(animal2->count(), 2);
  EXPECT_EQ(animal->type(), "wild");
  EXPECT_EQ(animal2->type(), "wild");
  EXPECT_EQ(animal->say(), "I am a wild kenguru, I like to jump and I feeded 0 kg");
  EXPECT_EQ(animal2->say(), "I am a wild kenguru, I like to jump and I feeded 1 kg");
  delete animal;
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("kenguru") == 1);  
  delete animal2;
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("kenguru") == 0);  
}

TEST(AnimalTest, WildAnimalFactoryDog) {
  WildAnimalFactory factory;
  Animal* animal = factory.create("dog");
  EXPECT_TRUE(animal == nullptr);
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("dog") == 0);
}


TEST(AnimalTest, HomeAnimalDog) {
  HomeAnimalFactory factory;
  Animal* animal = factory.create("dog");
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("dog") == 1);
  EXPECT_EQ(animal->count(), 1);
  EXPECT_EQ(animal->type(), "home");
  EXPECT_EQ(animal->say(), "I am a home dog, I am hungry and I feeded 0 kg");
  animal->eat(10);
  EXPECT_EQ(animal->say(), "I am a home dog, I am hungry and I feeded 10 kg");
  animal->eat(10);
  EXPECT_EQ(animal->say(), "I am a home dog, I am hungry and I feeded 20 kg");
  animal->eat(10);
  EXPECT_EQ(animal->say(), "I am a home dog, I not hungry any more and I feeded 30 kg");
  delete animal;
}

TEST(AnimalTest, HomeAnimalCat) {
  HomeAnimalFactory factory;
  Animal* animal = factory.create("cat");
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("cat") == 1);
  EXPECT_EQ(animal->count(), 1);
  EXPECT_EQ(animal->type(), "home");
  EXPECT_EQ(animal->say(), "I am a home cat, I am lazy and I feeded 0 kg");
  delete animal;
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("cat") == 0);
}

TEST(AnimalTest, ImaginaryAnimal) {
  HomeAnimalFactory home_factory;
  Animal* animal = home_factory.create("imaginary");
  ASSERT_FALSE(animal == nullptr);
  EXPECT_EQ(animal->type(), "imaginary");
  EXPECT_EQ(animal->say(), "I don't follow the rules");
  EXPECT_EQ(animal->count(), 1);
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("imaginary") == 1);
  delete animal;
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("imaginary") == 0);
}

TEST(AnimalTest, ImaginaryAnimalOnWildFactory) {
  WildAnimalFactory home_factory;
  Animal* animal = home_factory.create("imaginary");
  ASSERT_FALSE(animal == nullptr);
  EXPECT_EQ(animal->type(), "imaginary");
  EXPECT_EQ(animal->say(), "I don't follow the rules");
  EXPECT_EQ(animal->count(), 1);
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("imaginary") == 1);
  delete animal;
  EXPECT_TRUE(AnimalCounter::instance().count_of_animals("imaginary") == 0);
}



