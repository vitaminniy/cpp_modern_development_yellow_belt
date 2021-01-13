#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Person {
public:
  Person(const std::string &name, const std::string &job)
      : Name(name), Job(job) {}

  virtual void Walk(const std::string &destination) const {
    std::cout << Who() << " walks to: " << destination << std::endl;
  }

  const std::string Name;
  const std::string Job;

protected:
  inline std::string Who() const { return Job + ": " + Name; }
};

class Student : public Person {
public:
  Student(const std::string &name, const std::string &favouriteSong)
      : Person(name, "Student"), FavouriteSong(favouriteSong) {}

  void Learn() { std::cout << Who() << " learns" << std::endl; }

  void Walk(const std::string &destination) const override {
    Person::Walk(destination);
    SingSong();
  }

  void SingSong() const {
    std::cout << Who() << " sings a song: " << FavouriteSong << std::endl;
  }

private:
  std::string FavouriteSong;
};

class Teacher : public Person {
public:
  Teacher(const std::string &name, const std::string &subject)
      : Person(name, "Teacher"), Subject(subject) {}

  void Teach() const {
    std::cout << Who() << " teaches: " << Subject << std::endl;
  }

private:
  const std::string Subject;
};

class Policeman : public Person {
public:
  Policeman(const std::string &name) : Person(name, "Policeman") {}

  void Check(const Person &p) const {
    std::cout << Who() << " checks " << p.Job << ". " << p.Job
              << "'s name is: " << p.Name << std::endl;
  }
};

void VisitPlaces(const Person &person, const std::vector<std::string> &places) {
  for (const auto &p : places) {
    person.Walk(p);
  }
}

int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});

  return 0;
}
