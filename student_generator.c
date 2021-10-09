#include <stdio.h>
#include <time.h>


int main(void)
{
    FILE *file = fopen("students.bin","w");
    srand(time(NULL));

    for(int i=0;i<25;i++)
    {
        int num = rand()%31;
        int lesson = rand()%11;
        int point = rand()%101;

        fprintf(file,"%d)%d)%d\n",num,lesson,point);
    }


}