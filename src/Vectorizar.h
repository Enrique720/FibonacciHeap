#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include "CImg/CImg.h"

using namespace cimg_library;
using namespace std;

template <class T>
vector<T> Vectorizar(string filename, int width, int height, int cuts=3)
{
    vector<T> R;
    CImg<T> img(filename.c_str());
    img.resize(width, height);
    CImg<T> img2 = img.haar(false, cuts);
    CImg<T> img3 = img2.crop(0, 0, 16, 16);
    cimg_forXY(img3, x, y) 
    { 
        R.push_back((img(x, y, 0) + img(x, y, 1) +  img(x, y, 2)) / 3);
    }
    return R;
}

