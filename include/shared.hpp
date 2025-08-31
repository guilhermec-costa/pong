#include <iostream>
#include <ostream>

typedef struct Vector2 {
  float x, y;

  Vector2() : x(0), y(0) {};
  Vector2(float x, float y) : x(x), y(y) {};
  Vector2(const Vector2& v) {
    std::cout << "Copying vector\n";
  };

  Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

  friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "X: " << v.x << " | Y: " << v.y << "\n";
    return os;
  };

} Vector2;

typedef struct Dimension {
private:
  Vector2 dimension;

public:
  Dimension() = default;
  Dimension(float w, float h) : dimension(Vector2{w, h}) {};
  float get_w() { return dimension.x; };

  float get_h() { return dimension.y; };
} Dimension;