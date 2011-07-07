/* vim:set ts=4 sw=4 sts=4 et: */

#ifndef IGRAPHPP_VECTOR_H
#define IGRAPHPP_VECTOR_H

#include <cstring>
#include <igraph/cpp/error.h>
#include <igraph/cpp/types.h>

namespace igraph {

class Matrix;

/// C++-style wrapper around an igraph_vector_t
class Vector {
public:
    typedef real_t& reference;
    typedef real_t& const_reference;
    typedef real_t* iterator;
    typedef const real_t* const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef real_t value_type;
    typedef real_t* pointer;
    typedef const real_t* const_pointer;

private:
    /// The igraph_vector_t instance encapsulated by the wrapper
    igraph_vector_t m_vector;

    /// Whether we own the given igraph_vector_t instance or not
    bool m_owner;

public:
    /*****************************/
    /* Constructors, destructors */
    /*****************************/

    /// Constructs a vector
    explicit Vector(size_type length = 0, pointer data = 0) : m_owner(true) {
        if (data) {
            IGRAPH_TRY(igraph_vector_init_copy(&m_vector, data, length));
        } else
            IGRAPH_TRY(igraph_vector_init(&m_vector, length));
    }

    /// Constructs a wrapper that wraps the given igraph_vector_t instance
    /**
     * \param  own  specifies whether we own the given \c igraph_vector_t instance
     *              or not. If own is false, the encapsulated \c igraph_vector_t
     *              will not be destroyed when the \c Vector wrapper is destroyed.
     */
    Vector(igraph_vector_t vector, bool own=true) : m_vector(vector), m_owner(own) {}

    /// Constructs a wrapper that refers to the same vector as the given igraph_vector_t* pointer
    Vector(igraph_vector_t* vector, bool own=false) : m_vector(*vector), m_owner(own) {}

    /// Copy constructor
    Vector(const Vector& other) : m_owner(true) {
        IGRAPH_TRY(igraph_vector_copy(&m_vector, &other.m_vector));
    }

    /// Constructor from STL container
    template <typename InputIterator>
    Vector(InputIterator first, InputIterator last) {
        IGRAPH_TRY(igraph_vector_init(&m_vector, 0));
        while (first != last) {
            this->push_back(*first);
            ++first;
        }
    }

    /// Destroys the vector
    ~Vector() {
        if (m_owner)
            igraph_vector_destroy(&m_vector);
    }

    /******************/
    /* Static methods */
    /******************/

    /// Constructs a vector containing a sequence
    Vector Seq(value_type from, value_type to) {
        igraph_vector_t vec;
        IGRAPH_TRY(igraph_vector_init_seq(&vec, from, to));
        return Vector(vec);
    }

    /********************/
    /* Instance methods */
    /********************/

    /// Appends another vector to this one
    void append(const Vector& from) {
        IGRAPH_TRY(igraph_vector_append(&m_vector, &from.m_vector));
    }

    /// Returns an iterator pointing to the first element of the vector
    iterator begin() {
        return &(VECTOR(m_vector)[0]);
    }

    /// Returns an iterator pointing to the first element of the vector (const)
    const_iterator begin() const {
        return &(VECTOR(m_vector)[0]);
    }

    /// Returns the last element of the vector
    reference back() {
        return VECTOR(m_vector)[size()-1];
    }

    /// Returns the last element of the vector (const variant)
    const_reference back() const {
        return VECTOR(m_vector)[size()-1];
    }

    /// Finds an element using binary search in a sorted vector
    /**
     * Returns \c true if the element is found, \c false otherwise.
     * If \p pos is not null, it will be assigned to the position
     * where the element was found, or where it should be inserted
     * if the element was not found to keep the vector sorted.
     */
    bool binsearch(value_type what, long int *pos = 0) {
        return igraph_vector_binsearch(&m_vector, what, pos);
    }

    /// Removes all the elements from the vector
    /**
     * Note that this function sets the length of the vector to zero, but it
     * does not allocate previously used memory -- it is still kept in case
     * the vector has to grow again.
     */
    void clear() {
        igraph_vector_clear(&m_vector);
    }

    /// Returns whether a given element is in the vector, using linear search
    bool contains(value_type e) {
        return igraph_vector_contains(&m_vector, e);
    }

    /// Returns a pointer to the internal igraph_vector_t
    igraph_vector_t* c_vector() {
        return &m_vector;
    }

    /// Returns a const pointer to the internal igraph_vector_t
    const igraph_vector_t* c_vector() const {
        return &m_vector;
    }

    /// Returns whether the vector is empty
    bool empty() const {
        return igraph_vector_empty(&m_vector);
    }

    /// Returns an iterator pointing after the last element of the vector
    iterator end() {
        return &(VECTOR(m_vector)[size()]);
    }

    /// Returns an iterator pointing after the last element of the vector (const)
    const_iterator end() const {
        return &(VECTOR(m_vector)[size()]);
    }

    /// Fills the vector with the given item
    void fill(value_type element) {
        igraph_vector_fill(&m_vector, element);
    }

    /// Returns the first element of the vector
    reference front() {
        return VECTOR(m_vector)[0];
    }

    /// Returns the first element of the vector (const variant)
    const_reference front() const {
        return VECTOR(m_vector)[0];
    }

    /// Inserts an element into the vector at a given index
    void insert(long int index, value_type e) {
        IGRAPH_TRY(igraph_vector_insert(&m_vector, index, e));
    }

    /// Returns the minimum element of the vector
    value_type min() const {
        return igraph_vector_min(&m_vector);
    }

    /// Returns the maximum element of the vector
    value_type max() const {
        return igraph_vector_max(&m_vector);
    }

    /// Returns the maximum absolute difference between two vectors
    value_type maxdifference(const Vector& other) const {
        return igraph_vector_maxdifference(&m_vector, &other.m_vector);
    }

    /// Pops an element from the end of the vector
    value_type pop_back() {
        return igraph_vector_pop_back(&m_vector);
    }

    /// Prints the vector to the standard output
    void print() const {
        igraph_vector_print(&m_vector);
    }

    /// Adds a new element to the end of the vector
    void push_back(value_type e) {
        IGRAPH_TRY(igraph_vector_push_back(&m_vector, e));
    }

    /// Removes an element at the given index from the vector
    void remove(long int index) {
        igraph_vector_remove(&m_vector, index);
    }

    /// Removes a section of the vector
    void remove_section(long int from, long int to) {
        igraph_vector_remove_section(&m_vector, from, to);
    }

    /// Reserves space for the given number of elements in the vector
    void reserve(long int newsize) {
        IGRAPH_TRY(igraph_vector_reserve(&m_vector, newsize));
    }

    /// Resizes the vector
    void resize(long int newsize) {
        IGRAPH_TRY(igraph_vector_resize(&m_vector, newsize));
    }

    /// Searches the vector for a given element from the given position
    bool search(long int from, value_type what, long int* pos = 0) {
        return igraph_vector_search(&m_vector, from, what, pos);
    }

    /// Returns the size of the vector
    size_t size() const {
        return igraph_vector_size(&m_vector);
    }

    /// Sorts the elements of the vector into ascending order
    void sort() {
        igraph_vector_sort(&m_vector);
    }

    /// Returns the sum of the elements of the vector
    value_type sum() const {
        return igraph_vector_sum(&m_vector);
    }

    /// Swaps the elements of this vector with another one if they are of equal length
    void swap(Vector& v2) {
        IGRAPH_TRY(igraph_vector_swap(&m_vector, &v2.m_vector));
    }

    /*************/
    /* Operators */
    /*************/

    /// Assignment operator: copies the given vector to this one
    Vector& operator=(const Vector& other) {
        IGRAPH_TRY(igraph_vector_update(&m_vector, &other.m_vector));
        return *this;
    }

    /// Assignment operator: copies the given array to this vector
    /**
     * It is assumed that the array has the required size.
     */
    Vector& operator=(const pointer other) {
        memcpy(m_vector.stor_begin, other, size());
        return *this;
    }

    /// Equality check: returns true if the two vectors are equal
    bool operator==(const Vector& other) const {
        return igraph_vector_is_equal(&m_vector, &other.m_vector);
    }

    /// Nonequality check: returns true if the two vectors are not equal
    bool operator!=(const Vector& other) const {
        return !((*this) == other);
    }

    /// Returns the element with the given index
    reference operator[](long int index) {
        return VECTOR(m_vector)[index];
    }

    /// Returns the element with the given index (const variant)
    value_type operator[](long int index) const {
        return VECTOR(m_vector)[index];
    }

    /// In-place addition of a constant
    Vector& operator+=(value_type plus) {
        igraph_vector_add_constant(&m_vector, plus);
        return *this;
    }

    /// In-place addition of a vector
    Vector& operator+=(const Vector& v2) {
        IGRAPH_TRY(igraph_vector_add(&m_vector, &v2.m_vector));
        return *this;
    }

    /// Addition of a scalar to a vector
    Vector operator+(value_type plus) const {
        Vector result(*this);
        result += plus;
        return result;
    }

    /// In-place subtraction of a constant
    Vector& operator-=(value_type minus) {
        igraph_vector_add_constant(&m_vector, -minus);
        return *this;
    }

    /// In-place subtraction of a vector
    Vector& operator-=(const Vector& v2) {
        IGRAPH_TRY(igraph_vector_sub(&m_vector, &v2.m_vector));
        return *this;
    }

    /// Negation of a vector
    Vector operator-(void) const {
        return (*this) * -1;
    }

    /// Subtraction of a scalar from a vector
    Vector operator-(value_type minus) const {
        Vector result(*this);
        result -= minus;
        return result;
    }

    /// In-place multiplication by a constant
    Vector& operator*=(const value_type by) {
        igraph_vector_scale(&m_vector, by);
        return *this;
    }

    /// In-place division by a constant
    Vector& operator/=(value_type by) {
        igraph_vector_scale(&m_vector, 1.0 / by);
        return *this;
    }

    /// Multiplication by a constant
    Vector operator*(value_type by) const {
        Vector result(*this);
        result *= by;
        return result;
    }

    /// Division by a constant
    Vector operator/(value_type by) const {
        Vector result(*this);
        result /= by;
        return result;
    }

    /// Vector-vector scalar product
    double operator*(const Vector& vector) const;

    /// Matrix-vector product, matrix is on the right
    Vector operator*(const Matrix& matrix) const;
};

/// Addition of a constant to a vector from the left
Vector operator+(real_t plus, const Vector& vector);

/// Subtraction of a constant from a vector from the left
Vector operator-(real_t minus, const Vector& vector);

/// Multiplication of a vector by a constant from the left
Vector operator*(real_t by, const Vector& vector);


}       // end of namespaces

#endif  // IGRAPHPP_VECTOR_H

