#include <netinet/in.h> // for uint32_t, ntohl
#include <stdint.h> // for uint32_t
#include <stddef.h> // for size_t
#include <stdlib.h> // for uint8_t
#include <stdio.h> // for printf

void usage() { // Professor gil
    printf("syntax : add_nbo <file1> <file2>\n");
    printf("sample : add_nbo a.bin c.bin\n");
}

uint32_t add_nbo(char *file_name) {

    FILE *F;
    uint32_t buf;

    F = fopen(file_name, "r"); //read

    if(F != NULL) { //Not empty file.

        fread(&buf, sizeof(buf), 1, F); //fread(memory addr, size, count, file);
        buf = ntohl(buf); //little endian -> network byte array(big endian)
        fclose(F); //open and close
        return buf;

    } else { //empty file
        printf("Open File Error!!\n");
        return 0;
    }
}

int main(int argc, char** argv) { //argv[0] = add_nbo(main)
                                  //argv[1] = thousand
                                  //argv[2] = five-hundred
    //printf("begin\n");
    if (argc != 3) {
        usage();
        return -1; //Error
    }

    // FILE *F;
    uint32_t buf[2]; //uint32_t : 32bit - 4byte unsigned
    buf[0] = add_nbo(argv[1]);
    buf[1] = add_nbo(argv[2]);
    uint32_t sum = buf[0] + buf[1];

    // printf 1000(thousand) + 500(five-hundred) = 1500(sum) -> result
    // ex) 1000(0x3e8) + 500(0x1f4) = 1500(0x5dc)
    //printf("1000(0x%x) + 500(0x%x) = 1500(0x%x)\n", buf[0], buf[1], sum);
    // 3e8 -> 1000, 1f4 -> 500

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", buf[0], buf[0], buf[1], buf[1], sum, sum);

    // printf("end\n");

    return 0;
}
