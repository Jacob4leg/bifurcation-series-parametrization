#include<iostream>
#include<functional>
#include "capd/capdlib.h"
#include "series.h"
#include "seriesSystem.h"

#ifndef SERIES_MAP_H
#define SERIES_MAP_H

using capd::autodiff::Node;



template<
typename T,
template<typename> class SeriesType,
template<typename,template<typename> class> class SystemType
>
class SeriesMap {
    typedef SeriesType<T> SeriesT;
    typedef SeriesType<Node> SeriesNode;

    template<typename type>
    using series_function_2D = SystemType<type, SeriesType>;

    typedef capd::vectalg::Matrix<T,0,0> MatrixType;
    typedef capd::map::Map<MatrixType> Map;
    typedef capd::vectalg::Vector<Node,0> NodeVector;
    typedef capd::vectalg::Vector<T,0> Vector;

    series_function_2D<T> fun_t;
    
    Map map;

    int n;

    static void nodeMap(Node /*t*/, Node in[], int dimIn, Node out[], int dimOut, Node params[], int noParams) {
        series_function_2D<Node> fun_node;
        
        assert(dimIn % 2 == 0);

        int n = dimIn / 2;
        
        assert(dimIn == dimOut);
        assert(noParams == 0);

        NodeVector v_in(dimIn);

        for(int i = 0; i < dimIn; i++) {
            v_in[i] = in[i];
        }

        NodeVector x(v_in.begin(), v_in.begin() + n);
        NodeVector y(v_in.begin() + n, v_in.end());
        
        SeriesNode series_x(x);
        SeriesNode series_y(y);

        auto series_out = fun_node(series_x, series_y);

        for(int i = 0; i < n; i++) {
            out[i] = series_out[0][i];
            out[n + i] = series_out[1][i];
        }
    }

    Map createSeriesTypeMap() {
        int dimIn = 2 * n, dimOut = 2 * n, noParams = 0;
        return Map(nodeMap, dimIn, dimOut, noParams);
    }

public:

    SeriesMap(int n) : n(n) {
        this->map = createSeriesTypeMap();
    }

    Vector operator()(SeriesType<T> x, SeriesType<T> y) {
        Vector v(2 * n);
        for(int i = 0; i < n; i++) {
            v[i] = x[i];
            v[n + i] = y[i];
        }
        return map(v);
    }

    // Vector findFixedPointCurve(Vector x) {
    //     assert(x.dimension() == 2 * n);

    //     double epsilon = 1e-6;

    //     Vector y;
    //     MatrixType Df(2 * n, 2 * n);
    //     MatrixType Id = MatrixType::Identity(2 * n);
    //     y = map(x,Df);

    //     std::cout << Df << std::endl;

    //     Vector N = -capd::matrixAlgorithms::gauss(Df - Id,y - x);
        
    //     Vector x1 = x + N;
    //     std::cout << x1 << std::endl;

    //     if(N.euclNorm() < epsilon)
    //         return x1;
    //     return findFixedPointCurve(x1);
    // }

};


#endif