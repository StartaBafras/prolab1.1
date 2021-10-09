#include <stdio.h>

int indexDosyasiOlustur();


typedef struct
{
    int ogrNo;
    int dersKodu;
    int puan;
    
}kayit;

int main(void)
{
    indexDosyasiOlustur();
}



int indexDosyasiOlustur()
{

    

    FILE *file = fopen("students.bin","rb");
    

    if (file == NULL)  return 1;

    char tmp[20]; // Linked list de gelebilir
    int caunter = 0;
    while (!feof(file))
    {
        fscanf(file,"%s",tmp);
        caunter++;
    }

    rewind(file);

    
    int data[caunter-1][4];
    
    caunter = 0;
    int konum;
    while (!feof(file))
    {   
        konum = ftell(file);
        data[caunter][3] = ftell(file);
        fscanf(file,"%d)%d)%d",&data[caunter][0],&data[caunter][1],&data[caunter][2]);
        caunter++;
    }
    
    fclose(file);

    int swap[4];

    for(int i=0;i<caunter-1;i++)
    {
        for(int j=i;j<caunter-1;j++)
        {
            if (data[i][0] > data[j][0])
            {
                swap[0] = data[i][0];
                swap[1] = data[i][1];
                swap[2] = data[i][2];
                swap[3] = data[i][3];

                data[i][0] = data[j][0];
                data[i][1] = data[j][1];
                data[i][2] = data[j][2];
                data[i][3] = data[j][3];

                data[j][0] = swap[0];
                data[j][1] = swap[1];
                data[j][2] = swap[2];
                data[j][3] = swap[3];

                j = i;
            }
        }
    }


    FILE *dosya = fopen("index.txt","w");
   
    
    if (file == NULL)  return 1;
    
    for(int i=0;i<caunter-1;i++)
    {
        fprintf(dosya,"%d)%d\n",data[i][0],data[i][3]);
    }
    
    
    return 0;
    

}
