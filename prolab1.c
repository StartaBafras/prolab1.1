#include <stdio.h>

int indexDosyasiOlustur();

int indexDosyasiniGoster();

int kayitEkle();

typedef struct kayit{
    int ogrNo;
    int dersKodu;
    int puan;
    int konum;
}kayit;



int main(void)
{
    indexDosyasiOlustur();

    indexDosyasiniGoster();

    kayitEkle();
}



int indexDosyasiniGoster()
{
    FILE *file = fopen("index.txt","r");

    if(file == NULL) return 1;

    int data[2];

    while (!feof(file))
    {
        fscanf(file,"%d)%d",&data[0],&data[1]);
        printf("Anahtar: %d Buffer: %d \n",data[0],data[1]); 
    }


}

int indexDosyasiOlustur()
{



    FILE *file = fopen("students.bin","rb");


    if (file == NULL)  return 1;

    char tmp[20]; // Linked list de gelebilir
    int caunter = 0;
    while (!feof(file))
    {
        fscanf(file,"%s",tmp); // Dosyanın ne kadar büyük olduğunu tespit etmek için bir okuma yapıyoruz
        caunter++;
    }

    rewind(file);


    kayit data[caunter-1]; // Dosya büyüklüğünün 1 eksiği 0 da dahil olarak bizim eleman sayımız

    caunter = 0;
    int konum;
    while (!feof(file))
    {
        konum = ftell(file);
        data[caunter].konum = ftell(file);// burada bir hata var geçici bir çözüm olarak ek değişken kullandık
        fscanf(file,"%d)%d)%d",&data[caunter].ogrNo,&data[caunter].dersKodu,&data[caunter].puan); // Dosyadaki kısımları okuyoruz ancak bütün bilgileri okumak gereksiz burası düzenleencek
        caunter++;
    }

    fclose(file);

    int swap[4];

    for(int i=0;i<caunter-1;i++) // Sıralama algoritmamız
    {
        for(int j=i;j<caunter-1;j++)
        {
            if (data[i].ogrNo > data[j].ogrNo)
            {
                swap[0] = data[i].ogrNo;
                swap[1] = data[i].dersKodu;
                swap[2] = data[i].puan;
                swap[3] = data[i].konum;

                data[i].ogrNo = data[j].ogrNo;
                data[i].dersKodu = data[j].dersKodu;
                data[i].puan = data[j].puan;
                data[i].konum = data[j].konum;

                data[j].ogrNo = swap[0];
                data[j].dersKodu = swap[1];
                data[j].puan = swap[2];
                data[j].konum = swap[3];

                j = i;
            }
        }
    }


    FILE *dosya = fopen("index.txt","w"); 


    if (file == NULL)  return 1;

    for(int i=0;i<caunter-1;i++)
    {
        fprintf(dosya,"%d)%d\n",data[i].ogrNo,data[i].konum); // index dosyası oluşturuluyor
    }

    fclose(dosya);

    return 0;

}

int kayitEkle(){
    kayit student; //Struct yap�m�z� student ismiyle kulland�k

    printf("Ogrenci no giriniz: "); //kullanicidan ogrenciye ait bilgileri aldik
    scanf("%d",&student.ogrNo);
    printf("Ders kodunu giriniz: ");
    scanf("%d",&student.dersKodu);
    printf("Puani giriniz: ");
    scanf("%d",&student.puan);

    FILE *fp = fopen("students.bin","ab");  //binary dosyamizi ekleme yapma modunda actik
    if ((fp = fopen ("students.bin", "ab")) == NULL) { //dosya acilamazsa ekrana hata g�sterdik
      printf("Dosya acma hatasi!");
      return 1;
  }
    fprintf(fp,"%d)%d)%d\n",student.ogrNo,student.dersKodu,student.puan); //Dosyamizin sonuna kullan�c� tarafindan girilen bilgileri yazdik
    fclose(fp);

    indexDosyasiOlustur(); //yaptigimiz eklemenin index dosyasinda sirali sekilde gozukmesi icin index dosyasini tekrar olusturduk.
}

