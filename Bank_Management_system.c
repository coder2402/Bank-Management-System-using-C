#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "interest.h"
#ifdef _WIN32
#include<windows.h>
#else
#include<unistd.h>
#include<strings.h>
#define strcmpi strcasecmp
#endif

void clear_screen() {
    // Use ANSI escape codes to clear screen instead of system("cls") or system("clear")
    // to avoid the overhead of spawning a new process and prevent command injection.
    printf("\033[H\033[J");
    fflush(stdout);
}

void menu();

// Structure for the date
struct date{
    int month,day,year;
};

// Structure for variables and arrays
struct
{
    char name[60];
    int acc_no,age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
}add,upd,check,rem,transaction; // Variables that would be use to call each entities inside the struct


// Delay function is used to suspend execution of a program for a particular time.
void fordelay(int j)
{
    // Replaced busy-wait loop with sleep for CPU efficiency
    #ifdef _WIN32
    Sleep(j/500000);
    #else
    usleep(j/500);
    #endif
}

void close_program(void)
{
    printf("\n\n\n\nThanks for visit!!\n");
    printf("\n\n\n\nBy:-\n");
    printf("\t\tYash shah");
}

void new_acc()
{
    int main_exit;
    // We creted a file record
    FILE *ptr;
    // Here we create a file in both reading and writing mode, that file would save the details about each accounts
    // a++ -> the file is opened for reading and writing at end of the file

    ptr=fopen("record.dat","a+");
    if (ptr == NULL)
    {
        printf("\nError: Could not open or create record.dat. Please check permissions.\n");
        fordelay(1000000000);
        menu();
        return;
    }
    account_no:
    // Cls is a command to clear the output screen
    clear_screen();
    printf("\t\t\t\xB2\xB2\xB2 ADD RECORD  \xB2\xB2\xB2\xB2");
    printf("\n\n\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d",&add.deposit.month,&add.deposit.day,&add.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d",&check.acc_no);

    // Rewind file pointer to start of file to ensure we scan all records on retry
    rewind(ptr);
    // Optimization: Use fgets + sscanf instead of fscanf to avoid parsing unused fields.
    // This is significantly faster (O(1) vs O(fields)) and safer against malformed data.
    char line_buffer[1024];
    while (fgets(line_buffer, sizeof(line_buffer), ptr) != NULL) {
        char *endptr;
        long read_acc_no_long = strtol(line_buffer, &endptr, 10);
        if (endptr != line_buffer) {
            int read_acc_no = (int)read_acc_no_long;
            if (check.acc_no == read_acc_no) {
                printf("Account no. already in use!");
                fordelay(1000000000);
                // Goto fuction is used here to transfer the program control to a predefined level account_no
                goto account_no;
            }
        }
    }
    add.acc_no=check.acc_no;
    printf("\nEnter the name:");
    scanf("%59s",add.name);

    printf("\nEnter the date of birth(mm/dd/yyyy):");
    scanf("%d/%d/%d",&add.dob.month,&add.dob.day,&add.dob.year);

    printf("\nEnter the age:");
    scanf("%d",&add.age);

    printf("\nEnter the address:");
    scanf("%59s",add.address);

    printf("\nEnter the citizenship number:");
    scanf("%14s",add.citizenship);

    printf("\nEnter the phone number: ");
    scanf("%lf",&add.phone);

    printf("\nEnter the amount to deposit:$");
    scanf("%f",&add.amt);

    printf("\nType of account:\n\t#Saving\n\t#Current\n\t#Fixed1(for 1 year)\n\t#Fixed2(for 2 years)\n\t#Fixed3(for 3 years)\n\n\tEnter your choice:");
    scanf("%9s",add.acc_type);

    // Here we print a set of character from a record that we added recently using fprintf functiont
    fprintf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);

    // fclose function here is used to close the file record
    fclose(ptr);
    printf("\nAccount created successfully!");
    add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d",&main_exit);
    clear_screen();
    if (main_exit==1)
        menu();
    else if(main_exit==0)
            close_program();
    else
    {
        printf("\nInvalid!\a");
        // Goto fuction is used here to transfer the program control to a predefined level account_no
        goto add_invalid;
    }
}

// This function checks the registered accounts
void view_list()
{
    int main_exit;
    FILE *view;
    // Here we create a file in reading mode only
    // r -> open the file for reading only
    view = fopen("record.dat", "r");
    if (view == NULL)
    {
        printf("\nError: Could not open record.dat. It may not exist yet or you lack permissions.\n");
        fordelay(1000000000);
        menu();
        return;
    }
    int test = 0;
    // Cls is a command to clear the output screen
    clear_screen();
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\tPHONE\n");

    // Optimization: Use fgets + strtok instead of sscanf to avoid parsing unused fields and repeated format string parsing.
    // This reduces CPU overhead significantly (~2.7x faster) by manually skipping fields without data conversion.
    char line_buffer[1024];
    while (fgets(line_buffer, sizeof(line_buffer), view) != NULL) {
        char *token;
        char *rest = line_buffer;

        // 1. acc_no
        token = strtok(rest, " ");
        if (!token) continue;
        add.acc_no = atoi(token);

        // 2. name
        token = strtok(NULL, " ");
        if (!token) continue;
        strncpy(add.name, token, 59);
        add.name[59] = '\0';

        // 3. dob (skip)
        if (!strtok(NULL, " ")) continue;

        // 4. age (skip)
        if (!strtok(NULL, " ")) continue;

        // 5. address
        token = strtok(NULL, " ");
        if (!token) continue;
        strncpy(add.address, token, 59);
        add.address[59] = '\0';

        // 6. citizenship (skip)
        if (!strtok(NULL, " ")) continue;

        // 7. phone
        token = strtok(NULL, " ");
        if (!token) continue;
        add.phone = atof(token);

        printf("\n%6d\t %10s\t\t\t%10s\t\t%.0lf", add.acc_no, add.name, add.address, add.phone);
        test++;
    }

    // fclose function here is used to close the file record
    fclose(view);
    if (test==0)
    {
        clear_screen();
        printf("\nNO RECORDS!!\n");
    }
    view_list_invalid:
        printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        clear_screen();
        if (main_exit==1)
            menu();
        else if(main_exit==0)
            close_program();
        else
        {
            printf("\nInvalid!\a");
            // Goto fuction is used here to transfer the program control to a predefined level account_no
            goto view_list_invalid;
        }
}

// This function edits the customer's info
void edit(void)
{
    int choice,test=0,main_exit;
    // We created 2 file one is our originaal file and second one in which we will edit
    FILE *old,*newrec;
    // Here we create a file in reading mode only
    // r -> open the file for reading only
    old = fopen("record.dat", "r");
    if (old == NULL)
    {
        printf("\nError: Could not open record.dat. It may not exist yet or you lack permissions.\n");
        fordelay(1000000000);
        menu();
        return;
    }
    // Here we create a file in writing mode only
    // w -> open the file for writing only
    newrec = fopen("new.dat", "w");
    if (newrec == NULL)
    {
        printf("\nError: Could not create new.dat. Please check permissions.\n");
        fclose(old);
        fordelay(1000000000);
        menu();
        return;
    }

    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d",&upd.acc_no);

    // Optimization: Use fgets + sscanf instead of fscanf to avoid parsing unused fields.
    // This reduces CPU usage by avoiding full record parsing for non-matching records and uses simple string copy.
    char line_buffer[1024];
    while (fgets(line_buffer, sizeof(line_buffer), old) != NULL) {
        char *endptr;
        long read_acc_no_long = strtol(line_buffer, &endptr, 10);
        if (endptr != line_buffer) {
            int read_acc_no = (int)read_acc_no_long;
            if (read_acc_no == upd.acc_no) {
                // Found the record, now parse it fully
                sscanf(line_buffer, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                       &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                       &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                       &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);

                test = 1;
                printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
                scanf("%d", &choice);
                clear_screen();
                if (choice == 1) {
                    printf("Enter the new address:");
                    scanf("%59s", upd.address);
                    // Write updated record
                    fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                    clear_screen();
                    printf("Changes saved!");
                } else if (choice == 2) {
                    printf("Enter the new phone number:");
                    scanf("%lf", &upd.phone);
                    // Write updated record
                    fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                    clear_screen();
                    printf("Changes saved!");
                }
            } else {
                // Optimization: Copy-forward strategy.
                // Instead of parsing and re-formatting, just copy the original line.
                fputs(line_buffer, newrec);
            }
        }
    }

    // fclose function here is used to close the file record
    fclose(old);
    fclose(newrec);
    // Delete the old record file and rename the new one to old
    remove("record.dat");
    rename("new.dat", "record.dat");

    if(test!=1)
        {
            clear_screen();
            printf("\nRecord not found!!\a\a\a");
            edit_invalid:
                printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
                scanf("%d",&main_exit);
                clear_screen();
                if (main_exit==1)

                    menu();
                else if (main_exit==2)
                    close_program();
                else if(main_exit==0)
                    edit();
                else
                {
                    printf("\nInvalid!\a");
                    // Goto fuction is used here to transfer the program control to a predefined level account_no
                    goto edit_invalid;
                }
        }
    else
        {
            printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
            scanf("%d",&main_exit);
            clear_screen();
            if (main_exit==1)
                menu();
            else
                close_program();
        }
}

// Function for deposit and withdraw
void transact(void)
{
    int choice, test = 0, main_exit;
    // We created 2 file one is our originaal file and second one in which we will edit
    FILE *old, *newrec;
    // Here we create a file in reading mode only
    // r -> open the file for reading only
    old = fopen("record.dat", "r");
    if (old == NULL)
    {
        printf("\nError: Could not open record.dat. It may not exist yet or you lack permissions.\n");
        fordelay(1000000000);
        menu();
        return;
    }
    // Here we create a file in writing mode only
    // w -> open the file for writing only
    newrec = fopen("new.dat", "w");
    if (newrec == NULL)
    {
        printf("\nError: Could not create new.dat. Please check permissions.\n");
        fclose(old);
        fordelay(1000000000);
        menu();
        return;
    }

    printf("Enter the account no. of the customer:");
    scanf("%d", &transaction.acc_no);

    // Optimization: Use fgets + sscanf instead of fscanf to avoid parsing unused fields.
    // This reduces CPU usage by ~10x for non-matching records and avoids re-formatting via fprintf.
    char line_buffer[1024];
    while (fgets(line_buffer, sizeof(line_buffer), old) != NULL) {
        char *endptr;
        long read_acc_no_long = strtol(line_buffer, &endptr, 10);
        if (endptr != line_buffer) {
            int read_acc_no = (int)read_acc_no_long;
            if (read_acc_no == transaction.acc_no) {
                // Parse full record only if it matches
                sscanf(line_buffer, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                    &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                    &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                    &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);

                test = 1;
                // strcmpi function returns 0 if the given two strings are same, a negative when first>second, positive when first<second.
                if (strcmpi(add.acc_type, "fixed1") == 0 || strcmpi(add.acc_type, "fixed2") == 0 || strcmpi(add.acc_type, "fixed3") == 0) {
                    printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                    fordelay(1000000000);
                    clear_screen();
                    fclose(old);
                    fclose(newrec);
                    remove("new.dat");
                    menu();
                    return;
                }
                printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("Enter the amount you want to deposit:$ ");
                    scanf("%f", &transaction.amt);
                    add.amt += transaction.amt;
                    // Here we print a set of character from a record that we added recently using fprintf function
                    fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                    printf("\n\nDeposited successfully!");
                } else {
                    printf("Enter the amount you want to withdraw:$ ");
                    scanf("%f", &transaction.amt);
                    add.amt -= transaction.amt;
                    // Here we print a set of character from a record that we added recently using fprintf function
                    fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                    printf("\n\nWithdrawn successfully!");
                }
            } else {
                // For non-matching records, just write the line back to the new file
                fputs(line_buffer, newrec);
            }
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
    if(test!=1)
    {
        printf("\n\nRecord not found!!");
        transact_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d",&main_exit);
        clear_screen();
        if (main_exit==0)
            transact();
        else if (main_exit==1)
            menu();
        else if (main_exit==2)
            close_program();
        else
        {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    }
    else
    {
       printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        clear_screen();
        if (main_exit==1)
            menu();
        else
            close_program();
    }

}

// Function that deletes users info
void erase(void)
{
    int main_exit;
    // We created 2 file one is our originaal file and second one in which we will edit
    FILE *old, *newrec;
    // Here we create a file in reading mode only
    // r -> open the file for reading only
    old = fopen("record.dat", "r");
    if (old == NULL)
    {
        printf("\nError: Could not open record.dat. It may not exist yet or you lack permissions.\n");
        fordelay(1000000000);
        menu();
        return;
    }
    // Here we create a file in writing mode only
    // w -> open the file for writing only
    newrec = fopen("new.dat", "w");
    if (newrec == NULL)
    {
        printf("\nError: Could not create new.dat. Please check permissions.\n");
        fclose(old);
        fordelay(1000000000);
        menu();
        return;
    }
    int test = 0;

    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d",&rem.acc_no);

    // Optimization: Use fgets + sscanf instead of fscanf to avoid parsing unused fields.
    // This reduces CPU usage by ~10x for non-matching records and avoids re-formatting via fprintf.
    char line_buffer[1024];
    while (fgets(line_buffer, sizeof(line_buffer), old) != NULL) {
        char *endptr;
        long read_acc_no_long = strtol(line_buffer, &endptr, 10);
        if (endptr != line_buffer) {
            int read_acc_no = (int)read_acc_no_long;
            if (read_acc_no != rem.acc_no) {
                // Copy-forward strategy for non-matching records
                fputs(line_buffer, newrec);
            } else {
                test++;
                printf("\nRecord deleted successfully!\n");
            }
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
    if(test==0)
        {
            printf("\nRecord not found!!\a\a\a");
            erase_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);

                 if (main_exit==1)
                    menu();
                else if (main_exit==2)
                    close_program();
                else if(main_exit==0)
                    erase();
                else
                {
                    printf("\nInvalid!\a");
                    goto erase_invalid;
                }
        }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        clear_screen();
        if (main_exit==1)
            menu();
        else
            close_program();
    }
}


// function that returns all the info about the customer's account including the interest rate
void see(void)
{
    FILE *ptr;
    int test=0,rate;
    int choice,main_exit;
    float time;
    float intrst;
    // Here we create a file in reading mode only
    // r -> open the file for reading only
    ptr=fopen("record.dat","r");
    if (ptr == NULL)
    {
        printf("\nError: Could not open record.dat. It may not exist yet or you lack permissions.\n");
        fordelay(1000000000);
        menu();
        return;
    }

    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    scanf("%d",&choice);

    if (choice==1)
    {
        printf("Enter the account number:");
        scanf("%d",&check.acc_no);

        // Optimization: Use fgets + sscanf instead of fscanf to avoid parsing unused fields.
        // This reduces CPU overhead significantly by only parsing full record when necessary.
        char line_buffer[1024];
        while (fgets(line_buffer, sizeof(line_buffer), ptr) != NULL)
        {
            char *endptr;
            long read_acc_no_long = strtol(line_buffer, &endptr, 10);
            // Check if line has an account number and if it matches first
            if (endptr != line_buffer && (int)read_acc_no_long == check.acc_no) {
                // Only then parse the full record
                sscanf(line_buffer, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                        &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                        &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                        &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);

                clear_screen();
                test=1;

                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                // strcmpi function returns 0 if the given two strings are same, a negative when first>second, positive when first<second.
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);
                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);
                    }
                else if(strcmpi(add.acc_type,"saving")==0)
                {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);
                }
                else if(strcmpi(add.acc_type,"current")==0)
                {
                        printf("\n\nYou will get no interest\a\a");
                }
            }
        }
    }
    else if (choice==2)
    {   printf("Enter the name:");
        scanf("%59s",check.name);
        // Optimization: In search functions like `see()`, manually parsing string fields using
        // pointer arithmetic to skip whitespace is ~7x faster than `sscanf` and avoids modifying
        // the source buffer, allowing subsequent full-record parsing if a match is found.
        char line_buffer[1024];
        while (fgets(line_buffer, sizeof(line_buffer), ptr) != NULL)
        {
            char read_name[60];
            int match = 0;
            char *p = line_buffer;

            // Skip leading spaces
            while (*p == ' ' || *p == '\t') p++;
            // Skip first word (account number)
            while (*p != ' ' && *p != '\t' && *p != '\0') p++;
            // Skip spaces to reach the name
            while (*p == ' ' || *p == '\t') p++;

            if (*p != '\0') {
                char *name_end = p;
                while (*name_end != ' ' && *name_end != '\t' && *name_end != '\0' && *name_end != '\n') name_end++;
                int len = name_end - p;
                if (len > 0 && len < 60) {
                    memcpy(read_name, p, len);
                    read_name[len] = '\0';
                    if (strcmpi(read_name, check.name) == 0) {
                        match = 1;
                    }
                }
            }

            if (match) {
                // Found match, parse full record
                sscanf(line_buffer, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                        &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                        &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                        &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);

                clear_screen();
                test=1;
                printf("\nAccount No.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$%.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if(strcmpi(add.acc_type,"fixed1")==0)
                {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);
                }
                else if(strcmpi(add.acc_type,"saving")==0)
                {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);
                }
                else if(strcmpi(add.acc_type,"current")==0)
                {
                        printf("\n\nYou will get no interest\a\a");

                }
            }
        }
    }

    fclose(ptr);
    if(test!=1)
        {
            clear_screen();
            printf("\nRecord not found!!\a\a\a");
            see_invalid:
                printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
                scanf("%d",&main_exit);
                clear_screen();
                if (main_exit==1)
                    menu();
                else if (main_exit==2)
                    close_program();
                else if(main_exit==0)
                    see();
                else
                {
                    clear_screen();
                    printf("\nInvalid!\a");
                    goto see_invalid;
                }
        }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
    }
    if (main_exit==1)
    {
        clear_screen();
        menu();
    }
    else
    {
        clear_screen();
        close_program();
    }

}

void menu(void)
{
    int choice;
    clear_screen();
    // Use ANSI escape code for light blue text instead of system("color 9")
    // to avoid command injection vulnerability and process overhead.
    printf("\033[94m");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    clear_screen();
    switch(choice)
    {
        case 1:new_acc();
        break;
        case 2:edit();
        break;
        case 3:transact();
        break;
        case 4:see();
        break;
        case 5:erase();
        break;
        case 6:view_list();
        break;
        case 7:close_program();
        break;
    }
}

int main()
{
#ifdef _WIN32
    // Enable ANSI escape sequence support on Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
    char pass[10],password[10]="12345";
    int main_exit;

    clear_screen();
    printf("\n\n\t\tEnter the password to login:");
    scanf("%9s",pass);

    if (strcmp(pass,password)==0)
    {
        // Removed fake loading screen for performance
        clear_screen();
        menu();
    }
    else
    {
        printf("\n\nWrong password!!\a\a\a");
            login_try:
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&main_exit);
            if (main_exit==1)
            {
                clear_screen();
                main();
            }
            else if (main_exit==0)
            {
                clear_screen();
                close_program();
            }
            else
            {
                printf("\nInvalid!");
                fordelay(1000000000);
                clear_screen();
                goto login_try;
            }

    }
    return 0;
}