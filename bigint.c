#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define POS_SIGN 1
#define NEG_SIGN 0

#define PARSE_ERROR -666

struct BigInt
{
    int size, sign;
    char *data;
};

typedef struct BigInt BigInt;

BigInt parse(char *s)
{
    BigInt bi;
    char *data;
    int n = strlen(s);
    if (s[0] == '-')
    {
        n--;
        bi.sign = NEG_SIGN;
        data = malloc(1 + n * sizeof(char));
        memcpy(data, &s[1], n);
        bi.data = data;
        bi.size = n;
    }
    else
    {
        bi.sign = POS_SIGN;
        bi.data = s;
        bi.size = n;
    }
    return bi;
}
//
//data = "123"
// char *toString(BigInt bi)
// {
//     char *s;
//     int strSize = bi.sign == 0 ? bi.size + 1 : bi.size;
//     s = malloc(1 + strSize * sizeof(char));
//     if (!bi.sign == 0)
//         s[0] = '-';
//     memcpy(s, bi.size, bi.data, bi.size);
//     memcpy(s, )
//         s[bi.size] = 0;
//     return s;
// }

int parse_char(char c)
{
    int value = c - '0';
    if (value > 9 || value < 0)
        return PARSE_ERROR;
    return value;
}

char parse_int(int i)
{
    int value = i + '0';
    return value;
}

int gt(BigInt b1, BigInt b2)
{
    if (b1.size > b2.size || b1.sign > b2.sign)
        return 1;
    else if (b2.size > b1.size || b2.sign > b1.sign)
        return 0;
    else
    {
        for (int i = b1.size - 1; i >= 0; i--)
        {
            if (b1.data[i] > b2.data[i])
                return 1;
        }
    }
    return 0;
}

int eq(BigInt b1, BigInt b2)
{
    return b1.sign == b2.sign && !strcmp(b1.data, b2.data);
}

BigInt ADD_BI_BI_impl(BigInt b1, BigInt b2)
{
    int i;
    int newSize = b1.size + 1;
    BigInt res;
    res.sign = POS_SIGN;
    res.data = malloc((newSize + 1) * sizeof(char));
    int k = b2.size;
    int last_i_b1 = b1.size - 1;
    int last_i_b2 = b2.size - 1;
    int x, y, sum, mod, rem;
    i = newSize--;
    res.data[newSize--] = 0;
    rem = 0;
    while (newSize > 0)
    {
        if (last_i_b2 < 0)
        {
            char c = b1.data[last_i_b1--];
            res.data[newSize--] = c;
            printf("current index: %d, c: %c\n", newSize+1, c);
            continue;
        }
        x = parse_char(b1.data[last_i_b1--]);
        y = parse_char(b2.data[last_i_b2--]);
        sum = x + y + rem;
        mod = sum % 10;
        rem = sum / 10;
        char crn = parse_int(mod);
        printf("x: %d, y: %d, sum: %d, mod: %d, rem: %d, i: %d, crn: %c, current index: %d\n", x, y, sum, mod, rem, i, crn, newSize);
        res.data[newSize] = crn;
        newSize--;
        i--;
    }
    return res;
}

BigInt ADD_BI_BI(BigInt b1, BigInt b2)
{
    return gt(b1, b2) ? ADD_BI_BI_impl(b1, b2) : ADD_BI_BI_impl(b2, b1);
}

void debug(BigInt bi)
{
    printf("Sign\tSize\tData\n");
    printf("%d\t%d\t%s\n", bi.sign, bi.size, bi.data);
}

int main(int argc, char *argv[])
{
    printf("char %c\n", 5 + '0');
    BigInt b1 = parse("128");
    BigInt b2 = parse("41248");
    debug(b1);
    debug(b2);
    BigInt b3 = ADD_BI_BI(b1, b2);
    debug(b3);
    return 0;
}
