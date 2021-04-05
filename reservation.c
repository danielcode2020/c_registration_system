#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <sys/types.h>
#include <unistd.h>

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

char * remove_spaces(char *str)
{
  char *out = str, *put = str;

  for(; *str != '\0'; ++str)
  {
    if((*str != ' '))
      *put++ = *str;
  }
  *put = '\0';

  return out;
}


int stringCompare(char mj1[], char mj2[])  // function definition
{
    int i = 0, flag = 0;
    while(mj1[i] != '\0' && mj2[i] != '\0'  ) // until atleast one string ends
    {
        /*
            Even if they differ by a single character,
            don't iterate further
        */
        if(mj1[i] != mj2[i])
        {
            flag = 1;
            break;
        }
        i++;
    }

    /*
        If all the characters are sequentially same as well as
        both strings have ended
    */
    if(flag == 0 && mj1[i] == '\0' && mj2[i] == '\0')
        return 1;
    else
        return 0;
}

cursor(bool showFlag) // function to show or hide the cursor in console
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


void wait(int seconds) // time delay
{
    #ifdef _WIN32
         Sleep(1000 * seconds );
    #else
         sleep(seconds);
    #endif // _WIN32
}

int my_atoi(char *str) // conversion of string to int
{
  int result;
  int puiss;

  result = 0;
  puiss = 1;
  while (('-' == (*str)) || ((*str) == '+'))
  {
      if (*str == '-')
        puiss = puiss * -1;
      str++;
  }
  while ((*str >= '0') && (*str <= '9'))
  {
      result = (result * 10) + ((*str) - '0');
      str++;
  }
  return (result * puiss);
}


void init()
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char text[50];

    strftime(text, sizeof(text)-1, "%#d%#m%#d", t);

    int text_int, line_int;

    FILE *f,*ft;
    char s[1000];
    int ch=0;
    char s2[10];


    f = fopen("E:\\reservations.txt", "a+");
    if (f == NULL)
    {
        printf("Can not open the file. \n");
    }

    text_int = my_atoi(text);

    int k = 0;
    ft = fopen("E:\\temp.txt", "w");
    while(fgets(s,1000,f) != NULL)
    {
        k++;
        strcpy(s2,s);
        strcpy(s2,remove_spaces(s2));

        line_int = my_atoi(s2);
        if(line_int<999){
            line_int=line_int*10;
        }
        if (text_int<999){
            text_int = text_int*10;
        }
        if(line_int<9999){
            line_int=line_int*10;
        }
        if (text_int<9999){
            text_int = text_int*10;
        }
        if (line_int>text_int)
        {
            fprintf(ft,strcat(s,"\n"));
        }

    }

    fclose(f);
    fclose(ft);
    remove("E:\\reservations.txt");
    rename("E:\\temp.txt","E:\\reservations.txt");
    loading();

}

void loading()
{
    cursor(false);
    system("cls");
    printf("Loading .");
    wait(1);
    printf("\rLoading ..");
    wait(1);
    printf("\rLoading ...");
    wait(1);
    system("cls");
    printf("\rLoading .");
    wait(1);
    printf("\rLoading ..");
    wait(1);
    printf("\rLoading ...");
    wait(1);
    system("cls");
    cursor(true);
}
void menu_principal()
{
    system("cls");
    printf(" 1.(s) Check for registration on a specific date  \n");
    printf(" 2.(d) Check for free dates to register on this day \n");
    printf(" 3.(w) Check for free dates to register on next 10 days \n");
    printf(" 4.(v) View the database \n");
    printf(" 5.(q) Exit \n");


}

void back_to_menu()
{
    char c;
    printf("\n________________________________________________________________________________________");

    printf("\npress 'm' for main menu \n");

    do{
    c = getch();

     }while ((c!='m'));

    menu_principal();
}
void check_menu()
{
     char text[100], m[10], d[10], h[10];

     time_t now = time(NULL);
     struct tm *t = localtime(&now);

     strftime(text, sizeof(text)-1, "%d %m %H", t); // current time

     bool b;
     b= true;

     while (b == true)
     {
        printf("Enter the month (1-12) : \n");
        gets(m);
        strcat(m," ");
        int k = my_atoi(m);
        if (k>0 && k<=12)
        {
            b = false;
        }
        else
        {
            error();
        }
     }
     b = true;

     while (b==true)
     {
        printf("Enter the day (1-31) : \n");
        gets(d);
        strcat(d," ");
        int k = my_atoi(d);
        if (k>0 && k<=31)
        {
            b = false;
        }
        else
        {
            error();
        }
     }
     b = true;
     while (b == true)
     {
        printf("Enter the hour (8-16) : \n");
        gets(h);
        int k = my_atoi(h);
        if (k>=8 && k<=16)
        {
            b = false;
        }
        else
        {
            error();
        }
     }

     char real_date[100]="";

     strcat(real_date, m);
     strcat(real_date, d);
     strcat(real_date, h);
     // date format in file is MM DD HH

     check(real_date);
}



void error()
{
    printf("Input not valid  \n");
}




void view_base()
{
    system("cls");
    FILE *f;
    char s[1000],m[10];
    m[10]="month";
    f = fopen("E:\\reservations.txt", "a+");
    if (f == NULL)
    {
        printf("Can not open the file. \n");
    }
    printf("Already reserved : \n");

    while(fgets(s,1000,f) != NULL)
        {
            char str[25]=" ";
            strcpy(str,s);
            int init_size = strlen(str);
            char delim[] = " ";
            char source[25]=" ";
            int k=0;

            char *ptr = strtok(str, delim);

            while(ptr != NULL)
            {
                k++;

                if (k==1)
                {
                    strcat(source,"month ");
                }
                if (k==2)
                {
                    strcat(source," day ");
                }
                if (k==3)
                {
                    strcat(source," hour ");
                }
                strcat(source,ptr);

                ptr = strtok(NULL, delim);
            }

            puts(source);
        }
    fclose(f);
    back_to_menu();
}



void check(char c[1000]) // check in file for  dates
{
    FILE *f;
    char s[1000];
    int ch=0;
    char s1[10], s2[10];

    f = fopen("E:\\reservations.txt", "a+");
    if (f == NULL)
    {
        printf("Can not open the file. \n");
    }
    strcpy(s1,c);
    strcpy(s1,remove_spaces(s1));
    int s1_i = 0;
    s1_i = my_atoi(s1);
    while(fgets(s,1000,f) != NULL)
    {
        strcpy(s2,remove_spaces(s));
        int s2_i = 0;
        s2_i = my_atoi(s2);

        if (s1_i==s2_i)
        {
            ch++;
            break;
        }
    }

    if (ch!=0)
    {
        printf("This date is occupied \n");
        wait(5);
    }
    else
    {
        printf("This date is free! Register ? (y/n) \n");

        char a = getch();
        if (a=='y')
        {
            fprintf(f,strcat(c,"\n"));
            fclose(f);
            puts("Recorded ! ");
            wait(5);
        }


    }


}

void check_today()
{
    system("cls");
    printf("Free hours : \n");
    check_hour("8");
    check_hour("9");
    check_hour("10");
    check_hour("11");
    check_hour("12");
    check_hour("13");
    check_hour("14");
    check_hour("15");
    check_hour("16");
    back_to_menu();
}

void check_10days()
{
    system("cls");
    printf("Free hours : \n");

    time_t now = time(NULL);
    char text[15];
    struct tm *t = localtime(&now);

    strftime(text, sizeof(text)-1, "%#d", t);

    int d = my_atoi(text);

    int n=0;
    while (n<=10)
    {
    if (d>31)
    {
        char b[10];
        sprintf(b, "%d", d);

        d= d % 10;
        for (int j = 8; j<17;j++)
        {
            char h[10];
            sprintf(h,"%d",j);
            check_day_hour(b,h);
        }
        d++;

    }
    else
    {
        char b[10];
        sprintf(b, "%d", d);
        for (int j = 8; j<17;j++)
        {
            char h[10];
            sprintf(h,"%d",j);
            check_day_hour(b,h);
        }
        d++;

    }
    n++;
    }
    back_to_menu();
}

int check_hour(char n[])
{
    FILE *f;
    char s[1000];


    f = fopen("E:\\reservations.txt", "a+");
    if (f == NULL)
    {
        printf("Can not open the file. \n");
    }
    char text[100];

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(text, sizeof(text)-1, "%#m %#d ", t);

    strcat(text,n);
    strcpy(text,remove_spaces(text));

    int k=0, c1=0, c2=0;

    c1=my_atoi(text);
    while(fgets(s,1000,f) != NULL)
    {
        for (int h = 0; h<strlen(s);h++)
        {
            if (s[h]=='\n')
            {
                s[h]=" ";
            }
        }

        strcpy(s,remove_spaces(s));

        c2 = my_atoi(s);

        if(c1==c2)
        {
            k++;

        }

    }
    if (k==0)
    {
        puts(n);

    }
    fclose(f);
}

int check_day_hour(char d[],char n[])  //d day, n hour
{
    FILE *f;
    char s[1000];


    f = fopen("E:\\reservations.txt", "a+");
    if (f == NULL)
    {
        printf("Can not open the file. \n");
    }
    char text[100];

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(text, sizeof(text)-1, "%#m", t);
    strcat(text,d);
    strcat(text,n);
    strcpy(text,remove_spaces(text));

    int k=0, c1=0, c2=0;

    c1=my_atoi(text);
    while(fgets(s,1000,f) != NULL)
    {
        for (int h = 0; h<strlen(s);h++)
        {
            if (s[h]=='\n')
            {
                s[h]=" ";
            }
        }

        strcpy(s,remove_spaces(s));

        c2 = my_atoi(s);

        if(c1==c2)
        {
            k++;

        }

    }
    if (k==0)
    {
        printf("day %s hour %s \n",d,n );

    }
    fclose(f);
}



int main()
{
    int k=0;
    bool b =true;
    while (b)
    {
        if (k==0){
            init();
            }
        k++;
        menu_principal();

        char a = getch();

        switch (a)
        {
        case('s'):
            {
                check_menu();
                break;
            }
        case('d'):
            {
                check_today();
                break;
            }
        case('w'):
            {
                check_10days();
                break;
            }
        case ('v'):
            {
                view_base();
                break;
            }
        case ('q'):
            {
                exit(0);
            }


        }
    }
}

