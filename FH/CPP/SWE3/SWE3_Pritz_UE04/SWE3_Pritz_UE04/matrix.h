#ifndef MATRIX_H
#define MATRIX_H
#include<vector>

template<typename T>
class Matrix {
	typedef T value_t;
	
private:
	std::vector<std::vector<value_t>> elements;

	// Adds the value of another rational
	void add(Matrix<value_t> const& other)
	{
		int lhs_value = get_value();
		int rhs_value = other.get_value();
		elements[0][0] += other.elements[0][0];
	}
	// Subtracts the value of another rational
	void sub(Matrix<value_t> const& other)
	{
		elements[0][0] -= other.elements[0][0];
	}
	// Multiplies by the value of another rational
	void mul(Matrix<value_t> const& other)
	{
		elements[0][0] *= other.elements[0][0];
	}
	// Divides by the value of another rational
	void div(Matrix<value_t> const& other)
	{
		elements[0][0] /= other.elements[0][0];
	}

public:

	Matrix()
	{
		elements = std::vector<std::vector<value_t>>();
	}
	Matrix(T const& val)
	{
		elements = std::vector<std::vector<value_t>>();
		elements.push_back(std::vector<value_t>());
		elements[0].push_back(val);
	}
	~Matrix()
	{
		
	}

	T get_element() const
	{
		return elements[0][0];
	} 

	// inside matrix_t
	int get_value() {
		if (elements == nullptr || elements.empty() || elements[0].empty) {
			return 0;
		}
		else {
			return elements[0][0];
		}
	}

	Matrix<T> operator=(Matrix<T> const& other)
	{
		elements = std::vector<std::vector<value_t>>();
		elements.push_back(std::vector<value_t>());
		if(other.elements.size() == 1 && other.elements[0].size() == 1)
			elements[0].push_back(other.elements[0][0]);
		return *this;
	}
	Matrix<value_t> operator+(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.add(other);
		return tmp;
	}
	// Subtract operator override.
	Matrix<value_t> operator-(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.sub(other);
		return tmp;
	}
	// Multiply operator override.
	Matrix<value_t> operator*(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.mul(other);
		return tmp;
	}
	// Divide operator override.
	Matrix<value_t> operator/(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.div(other);
		return tmp;
	}
	// Add assignment operator override.
	Matrix<value_t> operator+=(Matrix<value_t> const& other)
	{
		add(other);
		return *this;
	}
	// Subtract assignment operator override.
	Matrix<value_t> operator-=(Matrix<value_t> const& other)
	{
		sub(other);
		return *this;
	}
	// Multiply assignment operator override.
	Matrix<value_t> operator*=(Matrix<value_t> const& other)
	{
		mul(other);
		return *this;
	}
	// Divide assignment operator override.
	Matrix<value_t> operator/=(Matrix<value_t> const& other)
	{
		div(other);
		return *this;
	}

	// Equal operator override.
	bool operator==(Matrix<value_t> const& other) const
	{
		return elements[0][0] == other.elements[0][0];
	}
	
	// Unequal operator override
	bool operator!=(Matrix<value_t> const& other) const
	{
		return elements[0][0] != other.elements[0][0];
	}
	// Greater than operator override
	bool operator>(Matrix<value_t> const& other) const
	{
		return elements[0][0] > other.elements[0][0];
	}
	// Less than operator override
	bool operator<(Matrix<value_t> const& other) const
	{
		return elements[0][0] < other.elements[0][0];
	}
	// Greater or equal than operator override
	bool operator>=(Matrix<value_t> const& other) const
	{
		return elements[0][0] >= other.elements[0][0];
	}
	// Less or equal than operator override
	bool operator<=(Matrix<value_t> const& other) const
	{
		return elements[0][0] <= other.elements[0][0];
	}
};

#endif