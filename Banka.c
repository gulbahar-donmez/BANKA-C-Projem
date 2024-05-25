#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <windows.h>



int id;
int secim;
int bakiye;
int rastgele;
int bak;

char ad[20];
char soyad[20];
char tel[20];
char adres[20];

FILE* dosya; //üzerinde çalýþtýðýmýz dosya
FILE* gecici;  //bir gecici dosya oluþturacaðýz ve tüm verileri gecici dosyanýn üzerine atacaðýz 


int cizim() {
	system("color 0a");

	FILE* file;
	char c;

	file = fopen("ybsb.txt", "r");

	if (file == NULL) {
		printf("Dosya Bulunamadý!.\n");
		exit(0);
	}

	while ((c = fgetc(file)) != EOF) {
		printf("%c", c);
	}

	fclose(file);

	printf("\n\n\n\n3 sn icinde anasayfaya yonlendirileceksiniz..."); Sleep(3000);

	return 0;


}


void ekle() {
	system("cls");

	printf("\nkayit edilecek musteri bilgilerinizi giriniz: \n");
	printf("ad:\n");
	scanf("%s", &ad);
	printf("soyadi:\n");
	scanf("%s", &soyad);
	printf("Telefon no:\n");
	scanf("%s", &tel);
	printf("Adres:\n");
	scanf("%s", &adres);

	if ((dosya = fopen("musterikayit.txt", "a")) != NULL) {

		fprintf(dosya, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);

	}

	printf("kayit islemi gerceklestiriliyor...\n");
	Sleep(2000);
	printf("kayit isleminiz gerceklestirildi...\n");
	printf("Ana Menuye yonlenririliyorsunuz");
	printf(""); Sleep(3000);
	fclose(dosya); //dosyayý pointer olarak kapattýk...

}

void listele() {

	system("cls"); //ekraný temizleyelim.
	printf("listeleme islemi gerceklestiriliyor...\n"); Sleep(2000);
	printf("listeleme islemi basariyla gerceklestirildi\n\n");
	printf("kayitli musteri bilgileri: \n");
	printf("********************************************************************\n");
	printf("Ad\t\tSoyadi\t\tTelefon no\t\tAdres\t\t\n\n");

	if ((dosya = fopen("musterikayit.txt", "r")) != NULL) {
		strcpy(ad, "");
		strcpy(soyad, "");
		strcpy(tel, "");
		strcpy(adres, "");

		while (!feof(dosya))
		{
			fscanf(dosya, "%s\t\t%s\t\t%s\t\t%s\n\n", ad, soyad, tel, adres);  //dosyadan alsýn
			printf("%s\t\t%s\t\t%s\t\t%s\n\n", ad, soyad, tel, adres);

		}
		printf("\n***************************************************************\n");

	}
	printf("Ana Menuye yonlenririliyorsunuz"); Sleep(2000);
	printf(""); Sleep(3000);
	Sleep(5000);
	fclose(dosya);

}

void Arama()
{
	system("cls"); //ekraný temizleyelim.

	char isim[20];
	int sonuc = 0; //olmayan bir kiþiyi de arayabiliriz..

	printf("Aradiginiz Musterinin ismi: ");
	scanf("%s", &isim);

	printf("aranan musteri bilgileri: \n.");
	printf("******************************\n");
	printf("Ad\tSoyadý\ttelefon no\tadres\n");

	if ((dosya = fopen("musterikayit.txt", "r")) != NULL) {
		while (!feof(dosya))
		{
			fscanf(dosya, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);  //dosyadan alsýn

			if (strcmp(isim, ad) == 0)
			{
				printf("%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);
				fclose(dosya);
				sonuc = 1;

				break; //while kýrmak için
			}

		}

		printf("\n******************************\n");
		Sleep(5000);
	}

	fclose(dosya);

	if (sonuc == 0)
	{
		Sleep(5000);
		printf("%s isimli musteri listede yoktur.", isim);
		Sleep(5000);
	}
}

void Yedekle() {
	if ((gecici = fopen("yedekkayit.txt", "w")) != NULL)
	{

		if ((dosya = fopen("musterikayit.txt", "r")) != NULL)
		{

			while (!feof(dosya))
			{

				fscanf(dosya, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);
				fprintf(gecici, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);

			}

		}

	}

	remove("musterikayit.txt");
	fclose(gecici);
	fclose(dosya);

}


void Guncelle(char* ptrisim) {
	if ((dosya = fopen("musterikayit.txt", "w")) != NULL) { //bu dosya varsa siler.0'dan baþlar

		if ((gecici = fopen("yedekkayit.txt", "r")) != NULL) {

			while (!feof(gecici))
			{
				fscanf(gecici, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);
				if (strcmp(ptrisim, ad) == 0)
				{
					continue;

				}
				fprintf(dosya, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);

			}
		}

	}
	remove("yedekkayit.txt");
	fclose(gecici);
	fclose(dosya);  //dosyayý pointer olarak kapattýk...





}

void Sil() {
	system("cls"); //ekraný temizleyelim.

	char isim[20];
	int sonuc = 0; //olmayan bir kiþiyi de arayabiliriz..

	printf("silmek istediginiz musterinin ismi:"); scanf("%s", &isim);

	if ((dosya = fopen("musterikayit.txt", "r")) != NULL) {

		while (!feof(dosya))
		{
			fscanf(dosya, "%s\t%s\t%s\t%s\n", ad, soyad, tel, adres);  //dosyadan alsýn
			if (strcmp(isim, ad) == 0) //kýyaslama yapýyoruz.
			{

				fclose(dosya); //dosyayý kapatýk
				Yedekle();
				Guncelle(isim);
				sonuc = 1;
				break; //while kýrmak için
			}





		}


	}

	fclose(dosya);
	if (sonuc == 0)
	{
		printf("%s isimli musteri listede yoktur.\n", isim);
	}
	else
	{
		printf("silme islemi gerceklestiriliyor...\n"); Sleep(2000);
		printf("silme islemi basariyla tamamlanmistir...\n");
		printf("Ana Menuye yonlenririliyorsunuz"); Sleep(2000);
		printf(""); Sleep(3000);
	}



}

void paraCek() {
	system("cls");
	int miktar;

	printf("Gecerli para cekilebilir bakiyeniz: %d\n", bak);
	printf("Cekmek istediginiz miktari giriniz: ");
	scanf("%d", &miktar);

	if (miktar > bak) {
		printf("Yetersiz bakiye. secim basarisiz.\n");
	}
	else {
		bak -= miktar;
		printf("Para cekme secimi basarili... \nYeni bakiyeniz: %d\n", bak);
	}
}

void paraYatir() {

	system("cls");
	int miktar;

	printf("Gecerli bakiyeniz: %d\n", bak);
	printf("Ytirmak istediginiz miktari giriniz: ");
	scanf("%d", &miktar);

	bak += miktar;
	printf("Para yatirma islemi basarili... \nYeni bakiyeniz: %d\n", bak);

}

void faturaOde() {
	int miktar, numara;
	system("cls");
	//rastgele1();
	printf("1-elektrik\n");
	printf("2-su\n");
	printf("3-dogalgaz\n");
	printf("4-telefon\n");
	scanf("%d", &secim);
	if (secim < 1 || secim>4)
	{
		printf("Hatali Secim Yaptiniz!");

	}
	else
	{
		{}
		printf("Fatura No: "); scanf("%d", &numara);
		int fatura = rand() % 100 + 20;
		printf("fatura Bedeli:%d TL\n", fatura);
		printf("1-ODEMEYI ONAYLIYORUM\n");
		printf("secim:");
		scanf("%d", &secim);
		if (secim != 1) {
			printf("odeme islemi iptal edildi.");
		}
		else
		{
			if (fatura > bak)
			{
				printf("yetersiz bakiye!!");

			}
			else
			{
				bak -= fatura;
				printf("fatura odeme isleminiz gerceklestiriliyor...\n"); Sleep(1000);
				printf("fatura odeme islemi basariyla gerceklestirildi...\n");
				printf("\tKALAN BAKIYENIZ:%d", bak);

			}

		}
	}

}

void havaleEFT() {
	//rastgele1();
	system("cls");

	int iban, miktar;
	printf("Havale yapmak istediginiz kisinin iban numarasini giriniz: ");
	scanf("%d", &iban);
	printf("Havale yapacagýnýz miktari giriniz: ");
	scanf("%d", &miktar);
	if (miktar > bak) {
		printf("Yetersiz bakiye.\n");
	}
	else {
		bak -= miktar;
		printf("EFT / havale seciminiz basarili.\nYeni bakiyeniz: %d\n", bak);
	}
}

void kredi() {
	int cekim;
	system("cls");

	printf("hakkinizda tanimlanabilecek kredi miktari hesaplaniyor...\n\n\n\n"); Sleep(5000);
	srand(time(NULL));
	int rastgele = rand() % 100000 + 10000;
	printf("\tCekilebilir miktariniz= %d\n", rastgele);
	printf("\tLutfen cekmek istediginiz miktari giriniz!\n ");
	scanf("%d", &cekim);

	if (cekim <= rastgele)
	{
		bak = rastgele + cekim;

		printf("\nyeni bakiyeniz: %d \n", bak);
	}

	else
	{
		printf("cekmek istediginiz miktara kredi puaniniz yetmemektedir.Lutfen cekebieceginiz bir deger giriniz.");
	}

}

void dolar() {
	system("cls");
	int pbirim;
	srand(time(NULL));
	int dolar = rand() % 10 + 20;
	printf("\tDolar Kuru: %d\n", dolar);
	printf("yatirmak istediginiz miktari giriniz:");
	scanf("%d", &pbirim);
	bak = dolar * pbirim + bak;
	printf("bakiyeniz:%d", bak);
}


void euro() {
	system("cls");
	int pbirim;
	srand(time(NULL));
	int euro = rand() % 10 + 20;
	printf("\tEuro Kuru: %d\n", euro);
	printf("yatirmak istediginiz miktari giriniz:");
	scanf("%d", &pbirim);
	bak = euro * pbirim + bak;
	printf("bakiyeniz:%d", bak);
}

void sterlin() {
	system("cls");
	int pbirim;
	srand(time(NULL));
	int sterlin = rand() % 10 + 20;
	printf("\tSterlin Kuru: %d\n", sterlin);
	printf("yatirmak istediginiz miktari giriniz:");
	scanf("%d", &pbirim);
	bak = sterlin * pbirim + bak;
	printf("bakiyeniz:%d", bak);
}

void yen() {
	system("cls");
	int pbirim;
	srand(time(NULL));
	int yen = rand() % 10 + 20;
	printf("\tYen Kuru: %d\n", yen);
	printf("yatirmak istediginiz miktari giriniz:");
	scanf("%d", &pbirim);
	bak = yen * pbirim + bak;
	printf("bakiyeniz:%d", bak);
}

void frang() {
	system("cls");
	int pbirim;
	srand(time(NULL));
	int frang = rand() % 10 + 20;
	printf("\tFrang Kuru: %d\n", frang);
	printf("yatirmak istediginiz miktari giriniz:");
	scanf("%d", &pbirim);
	bak = frang * pbirim + bak;
	printf("bakiyeniz:%d", bak);
}


void dovizmenu() {
	system("cls");
	printf("BANKAMIZDAN DOVIZ SATIS ISLEMI YAPILAMAMAKTADIR!!!\n\n");

	printf("\t1-dolar\n");
	printf("\t2-euro\n");
	printf("\t3-sterlin \n");
	printf("\t4-yen\n");
	printf("\t5-frang\n");
	printf("\t6-cikis\n\n");
	printf("\tlutfen giris yapmak istediginiz para birimini seciniz!\n");
	scanf("%d", &secim);

	switch (secim)
	{
	case 1:
		dolar();
		break;
	case 2:
		euro();
		break;
	case 3:
		sterlin();
		break;
	case 4:
		yen();
		break;
	case 5:
		frang();
		break;
	case 6:
		exit(6);
		break;

	default:
		printf("hatali secim yaptiniz!");
		break;
	}


}


void yetkiligiris() {

	system("cls");
	//YAPILACAK: if koþulu konulacak eðer adminse bu ekrana gidecek deðilse ana menuye ya da müþteri giriþ ekranýna atacak
	int secim = -1;
	while (secim != 0)  //0 bastýðýnda program sonlanacak.
	{
		system("cls");

		printf("\nlutfen yapmak istediðiniz islemi seciniz...\n");
		printf("\n1-Ekle\n");
		printf("\n2-Listele\n");
		printf("\n3-Ara\n");
		printf("\n4-Sil\n");
		printf("\n5 cikis\n");
		printf("seciminiz : ");
		scanf("%d", &secim);
		printf("isleminiz gerceklestiriliyor...");
		Sleep(2000);

		switch (secim)

		{

		case 1:
			ekle();
			break;
		case 2:
			listele();
			break;
		case 3:
			Arama();
			break;
		case 4:
			Sil();
			break;
		case 5:
			printf("cikisiniz yapiliyor..."); Sleep(1000);
			printf("\ncikisiniz yapilmistir.Herhangi bir dugmeye basarsaniz sistemden cikmis olucaksiniz!\n\n");
			exit(5);

			break;
		default:
			printf("hatali secim yaptiniz!!!!");
			break;
		}

	}


}


int musterigiris() {
	system("cls");

	int secc = -1;

	while (secc != 7) {
		system("cls");
		printf("\nKullanilabilir bakiyeniz : %d TL \n\n", bak);

		printf("\t1. Paraya Cek\n");
		printf("\t2. Para Yatir\n");
		printf("\t3. Fatura Ode\n");
		printf("\t4. Havale/EFT\n");
		printf("\t5.Kredi islemleri\n");
		printf("\t6.Doviz islemleri\n");
		printf("\t7. Cikis\n");
		printf("\tSeciminizi yapiniz: ");
		scanf("%d", &secim);

		switch (secim)
		{
		case 1:paraCek();
			break;
		case 2:paraYatir();
			break;
		case 3:faturaOde();
			break;
		case 4:havaleEFT();
			break;
		case 5:kredi();
			break;
		case 6:dovizmenu();
			break;
		case 7: exit(7);
			break;
		default:
			printf("Hatali Secim Yaptiniz..");
			break;
		}

		printf("islemleriniz bitmistir...Ana menuye yonlendiriliyorsunuz..."); Sleep(5000);

	}

	return 0;
}

void giris() {
	cizim();
	system("cls");
	printf("\t1-YETKILI MENU:\n");
	printf("\t2-MUSTERI MENU:\n");
	printf("\t3-CIKIS:\n\n");
	printf("\tLutfen ID Giriniz:  ");
	scanf("%d", &secim);

	switch (secim)
	{
	case 1:
		yetkiligiris();
		break;
	case 2:
		musterigiris();
		break;
	case 3:
		printf("\tcikisiniz yapiliyor...\n"); Sleep(1000);
		printf("\tcikisiniz yapilmistir.Herhangi bir dugmeye basarsaniz sistemden cikmis olacaktir!\n\n");
		exit(3);
		break;
	default:
		system("cls");
		printf("Hatali giris yaptiniz! Girise yonlendiriliyorsunuz..."); Sleep(2000);
		system("cls");
		giris();
		break;
	}

}

int main() {
	srand(time(NULL));
	bak = rand() % 1000000000 + 10000;
	giris();

	return 0;
}

