#include <cmath>
#include <iomanip>
#include <iostream>
#include <istream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

static constexpr double kPi = 3.14;
static const std::string kRect = "RECT";
static const std::string kTriangle = "TRIANGLE";
static const std::string kCircle = "CIRCLE";

struct Figure {
  virtual std::string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;

  Figure() = default;
  virtual ~Figure() = default;

  Figure(Figure &&) = delete;
  Figure(const Figure &) = delete;
  Figure &operator=(const Figure &) = delete;
  Figure &operator=(Figure &&) = delete;
};

class Rect : public Figure {
public:
  constexpr Rect(int width, int height)
      : perimeter(2 * width + 2 * height), area(width * height) {}

  inline std::string Name() const override { return kRect; }
  inline double Perimeter() const override { return perimeter; }
  inline double Area() const override { return area; }

private:
  const double perimeter{};
  const double area{};
};

class Triangle : public Figure {
public:
  constexpr Triangle(int a, int b, int c)
      : perimeter(a + b + c), area([a, b, c]() -> double {
          const auto half = static_cast<double>(a + b + c) / 2;
          return std::sqrt(half * (half - a) * (half - b) * (half - c));
        }()) {}

  inline std::string Name() const override { return kTriangle; }
  inline double Perimeter() const override { return perimeter; }
  inline double Area() const override { return area; }

private:
  const double perimeter{};
  const double area{};
};

class Circle : public Figure {
public:
  constexpr Circle(int radius)
      : perimeter(2 * kPi * radius), area(kPi * radius * radius) {}

  inline std::string Name() const override { return kCircle; }
  inline double Perimeter() const override { return perimeter; }
  inline double Area() const override { return area; }

private:
  const double perimeter{};
  const double area{};
};

std::shared_ptr<Figure> CreateFigure(std::istream &src) {
  std::string fig;
  src >> fig;

  if (fig == kRect) {
    int width, height;
    src >> width >> height;

    return std::make_shared<Rect>(width, height);
  }

  if (fig == kTriangle) {
    int a, b, c;
    src >> a >> b >> c;

    return std::make_shared<Triangle>(a, b, c);
  }

  if (fig == kCircle) {
    int r;
    src >> r;

    return std::make_shared<Circle>(r);
  }

  return nullptr;
}

int main() {
  std::vector<std::shared_ptr<Figure>> figures;
  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is(line);

    std::string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> std::ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto &current_figure : figures) {
        std::cout << std::fixed << std::setprecision(3)
                  << current_figure->Name() << " "
                  << current_figure->Perimeter() << " "
                  << current_figure->Area() << std::endl;
      }
    }
  }
  return 0;
}
