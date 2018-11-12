#include <catch2/catch.hpp>

#include "../../../include/TimberWolf/Core/Color.hpp"

SCENARIO ("Color objects can be constructed", "[core][color]") {

    GIVEN ("a default constructed Color") {
        tw::Color color;

        WHEN ("red, green, blue, and alpha channels are provided as normalized floats") {
            color = tw::Color(0.22f, 0.44f, 0.66f, 0.88f);

            THEN ("Each of the values should be assigned unchanged") {
                REQUIRE (color.getR() == 0.22f);
                REQUIRE (color.getG() == 0.44f);
                REQUIRE (color.getB() == 0.66f);
                REQUIRE (color.getA() == 0.88f);
            }
        }

        WHEN ("red, green, blue, and alpha channels are provided as floats with values greater than 1") {
            color = tw::Color(1.22f, 1.44f, 1.66f, 1.88f);

            THEN ("Each of the values should be clamped to 1") {
                REQUIRE (color.getR() == 1.f);
                REQUIRE (color.getG() == 1.f);
                REQUIRE (color.getB() == 1.f);
                REQUIRE (color.getA() == 1.f);
            }
        }

        WHEN ("red, green, blue, and alpha channels are provided as floats with values less than 1") {
            color = tw::Color(-0.22f, -0.44f, -0.66f, -0.88f);

            THEN ("Each of the values should be clamped to 0") {
                REQUIRE (color.getR() == 0.f);
                REQUIRE (color.getG() == 0.f);
                REQUIRE (color.getB() == 0.f);
                REQUIRE (color.getA() == 0.f);
            }
        }

    }

}
