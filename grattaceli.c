#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_N 10
void leggi_file(char fn[], int mat[MAX_N][MAX_N], int *N, int *altezze);
int controllo(int mat[MAX_N][MAX_N], int *altezze, int N);


int main(int argc, char *argv[])
{
    int N;
    int *altezze;
    int mat[MAX_N][MAX_N];
    leggi_file(argv[1], mat, &N, altezze);
    printf("%d\n", controllo(mat,altezze,N));
    return 0;
}


void leggi_file(char *fn, int mat[MAX_N][MAX_N], int *N,  int *altezze){
    FILE *fp;
    int i=0,j=0;
    fp = fopen(fn, "rb");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }

    fread(N, sizeof(int), 1, fp);



    altezze = malloc((*N)*4*sizeof(int));

    for(i=0; i<*N; i++){
        for(j=0; j<*N;j++){
            fread(&mat[i][j], sizeof(int), 1, fp);
        }
    
    }
    for(j=0; j<*N;j++){
        fread(&altezze[j], sizeof(int), 1, fp);
    }
    fclose(fp);
}

int controllo(int mat[MAX_N][MAX_N], int *altezze, int N){
    
    int i=0,j=0;

    int m=0,n=0,k=0;
    for(i=0; i<N;i++){
        int max_d = mat[i][0], max_s = mat[i][N-1];
        int n_vette_s = 1, n_vette_d = 1;   
   

        
        /*int ck[N] = {0};*/

        for(m=0;m<N;m++){
            for(n=0;k<N;n++){
                for(k=0;k<N;k++){
                    if( k!=n){
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

       
        n_vette_s = 1, n_vette_d = 1;  
        for(j=0; j<N; j++){
            if(mat[i][j]>max_s){
                n_vette_s++;
                max_s = mat[i][j];
            }    
            if(mat[i][N-j-1]>max_d){
                n_vette_d++;
                max_d = mat[i][N-j-1];
            }

            if((n_vette_s != altezze[N*3 + j -1]) || (n_vette_d != altezze[N*1 + j -1])){
                return 0; 
            }
        }

        n_vette_s = 1, n_vette_d = 1;
        for(j=0; j<N; j++){
            if(mat[j][i]>max_s){
                n_vette_s++;
                max_s = mat[j][i];
            }    
            if(mat[j][N-i-1]>max_d){
                n_vette_d++;
                max_d = mat[j][N-i-1];
            }
            if((n_vette_s != altezze[i]) || (n_vette_d != altezze[N*2 + i -1])){
                return 0;
            }
        }
        
    }
    return 1;
}
