#include <stdio.h>
#include <stdlib.h>

int indexDosyasiOlustur();

int indexDosyasiniGoster();

int kayitEkle();

int indeksDosyasiniSil();

int veriDosyasiniGoster();

int kayitBul(int number,int *location);

int* find_neighbor(int *data, int index,int *location);

int kayitGuncelle();

typedef struct kayit{
    int ogrNo;
    int dersKodu;
    int puan;
    int konum;
}kayit;



int main(void)
{
    indexDosyasiOlustur();

    //indexDosyasiniGoster();

    //kayitEkle();

    //indeksDosyasiniSil();

    //veriDosyasiniGoster();
    int *location = malloc(sizeof(int)*2);
    int a = kayitBul(16,location);
    if(a == 2) printf("Ogrenci bulunamadi");
    free(location);
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

    fclose(file);

    return 0;


}

int indexDosyasiOlustur()
{



    FILE *file = fopen("students.bin","rb");


    if (file == NULL)  return 1;

    char tmp[20]; // Linked list de gelebilir
    int counter = 0;
    while (!feof(file))
    {
        fscanf(file,"%s",tmp); // Dosyanın ne kadar büyük olduğunu tespit etmek için bir okuma yapıyoruz
        counter++;
    }

    rewind(file);


    kayit data[counter]; // Dosya büyüklüğünün 1 eksiği 0 da dahil olarak bizim eleman sayımız

    counter = 0;
    int konum;
    while (!feof(file))
    {
        konum = ftell(file);
        data[counter].konum = ftell(file);// burada bir hata var geçici bir çözüm olarak ek değişken kullandık
        fscanf(file,"%d)%d)%d",&data[counter].ogrNo,&data[counter].dersKodu,&data[counter].puan); // Dosyadaki kısımları okuyoruz ancak bütün bilgileri okumak gereksiz burası düzenleencek
        counter++;
    }

    fclose(file);

    int swap[4];

    for(int i=0;i<counter;i++) // Sıralama algoritmamız
    {
        for(int j=i;j<counter;j++)
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

    for(int i=0;i<counter;i++)
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

int indeksDosyasiniSil(){

    int secim;

    printf("Index dosyasini silmek istediginize emin misiniz?(Bu islem geri alinamaz!!!)\n");
    printf("Seciminiz evet ise 1, Hayir ise 0 yaziniz.");
    scanf("%d",&secim);

    if (secim == 1)
        {
        if (remove("index.txt") == 0)
        {
            printf("Dosya basarili bir sekilde silindi");
        }
        else
        {
            printf("Dosya silinemedi");
        }
        }
    else if(secim == 0)
        {
        return 0;
        }
    }


int veriDosyasiniGoster()
{
    FILE *file = fopen("students.bin","rb");

    if(file == NULL) return 1;

    kayit student;

    while (!feof(file))
    {
        fscanf(file,"%d)%d)%d",&student.ogrNo,&student.dersKodu,&student.puan);
        printf("Ogrenci No: %d Ders Kodu: %d Puanı: %d\n",student.ogrNo,student.dersKodu,student.puan);
    }

    fclose(file);

    return 0;


}

int kayitBul(int number, int *location)
{
    FILE *file = fopen("index.txt","r");
    if(file == NULL) return 1;

    char tmp[20];

    int caunter = 0;

    while (!feof(file))
    {
        fscanf(file,"%s",tmp);
        caunter++;
    }

    rewind(file);

    int data[caunter-1][2];
    caunter = 0;

    while (!feof(file))
    {
        fscanf(file,"%d)%d",&data[caunter][0],&data[caunter][1]);
        caunter++;
    }

    fclose(file);

    int min = 0;
    int max = caunter-2; //boşluğu da okuduğu için 2 çıkartıyoruz
    int mid = max/2;

    int *p = &data[0][0];

    //int *location = malloc(sizeof(int)*2); // fonksiyon içindeki değerler belirsiz olduğu için static terimini kabul etmedi bu yola gittik
    //silinmemesi için erken tanımlıyoruz
    while(1)
    {
        mid = min + ((max -min) /2);

        if(data[mid][0] == number)
        {
            

            find_neighbor(&data[0][0],mid,location);

            /*
            printf("\n%d\n",location[0]);
            printf("%d\n",location[1]);
            return 0;*/ // Return ifadesi hatalı
            break;
            
        }
        else if(data[mid][0] < number)
        {
            min = mid +1;
        }
        else
        {
            max = mid -1;
        }

        if(max-min<0)
        {
            return 2; //Hata kontrolü yapılmalı
        }
    }
    
    FILE *file2 = fopen("students.bin","rb");

    if(file2 == NULL) return 1;
    
    kayit students;

    for(int i = location[0]; i<=location[1];i++)
    {
        fseek(file2,data[i][1],SEEK_SET);
        fscanf(file2,"%d)%d)%d",&students.ogrNo,&students.dersKodu,&students.puan);
        printf("Ogrenci no: %d Ders no: %d Puan: %d \n \n",students.ogrNo,students.dersKodu,students.puan);
    }
    

}

int* find_neighbor(int *data, int index, int *location)
{
    int min=index, max=index;
    
    int caunter = 0;
    while (1)
    {
        if(*(data+(max*2)+2) == *(data+(index*2)))
        {
            max++;
            //printf("%d\n",*(data+max));
        }
        else break;
    }

    while (1)
    {
        if(*(data+(min*2)-2) ==  *(data+(index*2)))
        {
            min--;
            //printf("%d\n",*(data+min));
        }
        else break;
    }
    
    location[0] = min;
    location[1] = max;

    //if(min == max) return min;
    //return (&spacing);
    

   
}
