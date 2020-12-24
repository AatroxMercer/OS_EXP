#include <stdio.h>

void *memset (void *__s, int __c, size_t __n) {
    size_t cnt = 0;
    size_t size_long = sizeof(unsigned long);

    unsigned char value_c = (unsigned char) __c;
    unsigned char* s_char = __s;

    // word alignment
    while (cnt < __n && (size_t)s_char % size_long) {
        *(s_char++) = value_c;
        cnt++;
    }

    // fast fill
    unsigned long value_l = 0;
    for (size_t i = size_long; i--;) {
        value_l = value_l << 8 | value_c;
    }
    unsigned long* s_long = (unsigned long *)s_char;
    while (cnt + 8 <= __n) {
        *(s_long++) = value_l;
        cnt += 8;
    }

    // wind up
    s_char = (unsigned char *) s_long;
    while (cnt < __n) {
        *s_char++ = value_c;
        cnt++;
    }

    return __s;
}

int main(void)
{
    char in[64];

    for (int i = 0; i < 64; ++i)
        in[i] = i;

    memset(in + 0, 0x0, sizeof(in) - 0);

    for (int i = 0; i < 64; i++) {
        printf("%4d", in[i]);
        if ((i & 0xf) == 0xf)
            printf("\n");
    }
    return 0;
}
