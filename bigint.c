#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#define POS_SIGN 1
#define NEG_SIGN 0

#define PARSE_ERROR -666

struct BigInt
{
    int size, sign;
    char *data;
};

typedef struct BigInt BigInt;

void set_sign(BigInt *bi, int sign)
{
    bi->sign = sign;
}

void set_data(BigInt *bi, char *data)
{
    bi->data = data;
}

void set_size(BigInt *bi, int n)
{
    bi->size = n;
}

int get_sign(BigInt *bi)
{
    return bi->sign;
}
int get_size(BigInt *bi)
{
    return bi->size;
}
char *get_data(BigInt *bi)
{
    return bi->data;
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
    {
        set_sign(bi, POS_SIGN);
        set_size(bi, n - 1);
        set_data(bi, &s[1]);
        break;
    }
    case '-':
    {
        set_sign(bi, NEG_SIGN);
        set_size(bi, n - 1);
        set_data(bi, &s[1]);
        break;
    }
    default:
    {
        set_sign(bi, POS_SIGN);
        set_size(bi, n);
        set_data(bi, s);
    }
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

int numerical_to_char(int i)
{
    int value = i + '0';
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
    if (get_size(b1) > get_size(b2) || get_sign(b1) > get_sign(b2))
        return 1;
    else if (get_size(b2) > get_size(b1) || get_sign(b2) > get_sign(b1))
        return 0;
    else
    {
        // We know they are of equal length here
        for (int i = get_size(b1) - 1; i >= 0; i--)
        {
            if (get_data(b1)[i] > get_data(b2)[i])
                return 1;
        }
    }
    return 0;
}

/**
 * Equality.
 * If signs and data are identical, we have equality.
 * */
int eq(BigInt b1, BigInt b2)
{
    return b1.sign == b2.sign && !strcmp(b1.data, b2.data);
}

BigInt *add_impl(BigInt *b1, BigInt *b2)
{
    BigInt *res;
    char *dat;
    res = malloc(sizeof(BigInt));
    int new_sz = get_size(b1) + 1;
    dat = malloc(1 + new_sz * sizeof(char));
    dat[new_sz] = 0;
    set_sign(res, POS_SIGN);
    set_size(res, new_sz);
    int a, b, i, j, k, rem, sum;
    rem = 0;
    i = get_size(b1) - 1;
    j = get_size(b2) - 1;
    k = new_sz - 1;
    for (; i >= 0; i--, j--, k--)
    {
        a = char_get_numerical(get_data(b1)[i]);
        b = char_get_numerical(get_data(b2)[j]);
        sum = a + b + rem;
        rem = sum / 10;
        int mod = sum % 10;
        char c = mod + '0';
        printf("a %d, b %d, sum %d, rem %d, mod %d, char %c\n", a, b, sum, rem, mod, c);
        dat[k] = c;
        if (j == 0 && rem != 0)
        {
            dat[--k] = rem + '0';
            break;
        }
    }
    if (!rem)
    {
        set_size(res, new_sz - 1);
        set_data(res, &dat[1]);
    }
    else
    {
        set_data(res, dat);
    }
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
        printf("%d\t%d\t%s\n", get_sign(bi), get_size(bi), get_data(bi));
    }
}

int main(int argc, char *argv[])
{
    BigInt *b1, *b2, *b3;
    b1 = parse("9");
    b2 = parse("99");
    b3 = add(b1, b2);
    debug(3, b1, b2, b3);
    return 0;
}
