#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//OGRENCI BILGILERINI BIR DOSYA DA TUTAN VE BILGILER UZERINDE CESITLI ISLEMLER YAPAN C PROGRAMI...
// HAZIRLAYAN : IBRAHIM HALIL TOPRAK HARRAN UNIVERSITESI BILGISAYAR MUHENDISLIGI BULUMU OGRENCISI...
typedef struct ogrenci{
		char ad[15];
		char soyad[15];
		char ogrno[10];
		char adres[40];
		char sehir[15];
		char tel[11];
	}ogrcim;

void kayitguncelle();
void kayitekle();
void kayitara();
void kayitlistele();
void kayitsil();
void menu();
// GORULDUGU GIBI PROGRAM 1 MAIN 6 VOID FONKSIYONA SAHIP...
int main()
{
	menu();

}

void kayitekle()
{
    int sinir,i=1;
	ogrcim *ogrenciobj,*ogrenciobj1;
	ogrenciobj=(ogrcim*)calloc(1,sizeof(ogrcim));
    ogrenciobj1=(ogrcim*)calloc(1,sizeof(ogrcim));
	FILE *ogrencidb;
	ogrencidb=fopen("userfile.txt","a+");
	printf("ogrencinin adini girin :");
	fflush(stdin);
	gets((*ogrenciobj).ad);
	printf("ogrencinin soyadini girin :");
	scanf("%s",(*ogrenciobj).soyad);
	printf("ogrencinin numarasini girin :");
	scanf("%s",(*ogrenciobj).ogrno);
	fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim);    //bu kod vasitasiyla dosya kac adet ogrenci oldugunu buluyoruz.
    rewind(ogrencidb);
	while(i<=sinir)                //bu döngü araciligiyla girilen kaydin dosyada olup olmadigini kontrol ediyoruz.
    {
        fread(ogrenciobj1,sizeof(ogrcim),1,ogrencidb);
        fseek(ogrencidb,2,SEEK_CUR);       //2 bayt kaydirmamizin sebebi dosyada kisi bilgileri alt alta siralanmasi "\n" hafizada 2 bayt yer kaplar.
        if(strcmp(ogrenciobj1->ogrno,ogrenciobj->ogrno)==0)
        {
            printf("\ngirilen ogrenci numarasi daha onceden bulundugu icin kaydiniz yapilamadi...\n");
            menu();
        }
        i++;
    }
    rewind(ogrencidb);
	printf("ogrencinin adresi girin :");
	scanf("%s",(*ogrenciobj).adres);
	printf("ogrencinin yasadigi sehiri girin :");
	scanf("%s",(*ogrenciobj).sehir);
	printf("ogrencinin telefon numarasini girin :");
	scanf("%s",(*ogrenciobj).tel);
	fwrite(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
	fprintf(ogrencidb,"\n");
	printf("\nkayit basari ile eklendi...\n");
	fclose(ogrencidb);
    free(ogrenciobj1);
	free(ogrenciobj);
	menu();
}
void kayitsil()
{
	ogrcim *ogrenciobj;
	char num[10];
	int say=0,j=0;
	FILE  *ogrencidb;
	FILE  *tempogrencidb;
	ogrencidb=fopen("userfile.txt","r+");
	ogrenciobj=(ogrcim*)calloc(1,sizeof(ogrcim));
	tempogrencidb=fopen("tempuserfile.txt","w+");
	if(ogrencidb==NULL)
    {
        printf("dosya acilamadi.\n");
        exit(1);
    }
    printf("silinecek ogrencinin okul numarasini girin : ");
    scanf("%s",num);
    int sinir,i=1;
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim); //bu kod vasitasiyla dosya kac adet ogrenci oldugunu buluyoruz.
    rewind(ogrencidb);
    while(i<=sinir)
    {
        fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
        fseek(ogrencidb,2,SEEK_CUR);
        if(strcmp((*ogrenciobj).ogrno,num))
        {
            fwrite(ogrenciobj,sizeof(ogrcim),1,tempogrencidb);
            fprintf(tempogrencidb,"\n");
        }
        if(strcmp((*ogrenciobj).ogrno,num)==0)
        {
            say++;                        // bu sayac vasitasiyla kaydin dosyada bulunup bulunmadigini kontrol ediyoruz.
        }
            i++;
    }

	free(ogrenciobj);

  if(say==0)  //kayit dosyada bulunamadiysa olustudurdugumuz ikinci dosyayi siliyoruz.
  {
      fclose(ogrencidb);
      fclose(tempogrencidb);
      remove("tempuserfile.txt");
      printf("kayit bulunamadi...\n");
      free(ogrenciobj);
      menu();
  }
  else if(say!=0)  //kayit dosyada bulunduysa asil dosyayi silip olusturdumuz ikinci dosyanin asil dosya olarak degistirip silme islemini tamamliyoruz.
  {
      fclose(ogrencidb);
      fclose(tempogrencidb);
      remove("userfile.txt");
      rename("tempuserfile.txt","userfile.txt");
      printf("kayit bulundu...\n");
      printf("kayit basari ile silindi...\n");
      free(ogrenciobj);
      menu();

  }

}

void menu()
{
	int tercih;
	printf("\n********************\n");
	printf("1-Ogrenci Girisi\n");
	printf("2-Kayit Arama.\n");
	printf("3-Kayit Guncelle.\n");
	printf("4-Kayit Sil.\n");
	printf("5-Listele\n");
	printf("6-Programdan cik.\n");
	printf("7-Ekrani Temizle\n");
	printf("\n********************\n");
    printf("Seciminiz?[1-7] : ");
    scanf("%d",&tercih);
	if(tercih==7)
    {
        system("cls");
        menu();
    }
	if(tercih==6)
	exit(0);
	while(tercih!=6)
	{
		switch(tercih)
		{
           case 1:{kayitekle();break;}
		   case 2:{kayitara();break;}
           case 3:{kayitguncelle();break;}
           case 4:{kayitsil();break;}
           case 5:{kayitlistele();break;}
		}
	}
}

void kayitlistele()
{
    ogrcim *ogrenciobj;
    FILE *ogrencidb;
    ogrencidb=fopen("userfile.txt","r+");
    if(ogrencidb==NULL)
    {
        printf("dosya acilamadi.\n");
        exit(1);
    }
    ogrenciobj=calloc(1,sizeof(ogrcim));
    int i=0,sinir,j=1;
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim); //bu kod vasitasiyla dosyada kac adet ogrenci oldugunu buluyoruz.
    rewind(ogrencidb);
    printf("  Ad                |SoyAd            |Numara      |Adres                                     |Tel              |Sehir               ");
    printf("\n*****************************************************************************************************************************\n");
    while((i/sizeof(ogrcim))<sinir)
       {
          fseek(ogrencidb,i,SEEK_SET);
          fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
          printf("%d- %15s  |%15s  |%10s  |%40s  |%15s  |%11s ",j,(*ogrenciobj).ad,(*ogrenciobj).soyad,(*ogrenciobj).ogrno,(*ogrenciobj).adres,(*ogrenciobj).tel,(*ogrenciobj).sehir);
          printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");
          i+=sizeof(ogrcim)+2;
          j++;
       }
if(sinir==0)
    printf("listelenecek herhangi bir kayit bulunmamaktadir...\n");
    free(ogrenciobj);
    fclose(ogrencidb);
    menu();
}

void kayitara()
{
    int kayitno,j,sinir;
    FILE *ogrencidb;
    ogrcim *ogrenciobj;
    ogrenciobj=(ogrcim*)calloc(1,sizeof(ogrcim));
    ogrencidb=fopen("userfile.txt","r+");
    if(ogrencidb==NULL)
    {
        printf("dosya acilamadi.\n");
        exit(1);
    }
    printf("aranacak ogrencinin sirasi :");
    scanf("%d",&kayitno);
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim);    //bu kod vasitasiyla dosyada kac adet ogrenci oldugunu buluyoruz.
    fseek(ogrencidb,0,SEEK_SET);
    if(kayitno<=sinir)
    {
        if(kayitno==1)
        {
            j=0;
        }
        else
        {
            j=(kayitno-1)*(sizeof(ogrcim)+2);  // bu kod araciligiyla imlecin dosyada ne kadar kaydirilacagini buluyoruz.
        }
        fseek(ogrencidb,j,SEEK_SET);
        fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
            printf("%d.siradaki ogrenci bulunmustur...\n\n",kayitno);
            printf("%d-%s %s %s.\n",kayitno,(*ogrenciobj).ad,(*ogrenciobj).soyad,(*ogrenciobj).ogrno);
            free(ogrenciobj);
            fclose(ogrencidb);
            menu();
    }
    else
    {
         printf("kayit bulunamadi...");
         	free(ogrenciobj);
         	fclose(ogrencidb);
            menu();

    }

}
void kayitguncelle()
{
    char num[10],guncel;
    int secim,kontr=0;
    FILE *ogrencidb,*tempogrencidb;   //görüldüðü gibi bilgileri guncellemek için iki farkli dosya kullaniyoruz.
    ogrcim *ogrenciobj;
    tempogrencidb=fopen("tempuserfile.txt","w+");
    ogrencidb=fopen("userfile.txt","a+");
    ogrenciobj=calloc(1,sizeof(ogrcim));
    printf("\nguncellemek istediginiz ogrencinin okul numarasini girin :");
    scanf("%s",&num);
    int sinir,i=1;
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim);  //bu kod vasitasiyla dosyada kac adet ogrenci oldugunu buluyoruz.
    rewind(ogrencidb);

    while(i<=sinir)
    {

        fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
        fseek(ogrencidb,2,SEEK_CUR);
        if(strcmp(ogrenciobj->ogrno,num)!=0)
        {
            fwrite(ogrenciobj,sizeof(ogrcim),1,tempogrencidb);
            fprintf(tempogrencidb,"\n");
        }
        if(strcmp(ogrenciobj->ogrno,num)==0)
        {
            printf("ogrenci bulunmustur...\n\n");
            back: printf("guncellemek istediginiz ogrencinin bilgileri>>\n\n");
            printf("%s ",(*ogrenciobj).ad);
            printf("%s ",(*ogrenciobj).soyad);
            printf("%s",(*ogrenciobj).ogrno);
            printf("\nAdres :%s",(*ogrenciobj).adres);
            printf("\nTel :%s",(*ogrenciobj).tel);
            printf("\nSehir :%s",(*ogrenciobj).sehir);
            printf("\n-----------------------\n");
           back2: printf("\nisim[1] || soyisim[2] || adres[3] || okulno[4] || sehir[5] || tel[6] || tum bigiler[7]\n");
            printf("\nsecimiminizi giriniz...");
            scanf("%d",&secim);
            switch(secim)    //switch-case yardimiyla guncelenmek istenen kullanicinin hangi bilgisi üzerinde degiþiklik yapilmasi gerektigini ogreniyoruz.
            {
            case 1:{
                printf("ogrencinin adini girin :");
	            scanf("%s",(*ogrenciobj).ad);
	            break;
              }
            case 2:{
                 printf("ogrencinin soyadini girin :");
	             scanf("%s",(*ogrenciobj).soyad);
	             break;
            }
            case 3:{
                printf("ogrencinin adresi girin :");
                scanf("%s",(*ogrenciobj).adres);
                break;
            }
            case 4:{
                printf("ogrencinin numarasini girin :");
	            scanf("%s",(*ogrenciobj).ogrno);
	            break;
            }
            case 5:{
                printf("ogrencinin yasadigi sehiri girin :");
	            scanf("%s",(*ogrenciobj).sehir);
	            break;
            }
            case 6:{
                 printf("ogrencinin telefon numarasini girin :");
	             scanf("%s",(*ogrenciobj).tel);
	             break;
            }
            case 7:{
                 printf("ogrencinin adini girin :");
	             scanf("%s",(*ogrenciobj).ad);
	             printf("ogrencinin soyadini girin :");
                 scanf("%s",(*ogrenciobj).soyad);
                 printf("ogrencinin adresi girin :");
                 scanf("%s",(*ogrenciobj).adres);
                 printf("ogrencinin numarasini girin :");
	             scanf("%s",(*ogrenciobj).ogrno);
	             printf("ogrencinin yasadigi sehiri girin :");
	             scanf("%s",(*ogrenciobj).sehir);
	             printf("ogrencinin telefon numarasini girin :");
	             scanf("%s",(*ogrenciobj).tel);
	             break;
            }

            default :{
                system("cls");
            printf("yanlis secim yaptiniz!!!\n");
            goto back;}       //eger kullanici yanlis bir seçim yaparsa onu uyarip goto komutuyla tekrar seçim yapmasini saglýyoruz.

            }
            printf("\nguncelleme islemine devam etmek icin 1'e ,islemi sonlandirmak icin herhangi bir tusa basiniz\n");
            guncel=getch();  //bu kod arailigiyla kullanicinin guncelleme islemine devam etmek isteyip istemedigini kontrol ediyoruz.
            if(guncel=='1')
            {
                goto back2;
            }
             fwrite(ogrenciobj,sizeof(ogrcim),1,tempogrencidb);
             fprintf(tempogrencidb,"\n");
             kontr++;        //bu sayac araciligiyla guncellenmek istenen kullanicinin bulunup bulunmadiðini kontrol ediyoruz.


            }
            i++;
        }

    if(kontr==0)
    {
        printf("\nguncellemek istediginiz ogrenci bulunamamistir.\n");
        fclose(ogrencidb);
        fclose(tempogrencidb);
        free(ogrenciobj);
        remove("tempuserfile.txt");
        menu();
    }
    if(kontr!=0)
    {
            fclose(ogrencidb);
             fclose(tempogrencidb);
             remove("userfile.txt");
             rename("tempuserfile.txt","userfile.txt");
             free(ogrenciobj);
             printf("\nkayit basariyla guncellenmistir...\n");
             menu();
    }
}
