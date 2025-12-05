
#include <chrono>
#include <iostream>
#include <thread>

#include "Tirelire.hpp"
//----------------------------------------------------------------------------
void _Voleur(Tirelire &Victime) {
    using namespace std::chrono_literals;
    Tirelire::Piece Msc{}; /** Most Significant Coin   :)  */

    while (!Victime.isEmpty()) {
        std::this_thread::sleep_for(5s);
        std::println("Tentative de vol...");
        if (Victime.countCoins(Tirelire::Piece::TWOEUROS) > 0)
            Msc = Tirelire::Piece::TWOEUROS;
        else if (Victime.countCoins(Tirelire::Piece::ONEEURO) > 0)
            Msc = Tirelire::Piece::ONEEURO;
        else if (Victime.countCoins(Tirelire::Piece::FIFTYCENTS) > 0)
            Msc = Tirelire::Piece::FIFTYCENTS;
        else if (Victime.countCoins(Tirelire::Piece::TWENTYCENTS) > 0)
            Msc = Tirelire::Piece::TWENTYCENTS;
        else if (Victime.countCoins(Tirelire::Piece::TENCENTS) > 0)
            Msc = Tirelire::Piece::TENCENTS;
        else if (Victime.countCoins(Tirelire::Piece::FIVECENTS) > 0)
            Msc = Tirelire::Piece::FIVECENTS;
        else if (Victime.countCoins(Tirelire::Piece::TWOCENTS) > 0)
            Msc = Tirelire::Piece::TWOCENTS;
        else if (Victime.countCoins(Tirelire::Piece::ONECENT) > 0)
            Msc = Tirelire::Piece::ONECENT;

        Victime.retrieve(Msc);

        std::println("J'ai volé une pièce de valeur {} centimes.", static_cast<int>(Msc));
    }
    std::println("Plus rien à voler, je m'en vais...");
}
//----------------------------------------------------------------------------
int main() {
    Tirelire SpiderCochon{};

    SpiderCochon.add(Tirelire::Piece::FIFTYCENTS);
    SpiderCochon.add(Tirelire::Piece::ONEEURO);
    SpiderCochon.add(Tirelire::Piece::TENCENTS);
    SpiderCochon.add(Tirelire::Piece::ONEEURO);

    std::jthread tVoleur(_Voleur, std::ref(SpiderCochon));

    return 0;
}
//----------------------------------------------------------------------------
