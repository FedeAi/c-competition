#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_N 10
void leggi_file(char fn[], int mat[][MAX_N], int *N, int altezze[]);
int controllo(int mat[MAX_N][MAX_N], int altezze[], int N);

int main(int argc, char *argv[])
{
    int N;
    int altezze[MAX_N*4] = {0};
    int mat[MAX_N][MAX_N] = {{0}};
    leggi_file(argv[1], mat, &N, altezze);
    printf("%d\n", controllo(mat,altezze,N));
    return 0;
}


void leggi_file(char *fn, int mat[][MAX_N], int *N, int altezze[]){
    FILE *fp = NULL;
    int i=0,j=0;
    fp = fopen(fn, "rb");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }

    fread(N, sizeof(int), 1, fp);
    for(i=0; i<*N; i++){
        for(j=0; j<*N;j++){
            fread(&(mat[i][j]), sizeof(int), 1, fp);
        }
    
    }
    for(j=0; j<(*N)*4;j++){
        fread(&(altezze[j]), sizeof(int), 1, fp);
    }
    fclose(fp);
}

int controllo(int mat[][MAX_N], int altezze[], int N){
    
    int i=0,j=0;

    int m=0,n=0,k=0;
    for(i=0; i<N;i++){
            
        /*int ck[N] = {0};*/

        for(m=0;m<N;m++){
            for(n=0;n<N;n++){
                for(k=0;k<N;k++){
                    if(k!=n){
                        if(mat[m][n]==mat[m][k]){
                            return 0;
                        }
                        if(mat[n][m] == mat[k][m]){
                            return 0;
                        }
                    }

                }
            }
        }

       
        int max_s = mat[i][0], max_d = mat[i][N-1];
        int n_vette_s = 1, n_vette_d = 1;  

        for(j=0; j<N; j++){
            if(mat[i][j]>max_s){
                n_vette_s++;
                max_s = mat[i][j];
            }    
            if(mat[i][N-j-1]>max_d){
                n_vette_d++;
                max_d = mat[i][N-j-1];
            }
        }
        if((n_vette_s != altezze[N*4 - i -1]) || (n_vette_d != altezze[N*1 + i])){
                return 0; 
        }

        /* max_d => max from top, max_s => max from bottom */

        max_d = mat[0][i], max_s = mat[N-1][i];
        n_vette_s = 1, n_vette_d = 1;
        for(j=0; j<N; j++){
            if(mat[j][i] > max_d){
                n_vette_d++;
                max_d = mat[j][i];
            }    
            if(mat[N-j-1][i]>max_s){
                n_vette_s++;
                max_s = mat[N-j-1][i];
            }
        }
        if((n_vette_s != altezze[N*3 -i -1]) || (n_vette_d != altezze[i])){
                return 0;
        }
        
    }
    return 1;
}
