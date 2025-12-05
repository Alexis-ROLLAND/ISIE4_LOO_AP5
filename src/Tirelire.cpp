#include "Tirelire.hpp"

//----------------------------------------------------------------------------
[[nodiscard]] bool Tirelire::isCoinValid(Piece Coin) noexcept {
    switch (Coin) {
    case Piece::ONECENT:
    case Piece::TWOCENTS:
    case Piece::FIVECENTS:
    case Piece::TENCENTS:
    case Piece::TWENTYCENTS:
    case Piece::FIFTYCENTS:
    case Piece::ONEEURO:
    case Piece::TWOEUROS:
        return true;
        break;
    default:
        return false;
        break;
    }
}
//----------------------------------------------------------------------------
void Tirelire::add(Piece Coin) {
    if (!this->isCoinValid(Coin))
        throw std::out_of_range("Coin is not valid");
    else
        this->Vault.push_back(Coin);
}
//----------------------------------------------------------------------------
[[nodiscard]] std::size_t Tirelire::countCoins(Piece CoinType) {
    if (this->isCoinValid(CoinType))
        return std::count(this->Vault.begin(), this->Vault.end(), CoinType);
    else
        throw std::out_of_range("Coin is not valid");
}
//----------------------------------------------------------------------------
// #define USE_LOOP_SUMMATION
#define USE_ACCUMLATE_ALGO

[[nodiscard]] unsigned int Tirelire::getTotal() noexcept {
    unsigned int Somme{0};

#ifdef USE_LOOP_SUMMATION
    for (unsigned int i = 0; i < this->Vault.size(); ++i) {
        Somme += static_cast<unsigned int>(this->Vault.at(i));
    }
#endif

#ifdef USE_ACCUMLATE_ALGO /**< Use of a lambda to sum coin values */
    Somme = std::accumulate(this->Vault.begin(), this->Vault.end(), 0U, [](unsigned int total, Piece coin) {
        return total + static_cast<unsigned int>(coin);
    });
#endif
    return Somme;
}
//----------------------------------------------------------------------------
void Tirelire::retrieve(Piece CoinType) {
    if (!this->isCoinValid(CoinType)) throw std::out_of_range("Coin is not valid");
    if (this->countCoins(CoinType) < 1) throw std::underflow_error("No corresponding coins inside the vault.");

    auto it = std::find(this->Vault.begin(), this->Vault.end(), CoinType);

    this->Vault.erase(it);
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
