#pragma once

#include <array>

namespace blcx {

    struct WriterBase
    {
    };

    template<bool isEstimatingSize, size_t bufferSize>
    struct Writer : WriterBase
    {
        std::array<char, bufferSize> buffer;
        size_t writtenBytes = 0;

        constexpr Writer &write(char c)
        {
            if (!isEstimatingSize)
            {
                buffer[writtenBytes] = c;
            }
            ++writtenBytes;
            return *this;
        }

        constexpr Writer &write(const char *cstr)
        {
            for (; *cstr != 0; ++cstr)
            {
                write(*cstr);
            }
            return *this;
        }

        constexpr Writer &write(const char *cstr, size_t length)
        {
            if (!isEstimatingSize)
            {
                for (size_t index = 0; index < length; ++index)
                {
                    buffer[writtenBytes+index] = cstr[index];
                }
            }
            writtenBytes += length;
        }
    };

    template<typename Generator>
    constexpr size_t estimateSize(Generator gen)
    {
        auto sizeEstimator = Writer<true, 1>{};
        gen(sizeEstimator);
        return sizeEstimator.writtenBytes;
    }

    template<typename Generator>
    constexpr auto generateString(Generator gen)
    {
        auto writer = Writer<false, estimateSize(gen)>{};
        gen(writer);
        return writer.buffer;
    }


} // namespace blcx {
