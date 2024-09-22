#include "DummyCapteurTemp.hpp"


float DummyCapteurTemp::getTemp() const noexcept{

    float temp{0};

    std::random_device rdev{};
    this->generator.seed(rdev());

    std::uniform_int_distribution<int16_t> distrib{this->getTmin(), this->getTmax()};   /** Construction du "vrai générateur" de nombres aléatoires*/

    int16_t rndValue;
    uint16_t Ecart;

    do{
        rndValue = distrib(this->generator);
        Ecart = std::abs(rndValue - this->getprevTemp());
    } while (Ecart > this->getDeltaMax());

    this->setprevTemp(rndValue);
    temp = static_cast<float>(rndValue) / 10.0;

    return temp;
}

