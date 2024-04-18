#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILENAME "products.txt"
#define FILEDAT "products.dat"
#define SIZE 50


typedef struct
{
    int productid;
    char productname[20];
    int categoryid;
    char categoryname[20];
    int stock;
    float price;
    bool active;    
}Product;

void importxtobinary(Product info[])
{
    FILE *bfptr = fopen(FILEDAT,"wb");
    FILE *fptr = fopen(FILENAME,"r");

    if((bfptr && fptr) == NULL)
    {
        puts("ERROR");
    }
    else
    {
        char strstring[50][100];
        int i = 1;

        for(int j = 0;j < 30;j++)
        {
        fgets(strstring[j],99,fptr);   
        }
        
        for(int j = 0;j < 30;j++)
        {
        char *tokptr = strtok(strstring[j],",");
        
        while(i != 7)
        {
            switch(i)
            {
            case 1:
            sscanf(tokptr,"%d",&info[j].productid);
            info[j].active = true;
            break;

            case 2:
            strcpy(info[j].productname,tokptr);
            info[j].active = true;
            break;

            case 3:
            sscanf(tokptr,"%d",&info[j].categoryid);
            info[j].active = true;
            break;

            case 4:
            strcpy(info[j].categoryname,tokptr);
            info[j].active = true;
            break;

            case 5:
            sscanf(tokptr,"%d",&info[j].stock);
            info[j].active = true;
            break;

            case 6:
            info[j].price = strtof(tokptr,NULL);
            info[j].active = true;
            break;

            default:
            break;
            }
            tokptr = strtok(NULL,",");
            i++;
            if(i == 6)
            {
               tokptr[strlen(tokptr)-1] = '\0'; 
            }
        }
            i = 1;
        }

        fwrite(info,sizeof(Product),30,bfptr);

    }
    fclose(bfptr);
    fclose(fptr);
}

void addnewproduct(Product info[])
{
    FILE *bfptr = fopen(FILEDAT,"rb+");

    if(bfptr == NULL)
    {
        puts("File could not be opened");
    }
    else
    {
    int count1 = 0;
    fseek(bfptr,0,SEEK_END);
    count1 = (ftell(bfptr)/sizeof(Product));
    rewind(bfptr);
    fread(info,sizeof(Product),count1,bfptr);

        printf("Please enter product name:");
        fflush(stdin);
        fgets(info[count1].productname,19,stdin);
        info[count1].productname[strlen(info[count1].productname)-1] = '\0';
        printf("Please enter category name:");
        fflush(stdin);
        fgets(info[count1].categoryname,19,stdin);
        info[count1].categoryname[strlen(info[count1].categoryname)-1] = '\0';
        printf("Please enter categoryid stock and price:");
        scanf("%d %d %f",&info[count1].categoryid,&info[count1].stock,&info[count1].price);
        info[count1].active = true;
        info[count1].productid = 100+count1+1;
        rewind(bfptr);
        fwrite(info,sizeof(Product),count1+1,bfptr);
        count1++;
    }
    fclose(bfptr);
}

void listactiveproducts(Product info[])
{
    FILE *bfptr = fopen(FILEDAT,"rb");
    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    else
    {
    int countactive = 0;
    fseek(bfptr,0,SEEK_END);
    countactive = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countactive,bfptr);
    rewind(bfptr);
    for(int i = 0;i < countactive;i++)
    {
        if(info[i].active)
        {
            printf("%d %s %d %s %d %.2f\n",info[i].productid,info[i].productname,info[i].categoryid,info[i].categoryname,
            info[i].stock,info[i].price);
        }
    }
    }
    fclose(bfptr);
}

void listinactiveproducts(Product info[])
{
    FILE *bfptr = fopen(FILEDAT,"rb");
    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    else
    {
    int countinactive = 0;
    fseek(bfptr,0,SEEK_END);
    countinactive = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countinactive,bfptr);
    rewind(bfptr);

    for(int i = 0;i < countinactive;i++)
    {
        if(!(info[i].active))
        {
            printf("%d %s %d %s %d %.2f\n",info[i].productid,info[i].productname,info[i].categoryid,info[i].categoryname,
            info[i].stock,info[i].price);
        }
    }
  }
  fclose(bfptr);
}

void findproductbyid(Product info[],int id)
{
    FILE *bfptr = fopen(FILEDAT,"rb");
    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    
    else
    {
    int countfind = 0;
    fseek(bfptr,0,SEEK_END);
    countfind = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countfind,bfptr);
    for(int i = 0;i < countfind;i++)
    {
        if(info[i].productid == id)
        {
            printf("%d %s %d %s %d %.2f\n",info[i].productid,info[i].productname,info[i].categoryid,info[i].categoryname,
            info[i].stock,info[i].price);
        }
    }
    }
    fclose(bfptr);
}

void updateproductbyid(Product info[],int id)
{
    FILE *bfptr = fopen(FILEDAT,"rb+");
    
    if(bfptr == NULL)
    {
        puts("Unable to resume process");
    }
    else
    {
    int countupdate = 0;
    fseek(bfptr,0,SEEK_END);
    countupdate = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countupdate,bfptr);
    int storeid = 0;
    int choice = 0;

    for(int i = 0;i <= countupdate;i++)
    {
        if(info[i].productid == id)
        {
            storeid = i;
        }
    }
    puts("Please choose which data you wish to update\n");
    tryagain:
    printf("1)Product name\n2)Category ID\n3)Category name\n4)Stock\n5)Price\n");
    scanf("%d",&choice);
    puts("Enter the new data:");

    switch (choice)
    {
    case 1:
    fflush(stdin);
    fgets(info[storeid].productname,18,stdin);
    info[storeid].productname[strlen(info[storeid].productname)-1] = '\0'; 
    rewind(bfptr);
    fwrite(info,sizeof(Product),countupdate,bfptr);  
    break;
    case 2:
    scanf("%d",&info[storeid].categoryid);  
    rewind(bfptr);
    fwrite(info,sizeof(Product),countupdate,bfptr);
    break;
    case 3:
    fflush(stdin);
    fgets(info[storeid].categoryname,18,stdin);
    info[storeid].categoryname[strlen(info[storeid].categoryname)-1] = '\0';
    rewind(bfptr); 
    fwrite(info,sizeof(Product),countupdate,bfptr);  
    break;
    case 4:
    scanf("%d",&info[storeid].stock);  
    rewind(bfptr);
    fwrite(info,sizeof(Product),countupdate,bfptr);  
    break;
    case 5:
    scanf("%f",&info[storeid].price); 
    rewind(bfptr);
    fwrite(info,sizeof(Product),countupdate,bfptr);  
    break;
    
    default:
    printf("Incorrect choice. Please try again ");
    goto tryagain;
    
    break;
    }
    }
    fclose(bfptr);
}

void changestatus(Product info[],int id)
{
    FILE *bfptr = fopen(FILEDAT,"rb+");
    
    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    else
    {
    int countchange = 0;
    fseek(bfptr,0,SEEK_END);
    countchange = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countchange,bfptr);
    rewind(bfptr);
        for(int i = 0;i <= countchange;i++)
        {
        if(info[i].productid == id)
        {
            if(info[i].active)
            {
            info[i].active = false;
            fwrite(info,sizeof(Product),countchange,bfptr);
            }
            else if(!info[i].active)
            {
                info[i].active = true;
                fwrite(info,sizeof(Product),countchange,bfptr);
            }
        }
        }
    }
    fclose(bfptr);
}

void updatestock(Product info[],int id,int choice)
{
    FILE *bfptr = fopen(FILEDAT,"rb+");

    int stockvalue = 0;

    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    else
    {
    int countstock = 0;
    fseek(bfptr,0,SEEK_END);
    countstock = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countstock,bfptr);
    rewind(bfptr);
        for(int i = 0;i <= countstock;i++)
        {
        if(info[i].productid == id && choice == 7)
        {
            puts("Enter the amount you wish to sell:");
            scanf("%d",&stockvalue);
            info[i].stock -= stockvalue;
            if(info[i].stock < 0)
            {
                puts("There is not enough products to sell,all the products at hand will be sold.");
                info[i].stock = 0;
            }
            fwrite(info,sizeof(Product),countstock,bfptr);
        }
        else if(info[i].productid == id && choice == 8)
        {
            puts("Enter the amount you wish to restock:");
            scanf("%d",&stockvalue);
            info[i].stock += stockvalue;
            fwrite(info,sizeof(Product),countstock,bfptr);
        }
        }
    }
    fclose(bfptr);
}

void updatepricesbycategory(Product info[])
{
    FILE *bfptr = fopen(FILEDAT,"rb+");

    int categoryid;

    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    else
    {
    int countprice = 0;
    fseek(bfptr,0,SEEK_END);
    countprice = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countprice,bfptr);
    rewind(bfptr);
        float ratio = 0;

        do
        {
        puts("Please enter the category you wish to update (between 1-5)\n");
        printf("1)Electronics\n2)Computers\n3)Women's Fashion\n4)Men's Fashion\n5)Home and Kitchen\n");
        scanf("%d",&categoryid);

        } while (categoryid < 1 || categoryid > 5);

        puts("Please enter a ratio you wish to update prices with");
        scanf("%f",&ratio);

        for(int i = 0;i <= countprice;i++)
        {
        if(info[i].categoryid == categoryid)
        {
           info[i].price = info[i].price*ratio;
        }
        }
        fwrite(info,sizeof(Product),countprice,bfptr);
        }
    fclose(bfptr);
}

void keysearch(Product info[])
{
    FILE *bfptr = fopen(FILEDAT,"rb+");

    int categoryid;

    if(bfptr == NULL)
    {
        puts("ERROR");
    }
    else
    {
    int countkey = 0;
    fseek(bfptr,0,SEEK_END);
    countkey = ftell(bfptr)/sizeof(Product);
    rewind(bfptr);
    fread(info,sizeof(Product),countkey,bfptr);
    rewind(bfptr);
    char keyword[25] = "";
    char pname[20] = "";
    char cname[20] = "";
    puts("Please enter the keyword");
    fflush(stdin);
    fgets(keyword,25,stdin);
    keyword[strlen(keyword)-1] = '\0';
    
    for(int i = 0;i <= countkey;i++)
    {
        for(int j = 0;j < 20;j++)
        {
            keyword[j] = tolower(keyword[j]);
            pname[j] = tolower(info[i].productname[j]);
            cname[j] = tolower(info[i].categoryname[j]);
        }

        if(strstr(pname,keyword) != NULL)
        {
        printf("%d %s %d %s %d %.2f\n",info[i].productid,info[i].productname,info[i].categoryid,info[i].categoryname,
            info[i].stock,info[i].price);
        }
        else if(strstr(cname,keyword) != NULL)
        {
        printf("%d %s %d %s %d %.2f\n",info[i].productid,info[i].productname,info[i].categoryid,info[i].categoryname,
            info[i].stock,info[i].price);   
        }
     }
   }
    fclose(bfptr);
}

int menu()
{
    int choice = 15;
    puts("\nPlease enter your choice");
    printf("1)Add new product\n2)List all active products\n3)List all inactive products\n4)Query a Product by ID\n5)Update product\n6)Change product status\n7)Sell product\n8)Restock product\n9)Change all prices by category\n10)Query product by text\n11)Import products text file\n0)Exit\n? ");
    scanf("%d",&choice);
    return choice;
}

int main(void)
{
   FILE *bfptr = fopen(FILEDAT,"rb+");
   if(bfptr == NULL)
   {
    puts("ERROR");
   }
   else
   {
   Product info[SIZE];
   int searchid;
   int choice = 35;
    do
    {
       choice = menu();

       switch(choice)
       {
        case 1:
        addnewproduct(info);
        fseek(bfptr,0,SEEK_END);
        break;

        case 2:
        listactiveproducts(info);   
        break;

        case 3:
        listinactiveproducts(info);   
        break;

        case 4:
        puts("Please enter the ID:");
        scanf("%d",&searchid);
        findproductbyid(info,searchid);   
        break;

        case 5:
        puts("Please enter the ID:");
        scanf("%d",&searchid);
        updateproductbyid(info,searchid);
        rewind(bfptr);
        fseek(bfptr,0,SEEK_END);
        int ncount = ftell(bfptr)/sizeof(Product);
        rewind(bfptr);
        fwrite(info,sizeof(Product),ncount,bfptr); 
        rewind(bfptr);
        break;

        case 6:
        puts("Please enter the ID:");
        scanf("%d",&searchid);
        changestatus(info,searchid);   
        break;

        case 7:
        puts("Please enter the ID:");
        scanf("%d",&searchid);
        updatestock(info,searchid,7);   
        break;

        case 8:
        puts("Please enter the ID:");
        scanf("%d",&searchid);
        updatestock(info,searchid,8);   
        break;

        case 9:
        updatepricesbycategory(info);  
        break;

        case 10:
        keysearch(info);   
        break;

        case 11:
        importxtobinary(info);   
        break;
       }
     } while (choice != 0);
   } 
   fclose(bfptr);
}