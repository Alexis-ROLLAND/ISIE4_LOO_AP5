//----------------------------------------------------------------------
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN /*! Use if doctest with its own main function*/
#include "doctest.h"
//----------------------------------------------------------------------

#include "Tirelire.hpp"

TEST_CASE("Tirelire tests") {
    Tirelire SpiderCochon{};

    CHECK(SpiderCochon.isEmpty() == true);

    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::ONECENT));
    CHECK(SpiderCochon.isEmpty() == false);

    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::TWOCENTS));
    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::FIVECENTS));
    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::TENCENTS));
    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::TWENTYCENTS));
    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::FIFTYCENTS));
    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::ONEEURO));
    CHECK_NOTHROW(SpiderCochon.add(Tirelire::Piece::TWOEUROS));

    CHECK_THROWS_WITH_AS(SpiderCochon.add(static_cast<Tirelire::Piece>(25)), "Coin is not valid", std::out_of_range);

    CHECK(SpiderCochon.getNbCoins() == 8);

    CHECK_NOTHROW(SpiderCochon.retrieve(Tirelire::Piece::ONECENT));
    CHECK(SpiderCochon.getNbCoins() == 7);
    CHECK_THROWS_WITH_AS(SpiderCochon.retrieve(Tirelire::Piece::ONECENT),
                         "No corresponding coins inside the vault.",
                         std::underflow_error);
    CHECK(SpiderCochon.getNbCoins() == 7);
    CHECK(SpiderCochon.countCoins(Tirelire::Piece::TWOCENTS) == 1);

    CHECK(SpiderCochon.getTotal() == 387);
}
