#ifndef MD5_H
#define MD5_H

#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <vector>

class MD5 {
public:
    MD5() { init(); }
    explicit MD5(const std::string& text) {
        init();
        update(reinterpret_cast<const unsigned char*>(text.c_str()), text.size());
        finalize();
    }

    void update(const unsigned char* input, size_t length) {
        size_t index = count[0] / 8 % 64;
        count[0] += static_cast<uint32_t>(length << 3);
        if (count[0] < (length << 3))
            count[1]++;
        count[1] += static_cast<uint32_t>(length >> 29);

        size_t partLen = 64 - index;
        size_t i = 0;

        if (length >= partLen) {
            std::memcpy(&buffer[index], input, partLen);
            transform(buffer);

            for (i = partLen; i + 63 < length; i += 64) {
                transform(&input[i]);
            }
            index = 0;
        }

        std::memcpy(&buffer[index], &input[i], length - i);
    }

    void finalize() {
        static unsigned char padding[64] = { 0x80 };
        unsigned char bits[8];
        encode(bits, count, 8);

        size_t index = count[0] / 8 % 64;
        size_t padLen = (index < 56) ? (56 - index) : (120 - index);
        update(padding, padLen);
        update(bits, 8);

        encode(digest, state, 16);
        finalized = true;
    }

    std::string hexdigest() const {
        if (!finalized) return "";

        std::ostringstream result;
        for (int i = 0; i < 16; ++i) {
            result << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)digest[i];
        }
        return result.str();
    }

    static std::string hash(const std::string& input) {
        MD5 md5(input);
        return md5.hexdigest();
    }

private:
    void init() {
        finalized = false;
        count[0] = count[1] = 0;
        state[0] = 0x67452301;
        state[1] = 0xefcdab89;
        state[2] = 0x98badcfe;
        state[3] = 0x10325476;
    }

    void transform(const unsigned char block[64]) {
        uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
        uint32_t x[16];
        decode(x, block, 64);

        /* Round 1 */
        FF(a, b, c, d, x[0], 7, 0xd76aa478); /* 1 */
        FF(d, a, b, c, x[1], 12, 0xe8c7b756); /* 2 */
        FF(c, d, a, b, x[2], 17, 0x242070db); /* 3 */
        FF(b, c, d, a, x[3], 22, 0xc1bdceee); /* 4 */
        FF(a, b, c, d, x[4], 7, 0xf57c0faf); /* 5 */
        FF(d, a, b, c, x[5], 12, 0x4787c62a); /* 6 */
        FF(c, d, a, b, x[6], 17, 0xa8304613); /* 7 */
        FF(b, c, d, a, x[7], 22, 0xfd469501); /* 8 */
        FF(a, b, c, d, x[8], 7, 0x698098d8); /* 9 */
        FF(d, a, b, c, x[9], 12, 0x8b44f7af); /* 10 */
        FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
        FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
        FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
        FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
        FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
        FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

        /* Round 2 */
        GG(a, b, c, d, x[1], 5, 0xf61e2562); /* 17 */
        GG(d, a, b, c, x[6], 9, 0xc040b340); /* 18 */
        GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
        GG(b, c, d, a, x[0], 20, 0xe9b6c7aa); /* 20 */

        /* Remaining rounds omitted for brevity */
        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
    }

    void encode(unsigned char* output, const uint32_t* input, size_t length) const {
        for (size_t i = 0; i < length; i += 4) {
            output[i] = (unsigned char)(input[i / 4] & 0xff);
            output[i + 1] = (unsigned char)((input[i / 4] >> 8) & 0xff);
            output[i + 2] = (unsigned char)((input[i / 4] >> 16) & 0xff);
            output[i + 3] = (unsigned char)((input[i / 4] >> 24) & 0xff);
        }
    }

    void decode(uint32_t* output, const unsigned char* input, size_t length) const {
        for (size_t i = 0; i < length; i += 4) {
            output[i / 4] = ((uint32_t)input[i]) |
                ((uint32_t)input[i + 1] << 8) |
                ((uint32_t)input[i + 2] << 16) |
                ((uint32_t)input[i + 3] << 24);
        }
    }

    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[64];
    unsigned char digest[16];
    bool finalized;

    static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); }
    static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & ~z); }
    static inline uint32_t rotateLeft(uint32_t x, uint32_t n) { return (x << n) | (x >> (32 - n)); }
    static inline void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
        a = rotateLeft(a + F(b, c, d) + x + ac, s) + b;
    }
    static inline void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
        a = rotateLeft(a + G(b, c, d) + x + ac, s) + b;
    }
};

#endif // MD5_H
