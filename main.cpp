#include <stdint.h> // for size_t
#include <netinet/in.h> // for uint32_t
#include <stdio.h> // for printf, fopen, fclose, fread
#include <stdlib.h> // for exit

uint32_t FileReader(char *file){
    FILE *fp = fopen(file, "rb");// open file

    uint32_t buffer;
    /*if(fp == NULL)
    {
        fprintf(stderr, "File Open Error!\n");
        return 1; // exit(1);
    }
    fread(&buffer, sizeof(buffer), 1, fp); // read file
    */

    size_t FileReadLength = fread(&buffer, 1, sizeof(buffer), fp);//added during code review
    if(FileReadLength != sizeof(uint32_t)){
        fprintf(stderr, "fread return %lu\n", FileReadLength);
        return 1; // exit(1);
    }

    printf("%x\n",buffer);
    buffer = ntohl(buffer); // NBO to HBO
    printf("%x\n",buffer);

    fclose(fp); // close file

    return buffer;
}
int main(int argc, char *argv[]){
    if(argc != 3){ // argv[0] = add-nbo, argv[1] = thousand.bin, argv[2] = five-hundred.bin
        printf("Input File Open Error!\n");
        printf("syntax : add-nbo <file1> <file2>\n");
        printf("sample : add-nbo a.bin b.bin\n");
        return 1; //exit(1)
    }

    uint32_t buffer1 = FileReader(argv[1]);
    uint32_t buffer2 = FileReader(argv[2]);

    uint32_t result = buffer1 + buffer2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", buffer1, buffer1, buffer2, buffer2, result, result);

    return 0; // exit(0)
}

