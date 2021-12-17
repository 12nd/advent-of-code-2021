#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_CAP 2000

const char binary[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
const char *digits = "0123456789ABCDEF";

int ver_sum = 0;

int bin_to_dec(char *bin)
{
    char *tmp = {0};
    return (int)strtol(bin, &tmp, 2);
}


int parse(char *message)
{
    /* version */
    char msg_seg[BUFFER_CAP] = {0};
    int msg_ptr = 0;
    memcpy(msg_seg, message+msg_ptr, 3);
    msg_ptr += 3;
    ver_sum += bin_to_dec(msg_seg);
    /* type ID */
    memcpy(msg_seg, message+msg_ptr, 3);
    msg_ptr += 3;

    /* if literal */
    if (bin_to_dec(msg_seg) == 4) {
        while (1) {
            /* move pointer to end of literal */
            if (message[msg_ptr] == '0') {
                msg_ptr += 5;
                break;
            }
            msg_ptr += 5;
        }

    } else {
        if (message[msg_ptr++] == '0') {
            memcpy(msg_seg, message + msg_ptr, 15);
            msg_ptr += 15;
            int subp_len = bin_to_dec(msg_seg);
            memcpy(msg_seg, message+msg_ptr, (unsigned long)subp_len);
            int subp_ptr = 0;
            while (subp_ptr < subp_len)
                subp_ptr += parse(msg_seg+subp_ptr);
            msg_ptr += subp_ptr;
        } else {
            memcpy(msg_seg, message + msg_ptr, 11);
            msg_ptr += 11;
            int subp_qty = bin_to_dec(msg_seg);
            for (int i=0; i<subp_qty; ++i) {
                msg_ptr += parse(message + msg_ptr);
            }
        }
    }
    return msg_ptr;
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
    for (int c = 0; *(line + c) != '\0'; ++c) {
        const char *p = strchr(digits, *(line + c));
        strcat(message, binary[p - digits]);
    }

    parse(message);
    printf("%d\n", ver_sum);
}
