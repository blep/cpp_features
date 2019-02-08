#include <blcx/constexpr_assert.hpp>
#include <iostream>


namespace blcx {

    namespace impl {
        constexpr size_t stringLength(const char *message) noexcept
        {
            int value = 0;
            for (; *message != 0; ++message)
            {
                ++value;
            }
            return value;
        }

        struct FormatArgSpec
        {
            enum class ArgMode
            {
                unknown,
                explicitPos,
                implicitPos
            };
            size_t argIndex = ~size_t(0);
            ArgMode mode = ArgMode::unknown;
        };

        struct Writer
        {
            char *output;
            bool enabled = false;
            size_t index = 0;

            constexpr void write(char c)
            {
                if (enabled)
                {
                    output[index] = c;
                }
                ++index;
            }

            constexpr void write(const char *src, size_t length)
            {
                if (enabled)
                {
                    for (size_t o = 0; o < length; ++o)
                    {
                        output[index++] = src[o];
                    }
                }
                else
                {
                    index += length;
                }
            }
        };

        struct FormatContext
        {
            const char *fmt;
            size_t nextArgIndex = 0;
            FormatArgSpec::ArgMode mode = FormatArgSpec::ArgMode::unknown;

            constexpr bool tryHandleEscape(char c)
            {
                if (fmt[0] == c) 
                {
                    ++fmt;
                    return true;
                }
                return false;
            }

            constexpr size_t parseUnsignedNumber()
            {
                size_t value = 0;
                while (*fmt != 0)
                {
                    char c = *fmt++;
                    if (c >= '0'  &&  c <= '9')
                    {
                        auto digit = size_t(c - '0');
                        value = value * 10 + digit;
                    }
                    else
                    {
                        break;
                    }
                }
                return value;
            }

            constexpr FormatArgSpec parseArgSpec()
            {
                auto spec = FormatArgSpec{};
                auto start = fmt;
                size_t argIndex = parseUnsignedNumber();
                spec.mode = (start == fmt) ? FormatArgSpec::ArgMode::implicitPos 
                                           : FormatArgSpec::ArgMode::explicitPos;
                if (mode != FormatArgSpec::ArgMode::unknown)
                {
                    blcx::assertTrue(mode == spec.mode, "cannot mix explicit arg index like {0} and implicit arg index {}");
                }
                if (spec.mode == FormatArgSpec::ArgMode::implicitPos)
                {
                    spec.argIndex = nextArgIndex;
                    ++nextArgIndex;
                }
                blcx::assertTrue(*fmt == '}', "missing } after format argument specification");
                return spec;
            }

            template <class... Args>
            constexpr size_t computeFormatBufferSize(const Args &...ts)
            {
                char dummy[1];
                auto writer = Writer{ dummy };
                format(writer, ts...);
                return writer.index;
            }

            template <class Arg>
            constexpr void formatArg(Writer &writer, const FormatArgSpec &spec, Arg arg)
            {
                size_t normalized = static_cast<size_t>(arg);
                if constexpr (std::is_signed_v<Arg>)
                {
                    if (arg < 0)
                    {
                        writer.write('-');
                        normalized = -normalized;
                    }
                }
                char buffer[21];
                index = sizeof(buffer) - 1;
                do
                {
                    char digit = '0' + normalized % 10;
                    normalized = normalized / 10;
                    buffer[index] = digit;
                    --index;
                } while (normalized != 0);
                writer.write(buffer, sizeof(buffer) - index);
            }

            template <class... Args>
            constexpr void format(Writer &writer, const Args &...ts)
            {
                size_t minSize = 0;
                while (*fmt != 0)
                {
                    char c = *fmt++;
                    if
                        switch (c)
                        {
                        case '{':
                            if (tryHandleEscape('{')) // escaped '{'
                            {
                                writer.write('{');
                            }
                            else // a formatted arguments
                            {
                                auto argSpec = ctx.parseArgSpec();
                                formatArg(writer, argSpec, get<argSpec.argIndex>(ts));
                            }
                            break;
                        case '}':
                            tryHandleEscape('{') // skip over '}' if escape escaped '{'
                                writer.write('}');
                            break;
                        default:
                            writer.write(c);
                            break;
                        }
                }
                writer.write('\0');
            }
        };



    } // namespace impl {


    template<size_t sz>
    struct FormatResult
    {
        char buffer[sz];

        constexpr operator std::string_view() const
        {
            return std::string_view{ buffer, sizeof(buffer) };
        }
    };

    template <class... Args>
    constexpr auto format(const char *fmt, const Args &...ts)
    {
        auto ctx = impl::FormatContext{ fmt };
        auto result = FormatResult< ctx.computeFormatBufferSize(ts...) >{};
        ctx.fmt = fmt;
        auto writer = Writer(result.buffer, 0, true);
        ctx.format(writer, ts...);
        return result;
    }


} // namespace blcx {



constexpr int isPositive(int x) {
    if (x < 0)
    {
        auto msg = blcx::format("x must be positive, but was {}", x);
        blcx::assertTrue(x >= 0, msg);
    }
    return 0;
}



int main()
{
    if constexpr (isPositive(3) == 0)
    {
        std::cout << "one\n";
    }
    if constexpr (isPositive(-17) == 0)
    {
        std::cout << "two\n";
    }
}
