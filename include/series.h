#include<iostream>
#include "capd/capdlib.h"

#ifndef SERIES_H
#define SERIES_H


template<typename T, class SeriesType>
class FunctionSeries{
protected:
    typedef capd::vectalg::Vector<T,0> Vector;

    int n;
    Vector coeffs;
    T remainder;

public:
    FunctionSeries() : n(0), coeffs({}), remainder(0) {}
    FunctionSeries(Vector coeffs) : n(coeffs.dimension()), coeffs(coeffs), remainder(0) {}
    FunctionSeries(Vector coeffs, T remainder) : n(coeffs.dimension()), coeffs(coeffs), remainder(remainder) {}
    FunctionSeries(std::initializer_list<T> coeffs) : n(coeffs.size()), coeffs(coeffs), remainder(0) {}
    FunctionSeries(std::initializer_list<T> coeffs, T remainder) : n(coeffs.size()), coeffs(coeffs), remainder(remainder) {}

    T& operator[](int k) {return coeffs[k];}
    const T& operator[](int k) const {return coeffs[k];}

    int& dim() {return n;}
    const int& dim() const {return n;}

    SeriesType operator+(const SeriesType& other) const {
        assert(this->n == other.n);
        return SeriesType(this->coeffs + other.coeffs, this->remainder + other.remainder);
    }

    SeriesType operator-(const SeriesType& other) const {
        assert(this->n == other.n);
        return SeriesType(this->coeffs - other.coeffs, this->remainder + other.remainder);
    }

    virtual SeriesType operator*(const SeriesType& other) const = 0;

    friend SeriesType operator*(const SeriesType& S, const T& scalar) {
        return SeriesType(scalar * S.coeffs, capd::abs(scalar) * S.remainder);
    }

    friend SeriesType operator*(const T& scalar, const SeriesType& S) {
        return S * scalar;
    }
    
    friend std::ostream& operator<<(std::ostream& ost, const SeriesType &s) {
        ost << s.coeffs << ", " << s.remainder;
        return ost;
    }


    // T norml1_weighted() const {
    //     T norm_weight = 1.0;
    //     T res = 0;
    //     T geometric_coeff = 1;

    //     for(int i = 0; i < this->n; i++) {
    //         res += geometric_coeff * capd::abs(this->operator[](i));
    //         geometric_coeff *= norm_weight;
    //     }
    //     res += this->remainder;
    //     return res;
    // }
};

template<typename T>
class TaylorSeries : public FunctionSeries<T, TaylorSeries<T>>{
    typedef capd::vectalg::Vector<T,0> Vector;
public:
    using FunctionSeries<T, TaylorSeries<T>>::FunctionSeries;
    TaylorSeries operator*(const TaylorSeries& other) const override {
        int dim = this->n;
        
        assert(dim == other.n);
        Vector res_coeffs(dim);
        Vector rem_coeffs(dim - 1);

        T zero(0);

        for(int k = 0; k < 2 * dim - 1; k++) {
            for(int i = 0; i <= k; i++) {
                T mult_res = (i < dim && (k - i) < dim) ? this->coeffs[i] * other[k - i] : zero;
                if(k < dim)
                    res_coeffs[k] += mult_res;
                else
                    rem_coeffs[k - dim] += mult_res;
            }
        }

        // zaimplementowac jeszcze remainder do wyliczenia

        // T res_tail = TaylorSeries(rem_coeffs).norml1_weighted();
        // res_tail += this->norml1_weighted() * other.remainder;
        // res_tail += other.norml1_weighted() * this->remainder;
        // res_tail += this->remainder * other.remainder;

        return TaylorSeries(res_coeffs);
    }


    
};

#endif