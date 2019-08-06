#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

char LOGIN_FILE_NAME[] = "account.txt";
char PRODUCT_FILE_NAME[] = "product.txt";
char ORDER_FILE_NAME[] = "order.txt";

int checkLogin(char fileInput[100], char name[100], char passwords[100]) {
	int userId;
	char userName[200];
	char userPass[200];
	int loginStatus = 0;
	FILE *filePointer;
	
	filePointer = fopen(fileInput, "r");
	
	if(filePointer == NULL) {
		printf("%s does not exist", fileInput);
		return -1;
	} else {
		while(!feof(filePointer)) {
			fscanf(filePointer, "UserID: %d\nName: %[^\n]\nPassword: %s\n\n", &userId, &userName, &userPass);
			if(strcmp(userName, name) == 0 && strcmp(userPass, passwords) == 0) {
				printf("UserID: %d\nName: %s\nPassword: %s\n\n", userId, userName, userPass);
				loginStatus = 1;
				break;
			}
		}
	}
	if(loginStatus == 1) {
		printf("Congratulations! You login successfully\n");
		printf("Welcome mister, %s\n\n", userName);
		
		return userId;
	} else {
		return -1;
	}
	fclose(filePointer);
}

void getProductList(char fileInput[100]) {
	int productID;
	char productName[100];
	int productPrice;
	int inStore;
	
	FILE *filePointer;

	filePointer = fopen(fileInput, "r");
	if(filePointer == NULL) {
		printf("%s does not exist", fileInput);
	} else {
		while(!feof(filePointer)) {
			fscanf(filePointer, "ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n", &productID, &productName, &productPrice, &inStore);
			printf("ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n", productID, productName, productPrice, inStore);
		}		
	}
	fclose(filePointer);
}

void writeOrder (int userId) {
	int flag = 0;
	int userChoice = 0;
	int userProductChoice;
	
	int productID;
	char productName[100];
	int productPrice;
	int inStore;
	
	int orderId;
	int amount;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	FILE *filePointer;
	FILE *filePointer2;
	int payStatus = 1;
	
	filePointer2 = fopen(ORDER_FILE_NAME, "a");
	if(filePointer2 == NULL) {
		printf("Fail to create/open file to write data");
	} else {
		printf("Order id:");
		scanf("%d", &orderId);
		fprintf(filePointer2,"OrderID: %d\nDate\: %d/%d/%d\nBuyerID\: %d\nContent:\n<begin>\n",orderId, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, userId);
		fclose(filePointer2);
	}
	
	while(1) {
		printf("Enter your choice of productId: ");
		scanf("%d", &userProductChoice);
		
		filePointer = fopen(PRODUCT_FILE_NAME, "r");
		while(!feof(filePointer)) {
			fscanf(filePointer, "ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n",&productID, &productName, &productPrice, &inStore);
			if(userProductChoice == productID && inStore > 0) {
				flag = 1;
				break;
			} else {
				flag = 0;
			}
		}
		fclose(filePointer);

		if(flag == 1) {
			printf("You choose the following product: \n");
			printf("ProductID: %d\nName: %s\nPrice: %d\nIn-store: %d\n\n", productID, productName, productPrice, inStore);
	
			printf("Enter the amount you want to buy: ");
			scanf("%d", &amount);
			if(amount > inStore) {
				printf("Please enter again. There is not enough stock for this product");
			} else {
				filePointer2 = fopen(ORDER_FILE_NAME, "a");
				if(filePointer2 == NULL) {
					printf("Fail to create/open file to write data");
				} else {
					fprintf(filePointer2, "%d - %d - %d\n", productID, amount, productPrice*amount);
					fclose(filePointer2);
				}
			}
		} else {
			printf("Sorry, your product is currently unavailable. Please return in the future to check one more time. Thank you for visiting our shop\n");
		}

		printf("Do you want to continue ?(Y/N) Y = 1, N = 0\n");
		scanf("%d", &userChoice);
		if(userChoice == 0) {
			filePointer2 = fopen(ORDER_FILE_NAME, "a");
			if(filePointer2 == NULL) {
				printf("Fail to create/open file to write data");
			} else {
				fprintf(filePointer2, "<end>\nPaid: %d\n\n", payStatus);
				fclose(filePointer2);
			}
			break;
		}
    }
}
int login() {
	int userId;
	char userName[100];
	char userPass[100];
	int userChoice;
	

	printf("Please login\n");
	while(1) {
		printf("Enter your username: ");
		gets(userName);
		
		printf("Enter your password: ");
		gets(userPass);
		
		userId = checkLogin(LOGIN_FILE_NAME, userName, userPass);
		if(userId > -1) {
			break;
		} else {
			printf("You enter incorrect login info\n");
			printf("Do you want to continue ?(Y/N) Y = 1, N = 0\n");
			scanf("%d", &userChoice);
			getchar();
			if(userChoice == 0) {
				break;
			}
		}
	}
	
	return userId;
}

int orderProducts(int userId) {
	printf("------ProductList------\n");
	getProductList(PRODUCT_FILE_NAME);
	
	writeOrder(userId);
}	

int main()
{
	int loginStatus;
	int userId;
	userId = login();
	
	if(userId > -1) {
		orderProducts(userId);
	}
	
	return 0;
}