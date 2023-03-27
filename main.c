#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMLINHA 512
#define tamM 15 ///Tamanho da matriz fixo pois ao fazer concatenando a parte visual no final ficava ruim
typedef struct _MM{
    int palavra;
//    int x;
//    int y;
    int score;
}MelhorMatriz;
int main()
{
    FILE *arq;
    srand(time(NULL));
    int r = rand();
    char nome[10];
    printf("Entre com o nome do .txt para a criacao da cruzada. (.txts prontos: animais.txt , objetos.txt)\n");
    fgets(nome,15,stdin);
    tiraBN(nome);
    printf("\n%s\n",nome);
    arq = fopen(nome,"r");
    if(arq == NULL){
        printf("NOT FOUND");
        printf("\nPress ENTER key to Continue\n");
        getchar();
        exit(0);
    }
    printf("FOUND\n\n");


    char buffer[TAMLINHA];
    int numP = 0;
    int maiorP = 0;
    int i,j,k,l,m;
    int score = 0;
    int interc = 0;
    int pColocadas = 1;
    int coloco = 1;
//    int tamM = 0;

    while(fgets(buffer,TAMLINHA,arq)){
        ++numP;
//        printf("\nTamanho de %s: %d",buffer,tamStr(buffer));
        if(tamStr(buffer) > maiorP){
            maiorP = tamStr(buffer);
        }
    }
    printf("\nNumero de palavras: %d",numP);
    printf("\nTam maiorP: %d\n",maiorP);
    char palavras[numP][maiorP];
    rewind(arq);
    i=0;
    while(fgets(buffer,TAMLINHA,arq) != NULL){
        strcpyMEU(buffer,palavras[i]);
        tiraBN(palavras[i]);
//        printf("\npalavras[%d]: %s",i,palavras[i]);
//        printf("\n%c,",palavras[i][3]);
        ++i;
    }
//    for(k = 0; k < numP; ++k){
//        for(l = 0; l < tamStr(palavras[k]); ++l){
//            ++tamM;
//        }
//    }
    char matriz[tamM][tamM];///matriz dinamica sera?
    for(i = 0; i < tamM; ++i){
        for(j = 0; j < tamM; ++j){
            matriz[i][j] = ' ';
        }
    }
//    for(i = 0; i < numP; ++i){
//        printf("\n%s,",palavras[i]);
//    }
    ///primeira palavra
    for(i = 0; i < tamStr(palavras[0]); ++i){
        matriz[0][i] = palavras[0][i];
    }

//    for(i = 0; i < tamStr(palavras[1]); ++i){
//        matriz[i][0] = palavras[1][i];
//    }

    int podepor;
    int tamantes;
    MelhorMatriz mm[numP];
    int cont,cont2,cont3;
    char palavras2[numP][maiorP];
    for(i = 0; i < numP; ++i){
        strcpyMEU(palavras[i],palavras2[i]);
    }
    for(cont = 0; cont < numP; ++cont){
        mm[cont].palavra = cont;
        interc = 0;
        pColocadas = 1;
        for(i = 0; i < tamM; ++i){
            for(j = 0; j < tamM; ++j){
                matriz[i][j] = ' ';
            }
        }
        for(i = 0; i < numP; ++i){
            strcpyMEU(palavras2[i],palavras[i]);
        }
        for(cont2 = 0; cont2 < tamStr(palavras[cont]); ++cont2){
            matriz[0][cont2] = palavras[cont][cont2];
        }
        coloco = 1;
        while(coloco){
            coloco = 0;
            /// --THE FOUR FOR'S--
            for(i = 0; i < tamM; ++i){
                for(j = 0; j < tamM; ++j){
                    for(k = 0; k < numP; ++k){
                        if(strcmp(palavras[k],palavras[mm[cont].palavra]) == 0){
                            limpaPalavra(palavras[k]);
                            if(k < numP-1){
                                ++k;
                            }
                            else{
                                break;
                            }
                        }
                        for(l = 0; l < tamStr(palavras[k]); ++l){
                            if(matriz[i][j] == palavras[k][l]){
                                printf("\nMatch: %s com %s na posicao %d com %d",matriz[i],palavras[k],j,l);
                                ///teste vertical
                                podepor = 1;
                                printf("\nVERTICAL");
                                for(tamantes = 0; tamantes <= l; ++tamantes){
                                    printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, tamantes = %d",k,l-tamantes,palavras[k][l-tamantes],i-tamantes,j,matriz[i-tamantes][j],tamantes);
                                    if((matriz[i-tamantes][j] != ' ' && matriz[i-tamantes][j] != palavras[k][l-tamantes]) || i-tamantes < 0){
                                        podepor = 0;
                                        break;
                                    }
                                }
                                if(podepor){
                                    for(m = 1; m < tamStr(palavras[k]); ++m){
                                        printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, m = %d",k,l+m,palavras[k][l+m],i+m,j,matriz[i+m][j],m);
                                        if((matriz[i+m][j] != ' ' && matriz[i+m][j] != palavras[k][m+l] )|| i+m >= tamM){
                                            podepor = 0;
                                            break;
                                        }
                                    }
                                    if(podepor){
                                        for(m = 0; m < tamStr(palavras[k]); ++m){
                                            printf("\nTransforma matriz[%d][%d] = %c em palavras[%d][%d] = %c",i-tamantes+1,j,matriz[i-tamantes+1][j],k,m,palavras[k][m]);
                                            if(matriz[i-tamantes+1][j] == palavras[k][m]){
                                                ++interc;
                                            }
                                            matriz[i-tamantes+1][j] = palavras[k][m];
                                            --tamantes;
                                        }
        //                                printf(" %s DEU BOM ",palavras[k]);
                                        ++pColocadas;
                                        coloco = 1;
                                        limpaPalavra(palavras[k]);
                                    }
                                }
                                ///teste horizontal
                                if(coloco == 0){
                                    printf("\nHORIZONTAL");
                                    podepor = 1;
                                    for(tamantes = 0; tamantes <= l; ++tamantes){
                                        printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, tamantes = %d",k,l-tamantes,palavras[k][l-tamantes],i,j-tamantes,matriz[i][j-tamantes],tamantes);
                                        if((matriz[i][j-tamantes] != ' ' && matriz[i][j-tamantes] != palavras[k][l-tamantes] )|| j-tamantes < 0){
                                            podepor = 0;
                                            break;
                                        }
                                    }
                                    if(podepor){
                                        for(m = 1; m < tamStr(palavras[k]); ++m){
                                            printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, m = %d",k,m,palavras[k][m],i,j+m,matriz[i][j+m],m);
                                            if((matriz[i][j+m] != ' ' && matriz[i][j+m] != palavras[k][m+l] )|| j+m >= tamM){
                                                podepor = 0;
                                                break;
                                            }
                                        }
                                        if(podepor){
                                            for(m = 0; m < tamStr(palavras[k]); ++m){
                                                printf("\nTransforma matriz[%d][%d] = %c em palavras[%d][%d] = %c",i,j-tamantes+1,matriz[i][j-tamantes+1],k,m,palavras[k][m]);
                                                if(matriz[i][j-tamantes+1] == palavras[k][m]){
                                                    ++interc;
                                                }
                                                matriz[i][j-tamantes+1] = palavras[k][m];
                                                --tamantes;
                                            }
        //                                    printf(" %s DEU BOM",palavras[k]);
                                            ++pColocadas;
                                            coloco = 1;
                                            limpaPalavra(palavras[k]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        mm[cont].score = interc;
        printf("mm[%d] score: %d",cont,mm[cont].score);
    }
    int maiorScore = 0;
    for(i = 0; i < numP; ++i){
        printf("\n1mm[%d] score %d, maior score %d",i, mm[i].score, maiorScore);
        if(mm[i].score > maiorScore){
            maiorScore = mm[i].score;
        }
    }
    for(cont3 = 0; cont3 < numP; ++cont3){
        printf("\n2mm[%d] score %d, maior score %d",cont3, mm[cont3].score, maiorScore);
        if(mm[cont3].score == maiorScore){
                break;
        }
    }
    for(k = 0; k < tamM; ++k){
        for(l = 0; l < tamM; ++l){
            matriz[k][l] = ' ';
        }
    }
    for(k = 0; k < numP; ++k){
        strcpyMEU(palavras2[k],palavras[k]);
    }
    for(cont2 = 0; cont2 < tamStr(palavras[mm[cont3].palavra]); ++cont2){
        matriz[0][cont2] = palavras[mm[cont3].palavra][cont2];
    }
    interc = 0;
    pColocadas = 1;
    coloco = 1;
    printf("==============================================================================================");
    ///Monta a matriz definitiva a partir da palavra que obteve o maior score.
    while(coloco){
        coloco = 0;
        /// --THE FOUR FOR'S--
        for(i = 0; i < tamM; ++i){
            for(j = 0; j < tamM; ++j){
                for(k = 0; k < numP; ++k){
                    if(strcmp(palavras[k],palavras[mm[cont3].palavra]) == 0){
//                        printf("\n%s e igual a %s, mm %d",palavras[k],palavras[mm[cont3].palavra],mm[cont3].palavra);
                        limpaPalavra(palavras[k]);
                        if(k < numP-1){
                            ++k;
                        }
                        else{
                            break;
                        }
                    }
                    for(l = 0; l < tamStr(palavras[k]); ++l){
                        if(matriz[i][j] == palavras[k][l]){
                            printf("\nMatch: %s com %s na posicao %d com %d",matriz[i],palavras[k],j,l);
                            ///teste vertical
                            podepor = 1;
                            printf("\nVERTICAL");
                            for(tamantes = 0; tamantes <= l; ++tamantes){
                                printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, tamantes = %d",k,l-tamantes,palavras[k][l-tamantes],i-tamantes,j,matriz[i-tamantes][j],tamantes);
                                if((matriz[i-tamantes][j] != ' ' && matriz[i-tamantes][j] != palavras[k][l-tamantes]) || i-tamantes < 0){
                                    podepor = 0;
                                    break;
                                }
                            }
                            if(matriz[i-tamantes][j] != ' ' && i-tamantes >= 0){
                                podepor = 0;
                            }
                            if(podepor){
                                for(m = 1; m < tamStr(palavras[k]); ++m){
                                    printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, m = %d",k,l+m,palavras[k][l+m],i+m,j,matriz[i+m][j],m);
                                    if((matriz[i+m][j] != ' ' && matriz[i+m][j] != palavras[k][m+l] )|| i+m >= tamM){
                                        podepor = 0;
                                        break;
                                    }
                                }
                                if(podepor){
                                    for(m = 0; m < tamStr(palavras[k]); ++m){
                                        printf("\nTransforma matriz[%d][%d] = %c em palavras[%d][%d] = %c",i-tamantes+1,j,matriz[i-tamantes+1][j],k,m,palavras[k][m]);
                                        if(matriz[i-tamantes+1][j] == palavras[k][m]){
                                            ++interc;
                                        }
                                        matriz[i-tamantes+1][j] = palavras[k][m];
                                        --tamantes;
                                    }
    //                                printf(" %s DEU BOM ",palavras[k]);
                                    ++pColocadas;
                                    coloco = 1;
                                    limpaPalavra(palavras[k]);
                                }
                            }
                            ///teste horizontal
                            if(coloco == 0){
                                printf("\nHORIZONTAL");
                                podepor = 1;
                                for(tamantes = 0; tamantes <= l; ++tamantes){
                                    printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, tamantes = %d",k,l-tamantes,palavras[k][l-tamantes],i,j-tamantes,matriz[i][j-tamantes],tamantes);
                                    if((matriz[i][j-tamantes] != ' ' && matriz[i][j-tamantes] != palavras[k][l-tamantes] )|| j-tamantes < 0){
                                        podepor = 0;
                                        break;
                                    }
                                }
                                if(matriz[i][j-tamantes] != ' ' && j-tamantes >= 0){
                                    podepor = 0;
                                }
                                if(podepor){
                                    for(m = 1; m < tamStr(palavras[k]); ++m){
                                        printf("\npalavras[%d][%d] = %c, matriz[%d][%d] = %c, m = %d",k,m,palavras[k][m],i,j+m,matriz[i][j+m],m);
                                        if((matriz[i][j+m] != ' ' && matriz[i][j+m] != palavras[k][m+l] )|| j+m >= tamM){
                                            podepor = 0;
                                            break;
                                        }
                                    }
                                    if(podepor){
                                        for(m = 0; m < tamStr(palavras[k]); ++m){
                                            printf("\nTransforma matriz[%d][%d] = %c em palavras[%d][%d] = %c",i,j-tamantes+1,matriz[i][j-tamantes+1],k,m,palavras[k][m]);
                                            if(matriz[i][j-tamantes+1] == palavras[k][m]){
                                                ++interc;
                                            }
                                            matriz[i][j-tamantes+1] = palavras[k][m];
                                            --tamantes;
                                        }
    //                                    printf(" %s DEU BOM",palavras[k]);
                                        ++pColocadas;
                                        coloco = 1;
                                        limpaPalavra(palavras[k]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("\nmm[%d] score: %d, interc %d",cont3,mm[cont3].score,interc);

    printf("\n\n");
    printf("\n. . . . . . . . . . . . . . . ..\n");
    for(i = 0; i < tamM; ++i){
        printf(".");
        for(j = 0; j < tamM; ++j){
//            if(matriz[i][j]!=' '){
                printf("%c ",matriz[i][j]);
//            }
//            else{
//                printf("%d ",rand()%10);
//            }
        }
        printf(".\n");
    }
    printf(". . . . . . . . . . . . . . . ..\n");
    for(i = 0; i < numP; ++i){
            printf("\nmm[%d] score: %d",i, mm[i].score);
        }
//    printf("TAMMATRIZ %d",tamM);
    printf("\nIntercessoes: %d, Palavras colocadas: %d/%d",mm[cont3].score,pColocadas,numP);
    fclose(arq);
    printf("\nPress ENTER key to Continue\n");
    getchar();
}
int tamStr(char *str){
    int i;
    int tam = 0;
    for (i = 0; str[i] != '\0'; ++i){
        ++tam;
    }
    return tam;
}
void tiraBN(char *str){
    int i;
    for(i = 0; str[i] != '\0'; ++i){
        if(str[i] == '\n'){
            str[i] = '\0';
        }
    }
}
void strcpyMEU(char *str1, char *str2){
    int i;
    for(i = 0; str1[i] != '\0'; ++i){
        str2[i] = str1[i];
    }
    str2[i] = '\0';
}
void limpaMatriz(char **matriz, int tamanho){
    int i,j;
    for(i = 0; i < tamanho; ++i){
        for(j = 0; j < tamanho; ++j){
            printf("r");
            matriz[i][j] = 32;
        }
    }
}
void limpaPalavra(char *palavra){
    int i;
    for(i = 0; i < tamStr(palavra); ++i){
        palavra[i] = '-';
    }
}
int ultimaPos(int *vet,int tam){
    int i,n = 0;
    for(i = 0; i < tam && vet[i] != ' '; ++i){
        ++n;
    }
    return n-1;
}
