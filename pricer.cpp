#include "pricer.h"
#include "idatabase.h"

Pricer::Pricer() {}

const double Wood_BasePrice = 5.0;
const double Metal_BasePrice = 10.0;
const double S_PriceFactor = 1.0;
const double M_PriceFactor = 1.5;
const double L_PriceFactor = 2;

double Pricer::getPriceAPI(int materialType, int materialSize)
{
    MaterialType mt = (MaterialType)materialType;
    MaterialSize ms = (MaterialSize)materialSize;
    double basePrice = 0;
    double factorPrice = 0;
    if (mt == MaterialType::mtWood) {
        basePrice = Wood_BasePrice;
    } else if (mt == MaterialType::mtMetal) {
        basePrice = Metal_BasePrice;
    }
    if (ms == MaterialSize::msS) {
        factorPrice = S_PriceFactor;
    } else if ((ms == MaterialSize::msM)) {
        factorPrice = M_PriceFactor;
    } else if ((ms == MaterialSize::msL)) {
        factorPrice = L_PriceFactor;
    }
    if (basePrice > 0 && factorPrice > 0) {
        return (basePrice * factorPrice);
    }
    return -1;
}
