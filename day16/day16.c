#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define BUFFER_CAP 2000

struct OUT {
    int msg_ptr;
    uint64_t ans;
};

uint64_t ver_sum = 0;

uint64_t bin_to_dec(char *bin)
{
    char *tmp = {0};
    return (uint64_t)strtol(bin, &tmp, 2);
}

struct OUT parse(char *message)
{
    /* version */
    char msg_seg[BUFFER_CAP] = {0};
    struct OUT out = {0};
    memcpy(msg_seg, message+out.msg_ptr, 3);
    out.msg_ptr += 3;
    ver_sum += bin_to_dec(msg_seg);
    /* type ID */
    memcpy(msg_seg, message+out.msg_ptr, 3);
    out.msg_ptr += 3;

    /* if literal */
    int type_id = (int)bin_to_dec(msg_seg);
    if (type_id == 4) {
        char lit_str[BUFFER_CAP] = {0};
        while (1) {
            strncat(lit_str, message + ++out.msg_ptr, 4);
            out.msg_ptr += 4;
            if (message[out.msg_ptr - 5] == '0') {
                out.ans = bin_to_dec(lit_str);
                break;
            }
        }

    } else {
        uint64_t numbers[BUFFER_CAP] = {0};
        int numbers_len = 0;
        struct OUT tmp = {0};

        if (message[out.msg_ptr++] == '0') {
            memcpy(msg_seg, message + out.msg_ptr, 15);
            out.msg_ptr += 15;
            int subp_len = (int)bin_to_dec(msg_seg);
            memcpy(msg_seg, message+out.msg_ptr, (unsigned long)subp_len);
            int subp_ptr = 0;
            while (subp_ptr < subp_len) {
                tmp = parse(msg_seg+subp_ptr);
                subp_ptr += tmp.msg_ptr;
                numbers[numbers_len++] = tmp.ans;
            }
            out.msg_ptr += subp_ptr;
        } else {
            memcpy(msg_seg, message + out.msg_ptr, 11);
            out.msg_ptr += 11;
            int subp_qty = (int)bin_to_dec(msg_seg);
            for (int i=0; i<subp_qty; ++i) {
                tmp = parse(message + out.msg_ptr);
                out.msg_ptr += tmp.msg_ptr;
                numbers[numbers_len++] = tmp.ans;
            }
        }
        /* calculate operations */
        if (type_id == 0) {
            for (int i=0; i<numbers_len; ++i) {
                out.ans += numbers[i];
            }
        } else if (type_id == 1) {
            uint64_t n = 1;
            for (int i=0; i<numbers_len; ++i) {
                n *= numbers[i];
                out.ans = n;
            }
        } else if (type_id == 2) {
            uint64_t min = INT_MAX;
            for (int i=0; i<numbers_len; ++i) {
                if (numbers[i] < min)
                    min = numbers[i];
            }
            out.ans = min;
        } else if (type_id == 3) {
            uint64_t max = 0;
            for (int i=0; i<numbers_len; ++i) {
                if (numbers[i] > max)
                    max = numbers[i];
            }
            out.ans = max;
        } else if (type_id == 5)
            out.ans = numbers[0] > numbers[1];
        else if (type_id == 6)
            out.ans = numbers[0] < numbers[1];
        else if (type_id == 7)
            out.ans = numbers[0] == numbers[1];
    }
    return out;
}


int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[BUFFER_CAP] = {0};
    char message[BUFFER_CAP * 5] = {0};
    fgets(line, BUFFER_CAP, inp_file);
    fclose(inp_file);
    line[strcspn(line, "\n")] = 0;

    const char binary[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    const char *digits = "0123456789ABCDEF";
    for (int c = 0; *(line + c) != '\0'; ++c) {
        const char *p = strchr(digits, *(line + c));
        strcat(message, binary[p - digits]);
    }

    uint64_t res = parse(message).ans;
    printf("%ld\n", ver_sum);
    printf("%ld\n", res);
}
