#include <stdio.h>
#include <stdlib.h>

//definisali smo XO
#define XO 3

int pocetak(){
    //Definisemo potrebne stavke
    int i1,i2,potez=0,br=0,i,j;

    //definisemo pokazivac na array koji ce nam kasnije sluziti da provjerimo koja smo polja koristili
    int *array;
    int size=9;

    //oslobodimo memoriju njogovu ili drugim rijecima ucinimo ga sposobnim za rad, da nam se ne prikazuju neki
    //random brojevi
    array = (int*)malloc(sizeof(int)*size);

    //definisemo tabelu polja koristeci 2d, umjesto crtica stavili smo brojeve jer je lakse kasnije
    //da vidimo koja su polja slobodna i da ne bi pogrijesili prilikom klika
    char tabela[XO][XO] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
    };
    //pokazivac na 2d niz tj pokazivac na tabelu iznad
    char (*p)[XO];
    p=tabela;

    //pozivamo funkciju kako bi dobili prvobitnu tabelu tj da vidimo kako izgleda
    nacrtajTabelu(p);

    //definisemo integer kako bi kasnije ga spojili sa funckijom
    int pr=0;

    //sada idemo na malo tezi dio, igra ima 9 poteza te poteze je potrebno raspodijeliti i
    // oznaciti ko je gdje sta igrao prvenstveno koristimo for petlju kako bi ogranicili na 9 poteza
    for(i=0;i<9;i++){

            //ovdje stoji uslov pr !=1 to znaci da nemamo jos pobjednika i da je igra u toku
    if(pr != 1){
        //ukoliko je potez 0 igra prvi igrac ukoliko je 1 igra drugi igrac
        if(potez == 0){

            printf("Na potezu je igrac 1: ");
            //pozivamo funkciju kako bi unijeli zeljeno polje od igraca prvog
            i1 = igrac(array);
            //ubacimo u tabelu njegov odgovor tj broj koji odabere
            napraviTabelu(p,i1,'X');
            // a zatim ispisemo tu tabelu
            nacrtajTabelu(p);
            // tu pozivamo funkciju koja provjerava da li igrac ima 3 spojena X ili O kako bi znali da li je
            // opobjedio
            pr=provjeriPobjedu(p,potez);
            //kada zavrsimo potez prvog igraca prebacujemo se na sljedeceg
            potez = 1;


        }else if(potez==1){
            //sve isto vrijedi ko za prvog igraca
            printf("Na potezu je igrac 2: ");
            i2 = igrac(array);
            napraviTabelu(p,i2,'O');
            nacrtajTabelu(p);
            pr=provjeriPobjedu(p,potez);


            potez = 0;


        }



    }
    }

}

//funkcija igrac gdje igrac unosi svoj broj
int igrac(int array[]){
    int i,j;
    //skeniramo broj
    scanf("%d",&i);
    for(j=0;j<=9;j++){
            //ukoliko je vec postojiuneseno slovo na mjesto njegovog broja zamolimo ga da unese drugo polje
    if(*(array+j) == i){
        printf("Molim vas unesite slobodan broj!\n");
        scanf("%d",&i);
    }}
    //ukoliko klikce neispravna polja ponavljamo mu da unese neko od validnih polja
    while (i<0 || i>9){
        printf("Unesite broj od 1 - 9!\n");
        scanf("%d",&i);
    }
    *(array+i) = i;

    return i;
}

//nakon svakog unosa tu se formira nova tabela drugim rijecima azuriramo vec postojecu
void napraviTabelu(char (*p)[XO],int x,char slovo){
    int i,j,br=0;
    //slijedi klasicna funkcija za pointere(pokazivace)
    for(i=0;i<XO;i++){
        for(j=0;j<XO;j++){
            if((br) == (x-1)){
                *(*(p+i)+j) = slovo;
                br=9;
            }

            else br++;
        }

    }
}

//nakon unosa i azuriranja tabele sljedecom funkcijom refreshujemo nasu tabelu u consoli te nam ispisuje nove
//rezultate
void nacrtajTabelu(char (*p)[XO]){
    int i,j;
    //takodjer koristeci pointere tj pokazivace
    for(i=0;i<XO;i++){
        for(j=0;j<XO;j++){
            printf(" %c -",*(*(p+i)+j));
        }
        printf("\n");
    }
}

//Kao sto smo ranije naveli tu je funkcija provjere da li je neko pobjednik
int provjeriPobjedu(char (*p)[XO], int potez){
    int i,j,dig1=0,dig2=0;
    //takodjer radimo preko pokazivaca
    for(i=0;i<XO;i++){
        for(j=0;j<XO;j++){
                // za pocetak skeniramo dijagonalo tj ovu "\"
                if(i==j)
                    {
                if (*(*(p+i)+j)=='X'){
                    dig1++;

                }
                    else if (*(*(p+i)+j)=='O'){
                    dig2++;

                }
                }
                //zatim provjerimo redove za X igraca a poslije za O igraca
                if(*(*(p+i)+j)=='X' && *(*(p+i)+j+1)=='X' && *(*(p+i)+j+2)=='X'){
                    printf("IMAMO POBJEDNIKA (IGRAC 1)!\n");
                    return 1;
                }
                if(*(*(p+i)+j)=='O' && *(*(p+i)+j+1)=='O' && *(*(p+i)+j+2)=='O'){
                    printf("IMAMO POBJEDNIKA (IGRAC 2)!\n");
                    return 1;
                }
                //kad smo provjerili redove provjeravamo i kolone
                if(*(*(p+j)+i)=='X' && *(*(p+j+1)+i)=='X' && *(*(p+j+2)+i)=='X'){
                    printf("IMAMO POBJEDNIKA (IGRAC 1)!\n");
                    return 1;
                }
                if(*(*(p+j)+i)=='O' && *(*(p+j+1)+i)=='O' && *(*(p+j+2)+i)=='O'){
                    printf("IMAMO POBJEDNIKA (IGRAC 2)!\n");
                    return 1;
                }

                //zatim provjerimo desnu dijagonalu tj "/" mogli smo i prethodnu dijagonalu na isti nacin
                // ali smo zadatak ucinili zanimljivijim
                if(*(*(p+i)+j+2)=='X' && *(*(p+i+1)+j+1)=='X' && *(*(p+i+2)+j)=='X'){
                    printf("IMAMO POBJEDNIKA (IGRAC 1)!\n");
                    return 1;
                }
                if(*(*(p+i)+j+2)=='O' && *(*(p+i+1)+j+1)=='O' && *(*(p+i+2)+j)=='O'){
                    printf("IMAMO POBJEDNIKA (IGRAC 2)!\n");
                    return 1;
                }





            }

        }
        //Ovu sluzi samo za prvu dijagonalu jer kao sto ste vidjeli ukljucen je gore u samom pocetku brojac
    if(dig1== 3){
        printf("IMAMO POBJEDNIKA (IGRAC 1)!\n");
        return 1;
    }else if (dig2== 3){
        printf("IMAMO POBJEDNIKA (IGRAC 2)!\n");
        return 1;
    }

    //ukoliko nema pobjednika jos vrati(return) se 0 ako neam pobjednika i 1 ako ima, gore smo definisali u ifu
    //ako ima pobjednik tj ako je pr != 1 da se nastavi igra ali ako vratimo tj returnamo vrijednost 1, igra
    //se obustavlja
return 0;
}

//kad smo sve spojili pozivamo u main funkciju
int main()
{
    printf("Zapocnite Igru!\n");
    pocetak();
    return 0;
}
