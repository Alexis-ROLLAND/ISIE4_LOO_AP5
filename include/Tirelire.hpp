/**
 *	@file	Tirelire.hpp
 * 	@brief
 * 	@author	Alexis ROLLAND
 * 	@date	2025-12
 *
 */

/** Code Guards : empêche les inclusions multiples - Idem C */
#ifndef __TIRELIRE_HPP__
#define __TIRELIRE_HPP__

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <print>
#include <stdexcept>
#include <vector>
/**
 * Tirelire class
 */
class Tirelire {
  public:
    enum class Piece : uint8_t {
        ONECENT = 1,      /**< 1 cent coin - Value is 1 cent          */
        TWOCENTS = 2,     /**< 2 cents coin - Value is 2 cents        */
        FIVECENTS = 5,    /**< 5 cents coin - Value is 5 cents        */
        TENCENTS = 10,    /**< 10 cents coin - Value is 10 cents      */
        TWENTYCENTS = 20, /**< 20 cents coin - Value is 20 cents      */
        FIFTYCENTS = 50,  /**< 50 cents coin - Value is 50 cents      */
        ONEEURO = 100,    /**< 1 euro coin - Value is 100 cents       */
        TWOEUROS = 200    /**< 2 euros coin - Value is 100 cents      */
    };

  private:
    std::vector<Piece> Vault{}; /**< Container for coins inside the vault */

    /**
     * @brief Checks if a coin is valid
     *
     * @param Coin
     * @return true if coin is valid
     * @return false if coin is not valid
     */
    [[nodiscard]] bool isCoinValid(Piece Coin) noexcept;

  public:
    Tirelire() = default;                                     /**< Default constructor */
    Tirelire(const Tirelire &other) = default;                /**< Copy constructor */
    Tirelire(Tirelire &&other) noexcept = default;            /**< Move constructor */
    Tirelire &operator=(const Tirelire &other) = default;     /**< Copy assignment operator */
    Tirelire &operator=(Tirelire &&other) noexcept = default; /**< Move assignment operator */
    virtual ~Tirelire() = default;                            /**< Default destructor */

    /**
     * @brief Checks if the vault is empty
     *
     * @return true if the vault is empty
     * @return false if the vault is not empty
     */
    [[nodiscard]] bool isEmpty() noexcept { return this->Vault.empty(); };

    /**
     * @brief Get the Nb Coins object
     *
     * @return auto
     * @remark auto return type to automaticaly adjust to std::size_t() or other real return type from size() function.
     */
    [[nodiscard]] auto getNbCoins() noexcept { return this->Vault.size(); };

    /**
     * @brief Adds a coin to the vault
     *
     * @param Coin The coin to add
     */
    void add(Piece Coin);

    /** @brief Gets the total value of coins inside the vault
     *
     * @return unsigned int Total value in centimes
     */
    [[nodiscard]] unsigned int getTotal() noexcept;

    /**
     * @brief Counts the number of coins of a specific type in the vault
     *
     * @param CoinType The type of coin to count
     * @return std::size_t The number of coins of the specified type
     */
    [[nodiscard]] std::size_t countCoins(Piece CoinType);

    /**
     * @brief Retrieves (removes) a coin of a specific type from the vault
     *
     * @param CoinType The type of coin to retrieve
     */
    void retrieve(Piece CoinType);
};

#endif /*  __TIRELIRE_HPP__ */
