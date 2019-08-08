#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
int productID;
char name[100];
int price;
int instore;
}Product;
static int id=1;
int choose;
FILE *fp;
void getfile(FILE *fp)
{
    int choice;
	Product p;
	//p.name=malloc(50*sizeof(char));
    while(1)
        {
        	printf("ProductID: ");
        	scanf("%d",&p.productID);
           // productID=id++;
           printf("Name :");
            scanf("%s",&p.name);
            printf("Price :");
            scanf ("%d", &p.price);
            printf("In-store :");
            scanf ("%d",&p.instore);
            fprintf(fp,"ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n",p.productID,p.name,p.price,p.instore);
            puts("Continute input file? press:1 Exit? press:0");
            scanf("%d",&choice);
            if(choice==0)
                {
                    break;
                }
        }
}
void readfile(FILE *fin)
{
	Product p;
	//p.name=malloc(50*sizeof(char));
    puts("Product info:\n");
    while(!feof(fin))
        {
            fscanf(fin,  "ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n",&p.productID,&p.name,&p.price,&p.instore);
            printf("ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n", p.productID,p.name, p.price, p.instore);
        }
}
int main()
{
    int n;
    FILE *fp;
    FILE *fin;
    while (1)
        {
            printf("Enter 1 to creat new file product\nEnter 2 to read file\nEnter 3 to update file\n");
            scanf("%d",&n);
            switch (n)
                {
                case 1:
                    fp=fopen("Product.txt","w");
                    if(fp != NULL)
                        {
                            getfile(fp);
                            fclose(fp);
                        }
                    break;
                case 2:
                 fin=fopen("Product.txt","r");
                    if(fin != NULL)
                        {
                            readfile(fin);
                            fclose(fin);
                        }
                    break;
                case 3:
                    fp=fopen("Product.txt","a+");
                    if(fp != NULL)
                        {
                            getfile(fp);
                            fclose(fp);
                        }
                    break;
                }
            puts("Continute programing(run again more a times) ? Press:1 Exit? Press:0");
            scanf("%d",&choose);
            if(choose==0)
                {
                    break;
                }
        }
    return 0;
}
