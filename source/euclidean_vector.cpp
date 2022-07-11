// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <algorithm>
#include <comp6771/euclidean_vector.hpp>
#include <numeric>
#include <string>

namespace comp6771 {
	// copy assignment
	auto euclidean_vector::operator=(euclidean_vector const& orig) -> euclidean_vector& {
		// coding against self assignment
		if (std::addressof(*this) == std::addressof(orig)) {
			return *this;
		}
		euclidean_vector(orig).swap(*this);
		return *this;
	}
	// move assignment
	auto euclidean_vector::operator=(euclidean_vector&& orig) noexcept -> euclidean_vector& {
		// coding against self assignment
		if (std::addressof(*this) == std::addressof(orig)) {
			return *this;
		}
		this->swap(orig);
		// set as zero dimension for moved from.
		orig.dimensions_ = 0;
		orig.magnitude_.reset();
		orig.norm_ = -1;

		return *this;
	}
	// set norm as -1 since vector can change non-const
	auto euclidean_vector::operator[](int const& index) -> double& {
		norm_ = -1;
		return magnitude_[static_cast<size_t>(index)];
	}
	// no need to handle out of range inputs
	auto euclidean_vector::operator[](int const& index) const -> const double& {
		return magnitude_[static_cast<size_t>(index)];
	}
	// returns a copy of current object
	// shouldnt be noexpect since you are making a copy then returning
	auto euclidean_vector::operator+() const -> euclidean_vector {
		return euclidean_vector(*this);
	}
	// shouldnt be noexpect since you are making a copy then returning
	auto euclidean_vector::operator-() const -> euclidean_vector {
		auto copy = euclidean_vector(*this);
		std::transform(copy.magnitude_.get(),
		               copy.magnitude_.get() + copy.dimensions(),
		               copy.magnitude_.get(),
		               [](double& mag) { return -mag; });
		return copy;
	}
	// throw euclidean vector error when not same dimension and set norm as negative
	auto euclidean_vector::operator+=(euclidean_vector const& rhs) -> euclidean_vector& {
		if (rhs.dimensions() != static_cast<int>(this->dimensions())) {
			throw euclidean_vector_error("Dimensions of LHS (" + std::to_string(this->dimensions())
			                             + ") and RHS(" + std::to_string(rhs.dimensions())
			                             + ") do not match");
		}
		norm_ = -1;
		std::transform(magnitude_.get(),
		               magnitude_.get() + this->dimensions(),
		               rhs.magnitude_.get(),
		               magnitude_.get(),
		               std::plus<>());
		return *this;
	}
	// throw euclidean vector error when not same dimension and set norm as negative
	auto euclidean_vector::operator-=(euclidean_vector const& rhs) -> euclidean_vector& {
		if (rhs.dimensions() != static_cast<int>(this->dimensions())) {
			throw euclidean_vector_error("Dimensions of LHS (" + std::to_string(this->dimensions())
			                             + ") and RHS(" + std::to_string(rhs.dimensions())
			                             + ") do not match");
		}
		norm_ = -1;
		std::transform(magnitude_.get(),
		               magnitude_.get() + this->dimensions(),
		               rhs.magnitude_.get(),
		               magnitude_.get(),
		               std::minus<>());
		return *this;
	}
	// shouldnt throw exceptions when multiplying
	auto euclidean_vector::operator*=(double rhs) noexcept -> euclidean_vector& {
		norm_ = -1;
		std::transform(magnitude_.get(),
		               magnitude_.get() + this->dimensions(),
		               magnitude_.get(),
		               [rhs](double& mag) { return mag * rhs; });
		return *this;
	}
	auto euclidean_vector::operator/=(double rhs) -> euclidean_vector& {
		if (rhs == 0.0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		norm_ = -1;
		std::transform(magnitude_.get(),
		               magnitude_.get() + this->dimensions(),
		               magnitude_.get(),
		               [rhs](double& mag) { return mag / rhs; });
		return *this;
	}
	// this can also throw exceptions since it is allocating resource for a vector
	// ditto for the list as well
	// Can just call the iterator construction for list and vector
	euclidean_vector::operator std::vector<double>() const {
		return std::vector<double>(magnitude_.get(), magnitude_.get() + this->dimensions());
	}
	euclidean_vector::operator std::list<double>() const {
		return std::list<double>(magnitude_.get(), magnitude_.get() + this->dimensions());
	}
	// Euclidean Norm
	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.norm_ != -1) {
			return v.norm_;
		}
		if (v.dimensions() == 0) {
			v.norm_ = 0;
			return v.norm_;
		}
		v.norm_ = std::sqrt(std::inner_product(v.magnitude_.get(),
		                                       v.magnitude_.get() + v.dimensions(),
		                                       v.magnitude_.get(),
		                                       0.0));
		return v.norm_;
	}
	// unit
	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		auto norm = euclidean_norm(v);
		if (norm == 0.0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		return euclidean_vector(v) /= norm;
	}
	// dot
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(x.dimensions())
			                             + ") and RHS(" + std::to_string(y.dimensions())
			                             + ") do not match");
		}
		// use address of subscript to get the start of iterators since magnitude is pricate
		return std::inner_product(&x[0], &x[0] + x.dimensions(), &y[0], 0.0);
	}
} // namespace comp6771
