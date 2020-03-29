#include <netinet/in.h> // for uint32_t, ntohl
#include <stdint.h> // for uint32_t
#include <stddef.h> // for size_t
#include <stdlib.h> // for uint8_t
#include <stdio.h> // for printf

void usage() {
    printf("syntax : add_nbo <file1> <file2>\n");
    printf("sample : add_nbo a.bin c.bin\n");
}

uint32_t add_nbo(char *argv) {
    FILE *F;
    uint32_t buf1;
    F = fopen(argv, "r");
    if(F != NULL) {
        fread(&buf1, sizeof(buf1), 1, F);
        buf1 = ntohl(buf1);
        fclose(F);
        return buf1;
    } else {
        printf("Open File Error!!\n");
        return 0;
    }

    return 0;
}

int main(int argc, char** argv) {
    // printf("begin\n");

    // FILE *F;
    uint32_t buf[2];
    buf[0] = add_nbo(argv[1]);
    buf[1] = add_nbo(argv[2]);
    if (argc != 3) {
        usage();
        return 0;
    }
    uint32_t sum = buf[0] + buf[1];

    // printf 1000(thousand) + 500(five-hundred) = 1500(sum) -> result
    // ex) 1000(0x3e8) + 5000(0x1f4) = 1500(0x5dc)
    printf("1000(0x%x) + 500(0x%x) = 1500(0x%x)\n", buf[0], buf[1], sum);
    // printf("end\n");

    return 0;
}
