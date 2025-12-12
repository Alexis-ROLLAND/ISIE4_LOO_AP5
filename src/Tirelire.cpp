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
        // this->Vault.push_back(Coin);  /**< OK version */
        this->getVault().push_back(Coin); /**< Using getter version - cleaner */
}
//----------------------------------------------------------------------------
[[nodiscard]] std::size_t Tirelire::countCoins(Piece CoinType) {
    if (this->isCoinValid(CoinType))
        // return std::count(this->Vault.begin(), this->Vault.end(), CoinType);  /**< OK version */
        return std::count(
            this->getVault().begin(), this->getVault().end(), CoinType); /**< Using getter version - cleaner */

    else
        throw std::out_of_range("Coin is not valid");
}
//----------------------------------------------------------------------------
// #define USE_LOOP_SUMMATION   /**< Simple loop version and basic access to the Vault */
#define USE_ACCUMLATE_ALGO /**< Use of the STL accumulate algorithm with a lambda function to sum coin values - Use    \
                              getter to acces Vault - Cleaner*/

[[nodiscard]] unsigned int Tirelire::getTotal() noexcept {
    unsigned int Somme{0};

#ifdef USE_LOOP_SUMMATION
    for (unsigned int i = 0; i < this->Vault.size(); ++i) {
        Somme += static_cast<unsigned int>(this->Vault.at(i));
    }
#endif

#ifdef USE_ACCUMLATE_ALGO /**< Use of a lambda to sum coin values */
    Somme = std::accumulate(this->getVault().begin(), this->getVault().end(), 0u, [](unsigned int total, Piece coin) {
        return total + static_cast<unsigned int>(coin);
    });
#endif
    return Somme;
}
//----------------------------------------------------------------------------
void Tirelire::retrieve(Piece CoinType) {
    if (!this->isCoinValid(CoinType)) throw std::out_of_range("Coin is not valid");
    if (this->countCoins(CoinType) < 1) throw std::underflow_error("No corresponding coins inside the vault.");

    // auto it = std::find(this->Vault.begin(), this->Vault.end(), CoinType);    /**< OK version  */
    auto it =
        std::find(this->getVault().begin(), this->getVault().end(), CoinType); /**< Using getter version - cleaner */

    // this->Vault.erase(it);                     /**< OK version  */
    this->getVault().erase(it); /**< Using getter version - cleaner */
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
