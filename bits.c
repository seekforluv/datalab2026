/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    int notX = ~x;
    int notY = ~y;
    int temp = notX | notY;
    return ~temp;
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int both1 = x & y;
    int notX = ~x;
    int notY = ~y;
    int both0 = notX & notY;

    int a = ~both1;
    int b = ~both0;
    return a & b;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x) {
        return !y;
    }
    if (!y) {
        return 0;
    }

    int diff = x ^ y;
    int sign = diff >> 31;
    return !sign;
}


/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int move16 = v > 65535;
    move16 = move16 << 4;
    v = v >> move16;

    int move8 = v > 255;
    move8 = move8 << 3;
    v = v >> move8;

    int move4 = v > 15;
    move4 = move4 << 2;
    v = v >> move4;

    int move2 = v > 3;
    move2 = move2 << 1;
    v = v >> move2;

    int move1 = v > 1;

    int ans = move16 | move8;
    ans = ans | move4;
    ans = ans | move2;
    ans = ans | move1;
    return ans;
}


/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int shiftN = n << 3;
    int shiftM = m << 3;

    int partN = x >> shiftN;
    int partM = x >> shiftM;
    int diff = partN ^ partM;
    diff = diff & 255;

    // + 0u 和左移必须放在一起，让左移使用 unsigned 运算
    int changeN = (diff + 0u) << shiftN;
    int changeM = (diff + 0u) << shiftM;

    int ans = x ^ changeN;
    ans = ans ^ changeM;
    return ans;
}


/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned ans = 0;
    int count = 32;

    while (count) {
        unsigned bit = v & 1;
        ans = ans << 1;
        ans = ans | bit;
        v = v >> 1;
        count = count - 1;
    }

    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int zero = !n;
    int step = n + ~0;
    step = step + zero;

    int keep = ~zero;
    keep = keep + 1;
    int mask = 0x7fffffff >> step;
    mask = mask | keep;

    int ans = x >> n;
    ans = ans & mask;
    return ans;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int part = x >> 16;
    part = ~part;
    int all16 = !part;
    int count = all16 << 4;

    int step = ~count;
    step = 24 + step;
    step = step + 1;
    part = x >> step;
    part = ~part;
    int all8 = !part;
    int add = all8 << 3;
    count = count + add;

    step = ~count;
    step = 28 + step;
    step = step + 1;
    part = x >> step;
    part = ~part;
    int all4 = !part;
    add = all4 << 2;
    count = count + add;

    step = ~count;
    step = 30 + step;
    step = step + 1;
    part = x >> step;
    part = ~part;
    int all2 = !part;
    add = all2 << 1;
    count = count + add;

    step = ~count;
    step = 31 + step;
    step = step + 1;
    part = x >> step;
    part = ~part;
    int all1 = !part;
    count = count + all1;

    part = ~x;
    int all32 = !part;
    return count + all32;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (!x) {
        return 0;
    }

    unsigned sign = x & 0x80000000;
    unsigned num = x;
    if (sign) {
        num = ~num;
        num = num + 1;
    }

    int power = 31;
    while (!(num & 0x80000000)) {
        num = num << 1;
        power = power - 1;
    }

    unsigned tail = num & 0x7fffffff;
    tail = tail >> 8;
    unsigned rest = num & 255;

    int more = rest > 128;
    int half = rest == 128;
    int odd = tail & 1;
    int round = half & odd;
    round = more | round;
    if (round) {
        tail = tail + 1;
    }

    unsigned exp = power + 127;
    exp = exp << 23;
    unsigned ans = exp + tail;
    ans = sign | ans;
    return ans;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = uf >> 23;
    exp = exp & 255;
    unsigned sign = uf & 0x80000000;
    unsigned tail = uf & 0x7fffff;

    if (exp == 255) {
        return uf;
    }

    if (exp == 0) {
        tail = tail << 1;
        return sign | tail;
    }

    exp = exp + 1;
    if (exp == 255) {
        tail = 0;
    }

    exp = exp << 23;
    unsigned ans = sign | exp;
    ans = ans | tail;
    return ans;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exp = uf2 >> 20;
    exp = exp & 2047;
    int power = exp - 1023;

    if (power < 0) {
        return 0;
    }
    if (power >= 31) {
        return ~0x7fffffff;
    }

    int high = uf2 & 0xfffff;
    high = high | 0x100000;
    int ans;

    if (power <= 20) {
        int step = 20 - power;
        ans = high >> step;
    } else {
        int step = power - 20;
        high = high << step;
        step = 52 - power;
        int low = uf1 >> step;
        ans = high | low;
    }

    if (sign) {
        return -ans;
    }
    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }

    if (x < -126) {
        int step = x + 149;
        return 1 << step;
    }

    if (x > 127) {
        return 0x7f800000;
    }

    int exp = x + 127;
    return exp << 23;
}
