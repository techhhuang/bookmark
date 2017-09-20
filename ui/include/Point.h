#ifndef _POINT_H
#define _POINT_H
namespace SmartUI {
template <typename ValueType>
class Point {
 public:
  /** Creates a point at the origin */
  Point() noexcept : mX(0), mY(0) {}

  /** Creates a copy of another point. */
  Point(const Point& other) noexcept : mX(other.mX), mY(other.mY) {}

  /** Creates a point from an (mX, y) position. */
  Point(ValueType x, ValueType y) noexcept : mX(x), mY(y) {}
  //==============================================================================
  /** Copies this point from another one. */
  Point& operator=(const Point& other) noexcept {
    mX = other.mX;
    mY = other.mY;
    return *this;
  }

  inline bool operator==(Point other) const noexcept {
    return mX == other.mX && mY == other.mY;
  }
  inline bool operator!=(Point other) const noexcept {
    return mX != other.mX || mY != other.mY;
  }

  /** Returns true if the point is (0, 0). */
  bool isOrigin() const noexcept {
    return mX == ValueType() && mY == ValueType();
  }
  bool isPositive() const noexcept { return mX >= 0 && mY >= 0; }

  /** Returns the point's x coordinate. */
  inline ValueType x() const noexcept { return mX; }

  /** Returns the point's y coordinate. */
  inline ValueType y() const noexcept { return mY; }

  /** Sets the point's x coordinate. */
  inline void setX(ValueType x) noexcept { mX = x; }

  /** Sets the point's y coordinate. */
  inline void setY(ValueType y) noexcept { mY = y; }

  //==============================================================================
  /** Returns a point with a given offset from this one. */
  Point translated(ValueType deltaX, ValueType deltaY) const noexcept {
    return Point(mX + deltaX, mY + deltaY);
  }

  /** Adds two points together */
  Point operator+(Point other) const noexcept {
    return Point(mX + other.mX, mY + other.mY);
  }

  /** Adds another point's coordinates to this one */
  Point& operator+=(Point other) noexcept {
    mX += other.mX;
    mY += other.mY;
    return *this;
  }

  /** Subtracts one points from another */
  Point operator-(Point other) const noexcept {
    return Point(mX - other.mX, mY - other.mY);
  }

  /** Subtracts another point's coordinates to this one */
  Point& operator-=(Point other) noexcept {
    mX -= other.mX;
    mY -= other.mY;
    return *this;
  }

  /** Multiplies two points together */
  template <typename OtherType>
  Point operator*(Point<OtherType> other) const noexcept {
    return Point((ValueType)(mX * other.mX), (ValueType)(mY * other.mY));
  }

  /** Multiplies another point's coordinates to this one */
  template <typename OtherType>
  Point& operator*=(Point<OtherType> other) noexcept {
    *this = *this * other;
    return *this;
  }

  /** Divides one point by another */
  template <typename OtherType>
  Point operator/(Point<OtherType> other) const noexcept {
    return Point((ValueType)(mX / other.mX), (ValueType)(mY / other.mY));
  }

  /** Divides this point's coordinates by another */
  template <typename OtherType>
  Point& operator/=(Point<OtherType> other) noexcept {
    *this = *this / other;
    return *this;
  }

  /** Returns a point whose coordinates are multiplied by a given scalar value.
   */
  template <typename FloatType>
  Point operator*(FloatType multiplier) const noexcept {
    return Point((ValueType)(mX * multiplier), (ValueType)(mY * multiplier));
  }

  /** Returns a point whose coordinates are divided by a given scalar value. */
  template <typename FloatType>
  Point operator/(FloatType divisor) const noexcept {
    return Point((ValueType)(mX / divisor), (ValueType)(mY / divisor));
  }

  /** Multiplies the point's coordinates by a scalar value. */
  template <typename FloatType>
  Point& operator*=(FloatType multiplier) noexcept {
    mX = (ValueType)(mX * multiplier);
    mY = (ValueType)(mY * multiplier);
    return *this;
  }

  /** Divides the point's coordinates by a scalar value. */
  template <typename FloatType>
  Point& operator/=(FloatType divisor) noexcept {
    mX = (ValueType)(mX / divisor);
    mY = (ValueType)(mY / divisor);
    return *this;
  }

  /** Casts this point to a Point<int> object. */
  Point<int> toInt() const noexcept {
    return Point<int>(static_cast<int>(mX), static_cast<int>(mY));
  }

  /** Casts this point to a Point<float> object. */
  Point<float> toFloat() const noexcept {
    return Point<float>(static_cast<float>(mX), static_cast<float>(mY));
  }

  /** Casts this point to a Point<double> object. */
  Point<double> toDouble() const noexcept {
    return Point<double>(static_cast<double>(mX), static_cast<double>(mY));
  }

  /** Returns the point as a string in the form "x, y". */
  //   String toString() const { return String(mX) + ", " + String(y); }

  //==============================================================================
  ValueType mX; /**< The point's X coordinate. */
  ValueType mY; /**< The point's Y coordinate. */
};
}

#endif