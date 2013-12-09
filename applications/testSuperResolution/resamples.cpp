﻿#include "resamples.h"
#include <cmath>
RGB24Buffer *resampleWithBilinearInterpolation(RGB24Buffer *startImage, double coefficient)
{
    RGB24Buffer *result = new RGB24Buffer((int)(startImage -> getH()*coefficient),(int)(startImage -> getW()*coefficient),false);
    for (int i = 0; i < result -> getH(); i++)
        for (int j = 0 ; j < result -> getW(); j++)
        {
            int xLeft = floor(((double)i) / coefficient);
            int yLeft = floor(((double)j) / coefficient);
            int xRight = min (xLeft+1,startImage -> getH()-1);
            int yRight = min (yLeft+1,startImage -> getW()-1);
            double k1 = ((double)i)/coefficient - (double)xLeft;
            double k2 = ((double)j)/coefficient - (double)yLeft;

            result -> element(i,j).r() =
                    startImage -> element(xLeft,yLeft).r() * k1 * k2 +
                    startImage -> element(xLeft,yRight).r() * k1 * (1 - k2) +
                    startImage -> element(xRight,yLeft).r() * (1 - k1) * k2 +
                    startImage -> element(xRight,yRight).r() * (1- k1) * (1 - k2);

            result -> element(i,j).g() =
                    startImage -> element(xLeft,yLeft).g() * k1 * k2 +
                    startImage -> element(xLeft,yRight).g() * k1 * (1 - k2) +
                    startImage -> element(xRight,yLeft).g() * (1 - k1) * k2 +
                    startImage -> element(xRight,yRight).g() * (1- k1) * (1 - k2);

            result -> element(i,j).b() =
                    startImage -> element(xLeft,yLeft).b() * k1 * k2 +
                    startImage -> element(xLeft,yRight).b() * k1 * (1 - k2) +
                    startImage -> element(xRight,yLeft).b() * (1 - k1) * k2 +
                    startImage -> element(xRight,yRight).b() * (1- k1) * (1 - k2);
        }
    return result;
}



/*RGBColor cubicPolynomial(RGBColor p0, RGBColor p1, RGBColor p2, RGBColor p3, double x)
{
    return p1 + 0.5 * x*(p2 - p0 + x*(2.0*p0 - 5.0*p1 + 4.0*p2 - p3 + x*(3.0*(p1 - p2) + p3 - p4)));
}*/

RGB24Buffer *resampleWithBicubicInterpolation(RGB24Buffer *startImage, double coefficient)
{
    RGB24Buffer *result = new RGB24Buffer((int)(startImage -> getH()*coefficient),(int)(startImage -> getW()*coefficient),false);

    /*for (int i = 0; i < result -> getH; i++)
        for (int j = 0; j < result -> getW; j++)
        {
            int si = (int)(i / coefficient);
            int sj = (int)(j / coefficient);
            double dx = (i / coefficient) - si;
            double dy = (j / coefficient) - sj;
            if ((si > 0) && (si < startImage -> getH - 2))
            {
                if ((sj > 0) && (sj < startImage -> getW - 2))
                {
                    RGBColor temp0 = cubicPolynomial(startImage -> element(si-1,sj).)
                }
            }
        }*/

    return result;
}



double LancsozFilter(double dist, int a)
{
    if (dist == 0)
        return 1;
    if (abs(dist) >= a)
        return 0;
    return (double)a * sin (M_PI * dist) * sin (M_PI * dist/(double)a) / (M_PI*M_PI*(double)a * (double)a);
}


RGB24Buffer *resampleWithLancsozFilter(RGB24Buffer *startImage, double coefficient, int a)
{
    RGB24Buffer *tempHorImage = new RGB24Buffer((int)(startImage -> getH()),(int)(startImage -> getW()*coefficient),false);
    for (int i = 0 ; i < tempHorImage -> getH(); i++)
        for (int j = 0; j < tempHorImage -> getW(); j++)
        {
            double nearY = floor(j / coefficient);
            uint8_t sumR = 0;
            uint8_t sumG = 0;
            uint8_t sumB = 0;
            double weight = 0;
            for (int y = nearY - a + 1; y < nearY + a; y++) {
                if ((y >= 0) && (y < startImage -> getW()))
                {
                    double lanc = LancsozFilter(nearY - y, a);
                    sumR += startImage -> element(i,y).r() * lanc;
                    sumG += startImage -> element(i,y).g() * lanc;
                    sumB += startImage -> element(i,y).b() * lanc;
                    weight += lanc;
                }
            }
            tempHorImage -> element(i,j).r() = sumR/weight;
            tempHorImage -> element(i,j).g() = sumG/weight;
            tempHorImage -> element(i,j).b() = sumB/weight;
        }

    RGB24Buffer *result = new RGB24Buffer((int)(tempHorImage -> getH()*coefficient),tempHorImage -> getW(),false);
    for (int i = 0 ; i < result -> getH(); i++)
        for (int j = 0; j < result -> getW(); j++)
        {
            double nearX = floor( i / coefficient);
            uint8_t sumR = 0;
            uint8_t sumG = 0;
            uint8_t sumB = 0;
            double weight = 0;
            for (int x = nearX - a + 1; x < nearX + a; x++) {
                if ((x >= 0) && (x < tempHorImage -> getH()))
                {
                    double lanc = LancsozFilter(nearX - x, a);
                    sumR += tempHorImage -> element(x,j).r() * lanc;
                    sumG += tempHorImage -> element(x,j).g() * lanc;
                    sumB += tempHorImage -> element(x,j).b() * lanc;
                    weight += lanc;
                }
            }
            result -> element(i,j).r() = sumR/weight;
            result -> element(i,j).g() = sumG/weight;
            result -> element(i,j).b() = sumB/weight;
        }
    delete_safe(tempHorImage);
    return result;
}


RGB24Buffer *resampleWithNearestNeighbour(RGB24Buffer *startImage, double coefficient) {
    RGB24Buffer *result = new RGB24Buffer((int)(startImage -> getH()*coefficient),(int)(startImage -> getW()*coefficient),false);
    for (int i = 0; i < result -> getH(); i++)
        for (int j = 0 ; j < result -> getW(); j++)
        {
            int xLeft = floor(((double)i) / coefficient);
            int yLeft = floor(((double)j) / coefficient);
            int xRight = min (xLeft+1,startImage -> getH()-1);
            int yRight = min (yLeft+1,startImage -> getW()-1);
            double k1 = ((double)i)/coefficient - (double)xLeft;
            double k2 = ((double)j)/coefficient - (double)yLeft;

            if (k1 > 0.5)
            {
                if (k2 > 0.5)
                    result -> element(i,j) = startImage -> element(xRight,yRight);
                else
                    result -> element(i,j) = startImage -> element(xRight,yLeft);
            }
            else
            {
                if (k2 > 0.5)
                    result -> element(i,j) = startImage -> element(xLeft,yRight);
                else
                    result -> element(i,j) = startImage -> element(xLeft,yLeft);
            }
        }
    return result;
}
