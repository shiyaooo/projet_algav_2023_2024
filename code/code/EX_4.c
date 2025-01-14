#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "EX_4.h"

#define LEFT_ROTATE(x, c) (((x) << (c)) | ((x) >> (32- (c))))

uint8_t* leng_initial_hex(uint64_t length){
    uint8_t* len=malloc(sizeof(uint8_t));
    for (int i = 0; i < 8; i++) {
        uint8_t tmp=(length * 8) >> (i * 8);
        len[i]=tmp;
    }
    return len;
}

void pad_message(uint8_t *message, uint64_t length) {
    uint8_t len_initial=length;
    if(length % 64!=56){
    // Ajouter le bit "1" au message
        message[length]=0x80;
        length++;
        //printf("ap len=%d\n",length);
        //printf("%02x \n", message[length-1]);


    // Ajouter le bit "0" jusqu'à ce que la taille soit égale à 448 (mod 512)
       while (length % 64!=56){//513/8=64
            message[length++]=0x00;
            //length++;
        }
    }

    // Ajouter la taille du message initial (en bits) codée en little-endian
    //需要将消息的初始长度（在填充之前的长度），以64位little-endian格式编码，//De l’ordre des octets 6> l’octet ->le poids le plus faible est enregistré à l’adresse mémoire la plus petite
    //并将这个64位的编码添加到消息末尾
    
    uint8_t* tmp=leng_initial_hex(len_initial);
    int i=0;
    while(i<8){
        message[length]=tmp[i];
        length++;
        i++;
    }
    free(tmp);
}

void MD5(char* input, uint64_t input_length, uint32_t *hash){
    //Note : Toutes les variables sont sur 32 bits
    uint32_t k[64];

    //Définir r comme suit :
    const uint32_t r[64] = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };

    //MD5 utilise des sinus d'entiers pour ses constantes 
    for (int i = 0; i < 64; i++) {
        k[i] = (uint32_t)(floor(fabs(sin(i + 1)) * pow(2, 32)));
    }

    //Initialise variables:
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;

    // Allouer de l'espace pour le message avec le padding
    uint8_t *message = (uint8_t *)malloc((input_length + 64) * sizeof(uint8_t));

    // Copier l'entrée dans le message
    memcpy(message, input, input_length);

    //Préparation du message (padding) :
    pad_message(message,input_length);

    //Découpage en blocs de 512 bits :
    for (uint64_t i = 0; i < input_length + 1; i += 64){
        //subdiviser en 16 mots de 32 bits en little-endian w[i], 0 ≤ i ≤ 15, 32 bits= 4 octets
        uint32_t* tmp =(uint32_t *)(message+i);

        uint32_t w[16];
        for (int i = 0; i < 16; i++){
            w[i]=tmp[i];
        }
        
        /*uint32_t w[16];
        for (int j = 0; j < 16; j++) {
            w[j] = (message[i + 4 * j]) | (message[i + 4 * j + 1] << 8) |
                   (message[i + 4 * j + 2] << 16) | (message[i + 4 * j + 3] << 24);
            printf("w[i]=%08x ",w[j]);
        }*/
        

        //initialiser les valeurs de hachage :
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        //Boucle principale :
        for(int i = 0; i < 64; i++){
            uint32_t f, g;
            if(i < 16){
                f = (b & c) | ((~b) & d); //f := (b et c) ou ((non b) et d)
                g = i;  //g := i
            }else if(i < 32){
                f = (d & b) | ((~d) & c);//f := (d et b) ou ((non d) et c)
                g = (5 * i + 1) % 16;//g := (5×i + 1) mod 16
            }else if(i < 48){
                f = b ^ c ^ d; //f := b xor c xor d
                g = (3 * i + 5) % 16;//g := (3×i + 5) mod 16
            }else{//i<64
                f = c ^ (b | (~d));//f := c xor (b ou (non d))
                g = (7 * i) % 16;//g := (7×i) mod 16
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = LEFT_ROTATE((a + f + k[i] + w[g]), r[i] ) + b;
            a = temp;
        }
        //ajouter le résultat au bloc précédent :
        h0 += a;
        h1 += b; 
        h2 += c;
        h3 += d;
    
    }
    
    //var entier empreinte := h0 concaténer h1 concaténer h2 concaténer h3 //(en little-endian)
    hash[0] = ((h0 & 0xFF) << 24) | ((h0 >> 8 & 0xFF) <<16) | ((h0 >> 16 & 0xFF) << 8) | ((h0 >> 24 & 0xFF));    
    hash[1] = ((h1 & 0xFF) << 24) | ((h1 >> 8 & 0xFF) <<16) | ((h1 >> 16 & 0xFF) << 8) | ((h1 >> 24 & 0xFF)); ;    
    hash[2] = ((h2 & 0xFF) << 24) | ((h2 >> 8 & 0xFF) <<16) | ((h2 >> 16 & 0xFF) << 8) | ((h2 >> 24 & 0xFF)); ;    
    hash[3] = ((h3 & 0xFF) << 24) | ((h3 >> 8 & 0xFF) <<16) | ((h3 >> 16 & 0xFF) << 8) | ((h3 >> 24 & 0xFF)); ;   
    free(message); 
}