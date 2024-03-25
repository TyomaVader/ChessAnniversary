#include "bitboards.h"

/**
 * @namespace KnightMasks
 * @brief Contains functions and constants related to knight masks in chess.
 */
namespace KnightMasks
{
    /**
     * Calculates the absolute difference between two uint8_t values.
     *
     * @param left The left operand.
     * @param right The right operand.
     * @return The absolute difference between the two values.
     */
    static consteval uint8_t absSubtract(uint8_t left, uint8_t right)
    {
        if (left >= right)
        {
            return left - right;
        }
        return right - left;
    }

    /**
     * Calculates the knight masks for each square on the chessboard.
     * 
     * @return An array of Bitboards representing the knight masks for each square.
     */
    static consteval array<Bitboard, 64> calculateMasks()
    {
        array<Bitboard, 64> masks{};

        uint8_t dx;
        uint8_t dy;

        for (uint8_t x0 = 0; x0 < 8; x0++)
        {
            for (uint8_t y0 = 0; y0 < 8; y0++)
            {
                for (uint8_t x1 = 0; x1 < 8; x1++)
                {
                    for (uint8_t y1 = 0; y1 < 8; y1++)
                    {

                        dx = KnightMasks::absSubtract(x0, x1);
                        dy = KnightMasks::absSubtract(y0, y1);

                        if ((dx == 2 and dy == 1) || (dx == 1 and dy == 2))
                        {
                            setOne(masks[y0 * 8 + x0], y1 * 8 + x1);
                        }
                    }
                }
            }
        }

        return masks;
    }

    /**
     * @brief Array of bitboard masks for knight moves.
     *
     * This array stores the pre-calculated bitboard masks for all possible knight moves on a chessboard.
     * Each element in the array represents a mask for a specific square on the chessboard.
     * The masks are used to efficiently determine the valid knight moves for a given position.
     */
    static constexpr array<Bitboard, 64> Masks = KnightMasks::calculateMasks();
}