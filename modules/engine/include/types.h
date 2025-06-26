#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace nobridge {

    using UIntVal = uint8_t;
    using UIntID = uint64_t;
    using IntScore = int16_t;

    const UIntVal HAND_LENGTH = 13;
    const UIntVal DECK_LENGTH = 52;

    template <typename K>
    using LegendMap = std::unordered_map<K, std::string>;

    template <typename K, typename V>
    using LegendMapT = std::unordered_map<K, V>;

    template <std::size_t N>
    using UIntArray = std::array<UIntVal, N>;

    using StringList = std::vector<std::string>;
    using ByteData = std::pair<const char*, std::size_t>;

    template <std::size_t N>
    using FloatArray = std::array<float, N>;

    template <std::size_t N>
    using StringArray = std::array<std::string, N>;

    namespace engine {
        // Game
        class Game;
        using GamePtr = std::shared_ptr<Game>;
        using GameList = std::vector<GamePtr>;

        // Player
        enum class Direction : UIntVal { NONE = 0, NORTH, EAST, SOUTH, WEST };
        enum class PlayerType : UIntVal { HUMAN = 1, COMPUTER };
        class Player;
        using PlayerPtr = std::shared_ptr<Player>;
        using PlayerList = std::vector<PlayerPtr>;

        // Card
        /**
         * SPADES [1-13] TWO - ACE
         * HEARTS [14-26]
         * DIAMONDS [27-39]
         * CLUBS [40-52]
         */

        enum class Suit : UIntVal { SPADES = 1, HEARTS, DIAMONDS, CLUBS };
        enum class Rank : UIntVal {
            TWO = 2,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING,
            ACE
        };

        using SuitList = std::array<Suit, 4>;
        const SuitList SUITLIST{Suit::SPADES, Suit::HEARTS, Suit::DIAMONDS,
                                Suit::CLUBS};

        class Card;
        using CardPtr = std::shared_ptr<Card>;
        using CardList = std::vector<CardPtr>;

        class Hand;
        using HandPtr = std::shared_ptr<Hand>;
        using HandList = std::vector<HandPtr>;

        // Bid
        enum BidType : UIntVal {
            PASS = 1,
            DOUBLE,
            REDOUBLE,
            ALERT,
            NORMAL,
            CONVENTIONAL
        };

        class Bid;
        using BidPtr = std::shared_ptr<Bid>;
        using BidList = std::vector<BidPtr>;

        // Contract
        class Contract;
        using ContractPtr = std::shared_ptr<Contract>;

        // Deck
        class Deck;
        using DeckPtr = std::shared_ptr<Deck>;
        using DealList = std::vector<CardList>;

        // Trick
        using TrickArray = std::array<CardPtr, 4>;
        using TrickList = std::vector<TrickArray>;

        const std::array<Suit, 4> SUIT_ARRAY{Suit::SPADES, Suit::HEARTS,
                                             Suit::DIAMONDS, Suit::CLUBS};

        const LegendMapT<char, Suit> SUIT_MAP{{'S', Suit::SPADES},
                                              {'H', Suit::HEARTS},
                                              {'D', Suit::DIAMONDS},
                                              {'C', Suit::CLUBS}};

        const LegendMapT<char, Rank> RANK_MAP{
            {'2', Rank::TWO},   {'3', Rank::THREE}, {'4', Rank::FOUR},
            {'5', Rank::FIVE},  {'6', Rank::SIX},   {'7', Rank::SEVEN},
            {'8', Rank::EIGHT}, {'9', Rank::NINE},  {'T', Rank::TEN},
            {'J', Rank::JACK},  {'Q', Rank::QUEEN}, {'K', Rank::KING},
            {'A', Rank::ACE}};

    }  // namespace engine

    namespace ansi {
        // --- Style Codes ---
        const std::string RESET = "\033[0m";
        const std::string BOLD = "\033[1m";
        const std::string DIM = "\033[2m";
        const std::string ITALIC = "\033[3m";
        const std::string UNDERLINE = "\033[4m";
        const std::string BLINK = "\033[5m";
        const std::string REVERSE = "\033[7m";
        const std::string HIDDEN = "\033[8m";

        // --- Foreground Color Codes ---
        namespace fg {
            const std::string BLACK = "\033[30m";
            const std::string RED = "\033[31m";
            const std::string GREEN = "\033[32m";
            const std::string YELLOW = "\033[33m";
            const std::string BLUE = "\033[34m";
            const std::string MAGENTA = "\033[35m";
            const std::string CYAN = "\033[36m";
            const std::string WHITE = "\033[37m";
            const std::string BRIGHT_BLACK = "\033[90m";
            const std::string BRIGHT_RED = "\033[91m";
            const std::string BRIGHT_GREEN = "\033[92m";
            const std::string BRIGHT_YELLOW = "\033[93m";
            const std::string BRIGHT_BLUE = "\033[94m";
            const std::string BRIGHT_MAGENTA = "\033[95m";
            const std::string BRIGHT_CYAN = "\033[96m";
            const std::string BRIGHT_WHITE = "\033[97m";
        }  // namespace fg

        // --- Background Color Codes ---
        namespace bg {
            const std::string BLACK = "\033[40m";
            const std::string RED = "\033[41m";
            const std::string GREEN = "\033[42m";
            const std::string YELLOW = "\033[43m";
            const std::string BLUE = "\033[44m";
            const std::string MAGENTA = "\033[45m";
            const std::string CYAN = "\033[46m";
            const std::string WHITE = "\033[47m";
            const std::string BRIGHT_BLACK = "\033[100m";
            const std::string BRIGHT_RED = "\033[101m";
            const std::string BRIGHT_GREEN = "\033[102m";
            const std::string BRIGHT_YELLOW = "\033[103m";
            const std::string BRIGHT_BLUE = "\033[104m";
            const std::string BRIGHT_MAGENTA = "\03-3[105m";
            const std::string BRIGHT_CYAN = "\033[106m";
            const std::string BRIGHT_WHITE = "\033[107m";
        }  // namespace bg

    }  // namespace ansi

}  // namespace nobridge

#endif
