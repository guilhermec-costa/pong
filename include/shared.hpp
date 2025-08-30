typedef struct Vector2 {
  float x, y;

  Vector2() : x(0), y(0) {};
  Vector2(float x, float y) : x(x), y(y) {}

  Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
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