#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXD 30 //dimensione massima dizionario
#define MPAROLA 50 //dimensione massima parole e codifiche
#define MRIGA 201 //dimensione massima riga del file
#define FDIZ "dizionario.txt"
#define FSORG "sorgente.txt"
#define FRICOD "ricodificato.txt"

typedef struct {
    char parola[MPAROLA]; char codifica[MPAROLA];
}s_codifica;

int LeggiSalvaDizionario(s_codifica dizionario[]);
void AnalisiRiga(char riga[], s_codifica dizionario[], int n_parol_diz, FILE *f_ricod);
int confronta(char riga[], int inizio, char parola[], int l);


int main(void){

    FILE *fin, *fout;
    s_codifica diz[MAXD];
    int n_parol_diz;
    char riga[MRIGA];

    n_parol_diz = LeggiSalvaDizionario(diz); //funzione prende il vettore di struct s_codifica

    fin = fopen(FSORG, "r");
    fout = fopen(FRICOD, "w");

    if (fin==NULL || fout==NULL) exit(EXIT_FAILURE);

    //Processo le righe del file di input e genero il file di output
    while(fgets(riga, MRIGA, fin)!=NULL){
        AnalisiRiga(riga, diz, n_parol_diz, fout);
    }

    fclose(fin);
    fclose(fout);
    return EXIT_SUCCESS;
}


int LeggiSalvaDizionario(s_codifica diz[]) {

    int n_parole, i;
    FILE *in = fopen(FDIZ, "r");
    if(in==NULL) return 0;

    fscanf(in, "%d", &n_parole);
    for (i = 0; i < n_parole; i++) {
        fscanf(in, "%s %s", diz[i].codifica, diz[i].parola);
    }

    fclose(in);
    return n_parole;
}


void AnalisiRiga(char riga[], s_codifica dizionario[], int n_parol_diz, FILE *f_ricod){
    int i, j, len, trovato;

    //Per ogni carattere della riga
    for(i=0; riga[i]!='\0'; i++){
        trovato = 0;
        //valuta se inizia un match con una parola del dizionario
        for(j=0; j<n_parol_diz; j++){ //nd=numero parole nel dizionario
            len = strlen(dizionario[j].parola);
            if (confronta(riga,i,dizionario[j].parola,len)){
                trovato = 1;
                    break; //se e' trovato allora ferma il ciclo di ricerca nel dizionario
            }
        }
    if (trovato==1){
        //stampa la codifica sul file di output e avanza di len-1 lettere
        fprintf(f_ricod, "%s", dizionario[j].codifica);
        i = i+(len-1); //-1 per compensare l'incremento successivo del for
    }else
        //altrimenti scrivi solo il carattere corrente
        fprintf(f_ricod, "%c", riga[i]);
    }
}

//Prende in ingresso, il vettore con la riga, la posizione di inizio realtiva
//al punto della riga al quale ero arrivato, la stringa con la parola del dizionario
//e un intero relativo alla lunghezza della parola del dizionario

int confronta(char riga[], int inizio, char parola[], int l){
    int j;

    for(j=0;j<l;j++){
        if(riga[inizio+j]!=parola[j])
            return 0;
    }
    return 1;
}