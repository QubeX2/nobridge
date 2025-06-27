#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace nobridge {

    // Points {{{
    // Pos: 0 - HCP
    const float ACE_POINTS = 4.5f;
    const float KING_POINTS = 3.5f;
    const float QUEEN_POINTS = 2.0f;
    const float JACK_POINTS = 1.0f;
    const float TEN_POINTS = 0.5f;

    // Pos: 1 - Four Card Major Suit
    const float LONG_MAJOR_SUIT = 1.0f;

    // Pos: 2 - Four Card Minor Suit
    const float LONG_MINOR_SUIT = 1.0f;
    // }}} End Points

    using UIntV = uint8_t;
    using UIntID = uint64_t;
    using IntScore = int16_t;

    const UIntV HAND_LENGTH = 13;
    const UIntV DECK_LENGTH = 52;

    template <typename K>
    using LegendM = std::unordered_map<K, std::string>;

    template <typename K, typename V>
    using LegendMT = std::unordered_map<K, V>;

    template <std::size_t N>
    using UIntA = std::array<UIntV, N>;

    template <std::size_t N, std::size_t M>
    using UInt2dA = std::array<std::array<UIntV, N>, M>;

    using StringL = std::vector<std::string>;
    // using ByteD = std::pair<const char*, std::size_t>;

    template <std::size_t N>
    using FloatA = std::array<float, N>;

    template <std::size_t N>
    using StringA = std::array<std::string, N>;

    namespace engine {
        // Game
        class Game;
        using GamePU = std::unique_ptr<Game>;
        using GameL = std::vector<GamePU>;

        // Player
        enum class Direction : UIntV { NORTH = 1, EAST, SOUTH, WEST };
        inline std::ostream& operator<<(std::ostream& os, const Direction& direction) {
            switch (direction) {
                case Direction::NORTH:
                    os << "N";
                    break;
                case Direction::EAST:
                    os << "E";
                    break;
                case Direction::SOUTH:
                    os << "S";
                    break;
                case Direction::WEST:
                    os << "W";
                    break;
            }
            return os;
        }

        using DirectionL = std::array<Direction, 4>;
        const DirectionL DIRECTION_L{Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
        const LegendMT<char, Direction> DIRECTION_M{
            {'N', Direction::NORTH},
            {'E', Direction::EAST},
            {'S', Direction::SOUTH},
            {'W', Direction::WEST},
        };

        enum class PlayerType : UIntV { HUMAN = 1, COMPUTER };
        class Player;
        using PlayerPU = std::unique_ptr<Player>;
        using PlayerM = std::unordered_map<Direction, PlayerPU>;
        // Play
        class Play;
        using PlayPU = std::unique_ptr<Play>;

        // Card
        /**
         * SPADES [1-13] TWO - ACE
         * HEARTS [14-26]
         * DIAMONDS [27-39]
         * CLUBS [40-52]
         */

        enum class Suit : UIntV { SPADES = 1, HEARTS, DIAMONDS, CLUBS };
        enum class Rank : UIntV { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

        using SuitL = std::array<Suit, 4>;
        const SuitL SUIT_L{Suit::SPADES, Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS};

        class Card;
        using CardP = std::shared_ptr<Card>;
        using CardL = std::vector<CardP>;

        class Hand;
        using HandPU = std::unique_ptr<Hand>;
        using HandList = std::vector<HandPU>;

        // Bid
        enum BidType : UIntV { PASS = 1, DOUBLE, REDOUBLE, ALERT, NORMAL, CONVENTIONAL };

        class Bid;
        using BidPU = std::unique_ptr<Bid>;
        using BidL = std::vector<BidPU>;

        // Contract
        class Contract;
        using ContractPU = std::unique_ptr<Contract>;

        // Deck
        class Deck;
        using DeckPU = std::unique_ptr<Deck>;
        using DealL = std::vector<CardL>;

        // Trick
        using TrickA = std::array<CardP, 4>;
        using TrickL = std::vector<TrickA>;

        const std::array<Suit, 4> SUIT_A{Suit::SPADES, Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS};

        const LegendMT<char, Suit> SUIT_M{
            {'S', Suit::SPADES}, {'H', Suit::HEARTS}, {'D', Suit::DIAMONDS}, {'C', Suit::CLUBS}};

        const LegendMT<char, Rank> RANK_M{{'2', Rank::TWO}, {'3', Rank::THREE}, {'4', Rank::FOUR},  {'5', Rank::FIVE},
                                          {'6', Rank::SIX}, {'7', Rank::SEVEN}, {'8', Rank::EIGHT}, {'9', Rank::NINE},
                                          {'T', Rank::TEN}, {'J', Rank::JACK},  {'Q', Rank::QUEEN}, {'K', Rank::KING},
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
