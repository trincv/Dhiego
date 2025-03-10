#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct Coordenadas{
    float x[700];
    float y[700];
    float origem[700];
} Coordenadas;

void Quebra_Coordenadas(float auxiliar[], char coordenadas[]);

int main()
{
    Coordenadas coor;
    float auxiliar[2];
    char coordenadas[20];
    int icont = 0, jcont = 0, tam = 0, linha = 0;
    float distance = 0;
    float shortcut = 0;
    float aux;     
    char c;
    char point[] = {"points "};
    
    FILE *point_out;

    point_out = fopen("L0Q1.out", "w");
    if(point_out == NULL){
        printf("Falhou");
        return 1;
    }else{
        FILE *point_in;

        point_in = fopen("L0Q1.in","r");

        if(point_in == NULL){
            printf("Falhou");
            return 1;
        }else{
            do{
                c = fgetc(point_in);
                if(c != EOF && linha == 1){
                    fprintf(point_out, "\n");
                    linha = 0;
                }
                if(c != ' ' && c != '\n' && c != EOF && !(c >= 'a' && c <= 'z')){
                    coordenadas[icont++] = c;
                }
                coordenadas[icont] = '\0';
                if((c == ' ' || c == EOF || c == '\n') && coordenadas[0] != '\0'){
                    Quebra_Coordenadas(auxiliar, coordenadas);
                    coor.x[jcont] = auxiliar[0];
                    coor.y[jcont] = auxiliar[1];
                    icont = 0;
                    jcont++;
                    if(c == EOF || c == '\n'){
                        
                        tam = jcont;

                        for(jcont = 0; jcont < tam - 1; jcont++){
                            distance += sqrt((coor.x[jcont] - coor.x[jcont + 1]) * (coor.x[jcont] - coor.x[jcont + 1]) + (coor.y[jcont] - coor.y[jcont + 1]) * (coor.y[jcont] - coor.y[jcont + 1]));
                        }
                        
                        shortcut = sqrt((coor.x[0] - coor.x[tam - 1]) * (coor.x[0] - coor.x[tam - 1]) + (coor.y[0] - coor.y[tam - 1]) * (coor.y[0] - coor.y[tam - 1]));
                        
                        for(icont = 0; icont < tam; icont++){
                            coor.origem[icont] = sqrt((coor.x[icont] * coor.x[icont]) + (coor.y[icont] * coor.y[icont]));
                        }
                        
                        for(icont = 0; icont < tam - 1; icont++){
                            for(jcont = icont + 1; jcont < tam; jcont++)
                                if(coor.origem[icont] > coor.origem[jcont]){
                                    aux = coor.origem[icont];
                                    coor.origem[icont] = coor.origem[jcont];
                                    coor.origem[jcont] = aux;
                                    aux = coor.x[icont];
                                    coor.x[icont] = coor.x[jcont];
                                    coor.x[jcont] = aux;
                                    aux = coor.y[icont];
                                    coor.y[icont] = coor.y[jcont];
                                    coor.y[jcont] = aux;
                                }
                        }
                        fprintf(point_out, "%s", point);
                        for(icont = 0; icont < tam; icont++){
                            fprintf(point_out, "(%.0f,%.0f) ", coor.x[icont], coor.y[icont]);
                        }
                        fprintf(point_out, "distance %.2f shortcut %.2f", distance, shortcut);
                        for(icont = 0; icont < tam; icont++){
                            coor.x[icont] = 0;
                            coor.y[icont] = 0;
                        }
                        linha = 1;
                        jcont = 0;
                        icont = 0;
                        distance = 0;
                    }
                }
            }while(c != EOF);
        
        }
        fclose(point_in);
    }
    fclose(point_out);
}


void Quebra_Coordenadas(float auxiliar[], char coordenadas[])
{

    char LD[10];
    char LE[10];
    float x = 0, y = 0, aux = 1;
    int icont, jcont, position = 0, num = 0;
    int tamD = 0, tamE = 0;
    
    for(icont = 1, jcont = 0; coordenadas[icont] != ','; icont++)
        LE[jcont++] = coordenadas[icont];
    
    LE[jcont] = '\0';
    
    for(icont += 1, jcont = 0; coordenadas[icont] != ')'; icont++)
        LD[jcont++] = coordenadas[icont];
        
    
    LD[jcont] = '\0';                                                                       
                                                                                //Lado esquerdo das coordenas
    if(LE[0] == '-'){
        for(icont = 0; LE[icont] != '\0'; icont++){
            if(LE[icont] == '.'){
                for(; LE[icont] != '\0'; icont++){
                    LE[icont] = LE[icont + 1];
                    position++;
                }
            }
        }
        position--;
        tamE = strlen(LE) - 1;
        if(position > 0){
            for(icont = tamE; icont >= 1; icont--, aux *= 10)
                num += (LE[icont] - '0') * aux;
            num -= num * 2;
            for(aux = 1; position > 0; position--, aux *= 10){}
            x = num / aux;
        }else{
            for(icont = tamE; icont >= 1; icont--, aux *= 10)
                num += (LE[icont] - '0') * aux;
            x = num - (num * 2);
        }
    }else{
        for(icont = 0; LE[icont] != '\0'; icont++){
            if(LE[icont] == '.'){
                for(; LE[icont] != '\0'; icont++){
                    LE[icont] = LE[icont + 1];
                    position++;
                }
            }
        }
        position--;
        tamE = strlen(LE) - 1;
        if(position > 0){
            for(icont = tamE; icont >= 0; icont--, aux *= 10)
                num += (LE[icont] - '0') * aux;
            for(aux = 1; position > 0; position--, aux *= 10){}
            x = num / aux;
        }else{
            for(icont = tamE; icont >= 0; icont--, aux *= 10)
                num += (LE[icont] - '0') * aux;
            x = num;
        }
    }
    position = 0;
    num = 0;                                                                            //Lado direito das coordenas
    if(LD[0] == '-'){
        for(icont = 0; LD[icont] != '\0'; icont++){
            if(LD[icont] == '.'){
                for(; LD[icont] != '\0'; icont++){
                    LD[icont] = LD[icont + 1];
                    position++;
                }
            }
        }
        position--;
        tamD = strlen(LD) - 1;
        if(position > 0){
            for(icont = tamD, aux = 1; icont >= 1; icont--, aux *= 10)
                num += (LD[icont] - '0') * aux;
            num -= num * 2;
            for(aux = 1; position > 0; position--, aux *= 10){}
            y = num / aux;
        }else{
            for(icont = tamD, aux = 1; icont >= 1; icont--, aux *= 10)
                num += (LD[icont] - '0') * aux;
            y = num - (num * 2);
        }
    }else{
        for(icont = 0; LD[icont] != '\0'; icont++){
            if(LD[icont] == '.'){
                for(; LD[icont] != '\0'; icont++){
                    LD[icont] = LD[icont + 1];
                    position++;
                }
            }
        }
        position--;
        tamD = strlen(LD) - 1;
        if(position > 0){
            for(icont = tamD, aux = 1; icont >= 0; icont--, aux *= 10)
                num += (LD[icont] - '0') * aux;
            for(aux = 1; position > 0; position--, aux *= 10){}
            y = num / aux;
        }else{
            for(icont = tamD, aux = 1; icont >= 0; icont--, aux *= 10)
                num += (LD[icont] - '0') * aux;
            y = num;
        }
    }
    auxiliar[0] = x;
    auxiliar[1] = y;
}
