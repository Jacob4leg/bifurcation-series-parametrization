#include<iostream>
#include<functional>
#include<vector>
#include "capd/capdlib.h"
// #include "seriesMap.h"
// #include "capd/dynsys/FadMap.h"
// #include "series.h"
#include "seriesSystem.h"
#include "seriesMap.h"

using namespace std;
using namespace capd;

using capd::autodiff::Node;


int main() {
    int dim = 2;

    SeriesMap<long double,TaylorSeries,HenonMap> henon(dim);

    long double coeffs[] = {1.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    LDVector x(dim,coeffs);
    LDVector y(dim,coeffs);

    TaylorSeries<long double> s_x(x);
    TaylorSeries<long double> s_y(y);

    LDVector v(2 * dim);
    
    for(int i = 0; i < dim; i++) {
        v[i] = x[i];
        v[dim + i] = y[i];
    }

    cout << v << endl;
    cout << henon(s_x,s_y) << endl;
    // cout << henon.findFixedPointCurve(v) << endl;

    // HenonMap<double,TaylorSeries> henon;
    // TaylorSeries<double> x({1,2,3,4,5,6});
    // TaylorSeries<double> y({1,1,1,1,1,1});

    // cout << henon(x,y) << endl;

    // SeriesMap<double,TaylorSeries, HenonMap> m(6);
    // cout << m(x,y) << endl;


    // auto f = [](double x) {return x + x;};


    // Function<double> F(f);

    // cout<< F(2.0) << endl;

    // DVector v{0,1,2,3,4,5};
    // cout << DVector(v.begin(), v.begin() + 3) << endl;

    // auto fun = [](TaylorSeries<double> x, TaylorSeries<double> y) {
    //     return x + y;
    // };

    // SeriesMap<double,TaylorSeries<double>> map(3, fun); 
    // auto fun = [](TaylorSeries<double> x, TaylorSeries<double> y) {
    //     return x * x + 2 * y;
    // };

    // // capd::map::Map<capd::vectalg::Matrix<DVector,0,0>> fun;

    // // DMap fun("var:x,y;fun:x+y,x;");
    // // DVector v{1,2};

    // // cout << fun.getMask(2) << endl;

    // TaylorSeries<double> series1({1,2,3});
    // TaylorSeries<double> series2({2,3,5});
    // // TaylorSeries<double> series1 = series + series;
    // cout << fun(series1, series2) << endl;
}