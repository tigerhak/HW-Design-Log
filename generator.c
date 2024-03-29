#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int main(void) {
    int num_nnz;
    int i;

    srand(time(NULL));

    printf("num_nnz? ");
    scanf("%d", &num_nnz);

    if (num_nnz >= 256 || num_nnz < 0) {
        printf("[ERROR] num_nnz should be in the range 0~255\n");
        return 1;
    }

    uint8_t *coo_row = (uint8_t *)malloc(num_nnz * sizeof(uint8_t));
    uint8_t *coo_col = (uint8_t *)malloc(num_nnz * sizeof(uint8_t));
    __fp16 *value = (__fp16 *)malloc(num_nnz * sizeof(__fp16));
    __fp16 vector[16];

    srand(time(NULL));
    for (i = 0; i < num_nnz; i++) {
        coo_row[i] = i / 16;
        coo_col[i] = i % 16;
        value[i] = (__fp16)(10.0 * rand() / (double)RAND_MAX);
    }

    for (i = 0; i < 16; i++) {
        vector[i] = (__fp16)(10.0 * rand() / (double)RAND_MAX);
    }

    FILE *matrixFile = fopen("/home/linaro/matrix.txt", "w");
    if (matrixFile == NULL) {
        printf("[ERROR] Unable to write to matrix.txt\n");
        return 1;
    }

    fprintf(matrixFile, "%hhu\n", num_nnz);
    for (i = 0; i < num_nnz; i++) {
        fprintf(matrixFile, "%hhu %hhu %f\n", coo_row[i], coo_col[i], (float)value[i]);
    }

    fclose(matrixFile);

    FILE *vectorFile = fopen("/home/linaro/vector.txt", "w");
    if (vectorFile == NULL) {
        printf("[ERROR] Unable to write to vector.txt\n");
        return 1;
    }

    for (i = 0; i < 16; i++) {
        fprintf(vectorFile, "%f\n", (float)vector[i]);
    }

    fclose(vectorFile);

    free(coo_row);
    free(coo_col);
    free(value);

    return 0;
}
