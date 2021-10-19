#include <stdio.h>
#include <stdlib.h>

int indexDosyasiOlustur();

int indexDosyasiniGoster();

int kayitEkle();

int indeksDosyasiniSil();

int veriDosyasiniGoster();

int kayitBul(int number,int *location);

int* find_neighbor(int *data, int index,int *location);

int kayitGuncelle(int s_number);

int kayitSil(int s_number);

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
    /*
    int *location = malloc(sizeof(int)*2);
    if(kayitBul(4,location) == 2) printf("Ogrenci bulunamadi");
    free(location);

    int s_number;
    printf("Kaydi silinecek ogrencinin numarasını giriniz: ");
    scanf("%d",&s_number);
    kayitSil(s_number);
    */
    kayitGuncelle(13);

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
        
        data[counter].konum = ftell(file);

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
    fseek(fp, 0, SEEK_END);
    fprintf(fp,"\n%d)%d)%d",student.ogrNo,student.dersKodu,student.puan); //Dosyamizin sonuna kullan�c� tarafindan girilen bilgileri yazdik
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

    int counter = 0;

    while (!feof(file))
    {
        fscanf(file,"%s",tmp);
        counter++;
    } // Bu kısma kadar dosyadaki satır sayısın tespit ediyoruz

    rewind(file);

    int data[counter-1][2];
    counter = 0;

    while (!feof(file))
    {
        fscanf(file,"%d)%d",&data[counter][0],&data[counter][1]);
        counter++;
    }//index okunuyor

    fclose(file);

    //Binary search için kullanılacak değişkenler tanımlandı
    int min = 0;
    int max = counter-2; //boşluğu da okuduğu için 2 çıkartıyoruz
    int mid = max/2;

    


    while(1)
    {
        mid = min + ((max -min) /2); // Arama aralığını güncelliyoruz

        if(data[mid][0] == number)
        {

            find_neighbor(&data[0][0],mid,location); //Olası komşuları arayan fonksiyon

            break;

        }
        else if(data[mid][0] < number)
        {
            min = mid +1; // Bulamama durumunda aralık güncellemesi yapıyoruz
        }
        else
        {
            max = mid -1; // Bulamama durumunda aralık güncellemesi yapıyoruz
        }

        if(max-min<0)
        {
            return 2; //Hata kontrolü yapılmalı
        }
    }

    FILE *file2 = fopen("students.bin","rb");

    if(file2 == NULL) return 2;

    kayit students;

    for(int i = location[0]; i<=location[1];i++)//Bulunanları yazdırıyoruz
    {
        fseek(file2,data[i][1],SEEK_SET);
        fscanf(file2,"%d)%d)%d",&students.ogrNo,&students.dersKodu,&students.puan);
        printf("%d) Ogrenci no: %d Ders no: %d Puan: %d \n \n",i -location[0]  + 1,students.ogrNo,students.dersKodu,students.puan);
    }

    fclose(file2);



}

int* find_neighbor(int *data, int index, int *location)
{
    int min=index, max=index;

    int counter = 0;
    while (1)
    {
        if(*(data+(max*2)+2) == *(data+(index*2))) //Düz işaretçi aritmetiği bir sonraki indexi kontrol ediyor
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

    location[0] = min; //Komşu varsa bunların bitiş ve başlangıç aralığını tespit ettik
    location[1] = max;





}

int kayitSil(int s_number)

{

    FILE *file = fopen("index.txt","r");
    if(file == NULL) return 1;

    char tmp[20];

    int counter = 0;

    while (!feof(file))
    {
        fscanf(file,"%s",tmp);
        counter++;
    } // Bu kısma kadar dosyadaki satır sayısın tespit ediyoruz

    rewind(file);

    int data[counter-1][2];
    counter = 0;

    while (!feof(file))
    {
        fscanf(file,"%d)%d",&data[counter][0],&data[counter][1]);
        counter++;
    }//index okunuyor

    fclose(file);




    int *location = malloc(sizeof(int)*2); // Kayitbul çalıştırılıyor
    int e = kayitBul(s_number,location);
    if(e == 2) printf("\nOgrenci bulunamadi\n");


    printf("Kacinci kaydin silinmesini istediginizi seciniz: ");
    scanf("%d",&s_number);

    if(!((location[0] + s_number - 1) <= location[1] && (location[0] + s_number - 1) >= location[0])) // Aralıkta olmalı
    {
        printf("Hatalı index seçimi");
        return 3;
    }



    FILE *file2 = fopen("students.bin","rb+");
    if(file2 == NULL) return 2;

    FILE *file3 = fopen("tmp.bin","wb+");


    fseek(file2,0,SEEK_END);
    int end = ftell(file2); // Dosyadaki toplam bayt sayısı bulunuyor
    rewind(file2);



    int *buffer = malloc(sizeof(int) * (int) (data[location[0]+s_number-1][1]+1));// Silinecek kısma kadar olan bayt sayısı büyüklüğünde alan açılıyor

    fread(buffer,(data[location[0]+s_number-1][1]+1),1,file2);// Silinecek kısma kadar okunuyor
    fwrite(buffer,(data[location[0]+s_number-1][1]),1,file3); //Okunan kısım yeni dosyaya yazılyor

    char c = 0;
    counter = 0;
    while( c != '\n' && c != EOF)//Silinecek kısım tek tek okunuyor böylece orası atlanmış oluyor
    {
        c=getc(file2);
        counter++;
    }

    if(c != EOF)//Son satırı silmek istersek ve bu if bloğu olmasa sonsuz döngüye girer
    {
        fputc('\n',file3);
        int *buffer2 = malloc(sizeof(int)*(end-(data[location[0]+s_number-1][1]))); // 2. kısım için alan ayrılıyor
        fread(buffer2,end-counter-(data[location[0]+s_number-1][1]+1),1,file2); //2. kısım okunuyor
        fwrite(buffer2,end-counter-(data[location[0]+s_number-1][1]+1),1,file3); //2. kısım yazılıyor

    }

    remove("students.bin");
    rename("tmp.bin","students.bin");
    fclose(file3);
    indexDosyasiOlustur();


}

int kayitGuncelle(int s_number)
{
   FILE *file = fopen("index.txt","r");
    if(file == NULL) return 1;

    char tmp[20];

    int counter = 0;

    while (!feof(file))
    {
        fscanf(file,"%s",tmp);
        counter++;
    } // Bu kısma kadar dosyadaki satır sayısın tespit ediyoruz

    rewind(file);

    int data[counter-1][2];
    counter = 0;

    while (!feof(file))
    {
        fscanf(file,"%d)%d",&data[counter][0],&data[counter][1]);
        counter++;
    }//index okunuyor

    fclose(file);

    int *location = malloc(sizeof(int)*2); // Kayitbul çalıştırılıyor
    int e = kayitBul(s_number,location);
    if(e == 2) printf("\nOgrenci bulunamadi\n");

    printf("Kacinci kaydin degistirilmesini istediginizi seciniz: ");
    scanf("%d",&s_number);

    if(!((location[0] + s_number - 1) <= location[1] && (location[0] + s_number - 1) >= location[0])) // Aralıkta olmalı
    {
        printf("Hatalı index seçimi");
        return 3;
    }

    int new_point;
    printf("Yeni puani giriniz: ");
    scanf("%d",&new_point);


    FILE *file2 = fopen("students.bin","rb+");
    if(file2 == NULL) return 2;



    fseek(file2,0,SEEK_END);
    int end = ftell(file2); // Dosyadaki toplam bayt sayısı bulunuyor
    rewind(file2);


    kayit student;
    fseek(file2,(data[location[0]+s_number-1][1]+1),SEEK_SET);
    fscanf(file2,"%d)%d)%d",&student.ogrNo,&student.dersKodu,&student.puan);


    int *buffer2 = malloc(sizeof(int)*(end-(data[location[0]+s_number-1][1]+1))); // 2. kısım için alan ayrılıyor
    fread(buffer2,end-(data[location[0]+s_number-1][1]+1),1,file2); //2. kısım okunuyor

    fseek(file2,(data[location[0]+s_number-1][1]+1),SEEK_SET);

    char c;
    counter = 0;
    while( c != '\n' && c != EOF)
    {
        c=getc(file);
        counter++;
    }

    fseek(file2,(data[location[0]+s_number-1][1]+1),SEEK_SET);

    fprintf(file2,"%d)%d)%d",student.ogrNo,student.dersKodu,new_point);
    if(c != EOF)
    {
        fwrite(buffer2,end-(data[location[0]+s_number-1][1])-counter-1,1,file2); //2. kısım yazılıyor, yazılan alanın boyutu ayarlanabilir
    }

    fclose(file2);


}
