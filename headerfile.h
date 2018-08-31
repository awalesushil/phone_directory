#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define MAXSIZE 2000
#define ENTER 13
#define TAB 9
#define BKSP 8


/* Declaring Global Variables */
FILE  *fp, *fp_log;		/* Global Declaration of file pointers */
char display_name[20];  /* Declaration of display user name variable */

/* Primary variables */
char f_name[MAXSIZE][20], l_name[MAXSIZE][20], adrs[MAXSIZE][20];
long long int p_num[MAXSIZE];

/* Structure to store log info */
struct log {
	char user_name[20];
	char password[20];
} log_rec;

void clear();
void log_in();
void mergesort_numbers(long long int [], char [][20], char [][20], char [][20], int);
void mergesort_character(char [][20], char [][20], char [][20], long long int [], int);

void log_in() {

	clear();
	
	printf ("Welcome to Phone Directory! \n \n");
	
	int n, flag = 0, ex = 1, i = 0, j = 0;
	char ch;
	char aux_user_name[20], aux_password[20]; /* Declaration of auxillay log in variables */

	fp_log = fopen ("logsheet.txt", "a+");
	
	printf ("Press 1 to log in \n");		 /* Log in Menu */
	printf ("Press 2 to sign up \n");
	printf ("Press 3 to exit \n");
	scanf ("%d", &n);
	
	clear();
	
	if (n == 1) {
		
		again:
			
		printf ("Enter username: ");
		scanf ("%s", aux_user_name);

		printf ("Enter password: ");
		while (1) {
			ch = getch (); // get character
			
			if (ch == ENTER || ch == TAB) {
				aux_password[i] = '\0';
				break;
			} else if (ch == BKSP) {
				if (i > 0) {
					i--;
					printf ("\b \b");	// for backspace
				}
			} else {
				aux_password[i++] = ch;
				printf ("* \b"); 	// replace password with *
			}
		}
		
		strcpy (display_name, aux_user_name); /* Copy user name for display */

		strcat(aux_user_name,".txt");

		while (ch = fgetc(fp_log) != EOF) {
				
			/* Compare auxillary log in variables with log in data from logsheet */
			
			fscanf (fp_log, "%s %s", log_rec.user_name, log_rec.password);
			
			if ((strcmp(log_rec.user_name, aux_user_name)) == 0 && (strcmp(log_rec.password, aux_password)) == 0) {
				
				fp = fopen (log_rec.user_name, "a+");
				
				clear();
				
				printf ("You have succesfully logged in! Press enter to continue. \n");
				
				getch();
				
				flag = 1;
				
			} else if ((strcmp(log_rec.user_name, aux_user_name)) == 0) {	// If only username match
				
				clear ();
						
				printf ("The username and password do not match! \n");
				printf ("Press 1 to try again or 0 to exit \n");
				
				scanf ("%d", &ex);
				
				if (ex == 0) {
					exit (-1);
				} else if (ex == 1) {
					clear ();
					goto again;	
				}
			}
		}
		
		
		if (flag == 0) { // If both username and password do not match
			
			clear();
			
			printf ("You haven't registered! \n");
			printf ("Press 1 to register or 0 to exit \n");
			
			scanf ("%d", &ex);
				
			if (ex == 0) {
				exit (-1);
			} else if (n == 1) {
				clear();
				goto sign_up;
			}
		}
	} else if (n == 2) {	/* Enter new log record */
		
		sign_up:
		
		printf ("Enter the details to create a new directory \n");
			
		printf ("Enter user name: ");
		scanf ("%s", log_rec.user_name);
		
		strcpy (display_name, log_rec.user_name); /* Copy user name for display */
		
		strcat (log_rec.user_name, ".txt");
		
		if ((fp = fopen(log_rec.user_name, "r")) != NULL ) { 	/* Check for redundancy */
			
			clear ();
			
			printf ("User Name exists. Press Enter to enter new user name. \n");
			
			getch();
			
			clear();
			
			goto sign_up;
		}

		printf ("Enter password: ");
		i = 0;
		while (1) {
			ch = getch (); // get character
			
			if (ch == ENTER || ch == TAB) {
				log_rec.password[i] = '\0';
				break;
			} else if (ch == BKSP) {
				if (i > 0) {
					i--;
					printf ("\b \b");	// for backspace
				}
			} else {
				log_rec.password[i++] = ch;
				printf ("* \b"); 	// replace password with *
			}
		}
		
		/* Enter new log record in logsheet */

		fprintf (fp_log, "%s %s \n", log_rec.user_name, log_rec.password); 

		fp = fopen(log_rec.user_name, "w+");

	} else if (n == 3) {
		exit (-1);
	} else {
		
		clear();
		
		printf ("Invalid entry ! Please, try again ! \n");
		
		log_in();
	}
	
	rewind (fp_log);	
}

void clear() {		/* Credit: cprogramming.com */
	
  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );
}

/* Function to merge sort by first name */
void mergesort_numbers(long long int a[], char b[][20], char c[][20], char d[][20], int n) {

	long long int aux[n];
	char aux1[n][20], aux2[n][20], aux3[n][20];
	int i, j, k, size, l1, l2, u1, u2;
	
	size = 1; /* Merge files of size 1 */
	
	while (size < n) {
		l1 = 0; /*initialize lower bounds of first file */
		k = 0; /*k is index for auxillary array. */
		
		while (l1 + size < n) {		/* Check to see of there are two files to merge */
			/* Remaining indices */
			
			l2 = l1 + size;
			u1 = l2 - 1;
			u2 = (l2 + size - 1 < n) ? l2 + size - 1: n - 1;
			
			for (i = l1, j = l2; i <= u1 && j <= u2; k++) {
				/* Insert Smaller into auxillary */
				if (a[i] <= a[j]) {
					aux[k] = a[i];
					strcpy(aux1[k], b[i]);
					strcpy(aux2[k], c[i]);
					strcpy(aux3[k], d[i++]);
				} else {
					aux[k] = a[j];
					strcpy(aux1[k], b[j]);
					strcpy(aux2[k], c[j]);
					strcpy(aux3[k], d[j++]);
				}
			}
			/* Insert the elements of remaining files */		
			for (; i <= u1; k++) {
				aux[k] = a[i];
				strcpy(aux1[k], b[i]);
				strcpy(aux2[k], c[i]);
				strcpy(aux3[k], d[i++]);
			}
			
			for (; j <= u2; k++) {
				aux[k] = a[j];
				strcpy(aux1[k], b[j]);
				strcpy(aux2[k], c[j]);
				strcpy(aux3[k], d[j++]);
			}
			
			/* Point l1 to the start of next sub file */
			
			l1 = u2 + 1;
		}
		
		/* Copy any remaining single file */
		
		for (i = l1; k < n; i++) {
			aux[k] = a[i];
			strcpy(aux1[k], b[i]);
			strcpy(aux2[k], c[i]);
			strcpy(aux3[k++], d[i]);
		}
		
		/* Copy aux into x and adjust size */
		
		for (i = 0; i < n; i++) {
			a[i] = aux[i];
			strcpy(b[i], aux1[i]);
			strcpy(c[i], aux2[i]);
			strcpy(d[i], aux3[i]);
		}
		
		size *= 2;}
}

/* Function to merge sort by character */
void mergesort_character(char a[][20], char b[][20], char c[][20], long long int d[], int n) {

	int i, j, k, size, l1, l2, u1, u2;
	char aux[n][20], aux1[n][20], aux2[n][20];
	long long int aux3[n];
	
	size = 1; /* Merge files of size 1 */

	while (size < n) {
		l1 = 0; /*initialize lower bounds of first file */
		k = 0; /*k is index for auxillary array. */

		while (l1 + size < n) {		/* Check to see of there are two files to merge */
			/* Remaining indices */

			l2 = l1 + size;
			u1 = l2 - 1;
			u2 = (l2 + size - 1 < n) ? l2 + size - 1: n - 1;

			for (i = l1, j = l2; i <= u1 && j <= u2; k++) {
				/* Insert Smaller into auxillary */
				if ((strcmp(a[i], a[j])) < 0) {
					strcpy(aux[k], a[i]);
					strcpy(aux1[k], b[i]);
					strcpy(aux2[k], c[i]);
					aux3[k] = d[i++];
				} else {
					strcpy(aux[k], a[j]);
					strcpy(aux1[k], b[j]);
					strcpy(aux2[k], c[j]);
					aux3[k] = d[j++];
				}
			}
			/* Insert the elements of remaining files */
			for (; i <= u1; k++) {
				strcpy(aux[k], a[i]);
				strcpy(aux1[k], b[i]);
				strcpy(aux2[k], c[i]);
				aux3[k] = d[i++];
			}

			for (; j <= u2; k++) {
				strcpy(aux[k], a[j]);
				strcpy(aux1[k], b[j]);
				strcpy(aux2[k], c[j]);
				aux3[k] = d[j++];
			}

			/* Point l1 to the start of next sub file */

			l1 = u2 + 1;
		}

		/* Copy any remaining single file */

		for (i = l1; k < n; i++) {
			strcpy(aux[k], a[i]);
			strcpy(aux1[k], b[i]);
			strcpy(aux2[k], c[i]);
			aux3[k++] = d[i];
		}

		/* Copy aux into x and adjust size */

		for (i = 0; i < n; i++) {
			strcpy(a[i], aux[i]);
			strcpy(b[i], aux1[i]);
			strcpy(c[i], aux2[i]);
			d[i] = aux3[i];
		}
		size *= 2;
	}
}
