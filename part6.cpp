#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void write(FILE*fout)
{   
    struct product
    {
    	int id;
    	int price;
    	int amount;
    };
    int n,i;
    puts("enter the number of product \n");
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
	("enter the id, the price and the amount of %d th product  ",i+1);
	scanf("%d%d%d",&product.id,&product.price,&product.amount);
	fprintf(fout,"%2d%5d%2d\n",product.id,product.price,product.amount);
	}
void print(fin)
{   
	struct product
    {
    	int id;
    	int price;
    	int amount;
    };
	while(!eof(fin))
	{
	fscan("%2d%5d%2d",&product.id,&product.price,&product.amount);
	switch (product.id)
	{
		case 1:
			{
				printf("ruler ");
				break;
			}
		case 2:
			{
				printf("pencil ");
				break;
			}
	    case 3:
			{
				printf("pen ");
				break;
			}
	}
	printf("price is %d , the amount is %d",product.price,product.amount);
	}	
}	

int main()
{   int choice=0;
	FILE *fin;
	FILE * fout;
	fout = fopen("C:/Users/pc/Documents/product.txt","r+");
	if(fout!=NULL)
	{   
	    while(1)
	    {
			printf("press 1 if you want to add product, press 2 if you want to delete product  3 if you want to see the product and 0 if you want to exit \n ");
			scanf(choice);
			if (choice==0) break;
			if (choice ==1 ) write(fout);
			if (choice==2 )  del(fin);
			if (choice==3)  print(fin);
		}
	}
	return 0;
}
	
