#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#define AN 15
#define AC 4
COORD cord= {0,0}; // this is global variable
void gotoa(int a,int b)
{
    cord.X=a;
    cord.Y=b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cord);
}
/*declaration of checking functions*/
void c_code(char[]);
int check(char[]);

/*structure declaration*/
typedef struct
{
    char name[AN],code[AC];
    float rate;
    int quantity;
} rec;
rec item;

/*declaration of display functions*/
void Curser(int);
void dbill();
void d_mainmenu();
void display(rec *,int,int);
void window(int,int,int,int);
void dis_con();
void d_search();
void highlight(int,int);

/*declaration of main menu functions*/
void bill() ;
void edit();
void add();
void del();
void exit();

/*declaration of display submenu functions*/
void d_code();
void d_rate();
void d_quan();
void d_all();

/*start of main*/
int main()
{
    d_mainmenu();
    return 0;
}

void d_mainmenu()
{
    int i;
    char ch;
    const char *menu[]= {"   calculate bill","   add goods","   edit goods","   display all ","   search", "   delete goods","   exit"};
    system("cls");
    window(25,50,20,32);
    gotoa(33,18);
    printf("MAIN MENU");
    for (i=0; i<=6; i++)
    {
        gotoa(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    curser(7);
}

void d_search()
{
    char ch;
    int i;
    const char *menu[]= {"   By Code","   By Rate","   By Quantity","   Back to main menu"};
    system("cls");
    window(25,50,20,32);
    gotoa(33,18);
    printf("SEARCH MENU");
    for (i=0; i<=3; i++)
    {
        gotoa(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    curser(4);
}

/*function for cursor movement*/
void curser(int no)
{
    int count=1;
    char ch='0';
    gotoa(30,23);
    while(1)
    {
        switch(ch)
        {
        case 80:
            count++;
            if (count==no+1) count=1;
            break;
        case 72:
            count--;
            if(count==0) count=no;
            break;
        }
        highlight(no,count);
        ch=getch();
        if(ch=='\r')
        {
            if(no==7)
            {
                if (count==1) bill() ;
                else if(count==2) add();
                else if(count==3) edit();
                else if (count==4) d_all();
                else if (count==5) d_search();
                else if (count==6) del();
                else   exit(0);
            }
            if(no==4)
            {
                if (count==1) d_code();
                else if (count==2)d_rate();
                else if (count==3) d_quan();
                else d_mainmenu();
            }
        }
    }
}

void highlight(int no,int count)
{
    if (no==4)
    {
        //textbackground(11);
        //textcolor(0);
        gotoa(30,23);
        printf("   By Code          ");
        gotoa(30,24);
        printf("   By Rate          ");
        gotoa(30,25);
        printf("   By Quantity      ");
        gotoa(30,26);
        printf("   Back to main menu");
        //textcolor(0);
        //textbackground(2);
        switch (count)
        {
        case 1:
            gotoa(30,23);
            printf(" - By Code          ");
            break;
        case 2:
            gotoa(30,24);
            printf(" - By Rate          ");
            break;
        case 3:
            gotoa(30,25);
            printf(" - By Quantity      ");
            break;
        case 4:
            gotoa(30,26);
            printf(" - Back to main menu");
            break;
        }
    }

    if(no==7)
    {
        
        gotoa (30,23);
        printf("   Calculate Bill ");
        gotoa (30,24);
        printf("   Add Goods      ");
        gotoa (30,25);
        printf("   Edit Goods     ");
        gotoa (30,26);
        printf("   Display All    ");
        gotoa (30,27);
        printf("   Search         ");
        gotoa (30,28);
        printf("   Delete Goods   ");
        gotoa (30,29);
        printf("   Exit           ");
        
        switch(count)
        {
        case 1:
            gotoa (30,23);
            printf(" - Calculate Bill ");
            break;
        case 2:
            gotoa (30,24);
            printf(" - Add Goods      ");
            break;
        case 3:
            gotoa (30,25);
            printf(" - Edit Goods     ");
            break;
        case 4:
            gotoa (30,26);
            printf(" - Display All    ");
            break;
        case 5:
            gotoa (30,27);
            printf(" - Search         ");
            break;
        case 6:
            gotoa (30,28);
            printf(" - Delete Goods   ");
            break;
        case 7:
            gotoa (30,29);
            printf(" - Exit           ");
            break;
        }
    }
}

void bill()
{
    char x[4]= {0};
    int j=29,q=0,size=0,i=1;
    float total=0,gtotal=0;
    FILE *file;
    file=fopen("record.txt","r+b");
    rewind(file);
    system("cls");
    dbill();
    gotoa(26,15);
    printf("enter  \"end\" to finish input");
    while(1)
    {
        gotoa(25,18);
        printf("                    ");
        gotoa(25,19);
        printf("                    ");
        gotoa(25,18);
        printf("enter item code:");
        scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
        gotoa(25,19);
        printf("enter quantity:");
        scanf("%d",&q);
        rewind(file);
        while(fread(&item,sizeof(item),1,file))
        {
            if((strcmp(item.code,x)==0))
            {
                total=item.rate*q;
                gotoa(11,j);
                printf("%4d",i);
                printf("%9s",item.name);
                printf("%13d",q);
                printf("%15.2f",item.rate);
                printf("%13.2f",total);
                gtotal=gtotal+total;
                size=sizeof(item);
                item.quantity=item.quantity-q;
                j+=2;
                i++;
                fseek(file,-size,SEEK_CUR);
                fwrite(&item,sizeof(item),1,file);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        gotoa(30,j+5);
        printf("TOTAL AMOUNT = NRs. %6.2f",gtotal);
    }
    fclose(file);
    getch();
    d_mainmenu();
}
/*function to display bill window*/
void dbill()
{
    int i;
    gotoa(20,10);
//;
    for (i=1; i<=10; i++)
        printf("*");
    printf(" * FASHION WEAR * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoa(30,11);
    printf("Departmental Store");
//textcolor(1);
    gotoa(32,25);
    printf("CUSTOMER'S BILL") ;
//textcolor(8);
    gotoa(13,27);
    printf("SN.   Item Name     Quantity     Rate          Total");

}
/*function to add records*/
void add ()
{
    FILE *file;
    char y[AC],x[12];
    system("cls");
//textbackground(11);
//textcolor(0);
    gotoa(25,25);
    printf("Enter new record(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","ab");
        c_code(y);
        strcpy(item.code,y);
        gotoa(22,28);
        printf("Enter rate of the item:");
        scanf("%f",&item.rate);
        gotoa(22,30);
        printf("Enter quantity of the item:");
        scanf("%d",&item.quantity);
        gotoa(22,32);
        printf("Enter name of the item:");
        scanf("%s",item.name);
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);
        gotoa(22,34);
        printf("Enter new record(Y/N)?");

    }
    d_mainmenu();
}

/*function to check availability of code*/
void c_code(char y[])
{
    int flag;
    FILE *file;
    file=fopen("record.txt","rb");
    while(1)
    {
        system("cls");
        window(20,58,23,36);
        gotoa(32,18);
        printf(" ADD Goods ")  ;
        flag=1;
        rewind(file);
        gotoa(22,25);
        printf("Enter new code of the Good:");
        scanf(" %[^\n]",y);
        while(fread(&item,sizeof(item),1,file)==1)
        {
            if (strcmp(y,item.code)==0)
            {
                flag=0;
                gotoa(26,30);
                printf("code already exists");
                gotoa(29,32);
                printf("enter again");
                getch();
                break;
            }
        }
        if (flag==1)
            break;
    }
}

/*function for editing*/
void edit()
{
    int flag=0,choice;
    char x[AC],y[AC];
    FILE *file;
    int size;
    system("cls");
//textcolor(0);
//textbackground(11);
    window(20,63,20,46);
    gotoa(35,18);
    printf("EDIT RECORDS");
    ;
    gotoa(25,23);
    printf("enter item code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file=fopen("record.txt","r+b");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {
                //textcolor(0);
                gotoa(25,27);
                printf("name       = %s",item.name);
                gotoa(25,28);
                printf("code       = %s",item.code);
                gotoa(25,29);
                printf("rate       = %g",item.rate);
                gotoa(25,30);
                printf("quantity   = %d",item.quantity);
                gotoa(25,32);;
                printf("Do you want to edit this record?(y/n):");
                fflush(file);
                if(toupper(getche())=='Y')
                {
                    //textcolor(0);
                    gotoa(25,34);
                    printf("1- edit name ");
                    gotoa(25,35);
                    printf("2- edit code ");
                    gotoa(25,36);
                    printf("3- edit rate ");
                    gotoa(25,37);
                    printf("4- edit quantity ");
                    gotoa(25,39);  ;
                    printf(" enter your choice(1, 2, 3, 4) ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    case 1:
                        system("cls");
                        window(23,48,20,40);
                        gotoa(35,18);
                        printf("EDIT RECORDS");
                        gotoa(25,24);
                        printf(" enter new name: ");
                        scanf("%s",item.name);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 2:
                        system("cls");
                        window(23,65,20,40);
                        gotoa(35,18);
                        printf("EDIT RECORDS");
                        gotoa(25,24);
                        c_code(y);
                        strcpy(item.code,y);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 3:
                        system("cls");
                        window(23,65,20,40);
                        gotoa(35,18);
                        printf("EDIT RECORDS");
                        gotoa(25,24);
                        printf(" enter new rate: ");
                        scanf("%f",&item.rate);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 4:
                        system("cls");
                        window(23,65,20,40);
                        gotoa(35,18);
                        printf("EDIT RECORDS");
                        gotoa(25,24);
                        printf(" enter new quantity: ");
                        scanf("%d",&item.quantity);
                        size=sizeof(item);
                        fseek(file,-size,1);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    }
                    gotoa(27,30);
                    printf("--- item edited---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        gotoa(32,30);
        printf("Item does not exist.");
        gotoa(36,32);
        printf("TRY AGAIN");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

/*function to display all records*/
void d_all()
{
    int i,j=1;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        display(&item,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            gotoa(27,47);/*textcolor(0)*/;
            printf("Press any key to see more...");
            getch();
            system("cls");
            dis_con();
            i=26;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        gotoa(24,30);
        printf("-- no Goods found --");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

/*function to display by quantity*/
void d_quan()
{
    int i,j=1;
    int a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    gotoa(16,20);;
    printf("Enter lower range: ");
    scanf("%d",&a);
    gotoa(16,21);
    printf("Enter upper range:");
    scanf("%d",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.quantity>=a)&&(item.quantity<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoa(27,47);
                printf("Press any key to see more...");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoa(28,30);
        printf(" No items found.");
    }
    getch();
    d_search();
    fclose(file);
}

/*function to display by rate*/
void d_rate()
{
    int i,j=1;
    float a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    gotoa(16,20);;
    printf("enter lower range: ");
    scanf("%f",&a);
    gotoa(16,21);
    printf("enter upper range: ");
    scanf("%f",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.rate>=a)&&(item.rate<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoa(27,47);
                printf("press any key to see more...");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoa(28,30);
        printf(" no item found ");
    }
    getch();
    fclose(file);
    d_search();
}

/*function to display by code*/
void d_code()
{
    int i,j=1;
    char x[4]= {0};
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    gotoa(16,20);;
    printf("enter item code: ");
    scanf("%s",x);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((strcmp(item.code,x)==0))
        {
            display(&item,i,j);
            i++;
            j++;
            break;
        }
    }
    if (i==26)
    {
        gotoa(28,30);
        printf("no item found");
    }
    getch();
    fclose(file);
    d_search();
}

/*function to display window for item display*/
void dis_con()
{
    int i;
    system("cls");
    gotoa(20,10);
    ;
    for (i=1; i<=10; i++)
        printf("*");
    printf(" * FASHION WEAR * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoa(30,11);
    printf("Departmental Store");
//textcolor(1);
    gotoa(32,17);
    printf("RECORDS") ;
//textcolor(8);
    gotoa(18,23);
    printf ("SN   Item Name   Item Code      Rate     Quantity");
}

/*function to display in screen*/
void display(rec *item,int i,int j)
{
    gotoa(16,i);//textcolor(13);
    printf("%4d",j);
    printf("%9s",item->name);
    printf("%12s",item->code);
    printf("%14.2f",item->rate);
    printf("%11d",item->quantity);
}

/*function to delete records*/
void del()
{
    int flag;
    char x[AN];
    FILE *file,*file1;
    system("cls");
    window(23,51,25,34);
    gotoa(29,18);
    printf("DELETE Goods");
    gotoa(27,27);
    printf("enter item code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","ab");
        file=fopen("record.txt","rb");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }
        gotoa(27,29);
        printf("---item deleted---");
        remove("record.txt");
        rename("record1.txt","record.txt");
    }
    if (flag==1)
    {
        gotoa(25,29);
        printf("---item does not exist---");
        gotoa(30,31);
        printf("TRY AGAIN");
    }
    fclose(file1);
    fclose(file);
    getch();
    d_mainmenu();
}

/*function to check validity of code while editing and deleting*/
int check(char x[AN])
{
    FILE *file;
    int flag=1;
    file=fopen("record.txt","rb");
    rewind(file);
    while (fread(&item,sizeof (item),1,file))
    {
        if(strcmp(item.code,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(file);
    return flag;
}

/*function to display box*/
void window(int a,int b,int c,int d)
{
    int i;
    system("cls");
    gotoa(20,10);
//textcolor(1);
    for (i=1; i<=10; i++)
        printf("*");
    printf(" * RR FASSIONS * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoa(30,11);
    printf("Departmental Store");
//textcolor(4);
    for (i=a; i<=b; i++)
    {
        gotoa(i,17);
        printf("\xcd");
        gotoa(i,19);
        printf("\xcd");
        gotoa(i,c);
        printf("\xcd");
        gotoa(i,d);
        printf("\xcd");
    }

    gotoa(a,17);
    printf("\xc9");
    gotoa(a,18);
    printf("\xba");
    gotoa(a,19);
    printf("\xc8");
    gotoa(b,17);
    printf("\xbb");
    gotoa(b,18);
    printf("\xba");
    gotoa(b,19);
    printf("\xbc");
//textcolor(4);
    for(i=c; i<=d; i++)
    {
        gotoa(a,i);
        printf("\xba");
        gotoa(b,i);
        printf("\xba");
    }
    gotoa(a,c);
    printf("\xc9");
    gotoa(a,d);
    printf("\xc8");
    gotoa(b,c);
    printf("\xbb");
    gotoa(b,d);
    printf("\xbc");
//textbackground(11);
//textcolor(0);
}