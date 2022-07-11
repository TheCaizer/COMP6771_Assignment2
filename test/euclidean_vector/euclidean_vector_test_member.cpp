#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <list>
#include <memory>

TEST_CASE("at() const") {
	auto const a = comp6771::euclidean_vector{1.2, 2.3, -3.4};
	auto const b = comp6771::euclidean_vector(0);

	SECTION("Exception") {
		REQUIRE_THROWS_WITH(a.at(-1), "Index -1 is not valid for this euclidean_vector object");
		REQUIRE_THROWS_WITH(a.at(4), "Index 4 is not valid for this euclidean_vector object");
		REQUIRE_THROWS_WITH(b.at(0), "Index 0 is not valid for this euclidean_vector object");
	}

	SECTION("Access") {
		CHECK(a.at(0) == 1.2);
		CHECK(a.at(1) == 2.3);
		CHECK(a.at(2) == -3.4);
	}
	SECTION("size_t Access") {
		CHECK(a.at(static_cast<size_t>(0)) == 1.2);
		CHECK(a.at(static_cast<size_t>(1)) == 2.3);
		CHECK(a.at(static_cast<size_t>(2)) == -3.4);
	}
	SECTION("check its a copy") {
		auto a1 = a.at(0);
		a1 = 2;
		CHECK(a.at(0) == 1.2);
	}
}

TEST_CASE("at() non-const") {
	auto a = comp6771::euclidean_vector{1.2, 2.3, -3.4};
	auto b = comp6771::euclidean_vector(0);

	SECTION("Exception") {
		REQUIRE_THROWS_WITH(a.at(-1), "Index -1 is not valid for this euclidean_vector object");
		REQUIRE_THROWS_WITH(a.at(4), "Index 4 is not valid for this euclidean_vector object");
		REQUIRE_THROWS_WITH(b.at(0), "Index 0 is not valid for this euclidean_vector object");
	}

	SECTION("Access") {
		CHECK(a.at(0) == 1.2);
		CHECK(a.at(1) == 2.3);
		CHECK(a.at(2) == -3.4);
	}
	SECTION("size_t Access") {
		CHECK(a.at(static_cast<size_t>(0)) == 1.2);
		CHECK(a.at(static_cast<size_t>(1)) == 2.3);
		CHECK(a.at(static_cast<size_t>(2)) == -3.4);
	}
	SECTION("check its a copy") {
		auto a1 = a.at(0);
		a1 = 2;
		CHECK(a.at(0) == 1.2);
	}

	SECTION("check if you can modify") {
		a.at(0) = -2;
		a.at(1) = -2.4;
		a.at(2) = 4.5;

		auto v = std::vector<double>{-2, -2.4, 4.5};

		CHECK(a.at(0) == -2);
		CHECK(a.at(1) == -2.4);
		CHECK(a.at(2) == 4.5);
		CHECK(static_cast<std::vector<double>>(a) == v);
	}
}

TEST_CASE("dimensions()") {
	auto a = comp6771::euclidean_vector(2, 3);
	auto b = comp6771::euclidean_vector{1, 2, 3};
	auto c = comp6771::euclidean_vector(0);

	auto const a1 = comp6771::euclidean_vector(2, 3);
	auto const b1 = comp6771::euclidean_vector{1, 2, 3};
	auto const c1 = comp6771::euclidean_vector(0);

	SECTION("Check the values") {
		CHECK(a.dimensions() == 2);
		CHECK(b.dimensions() == 3);
		CHECK(c.dimensions() == 0);
	}
	SECTION("Check the values for const") {
		CHECK(a1.dimensions() == 2);
		CHECK(b1.dimensions() == 3);
		CHECK(c1.dimensions() == 0);
	}

	SECTION("Check that it doesnt change") {
		auto num = a.dimensions();
		CHECK(a.dimensions() == 2);
		CHECK(num == 2);
		num = 3;
		CHECK(num == 3);
		CHECK(a.dimensions() == 2);
	}
}
