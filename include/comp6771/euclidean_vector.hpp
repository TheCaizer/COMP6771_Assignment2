#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Mainly followed on where to implement and define the functions
		// https://edstem.org/au/courses/8629/discussion/928372

		// 1. Constructors
		// All constructors were not noexcepts since they allocate resources and
		// could throw exception.
		// implemented in hpp since they are mostly 1-2 line and to keep consistent with where
		// it is implemented

		// Default Constructor, just call the int double constructor
		euclidean_vector()
		: euclidean_vector(1, 0.0) {}

		// dimension only constructor
		explicit euclidean_vector(int dimensions)
		: euclidean_vector(dimensions, 0.0) {}

		// dimension and magnitude constructor
		euclidean_vector(int dimensions, double magnitude)
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		: magnitude_{std::make_unique<double[]>(static_cast<size_t>(dimensions))}
		, dimensions_{static_cast<std::size_t>(dimensions)}
		, norm_{-1} {
			// get the pointer to magnitude_ then fill the array with magnitude up to dimensions_
			std::fill(magnitude_.get(), magnitude_.get() + dimensions_, magnitude);
		}

		// iterator constructor
		// call the int constructor by finding distance between two iterator and then cast it as int
		// then just copy over the values
		euclidean_vector(std::vector<double>::const_iterator start,
		                 std::vector<double>::const_iterator end)
		: euclidean_vector(static_cast<int>(std::distance(start, end))) {
			std::copy(start, end, magnitude_.get());
		}

		// list constructor
		// find the size of list and call the int constructor then copy over the values
		// default constructor with empty list
		euclidean_vector(std::initializer_list<double> double_list)
		: euclidean_vector(static_cast<int>(double_list.size())) {
			std::copy(double_list.begin(), double_list.end(), magnitude_.get());
		}

		// Copy constructor
		// calls the int constructor by getting the dimensions then copy the norm
		// and then copy all the values
		euclidean_vector(euclidean_vector const& vec)
		: euclidean_vector(vec.dimensions()) {
			norm_ = vec.norm_;
			std::copy(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimensions(), magnitude_.get());
		}

		// Move Constructor
		// the moved_from should be 0 after move, just use exchange like the lectuire slides
		euclidean_vector(euclidean_vector&& vec) noexcept
		: magnitude_{std::exchange(vec.magnitude_, nullptr)}
		, dimensions_{std::exchange(vec.dimensions_, 0)}
		, norm_{std::exchange(vec.norm_, -1)} {}

		// 2. Destructor
		// declared explicitly as default
		~euclidean_vector() = default;

		// 3. Operations
		// declaration here definition in cpp
		auto operator=(euclidean_vector const&) -> euclidean_vector&;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;

		auto operator[](int const&) -> double&;
		auto operator[](int const&) const -> const double&;

		auto operator+() const -> euclidean_vector;
		auto operator-() const -> euclidean_vector;
		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		auto operator*=(double) noexcept -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;

		explicit operator std::vector<double>() const;
		explicit operator std::list<double>() const;

		// 4. Member
		// defining them here since they are quite short
		// double at() const
		[[nodiscard]] auto at(int index) const -> double {
			if (index < 0 || index >= this->dimensions()) {
				throw euclidean_vector_error("Index " + std::to_string(index)
				                             + " is not valid for this euclidean_vector object");
			}
			return magnitude_[static_cast<size_t>(index)];
		}
		// double at() non-const so norm can change
		[[nodiscard]] auto at(int index) -> double& {
			if (index < 0 || index >= this->dimensions()) {
				throw euclidean_vector_error("Index " + std::to_string(index)
				                             + " is not valid for this euclidean_vector object");
			}
			norm_ = -1;
			return magnitude_[static_cast<size_t>(index)];
		}
		// dimensions()
		[[nodiscard]] auto dimensions() const noexcept -> int {
			return static_cast<int>(dimensions_);
		}

		// 5. Friends
		// ==
		friend auto operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) noexcept
		   -> bool {
			if (lhs.dimensions() != rhs.dimensions()) {
				return false;
			}
			return std::equal(lhs.magnitude_.get(),
			                  lhs.magnitude_.get() + lhs.dimensions(),
			                  rhs.magnitude_.get());
		}
		// !=
		friend auto operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) noexcept
		   -> bool {
			return !(lhs == rhs);
		}

		// addition
		// dont have to check dimension since +=, -=, /= all check same execption when you call
		friend auto operator+(euclidean_vector const& lhs, euclidean_vector const& rhs)
		   -> euclidean_vector {
			return euclidean_vector(lhs) += rhs;
		}
		// subtraction
		friend auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs)
		   -> euclidean_vector {
			return euclidean_vector(lhs) -= rhs;
		}
		// multiplication
		friend auto operator*(euclidean_vector const& lhs, double rhs) noexcept -> euclidean_vector {
			return euclidean_vector(lhs) *= rhs;
		}
		// same as above just swap the ordering
		friend auto operator*(double lhs, euclidean_vector const& rhs) noexcept -> euclidean_vector {
			return euclidean_vector(rhs) *= lhs;
		}
		// division
		// same as +=, /= checks for zero rhs
		friend auto operator/(euclidean_vector const& lhs, double rhs) -> euclidean_vector {
			return euclidean_vector(lhs) /= rhs;
		}
		// ostream
		friend auto operator<<(std::ostream& os, euclidean_vector const& rhs) -> std::ostream& {
			auto stream = std::ostringstream();
			stream << '[';
			if (rhs.dimensions() != 0) {
				std::copy(rhs.magnitude_.get(),
				          rhs.magnitude_.get() + rhs.dimensions(),
				          std::ostream_iterator<double>(stream, " "));
				// remove last space
				stream.seekp(-1, std::ios_base::end);
			}
			stream << ']';
			os << stream.str();
			return os;
		}

	private:
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		std::size_t dimensions_;

		// if it is -1 it has not been calculated or invalid
		mutable double norm_;

		// helper function from lecture that swaps the other vector with this vector
		auto swap(euclidean_vector& other) noexcept -> void {
			std::swap(dimensions_, other.dimensions_);
			std::swap(magnitude_, other.magnitude_);
			std::swap(norm_, other.norm_);
		}

		friend auto euclidean_norm(euclidean_vector const& v) -> double;
	};
	// Utility function
	// euclidean_norm is a private friend so can acess norm_
	auto euclidean_norm(euclidean_vector const& v) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
