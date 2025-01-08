#include<iostream>
#include<vector>
#include "capd/capdlib.h"
#include "series.h"

#ifndef SERIES_SYSTEM_H
#define SERIES_SYSTEM_H



template<typename T, template<typename> class SeriesType>
class SeriesSystem{
    typedef std::vector<SeriesType<T>> SeriesVector;
public:

    template<typename U>
    using SeriesTypeAlias = SeriesType<U>;

    virtual SeriesVector evaluate(SeriesType<T> x, SeriesType<T> y) = 0;
    SeriesVector operator()(SeriesType<T> x, SeriesType<T> y) {return evaluate(x,y);}
};

template<typename T, template<typename> class SeriesType>
class HenonMap : public SeriesSystem<T,SeriesType>{
    typedef std::vector<SeriesType<T>> SeriesVector;
    typedef capd::vectalg::Vector<T,0> Vector;
public:
    SeriesVector evaluate(SeriesType<T> x, SeriesType<T> y) {
        assert(x.dim() == y.dim());
        int n = x.dim();
        Vector v_param(n);
        Vector v_scalar(n);

        T one(1);

        v_param[1] = one;
        v_scalar[0] = one;
        SeriesType<T> series_param(v_param);
        SeriesType<T> series_scalar(v_scalar);

        SeriesType<T> out_1 = series_scalar - series_param * x * x + y;
        SeriesType<T> out_2 = x;

        return SeriesVector{out_1, out_2};
    }
};


#endif