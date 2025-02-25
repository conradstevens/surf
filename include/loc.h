#ifndef LOC_H
#define LOC_H

/**
 * @brief Stores the basic kinematic and physical property data members of the object
 * @note Values are in relation to the window size of (-1, 1)
 */
struct Loc {
    /**
     * @param x, y locations in (-1, 1)
     * @param x_buf, y_buf how far from the centre of the object must be offscreen before it's deleted automatically
     * @param angle is in radians
     * @param speed the speed of the object in distance (-1, 1) per second
     * @param rps rotations per second
     * @param direction the direction of the objects speed represented as a vector
     */
    float x{}, y{};
    float x_buf{}, y_buf{};
    float angle{};
    float speed{};
    float rps{};
    std::vector<float> direction{0.0f, 0.0f};

    /**
     * @brief Constructors set default values when the values are not provided
     * the more kinematic data members are set at runtime
     */
    Loc() = default;
    Loc(float x, float y) : x{x}, y{y} {}
    Loc(float x, float y, float x_buf, float y_buf) : x{x}, y{y}, x_buf{x_buf}, y_buf{y_buf} {}
};

#endif //LOC_H
