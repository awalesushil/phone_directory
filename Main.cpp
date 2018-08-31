/*
	Project : Phone Directory
	Author	: Sushil Awale [0540]
	Date	: 05-07-2016
*/

/* Header files */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "headerfile.h"
#define MAXSIZE 2000

/* Declaring Global Variables */
int count; 	/* Count total no. of records */
int flag;

/* Structure to store contacts*/
struct contact {
	char first_name[20];
	char last_name[20];
	long long int phone_no;
	char address[20];
} record;

/* User-defined functions: Declaration */
int transfer_primary();
void menu_display();
void enter_new_contact();
void display();
void search_menu();
void search_string(char [][20]);
void search_num();
void binsrch(long long int a[], long long int, int, int);
void delete_contact();

/* Main Function */
int main () {

	log_in();
	
	clear();
	
	/* Documentation */
	printf ("Hello %s! Welcome to the Phone Directory! \n \n", display_name);
	printf ("About Phone Directory \n");
	printf ("* This is a simple phone directory to store phone numbers, and address.\n");
	printf ("* Features \n");
	printf ("* Enter new contacts. \n");
	printf ("* Fast search with binary search \n");
	printf ("* Delete contacts. \n");
	printf ("* Author: Sushil Awale \n");
	printf ("* Version: 1.0 \t 2016-08-28 \n");
	printf ("Press Enter to continue. \n");
	
	transfer_primary();

	getch();
	
	menu_display();
	
	getch();

	return 0;
}

/* Main Menu Display Function */
void menu_display() {
	
	clear();
	
	int menu;
	
	printf ("Menu \n");
	printf ("1. Enter new contact \n");
	printf ("2. Display \n");
	printf ("3. Search record \n");
	printf ("4. Delete record \n");
	printf ("5. Log out \n");
	printf ("0. Exit \n");
	scanf ("%d", &menu);

	clear();
	
	switch (menu) {
		case 1:
			enter_new_contact();
			
		case 2:
			display();
			
		case 3:
			search_menu();
			
		case 4:
			delete_contact();
			
		case 5:
			
			clear();
			
			printf ("\n You have succesfully logged out. Press Enter \n");
			
			fclose (fp);
			
			getch();
			
			main();
		case 0:
			exit(-1);
		default:
			printf ("Invalid Operation \n");
			menu_display();
	}
}

/* Function to add new contact */
void enter_new_contact () {

	int i, n, k, number;
	
	printf ("How many contacts do you want to save?:");
	scanf("%d", &n);

	/* Enter New Records */

	for (i = 0; i < n; i++) {
		
		clear();
		
		printf ("Entry %d \n", i);
		
		printf ("Enter first name: ");
		scanf ("%s", record.first_name);

		printf ("Enter last name: ");
		scanf ("%s", record.last_name);
		
		printf ("Enter phone number: ");
		scanf ("%lld", &record.phone_no);

		printf ("Enter address: ");
		scanf ("%s", record.address);

		fprintf (fp, "%s %s %lld %s \n", record.first_name, record.last_name, record.phone_no, record.address);
	}

	printf ("%d contact/s have been recorded \n", n);
	
	rewind(fp);
	
	transfer_primary();
	
	getch();
	
	menu_display(); 	
}

/* Function to display display menu */
void display() {
	
	int sub_menu, i = 0;
	
	mergesort_character(f_name, l_name, adrs, p_num, count);
	
	printf ("Sub-Menu \n");
	printf ("1. Display All \n");
	printf ("2. Display all Names \n");
	printf ("3. Display all First Names \n");
	printf ("4. Display all Last Names \n");
	printf ("5. Display all Numbers \n");
	printf ("6. Display all Addresses \n");
	scanf ("%d", &sub_menu);

	switch (sub_menu) {
		case 1:
			printf ("S.No.|\t First Name |\t  Last Name |\t  Phone No. |\t    Address |\n \n");
	
			do {
				printf ("| %2d |\t %10s |\t %10s |\t %10lld |\t %10s |\n", i, f_name[i], l_name[i], p_num[i], adrs[i]);
				i++;
			} while (i < count);
	
			getch();
	
			menu_display();
			
		case 2:
			
			printf ("S.No.|\t First Name |\t  Last Name |\n\n");
		
			do {
				printf ("| %2d |\t %10s |\t %10s |\n", i, f_name[i], l_name[i]);
				i++;
			} while (i < count);
			
			getch();
			
			menu_display();
			
		case 3:
			
			printf ("S.No.|\t  First Name |\n\n");
			
			do {
				printf ("| %2d |\t %10s |\n", i, f_name[i]);
				i++;
			} while (i < count);
			
			getch();
			
			menu_display();
			
		case 4:
			mergesort_character(l_name, f_name, adrs, p_num, count);
	
			printf ("S.No.|\t  Last Name |\n \n");
			
			do {
				printf ("| %2d |\t %10s |\n", i, l_name[i]);
				i++;
			} while (i < count);
			
			getch();
			
			menu_display();
			
		case 5:
			mergesort_numbers(p_num, f_name, l_name, adrs, count);
	
			printf ("S.No.|\t  Phone No. |\n \n");
			
			do {
				printf ("| %2d |\t %10lld |\n", i, p_num[i]);
				i++;
			} while (i < count);
			
			getch();
			
			menu_display();
		case 6:
			mergesort_character(adrs, f_name, l_name, p_num, count);
	
			printf ("S.No.|\t    Address | \n \n");
			
			do {
				printf ("| %2d |\t %10s |\n", i, adrs[i]);
				i++;
			} while (i < count);
			
			getch();
			
			menu_display();
		default:
			printf ("Invalid Opeartion \n");
			display();
	}
}

/* Function to search */
void search_menu () {
	
	clear();
	
	int menu;
	
	printf ("1. Search by first name \n");
	printf ("2. Search by last name \n");
	printf ("3. Search by phone number \n");
	printf ("4. Search by address \n");
	printf ("5. Go to main menu \n");
	printf ("0. Exit \n");
	scanf ("%d", &menu);
	
	switch (menu) {
		case 1: 
			search_string(f_name);
		case 2:
			search_string(l_name);
		case 3:
			search_num();
		case 4:
			search_string(adrs);
		case 5:
			menu_display();
		case 0:
			exit(-1);
		default:
			printf ("Invalid Entry ! Please, try again \n");
			
			getch();
			
			clear();
			
			search_menu();	
	}
}

/* Function to search by string */
void search_string(char a[][20]) {
	
	clear();
	
	char key[20];
	int i, flag = 0;
	
	printf ("Enter search term: ");
	scanf ("%s", key);
	
	printf ("S.No.|\t First Name |\t  Last Name |\t  Phone No. |\t   Address |\n \n");
	
	for ( i = 0; i < count; i++) {
		if (strcmp(key, a[i]) == 0) { // Compare entered key with the passed array
			printf ("| %2d |\t %10s |\t %10s |\t %lld |\t %10s |\n", i, f_name[i], l_name[i], p_num[i], adrs[i]);
			flag = 1;
		}
	}
	
	if (flag == 0) {
		clear();
		printf ("Record not found. Press enter. \n");
	}
	
	getch ();
	
	search_menu();
}

/* Function to search by number */

void search_num () {
	
	clear();
	
	long long int key;
	
	mergesort_numbers(p_num, f_name, l_name, adrs, count);
	
	printf ("Enter phone number: ");
	scanf ("%lld", &key);
	
	binsrch (p_num, key, 0, count); // call binary search function
	
	getch();
	
	search_menu();
}

void binsrch (long long int a[], long long int key, int low, int high) {
	
	int mid, i, flag = 0;
	
	if (low > high) { 
		printf ("Record Not Found! Please, try again ! \n");
	} else {
		mid = ((low + high) / 2);
		
		if (key == a[mid]) {
			printf ("S.No |\t First Name |\t  Last Name |\t Phone No.  |\t   Address |\n \n");

			printf ("| %2d |\t %10s |\t %10s |\t %lld |\t %10s |\n", i, f_name[mid], l_name[mid], p_num[mid], adrs[mid]);				
		} else if (key < a[mid]) {
			binsrch(a, key, low, mid-1);	// Recursively call binary function
		} else if (key > a[mid]) {
			binsrch(a, key, mid+1, high);	// Recursively call binary function
		}
	}
	
		getch ();
		
		search_menu();
}

/* Function to delete contact */
void delete_contact () {
	
	fclose (fp); // CLose the file which was open in append mode
	
	int i, flag;
	
	// Auxillary varibles for delete funciton
	
	char del_f_name[20];
	char del_l_name[20];
	
	fp = fopen (log_rec.user_name, "w+"); // Open file in write mode

	printf ("Enter record details for deletion \n");
	printf ("Enter first name: ");
	scanf ("%s", del_f_name);
	
	printf ("Enter last name: ");
	scanf ("%s", del_l_name);
	
	for (i = 0; i < count; i++) {
		
		/*Compare auxillary delete variables with respective arrays */
		
		if (strcmp(del_f_name, f_name[i]) == 0 && strcmp(del_l_name, l_name[i]) == 0) { 
				
				/* Store null value in the respective arrays */
				for (i; i < count; i++) {
					
					strcpy(f_name[i], f_name[i+1]);
					strcpy(l_name[i], l_name[i+1]);
					strcpy(adrs[i], adrs[i+1]);
					p_num[i] = p_num[i+1];	
				}
				flag = 1;
				count--;
		} 
	} 
	
	if (flag = 0) {
		printf ("Record was not found ! \n");
		
		getch ();
		
		menu_display();	
	}
	
	// Write the records in the file
	
	for (i = 0; i < count; i++) {
		strcpy (record.first_name, f_name[i]);
		strcpy (record.last_name, l_name[i]);
		strcpy (record.address, adrs[i]);
		record.phone_no = p_num[i];
		fprintf (fp, "%s %s %d %s \n", record.first_name, record.last_name, record.phone_no, record.address);
	}
	
	fclose (fp);
	
	printf ("1 record has been deleted \n");
	
	getch ();
	
	menu_display();
}

/* Transfer data to primary memory */
int transfer_primary() {
		
	rewind(fp);
	
	int i = 0, k;
	
	char c;
	
	do {
		
		fscanf (fp, "%s %s %lld %s", record.first_name, record.last_name, &record.phone_no, record.address);
		
		strcpy (f_name[i], record.first_name); // Copy from file to primary variable
		for (k = 0; f_name[i][k]; k++) {		/* Convert to lower case */
  			f_name[i][k] = tolower(f_name[i][k]);
		} 
		
		strcpy (l_name[i], record.last_name);	// Copy from file to primary variable	
		for (k = 0; l_name[i][k]; k++) {		/* Convert to lower case */
  			l_name[i][k] = tolower(l_name[i][k]);
		}
		
		p_num[i] = record.phone_no;	// Copy from file to primary variable
		
		strcpy (adrs[i], record.address);	// Copy from file to primary variable
		for (k = 0; adrs[i][k]; k++) {		/* Convert to lower case */
  			adrs[i][k] = tolower(adrs[i][k]);
		}
	    
		i++;	
	} while (c = getc(fp) != EOF);
	
	count = i - 1;
	
	rewind(fp);
	
	mergesort_character(f_name, l_name, adrs, p_num, count);
	
	return count;
}


