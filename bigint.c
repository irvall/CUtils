#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#define POS_SIGN 1
#define NEG_SIGN 0

#define PARSE_ERROR -666

#define GET_SIZE(bi) (bi->size)
#define GET_SIGN(bi) (bi->sign)
#define GET_DATA(bi) (bi->data)
#define SET_SIZE(bi, sz) (bi->size = sz)
#define SET_SIGN(bi, si) (bi->size = si)
#define INT_TO_CHAR(i) (i + 48)
#define CHAR_TO_INT(c) (c - 48)

struct BigInt
{
    int size, sign;
    char *data;
};

typedef struct BigInt BigInt;

void SET_DATA(BigInt *bi, char *data)
{
    bi->data = data;
}
void set_bi_data(BigInt *bi, int size, int sign, char *data)
{
    bi->size = size;
    bi->sign = sign;
    bi->data = data;
}

int is_numerical(int i)
{
    return i >= '0' && i <= '9';
}

/**
 * Validates a string is formatted as number.
 * Examples: 
 *  {"123", "+123", "-123"}     -> 1
 * {"s123", "hello", "133T"}    -> Error
 * */
int validate(char *s)
{
    int i, n;
    n = strlen(s);
    if (s[0] != '+' &&
        s[0] != '-' &&
        !is_numerical(s[0]))
        return PARSE_ERROR;
    for (i = 1; i < n; i++)
        if (!is_numerical(s[i]))
            return PARSE_ERROR;
    return 1;
}

/**
 * Accepts a string formatted as a number.
 * Returns pointer to a BigInt.
 * */
BigInt *parse(char *s)
{
    assert(validate(s) == 1);
    BigInt *bi;
    int n;
    bi = malloc(sizeof(BigInt));
    n = strlen(s);
    switch (s[0])
    {
    case '+':
        set_bi_data(bi, n - 1, POS_SIGN, &s[1]);
        break;
    case '-':
        set_bi_data(bi, n - 1, NEG_SIGN, &s[1]);
        break;
    default:
        set_bi_data(bi, n, POS_SIGN, s);
        break;
    }
    return bi;
}

int char_get_numerical(char c)
{
    int value = c - '0';
    if (value > 9 || value < 0)
        return PARSE_ERROR;
    return value;
}


/**
 * Greater than.
 * Is b1 > b2?
 * */
int gt(BigInt *b1, BigInt *b2)
{
    if (GET_SIZE(b1) > GET_SIZE(b2) || GET_SIGN(b1) > GET_SIGN(b2))
        return 1;
    else if (GET_SIZE(b2) > GET_SIZE(b1) || GET_SIGN(b2) > GET_SIGN(b1))
        return 0;
    else
    {
        // b1 and b2 are of equal length here
        for (int i = GET_SIZE(b1) - 1; i >= 0; i--)
        {
            if (GET_SIGN(b1))
            {
                if (GET_DATA(b1)[i] > GET_DATA(b2)[i])
                {
                    return 1;
                }
            }
            else
            {
                if (GET_DATA(b2)[i] > GET_DATA(b1)[i])
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * Is b1 less than b2?
 * */
int lt(BigInt *b1, BigInt *b2)
{
    return gt(b2, b1);
}

/**
 * Equality.
 * If signs and data are identical, we have equality.
 * */
int eq(BigInt b1, BigInt b2)
{
    return b1.sign == b2.sign && !strcmp(b1.data, b2.data);
}

/*
Notes:
Add two strings numerically into new string.
1. Add the LSDs, check for remainder in a loop 
2. If b1 > b2, remember to copy digits directly to b3
3.

res = 000 (108)
9
99

9 + 9 = 18
res[2] = 8
rem = 1

1 + 9 = 10
res[1] = 0
rem = 1
*/
BigInt *add_impl(BigInt *b1, BigInt *b2)
{
    BigInt *res;
    char *dat;
    int a, b, i, j, k, sum, new_sz;
    res = malloc(sizeof(BigInt));
    new_sz = GET_SIZE(b1) + 1;
    dat = malloc(1 + new_sz * sizeof(char));
    sum = dat[new_sz] = 0;
    SET_SIGN(res, POS_SIGN);
    SET_SIZE(res, new_sz);
    i = GET_SIZE(b1) - 1;
    j = GET_SIZE(b2) - 1;
    k = new_sz - 1;
    for (;k >= 0;)
    {
        a = (i >= 0) ? CHAR_TO_INT(GET_DATA(b1)[i--]) : 0;
        b = (j >= 0) ? CHAR_TO_INT(GET_DATA(b2)[j--]) : 0;
        sum = a + b + (sum/10);
        dat[k--] = INT_TO_CHAR(sum % 10);
    }
    dat[0] == 48 ? SET_DATA(res, &dat[1]) : SET_DATA(res, dat);
    return res;
}

/**
 * Ensures that b1 >= b2 when calling addition.
 * */
BigInt *add(BigInt *b1, BigInt *b2)
{
    return gt(b1, b2) ? add_impl(b1, b2) : add_impl(b2, b1);
}

/**
 * Takes BigInts as a variadic parameter.
 * For getting stats about 'n' BigInts.
 * */
void debug(int n, ...)
{
    va_list args;
    va_start(args, n);

    printf("Sign\tSize\tData\n");
    for (int i = 0; i < n; i++)
    {
        BigInt *bi = va_arg(args, BigInt *);
        printf("%d\t%d\t%s\n", GET_SIGN(bi), GET_SIZE(bi), GET_DATA(bi));
    }
}

int main(int argc, char *argv[])
{
    BigInt *a, *b;
    a = parse(argv[1]);
    b = parse(argv[2]);
    printf("%s + %s = %s (expected: %d)\n", GET_DATA(a), GET_DATA(b), GET_DATA(add(a, b)), atoi(argv[1]) + atoi(argv[2]));
    return 0;
}
