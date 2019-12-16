#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_N 10
int leggi_file(char fn[], int *N, int **mat, int *altezze);
int controllo(int **mat, int *altezze, int N);


int main(int argc, char *argv[])
{
    int N;
    int **mat, *altezze;
    printf("lettura");
    leggi_file(argv[1], &N, mat, altezze);
    printf("lettura");
    printf("%d\n", controllo(mat,altezze,N));
    return 0;
}


int leggi_file(char *fn, int *N, int **mat, int *altezze){
    FILE *fp;
    int i=0,j=0;
    fp = fopen(fn, "rb");
    if(fp==NULL){
        return 100;
    }
    fread(N, sizeof(int), 1, fp);

    for(i = 0; i < *N; i++) mat[i] = (int *)malloc((*N) * sizeof(int));

    altezze = malloc((*N)*4*sizeof(int));

    printf("test");
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

int controllo(int **mat, int *altezze, int N){
    
    int i=0,j=0;

    int m=0,n=0,k=0;
    for(i=0; i<N;i++){
        int max_d = mat[i][0], max_s = mat[i][N];
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
        for(j=1; j<N; j++){
            if(mat[i][j]>max_s){
                n_vette_s++;
                max_s = mat[i][j];
            }    
            if(mat[i][N-j-1]>max_d){
                n_vette_d++;
                max_d = mat[i][N-j-1];
            }

            if((n_vette_s != altezze[N*3 + j]) || (n_vette_d != altezze[N*1 + j])){
                return 0; 
            }
        }

  
        for(j=1; j<N; j++){
            if(mat[j][i]>max_s){
                n_vette_s++;
                max_s = mat[j][i];
            }    
            if(mat[j][N-i-1]>max_d){
                n_vette_d++;
                max_d = mat[j][N-i-1];
            }
            if((n_vette_s != altezze[i]) || (n_vette_d != altezze[N*2 + i])){
                return 0;
            }
        }
        return 1;
    }
}
