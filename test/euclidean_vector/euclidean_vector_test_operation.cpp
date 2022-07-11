#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <list>
#include <memory>
#pragma GCC diagnostic ignored "-Wself-move"

TEST_CASE("Copy Assignment") {
	auto const a = comp6771::euclidean_vector({});
	auto const b = comp6771::euclidean_vector();
	auto const c = comp6771::euclidean_vector{1, 2, 3};

	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{0.0};
	auto const v3 = std::vector<double>{1, 2, 3};

	auto a1 = comp6771::euclidean_vector();
	auto b1 = comp6771::euclidean_vector{1, 2, 3};
	auto c1 = comp6771::euclidean_vector({});

	a1 = a;
	b1 = b;
	c1 = c;

	SECTION("Check they are equal") {
		REQUIRE(a1 == a);
		REQUIRE(b1 == b);
		REQUIRE(c1 == c);

		REQUIRE(static_cast<std::vector<double>>(a1) == v1);
		REQUIRE(static_cast<std::vector<double>>(b1) == v2);
		REQUIRE(static_cast<std::vector<double>>(c1) == v3);
	}

	SECTION("check self assignment") {
		a1 = a1;
		b1 = b1;
		c1 = c1;

		REQUIRE(static_cast<std::vector<double>>(a1) == v1);
		REQUIRE(static_cast<std::vector<double>>(b1) == v2);
		REQUIRE(static_cast<std::vector<double>>(c1) == v3);
	}

	SECTION("Check they are not a reference") {
		b1 *= 2;
		c1 *= 3;
		REQUIRE(static_cast<std::vector<double>>(b) == v2);
		REQUIRE(static_cast<std::vector<double>>(c) == v3);
	}
}

TEST_CASE("Move assignment") {
	auto a = comp6771::euclidean_vector({});
	auto b = comp6771::euclidean_vector();
	auto c = comp6771::euclidean_vector{1, 2, 3};

	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{0.0};
	auto const v3 = std::vector<double>{1, 2, 3};

	auto a1 = comp6771::euclidean_vector();
	auto b1 = comp6771::euclidean_vector{1, 2, 3};
	auto c1 = comp6771::euclidean_vector({});

	// NOLINTNEXTLINE
	a1 = std::move(a);
	// NOLINTNEXTLINE
	b1 = std::move(b);
	// NOLINTNEXTLINE
	c1 = std::move(c);

	SECTION("Check they are right") {
		REQUIRE(static_cast<std::vector<double>>(a1) == v1);
		REQUIRE(static_cast<std::vector<double>>(b1) == v2);
		REQUIRE(static_cast<std::vector<double>>(c1) == v3);
	}

	SECTION("Check self assignment") {
		// NOLINTNEXTLINE
		a1 = std::move(a1);
		// NOLINTNEXTLINE
		b1 = std::move(b1);
		// NOLINTNEXTLINE
		c1 = std::move(c1);
		// NOLINTNEXTLINE
		REQUIRE(a1.dimensions() == 0);
		// NOLINTNEXTLINE
		REQUIRE(b1.dimensions() == 1);
		// NOLINTNEXTLINE
		REQUIRE(c1.dimensions() == 3);

		REQUIRE(static_cast<std::vector<double>>(a1) == v1);
		REQUIRE(static_cast<std::vector<double>>(b1) == v2);
		REQUIRE(static_cast<std::vector<double>>(c1) == v3);
	}

	SECTION("Check leaves zero") {
		// NOLINTNEXTLINE
		REQUIRE(a.dimensions() == 0);
		// NOLINTNEXTLINE
		REQUIRE(b.dimensions() == 0);
		// NOLINTNEXTLINE
		REQUIRE(c.dimensions() == 0);
		// NOLINTNEXTLINE
		REQUIRE_THROWS_WITH(a.at(0), "Index 0 is not valid for this euclidean_vector object");
		// NOLINTNEXTLINE
		REQUIRE_THROWS_WITH(b.at(0), "Index 0 is not valid for this euclidean_vector object");
		// NOLINTNEXTLINE
		REQUIRE_THROWS_WITH(c.at(0), "Index 0 is not valid for this euclidean_vector object");
	}
}
TEST_CASE("Subscript non-const") {
	auto a = comp6771::euclidean_vector{1.2, 2.3, -3.4};

	SECTION("ACCESS") {
		CHECK(a[0] == 1.2);
		CHECK(a[1] == 2.3);
		CHECK(a[2] == -3.4);

		double a1 = a[0];
		double b2 = a[1];
		double c3 = a[2];

		CHECK(a1 == 1.2);
		CHECK(b2 == 2.3);
		CHECK(c3 == -3.4);

		a1 = 2;
		CHECK(a[0] == 1.2);
	}

	SECTION("Change values") {
		a[0] = 2.4;
		a[1] = 0.0;
		a[2] = -90;

		CHECK(a[0] == 2.4);
		CHECK(a[1] == 0.0);
		CHECK(a[2] == -90);
	}
}

TEST_CASE("Subscript const") {
	auto const a = comp6771::euclidean_vector{1.2, 2.3, -3.4};

	SECTION("ACCESS") {
		CHECK(a[0] == 1.2);
		CHECK(a[1] == 2.3);
		CHECK(a[2] == -3.4);

		double a1 = a[0];
		double b2 = a[1];
		double c3 = a[2];

		CHECK(a1 == 1.2);
		CHECK(b2 == 2.3);
		CHECK(c3 == -3.4);

		a1 = 2;
		CHECK(a[0] == 1.2);
	}
}

TEST_CASE("Unary plus") {
	auto a = comp6771::euclidean_vector{1.2, 2.3, -3.4};
	auto const a1 = comp6771::euclidean_vector{1.2, 2.3, -3.4};

	auto b = +a;
	auto b1 = +a1;

	auto const v1 = std::vector<double>{1.2, 2.3, -3.4};

	SECTION("Check right values") {
		CHECK(a == b);
		CHECK(v1 == static_cast<std::vector<double>>(a));
		CHECK(v1 == static_cast<std::vector<double>>(b));
		CHECK(static_cast<std::vector<double>>(a) == static_cast<std::vector<double>>(b));
	}
	SECTION("Check values for const version") {
		CHECK(a1 == b1);
		CHECK(v1 == static_cast<std::vector<double>>(a1));
		CHECK(v1 == static_cast<std::vector<double>>(b1));
		CHECK(static_cast<std::vector<double>>(a1) == static_cast<std::vector<double>>(b1));
	}
	SECTION("Check returns copy") {
		b *= 3;
		CHECK(v1 != static_cast<std::vector<double>>(b));
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}

	SECTION("Check returns copy const version") {
		b1 *= 3;
		CHECK(v1 != static_cast<std::vector<double>>(b1));
		CHECK(v1 == static_cast<std::vector<double>>(a1));
	}
}

TEST_CASE("Negation for const and non const") {
	auto a = comp6771::euclidean_vector{1.2, 2.3, -3.4};
	auto const a1 = comp6771::euclidean_vector{1.2, 2.3, -3.4};

	auto b = -a;
	auto b1 = -a1;

	auto const v1 = std::vector<double>{-1.2, -2.3, 3.4};
	auto const v2 = std::vector<double>{1.2, 2.3, -3.4};

	SECTION("Check right values") {
		CHECK(v1 == static_cast<std::vector<double>>(b));
		CHECK(v1 == static_cast<std::vector<double>>(b1));
	}
	SECTION("Check returns copy") {
		b *= 3;
		CHECK(v2 == static_cast<std::vector<double>>(a));
		CHECK(v2 == static_cast<std::vector<double>>(a1));
	}
}
TEST_CASE("+=") {
	auto a = comp6771::euclidean_vector(3, 3);
	auto b = comp6771::euclidean_vector{1, 2, 3};
	auto c = comp6771::euclidean_vector{1, 2};
	auto const v1 = std::vector<double>{4, 5, 6};
	auto const v2 = std::vector<double>{6, 6, 6};

	SECTION("exception check") {
		REQUIRE_THROWS_WITH(b += c, "Dimensions of LHS (3) and RHS(2) do not match");
		REQUIRE_THROWS_WITH(c += b, "Dimensions of LHS (2) and RHS(3) do not match");
	}

	SECTION("add 2") {
		a += b;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}
	SECTION("self adding") {
		a += a;
		CHECK(v2 == static_cast<std::vector<double>>(a));
	}
}

TEST_CASE("-=") {
	auto a = comp6771::euclidean_vector(3, 3);
	auto b = comp6771::euclidean_vector{1, 2, 3};
	auto c = comp6771::euclidean_vector{1, 2};
	auto const v1 = std::vector<double>{2, 1, 0};
	auto const v2 = std::vector<double>{0, 0, 0};

	SECTION("exception check") {
		REQUIRE_THROWS_WITH(b -= c, "Dimensions of LHS (3) and RHS(2) do not match");
		REQUIRE_THROWS_WITH(c -= b, "Dimensions of LHS (2) and RHS(3) do not match");
	}

	SECTION("minus 2") {
		a -= b;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}
	SECTION("self minusing") {
		a -= a;
		CHECK(v2 == static_cast<std::vector<double>>(a));
	}
}

TEST_CASE("*=") {
	auto a = comp6771::euclidean_vector(3, 3);
	auto const v0 = std::vector<double>{0, 0, 0};
	auto const v1 = std::vector<double>{9, 9, 9};
	auto const v2 = std::vector<double>{3, 3, 3};
	auto const v3 = std::vector<double>{4.5, 4.5, 4.5};

	SECTION("multiplying int") {
		a *= 1;
		CHECK(v2 == static_cast<std::vector<double>>(a));
		a *= 3;
		CHECK(v1 == static_cast<std::vector<double>>(a));
		a *= 0;
		CHECK(v0 == static_cast<std::vector<double>>(a));
	}
	SECTION("multiplying double") {
		a *= 1.5;
		CHECK(v3 == static_cast<std::vector<double>>(a));
	}
}

TEST_CASE("/=") {
	auto a = comp6771::euclidean_vector(2, 6);
	auto const v0 = std::vector<double>{6, 6};
	auto const v1 = std::vector<double>{3, 3};
	auto const v2 = std::vector<double>{2.4, 2.4};

	SECTION("exception check") {
		REQUIRE_THROWS_WITH(a /= 0, "Invalid vector division by 0");
	}
	SECTION("dividing int") {
		a /= 1;
		CHECK(v0 == static_cast<std::vector<double>>(a));
		a /= 2;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}
	SECTION("dividing double") {
		a /= 2.5;
		CHECK(v2 == static_cast<std::vector<double>>(a));
	}
}
TEST_CASE("zero dimension for operator") {
	auto a = comp6771::euclidean_vector(0);
	auto b = comp6771::euclidean_vector(0);
	auto v1 = std::vector<double>{};

	auto plus = +a;
	auto neg = -a;
	SECTION("right values for plus minus") {
		CHECK(v1 == static_cast<std::vector<double>>(plus));
		CHECK(v1 == static_cast<std::vector<double>>(neg));
	}

	SECTION("right values for div") {
		a /= 3;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}

	SECTION("right values for multiply") {
		a *= 3;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}

	SECTION("right values for plus compound") {
		a += b;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}
	SECTION("right values for minus compound") {
		a -= b;
		CHECK(v1 == static_cast<std::vector<double>>(a));
	}
}
TEST_CASE("vector conversion") {
	auto const a = comp6771::euclidean_vector(0);
	auto const b = comp6771::euclidean_vector(3, 4);
	auto const a1 = static_cast<std::vector<double>>(a);
	auto const b1 = static_cast<std::vector<double>>(b);
	auto const v1 = std::vector<double>{};
	auto const v2 = std::vector<double>{4, 4, 4};

	SECTION("check right values") {
		CHECK(v1 == a1);
		CHECK(v2 == b1);
	}
}
TEST_CASE("list conversion") {
	auto const a = comp6771::euclidean_vector(0);
	auto const b = comp6771::euclidean_vector(3, 4);

	auto const a1 = static_cast<std::list<double>>(a);
	auto const b1 = static_cast<std::list<double>>(b);

	auto const v1 = std::list<double>{};
	auto const v2 = std::list<double>{4, 4, 4};

	SECTION("check right values") {
		CHECK(v1 == a1);
		CHECK(v2 == b1);
	}
}