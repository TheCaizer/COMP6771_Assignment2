#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <list>
#include <memory>
#include <sstream>

TEST_CASE("Equal") {
	auto a = comp6771::euclidean_vector(2, 3);
	auto b = comp6771::euclidean_vector{1, 2, 3};
	auto c = comp6771::euclidean_vector(0);
	auto d = comp6771::euclidean_vector(2, 4);
	auto e = comp6771::euclidean_vector{3, 3};

	auto const a1 = comp6771::euclidean_vector(2, 3);
	auto const b1 = comp6771::euclidean_vector{1, 2, 3};
	auto const c1 = comp6771::euclidean_vector(0);
	auto const d1 = comp6771::euclidean_vector{3, 3};

	SECTION("Check works") {
		// const and non const
		CHECK(a == a1);
		CHECK(b == b1);
		CHECK(c == c1);
		// same dimension and magnitude and non-const
		CHECK(a == e);
		// same dimension and magnitude and const
		CHECK(a1 == d1);
		// different dimensions
		CHECK_FALSE(a == b1);
		CHECK_FALSE(c1 == a);
		// Same dimension different magnitude
		CHECK_FALSE(a == d);
		// check if self is same non-const
		CHECK(a == a);
		// check if self is same const
		CHECK(a1 == a1);
	}
}

TEST_CASE("Not Equal") {
	auto a = comp6771::euclidean_vector(2, 3);
	auto b = comp6771::euclidean_vector{1, 2, 3};
	auto c = comp6771::euclidean_vector(0);
	auto d = comp6771::euclidean_vector(2, 4);
	auto e = comp6771::euclidean_vector{3, 3};

	auto const a1 = comp6771::euclidean_vector(2, 3);
	auto const b1 = comp6771::euclidean_vector{1, 2, 3};
	auto const c1 = comp6771::euclidean_vector(0);
	auto const d1 = comp6771::euclidean_vector{3, 3};

	SECTION("Check works") {
		// const and non const
		CHECK_FALSE(a != a1);
		CHECK_FALSE(b != b1);
		CHECK_FALSE(c != c1);
		// same dimension and magnitude and non-const
		CHECK_FALSE(a != e);
		// same dimension and magnitude and const
		CHECK_FALSE(a1 != d1);
		// different dimensions
		CHECK(a != b1);
		CHECK(c1 != a);
		// Same dimension different magnitude
		CHECK(a != d);
		// check if self is same non-const
		CHECK_FALSE(a != a);
		// check if self is same const
		CHECK_FALSE(a1 != a1);
	}
}
TEST_CASE("Plus") {
	auto const a = comp6771::euclidean_vector(2, 3);
	auto const b = comp6771::euclidean_vector{1, 2, 3};
	auto const c = comp6771::euclidean_vector(0);
	auto const d = comp6771::euclidean_vector(2, 4);

	auto const zero = comp6771::euclidean_vector({});
	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{7, 7};

	SECTION("Zero dim") {
		auto f = zero + c;
		CHECK(static_cast<std::vector<double>>(f) == v1);
		CHECK(f.dimensions() == 0);
	}
	SECTION("Exception") {
		REQUIRE_THROWS_WITH(a + b, "Dimensions of LHS (2) and RHS(3) do not match");
		REQUIRE_THROWS_WITH(b + a, "Dimensions of LHS (3) and RHS(2) do not match");
	}
	SECTION("add 2") {
		auto g = a + d;
		CHECK(static_cast<std::vector<double>>(g) == v2);
		auto h = d + a;
		CHECK(static_cast<std::vector<double>>(h) == v2);
	}
	SECTION("check it returns a new object") {
		auto i = a + d;
		CHECK(std::addressof(i) != std::addressof(a));
		CHECK(std::addressof(i) != std::addressof(d));
	}
}

TEST_CASE("Minus") {
	auto const a = comp6771::euclidean_vector(2, 3);
	auto const b = comp6771::euclidean_vector{1, 2, 3};
	auto const c = comp6771::euclidean_vector(0);
	auto const d = comp6771::euclidean_vector(2, 4);

	auto const zero = comp6771::euclidean_vector({});
	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{-1, -1};
	auto const v3 = std::vector<double>{1, 1};

	SECTION("Zero dim") {
		auto f = zero - c;
		CHECK(static_cast<std::vector<double>>(f) == v1);
		CHECK(f.dimensions() == 0);
	}
	SECTION("Exception") {
		REQUIRE_THROWS_WITH(a - b, "Dimensions of LHS (2) and RHS(3) do not match");
		REQUIRE_THROWS_WITH(b - a, "Dimensions of LHS (3) and RHS(2) do not match");
	}
	SECTION("minus 2") {
		auto g = a - d;
		CHECK(static_cast<std::vector<double>>(g) == v2);

		auto h = d - a;
		CHECK(static_cast<std::vector<double>>(h) == v3);
	}
	SECTION("check it returns a new object") {
		auto i = a - d;
		CHECK(std::addressof(i) != std::addressof(a));
		CHECK(std::addressof(i) != std::addressof(d));
	}
}
TEST_CASE("Multiply") {
	auto const a = comp6771::euclidean_vector(2, 3);

	auto const zero = comp6771::euclidean_vector({});
	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{9, 9};
	auto const v3 = std::vector<double>{0, 0};

	SECTION("Zero dim") {
		auto f = zero * 2;
		CHECK(static_cast<std::vector<double>>(f) == v1);
		CHECK(f.dimensions() == 0);
	}
	SECTION("test multiply both version of * and multiply by 0") {
		auto g = a * 3;
		CHECK(static_cast<std::vector<double>>(g) == v2);

		auto h = 3 * a;
		CHECK(static_cast<std::vector<double>>(h) == v2);

		auto n = a * 0;
		CHECK(static_cast<std::vector<double>>(n) == v3);

		auto m = 0 * a;
		CHECK(static_cast<std::vector<double>>(m) == v3);
	}
	SECTION("check it returns a new object") {
		auto i = a * 4;
		CHECK(std::addressof(i) != std::addressof(a));
	}
}
TEST_CASE("Divide") {
	auto const a = comp6771::euclidean_vector(2, 3);

	auto const zero = comp6771::euclidean_vector({});
	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{1.5, 1.5};
	auto const v3 = std::vector<double>{0.5, 0.5};

	SECTION("Exception") {
		REQUIRE_THROWS_WITH(a / 0, "Invalid vector division by 0");
		REQUIRE_THROWS_WITH(zero / 0, "Invalid vector division by 0");
	}
	SECTION("Zero dim") {
		auto f = zero / 2;
		CHECK(static_cast<std::vector<double>>(f) == v1);
		CHECK(f.dimensions() == 0);
	}
	SECTION("test dividing") {
		auto g = a / 2;
		CHECK(static_cast<std::vector<double>>(g) == v2);
		auto h = g / 3;
		CHECK(static_cast<std::vector<double>>(h) == v3);
	}
	SECTION("check it returns a new object") {
		auto i = a / 4;
		CHECK(std::addressof(i) != std::addressof(a));
	}
}

TEST_CASE("Output Stream") {
	auto const zero = comp6771::euclidean_vector(0);
	auto const a = comp6771::euclidean_vector{1, 2, 3};
	auto const neg = comp6771::euclidean_vector{-1, -2, -3};

	SECTION("Test zero dimension output") {
		auto output = std::stringstream();
		output << zero;
		CHECK(output.str() == "[]");
	}

	SECTION("Test output") {
		auto output = std::stringstream();
		output << a;
		CHECK(output.str() == "[1 2 3]");
	}
	SECTION("Test negative output") {
		auto output = std::stringstream();
		output << neg;
		CHECK(output.str() == "[-1 -2 -3]");
	}
}
