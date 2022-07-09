#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <memory>
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
		// 1. Constructors
		euclidean_vector();
		explicit euclidean_vector(int);
		euclidean_vector(int, double);
		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
		euclidean_vector(std::initializer_list<double>);
		euclidean_vector(euclidean_vector const&);
		euclidean_vector(euclidean_vector&&) noexcept;
		// 2. Destructor
		~euclidean_vector() = default;

	private:
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		int dimension_;
		double norm_;
	};
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
