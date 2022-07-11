#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <list>
#include <memory>
#include <sstream>
#include <vector>

TEST_CASE("norm") {
	auto const zero = comp6771::euclidean_vector(0);
	auto a = comp6771::euclidean_vector{1, 2, 3};
	auto const neg = comp6771::euclidean_vector{-1, -2, -3};

	SECTION("Test zero dimension") {
		auto en_zero = comp6771::euclidean_norm(zero);
		CHECK(en_zero == 0);
	}

	SECTION("Test positve") {
		auto en_pos = comp6771::euclidean_norm(a);
		CHECK(en_pos == Approx(3.741657387));
	}
	SECTION("Test negative ") {
		auto en_neg = comp6771::euclidean_norm(neg);
		CHECK(en_neg == Approx(3.741657387));
	}
	SECTION("Test Changing norm") {
		a[0] = 2;
		auto en_pos = comp6771::euclidean_norm(a);
		CHECK(en_pos == Approx(4.123105626));

		a += neg;
		auto en_pos2 = comp6771::euclidean_norm(a);
		CHECK(en_pos2 == Approx(1));
	}
	SECTION("Test Changing norm part 2") {
		a.at(1) = 20;
		auto en_pos = comp6771::euclidean_norm(a);
		CHECK(en_pos == Approx(20.2484567));

		a -= neg;
		auto en_pos2 = comp6771::euclidean_norm(a);
		CHECK(en_pos2 == Approx(22.89104628));
	}

	SECTION("Test Changing norm part 3") {
		a *= 3;
		auto en_pos = comp6771::euclidean_norm(a);
		CHECK(en_pos == Approx(11.22497216));

		a /= 4;
		auto en_pos2 = comp6771::euclidean_norm(a);
		CHECK(en_pos2 == Approx(2.80624304));
	}

	SECTION("Test caching") {
		auto norm = comp6771::euclidean_norm(a);
		CHECK(norm == Approx(3.741657387));
		auto norm2 = comp6771::euclidean_norm(a);
		CHECK(norm2 == Approx(3.741657387));
	}
}

TEST_CASE("Unit") {
	auto const zero = comp6771::euclidean_vector(0);
	auto const a = comp6771::euclidean_vector{1, 2, 3};
	auto const neg = comp6771::euclidean_vector{-1, -2, -3};
	auto const empty = comp6771::euclidean_vector{0, 0, 0};

	auto const v1 = std::vector<double>{0.2672612419, 0.5345224838, 0.8017837257};
	auto const v2 = std::vector<double>{-0.2672612419, -0.5345224838, -0.8017837257};

	SECTION("Exception") {
		REQUIRE_THROWS_WITH(comp6771::unit(zero),
		                    "euclidean_vector with no dimensions does not have a unit vector");
		REQUIRE_THROWS_WITH(comp6771::unit(empty),
		                    "euclidean_vector with zero euclidean normal does not have a unit "
		                    "vector");
	}
	SECTION("test positive") {
		auto unit = comp6771::unit(a);
		REQUIRE_THAT(static_cast<std::vector<double>>(unit), Catch::Approx(v1));
	}

	SECTION("test negative") {
		auto neg_unit = comp6771::unit(neg);
		REQUIRE_THAT(static_cast<std::vector<double>>(neg_unit), Catch::Approx(v2));
	}
}

TEST_CASE("Dot") {
	auto const zero = comp6771::euclidean_vector(0);
	auto const a = comp6771::euclidean_vector{1, 2, 3};
	auto const neg = comp6771::euclidean_vector{-1, -2, -3};
	auto const empty = comp6771::euclidean_vector({});
	auto const b = comp6771::euclidean_vector{10, 2.3, 3.4};

	SECTION("Exception") {
		REQUIRE_THROWS_WITH(comp6771::dot(zero, a), "Dimensions of LHS(0) and RHS(3) do not match");
		REQUIRE_THROWS_WITH(comp6771::dot(a, zero), "Dimensions of LHS(3) and RHS(0) do not match");
	}
	SECTION("zero dimension") {
		CHECK(comp6771::dot(zero, empty) == 0);
	}

	SECTION("test") {
		CHECK(comp6771::dot(a, neg) == -14);
	}

	SECTION("test 2") {
		CHECK(comp6771::dot(a, b) == Approx(24.8));
	}
}