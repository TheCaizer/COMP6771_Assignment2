#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <list>
#include <memory>

// My rational is to test if the euclidean vector and the vector form are the same after calling
// fucntion. Then test edge cases that include zero dim only since we can assume that user supplies
// valid parameters to the constructors. I also test for whatever is in the specs and what is
// required for the exception to work. For parameters that can be ints I also test if size_t works
// since my dimension is in size_t. Then I create a vector to check that the euclidean vector is the
// same as the vector. In order to do this I assume dimensions() and static_cast of vector and list
// works as inteneded

TEST_CASE("Default Constructors") {
	// {} should call default constructor
	auto const a1 = comp6771::euclidean_vector{};
	auto const b1 = comp6771::euclidean_vector();
	auto const v = std::vector<double>{0.0};
	SECTION("Check dim and throws") {
		REQUIRE(a1.dimensions() == 1);
		REQUIRE(a1[0] == 0.0);
		REQUIRE_THROWS_WITH(a1.at(1), "Index 1 is not valid for this euclidean_vector object");
		REQUIRE(a1 == b1);
	}
	SECTION("Check vector and value") {
		CHECK(v == static_cast<std::vector<double>>(a1));
		CHECK(v == static_cast<std::vector<double>>(b1));
	}
}
TEST_CASE("Empty List and Iter should be zero dimension") {
	auto const a1 = comp6771::euclidean_vector(0);
	auto const b1 = comp6771::euclidean_vector({});

	auto const c1 = std::vector<double>{};
	auto const d1 = comp6771::euclidean_vector(c1.begin(), c1.end());
	SECTION("Check empty") {
		REQUIRE(a1.dimensions() == 0);
		REQUIRE_THROWS_WITH(a1.at(0), "Index 0 is not valid for this euclidean_vector object");
		REQUIRE(b1.dimensions() == a1.dimensions());
		REQUIRE(a1 == b1);

		REQUIRE(c1.empty());
		REQUIRE(d1.dimensions() == 0);
		REQUIRE(d1 == a1);
	}
}

TEST_CASE("Test zero dimension vector") {
	auto const a1 = comp6771::euclidean_vector(0);
	auto const v = std::vector<double>{};
	SECTION("Check the dimension and throws") {
		REQUIRE(a1.dimensions() == 0);
		REQUIRE_THROWS_WITH(a1.at(0), "Index 0 is not valid for this euclidean_vector object");
	}
	SECTION("Check vector and value") {
		CHECK(v == static_cast<std::vector<double>>(a1));
	}
}

TEST_CASE("Testing dimension constructor") {
	auto const a1 = comp6771::euclidean_vector(3);
	auto const b1 = comp6771::euclidean_vector(static_cast<size_t>(3));
	auto const v = std::vector<double>{0, 0, 0};
	SECTION("Check the dimension and throws") {
		REQUIRE(a1.dimensions() == 3);
		REQUIRE_THROWS_WITH(a1.at(3), "Index 3 is not valid for this euclidean_vector object");
	}
	SECTION("Check vector and value") {
		REQUIRE(a1[0] == 0.0);
		REQUIRE(a1[1] == 0.0);
		REQUIRE(a1[2] == 0.0);

		CHECK(v == static_cast<std::vector<double>>(a1));
	}
	SECTION("Check vector and value with size_t") {
		REQUIRE(b1[0] == 0.0);
		REQUIRE(b1[1] == 0.0);
		REQUIRE(b1[2] == 0.0);

		CHECK(v == static_cast<std::vector<double>>(b1));
	}
}

TEST_CASE("Testing dimension and magnitude constructor") {
	auto const a = comp6771::euclidean_vector(3, 3);
	auto const b = comp6771::euclidean_vector(4, -3);
	auto const c = comp6771::euclidean_vector(0, 2);

	auto const v1 = std::vector<double>{3, 3, 3};
	auto const v2 = std::vector<double>{-3, -3, -3, -3};
	auto const v3 = std::vector<double>{};
	SECTION("Dimension and throw") {
		REQUIRE(a.dimensions() == 3);
		REQUIRE_THROWS_WITH(a.at(3), "Index 3 is not valid for this euclidean_vector object");

		REQUIRE(c.dimensions() == 0);
		REQUIRE_THROWS_WITH(c.at(0), "Index 0 is not valid for this euclidean_vector object");
	}
	SECTION("Check vector") {
		CHECK(v1 == static_cast<std::vector<double>>(a));
		CHECK(v2 == static_cast<std::vector<double>>(b));
		CHECK(v3 == static_cast<std::vector<double>>(c));
	}
}
TEST_CASE("Testing Iterator Constructor") {
	auto const v1 = std::vector<double>{2, 3, 1};
	auto const v2 = std::vector<double>{-3, -3, 2, -100.3};
	auto const v3 = std::vector<double>{};

	auto const a = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const b = comp6771::euclidean_vector(v2.begin(), v2.end());
	auto const c = comp6771::euclidean_vector(v3.begin(), v3.end());

	SECTION("Check Dimension") {
		REQUIRE(a.dimensions() == 3);
		REQUIRE(b.dimensions() == 4);
		REQUIRE(c.dimensions() == 0);
	}
	SECTION("Check values") {
		REQUIRE(v2[0] == -3);
		REQUIRE(v2[1] == -3);
		REQUIRE(v2[2] == 2);
		REQUIRE(v2[3] == -100.3);
	}
	SECTION("Check vector") {
		CHECK(v1 == static_cast<std::vector<double>>(a));
		CHECK(v2 == static_cast<std::vector<double>>(b));
		CHECK(v3 == static_cast<std::vector<double>>(c));
	}
}

TEST_CASE("List Constructor") {
	auto const a = comp6771::euclidean_vector({});
	auto const b = comp6771::euclidean_vector{};
	auto const c = comp6771::euclidean_vector{1, 2, 3, 4, 5};

	auto l = std::initializer_list<double>{-2, -3, -4};
	auto l2 = static_cast<std::list<double>>(l);
	auto const d = comp6771::euclidean_vector(l);

	auto v1 = std::list<double>{};
	auto v2 = std::list<double>{0};
	auto v3 = std::list<double>{1, 2, 3, 4, 5};

	SECTION("Check dimensions") {
		REQUIRE(a.dimensions() == 0);
		REQUIRE(b.dimensions() == 1);
		REQUIRE(c.dimensions() == 5);
		REQUIRE(d.dimensions() == 3);
	}

	SECTION("Check list") {
		CHECK(v1 == static_cast<std::list<double>>(a));
		CHECK(v2 == static_cast<std::list<double>>(b));
		CHECK(v3 == static_cast<std::list<double>>(c));
		CHECK(l2 == static_cast<std::list<double>>(d));
	}
}

TEST_CASE("Copy COnstructor") {
	auto const a = comp6771::euclidean_vector();
	auto const b = comp6771::euclidean_vector(0);
	auto const c = comp6771::euclidean_vector(2, 3);
	auto const d = comp6771::euclidean_vector(1, 1);

	auto copy_a = a;
	auto copy_b = b;
	auto copy_c = c;

	auto const v1 = std::vector<double>{0.0};
	auto const v2 = std::vector<double>{};
	auto const v3 = std::vector<double>{3, 3};

	SECTION("Check they are equal") {
		REQUIRE(a == copy_a);
		REQUIRE(b == copy_b);
		REQUIRE(c == copy_c);

		REQUIRE(static_cast<std::vector<double>>(a) == v1);
		REQUIRE(static_cast<std::vector<double>>(b) == v2);
		REQUIRE(static_cast<std::vector<double>>(c) == v3);

		REQUIRE(static_cast<std::vector<double>>(copy_a) == v1);
		REQUIRE(static_cast<std::vector<double>>(copy_b) == v2);
		REQUIRE(static_cast<std::vector<double>>(copy_c) == v3);
	}
	SECTION("Check they are a copy") {
		copy_b = copy_a;
		copy_a *= 3;
		copy_c[1] = 0.2;

		REQUIRE(static_cast<std::vector<double>>(a) == v1);
		REQUIRE(static_cast<std::vector<double>>(b) == v2);
		REQUIRE(static_cast<std::vector<double>>(c) == v3);
	}
}

TEST_CASE("move constructor") {
	auto a = comp6771::euclidean_vector();
	auto b = comp6771::euclidean_vector(0);
	auto c = comp6771::euclidean_vector(2, 3);

	auto copy_a = std::move(a);
	auto copy_b = std::move(b);
	auto copy_c = std::move(c);

	auto const v1 = std::vector<double>{0.0};
	auto const v2 = std::vector<double>{};
	auto const v3 = std::vector<double>{3, 3};

	SECTION("Check they are equal") {
		REQUIRE(static_cast<std::vector<double>>(copy_a) == v1);
		REQUIRE(static_cast<std::vector<double>>(copy_b) == v2);
		REQUIRE(static_cast<std::vector<double>>(copy_c) == v3);
	}

	SECTION("Check leaves zero") {
		// NOLINTNEXTLINE
		REQUIRE(a.dimensions() == 0);
		// NOLINTNEXTLINE
		REQUIRE(b.dimensions() == 0);
		// NOLINTNEXTLINE
		REQUIRE(c.dimensions() == 0);

		REQUIRE_THROWS_WITH(a.at(0), "Index 0 is not valid for this euclidean_vector object");
		REQUIRE_THROWS_WITH(b.at(0), "Index 0 is not valid for this euclidean_vector object");
		REQUIRE_THROWS_WITH(c.at(0), "Index 0 is not valid for this euclidean_vector object");
	}
}

TEST_CASE("Creation of unit vectors") {
	SECTION("You have two identical vectors") {
		auto a = comp6771::euclidean_vector(2);
		a[0] = 1;
		a[1] = 2;
		auto b = comp6771::euclidean_vector(2);
		b[0] = 1;
		b[1] = 2;

		auto c = comp6771::unit(a);
		auto d = comp6771::unit(b);
		REQUIRE(c == d);
	}
}
