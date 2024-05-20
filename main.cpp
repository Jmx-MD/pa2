#include "Sculptor.h"

int main() {
    Sculptor sculptor(19, 19, 19); // Cria um espaço 19x19x19 para a escultura

    
    sculptor.setColor(1.0, 0.0, 0.0, 1.0); // Define a cor para vermelho, com opacidade máxima

    // Cria "linhas" - de (7,14,10) até (8,14,10), (12,14,10) até (13,14,10)
    sculptor.putVoxel(7, 14, 10);
    sculptor.putVoxel(8, 14, 10);
    sculptor.putVoxel(12, 14, 10);
    sculptor.putVoxel(13, 14, 10);

    // Cria "linhas" - de (6,13,10) até (9,13,10), (11,13,10) até (14,13,10)
    for (int x = 6; x < 10; x++) {
            sculptor.putVoxel(x, 13, 10);
       
    }
    for (int x = 11; x < 15; x++) {
        sculptor.putVoxel(x, 13, 10);

    }

    // Cria retângulos de (5,10,10) até (6,12,10), (9,10,10) até (10,12,10)
    for (int x = 5; x < 7; x++) {
        for (int y = 10; y < 13; y++) {
                sculptor.putVoxel(x, y, 10);
        }
    }
    for (int x = 9; x < 11; x++) {
        for (int y = 10; y < 13; y++) {
            sculptor.putVoxel(x, y, 10);
        }
    }

    // Cria retângulo de (7,9,10) até (13,13,10)
    for (int x = 7; x < 14; x++) {
        for (int y = 9; y < 14; y++) {
            sculptor.putVoxel(x, y, 10);
        }
    }

    // Dois cubinhos nos cantos
    sculptor.putVoxel(6, 13, 10);
    sculptor.putVoxel(9, 13, 10);

    // Duas "linhas" na parte de baixo - (8,8,10) até (12,8,10), (9,7,10) até (11,7,10)
    for (int x = 8; x < 13; x++) {
        sculptor.putVoxel(x, 8, 10);

    }
    for (int x = 9; x < 12; x++) {
        sculptor.putVoxel(x, 7, 10);

    }

    // Pontinho na parte inferior
    sculptor.putVoxel(10, 6, 10);


    sculptor.writeOFF("heart.off"); // salva o resultado num arquivo

    return 0;
}
