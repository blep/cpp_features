#pragma once

#include <stdexcept>
#include <string_view>


namespace blcx {

#define BLCX_FAILMSG_PRINTER() \
    BLCX_PRINT_LETTER(a, 'a')    \
    BLCX_PRINT_LETTER(b, 'b')    \
    BLCX_PRINT_LETTER(c, 'c')    \
    BLCX_PRINT_LETTER(d, 'd')    \
    BLCX_PRINT_LETTER(e, 'e')    \
    BLCX_PRINT_LETTER(f, 'f')    \
    BLCX_PRINT_LETTER(g, 'g')    \
    BLCX_PRINT_LETTER(h, 'h')    \
    BLCX_PRINT_LETTER(i, 'i')    \
    BLCX_PRINT_LETTER(j, 'j')    \
    BLCX_PRINT_LETTER(k, 'k')    \
    BLCX_PRINT_LETTER(l, 'l')    \
    BLCX_PRINT_LETTER(m, 'm')    \
    BLCX_PRINT_LETTER(n, 'n')    \
    BLCX_PRINT_LETTER(o, 'o')    \
    BLCX_PRINT_LETTER(p, 'p')    \
    BLCX_PRINT_LETTER(q, 'q')    \
    BLCX_PRINT_LETTER(r, 'r')    \
    BLCX_PRINT_LETTER(s, 's')    \
    BLCX_PRINT_LETTER(t, 't')    \
    BLCX_PRINT_LETTER(u, 'u')    \
    BLCX_PRINT_LETTER(v, 'v')    \
    BLCX_PRINT_LETTER(w, 'w')    \
    BLCX_PRINT_LETTER(x, 'x')    \
    BLCX_PRINT_LETTER(y, 'y')    \
    BLCX_PRINT_LETTER(z, 'z')    \
    BLCX_PRINT_LETTER(A, 'A')    \
    BLCX_PRINT_LETTER(B, 'B')    \
    BLCX_PRINT_LETTER(C, 'C')    \
    BLCX_PRINT_LETTER(D, 'D')    \
    BLCX_PRINT_LETTER(E, 'E')    \
    BLCX_PRINT_LETTER(F, 'F')    \
    BLCX_PRINT_LETTER(G, 'G')    \
    BLCX_PRINT_LETTER(H, 'H')    \
    BLCX_PRINT_LETTER(I, 'I')    \
    BLCX_PRINT_LETTER(J, 'J')    \
    BLCX_PRINT_LETTER(K, 'K')    \
    BLCX_PRINT_LETTER(L, 'L')    \
    BLCX_PRINT_LETTER(M, 'M')    \
    BLCX_PRINT_LETTER(N, 'N')    \
    BLCX_PRINT_LETTER(O, 'O')    \
    BLCX_PRINT_LETTER(P, 'P')    \
    BLCX_PRINT_LETTER(Q, 'Q')    \
    BLCX_PRINT_LETTER(R, 'R')    \
    BLCX_PRINT_LETTER(S, 'S')    \
    BLCX_PRINT_LETTER(T, 'T')    \
    BLCX_PRINT_LETTER(U, 'U')    \
    BLCX_PRINT_LETTER(V, 'V')    \
    BLCX_PRINT_LETTER(W, 'W')    \
    BLCX_PRINT_LETTER(X, 'X')    \
    BLCX_PRINT_LETTER(Y, 'Y')    \
    BLCX_PRINT_LETTER(Z, 'Z')    \
    BLCX_PRINT_LETTER(0, '0')    \
    BLCX_PRINT_LETTER(1, '1')    \
    BLCX_PRINT_LETTER(2, '2')    \
    BLCX_PRINT_LETTER(3, '3')    \
    BLCX_PRINT_LETTER(4, '4')    \
    BLCX_PRINT_LETTER(5, '5')    \
    BLCX_PRINT_LETTER(6, '6')    \
    BLCX_PRINT_LETTER(7, '7')    \
    BLCX_PRINT_LETTER(8, '8')    \
    BLCX_PRINT_LETTER(9, '9')

    /**
    * Print a message by relying on the function name in the stack trace failure.
    * A small script is then used to convert the compilation stack trace failure into the original message.
    */
    struct CExprFailureMessage
    {
        const char *message;
        size_t index;

        constexpr static void print(const char *messageToPrint)
        {
            auto msg = CExprFailureMessage{ messageToPrint , stringLength(messageToPrint) };
            msg.printPreviousChar();
        }

        constexpr static void print(const char *messageToPrint, size_t length)
        {
            auto msg = CExprFailureMessage{ messageToPrint , length };
            msg.printPreviousChar();
        }

    private:
        constexpr static size_t stringLength(const char *message)
        {
            int value = 0;
            for (; *message != 0; ++message)
            {
                ++value;
            }
            return value;
        }


        constexpr void printPreviousChar()
        {
            if (index == 0)
            {
                throw std::exception(message);
            }
            --index;
            char c = message[index];
            switch (c)
            {
                // For alphanum, use specific method to minimize stack depth
#define BLCX_PRINT_LETTER( letter, c )     \
        case c:                             \
            printLetter_ ## letter();       \
            break;                  
                BLCX_FAILMSG_PRINTER()
#undef BLCX_PRINT_LETTER
            default:
                // other fallback on dumping the hexa character code
                // dispatch the low 4 bits...
                printByte(static_cast<unsigned char>(c), 0);
            }
        }

        constexpr void printByte(unsigned char c, int shift)
        {
            switch ((c >> shift) & 15)
            {
            case 0: printByte_0(c, shift); break;
            case 1: printByte_1(c, shift); break;
            case 2: printByte_2(c, shift); break;
            case 3: printByte_3(c, shift); break;
            case 4: printByte_4(c, shift); break;
            case 5: printByte_5(c, shift); break;
            case 6: printByte_6(c, shift); break;
            case 7: printByte_7(c, shift); break;
            case 8: printByte_8(c, shift); break;
            case 9: printByte_9(c, shift); break;
            case 10: printByte_10(c, shift); break;
            case 11: printByte_11(c, shift); break;
            case 12: printByte_12(c, shift); break;
            case 13: printByte_13(c, shift); break;
            case 14: printByte_14(c, shift); break;
            case 15: printByte_15(c, shift); break;
            default:
                throw std::exception("unreachable code");
            }
        }

#define BLCX_PRINT_LETTER( letter, c )         \
    constexpr void printLetter_ ## letter()     \
    {                                           \
        printPreviousChar();                    \
    }

        BLCX_FAILMSG_PRINTER()
#undef BLCX_PRINT_LETTER

#define BLCX_PRINTBYTE_DIGIT(digit)                                    \
    constexpr void printByte_ ## digit(unsigned char c, int shift)      \
    {                                                                   \
        if (shift == digit)                                             \
        {                                                               \
            printByte(c, 4);                                            \
        }                                                               \
        else                                                            \
        {                                                               \
            printPreviousChar();                                        \
        }                                                               \
    }

            BLCX_PRINTBYTE_DIGIT(0)
            BLCX_PRINTBYTE_DIGIT(1)
            BLCX_PRINTBYTE_DIGIT(2)
            BLCX_PRINTBYTE_DIGIT(3)
            BLCX_PRINTBYTE_DIGIT(4)
            BLCX_PRINTBYTE_DIGIT(5)
            BLCX_PRINTBYTE_DIGIT(6)
            BLCX_PRINTBYTE_DIGIT(7)
            BLCX_PRINTBYTE_DIGIT(8)
            BLCX_PRINTBYTE_DIGIT(9)
            BLCX_PRINTBYTE_DIGIT(10)
            BLCX_PRINTBYTE_DIGIT(11)
            BLCX_PRINTBYTE_DIGIT(12)
            BLCX_PRINTBYTE_DIGIT(13)
            BLCX_PRINTBYTE_DIGIT(14)
            BLCX_PRINTBYTE_DIGIT(15)

#undef BLCX_PRINTBYTE_DIGIT

    };

#undef BLCX_FAILMSG_PRINTER

    /**
    * Asserts at compile-time that given expression is true, and emit a dynamic message on failure.
    *
    * @param shouldBeTrue if \c false, the compilation abort and encodes \a message in the compile error stack.
    * @param message zero-terminated string to output if \a shouldBeTrue is \c false.
    */
    constexpr bool assertTrue(bool shouldBeTrue, const char *message)
    {
        if (!shouldBeTrue)
        {
            CExprFailureMessage::print(message);
        }
        return shouldBeTrue;
    }


    /**
    * Asserts at compile-time that given expression is true, and emit a dynamic message on failure.
    *
    * @param shouldBeTrue if \c false, the compilation abort and encodes \a message in the compile error stack.
    * @param message bytes or string to output if \a shouldBeTrue is \c false.
    * @param messageLength number of bytes from \a message to output if \a shouldBeTrue is \c false (terminal-zero need not be included if present).
    */
    constexpr bool assertTrue(bool shouldBeTrue, const char *message, size_t messageLength)
    {
        if (!shouldBeTrue)
        {
            CExprFailureMessage::print(message, messageLength);
        }
        return shouldBeTrue;
    }


    /**
    * Asserts at compile-time that given expression is true, and emit a dynamic message on failure.
    *
    * @param shouldBeTrue if \c false, the compilation abort and encodes \a message in the compile error stack.
    * @param message bytes or string to output if \a shouldBeTrue is \c false.
    */
    constexpr bool assertTrue(bool shouldBeTrue, std::string_view message)
    {
        if (!shouldBeTrue)
        {
            CExprFailureMessage::print(message.data(), message.max_size());
        }
        return shouldBeTrue;
    }

} // namespace blcx
