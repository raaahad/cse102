#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>

//Funciton prototype
void auth();
void reg(int *logged_in_check);
void login(int *logged_in_check);
void reset_pass();
void suspend_user();
void disable_suspend(int t_line);
void attendance_reg();
void usr_is_present(char name[30], char roll[30], char role[30], char date[30]);
void usr_is_absent(char name[30], char roll[30], char role[30], char date[30]);
void check_attendance_day_wise(char search_key[30]);
void fetch_all_att();
void search_att_with_roll();

//user structure will create variable everytime
struct user{
    char name[30];
    char password[30];
    int roll[10];
    char role[30];
};


//some global variable to call in most of the function
char stored_name[30];
char stored_pass[30];
char stored_roll[30];
char stored_role[30];
char stored_key[30];

int main(){

    //auth() fucntion is handling other functions
    auth();

}

void auth(){

    printf("---------------------------------------\n");
    printf("Welcome to Attendance Management System");
    printf("\n---------------------------------------");

    // setting logged status 0 in first state
    int* logged_in = 0;

    printf("\n\n\n");
    //This are option availave for everyone
    printf("1.Login \t2.Register \t3.Reset Password \t0.Exit");
    printf("\n\n\n");

    int user_choice;

    do{
        scanf("%d", &user_choice);

        switch(user_choice){
            case 1:
                // calling login() function and passing logged_in value 0. This value will be 1 once successfully logged in
                login(&logged_in);
                break;
            case 2:
                reg(&logged_in);
                break;
            case 3:
                //key is necessary for reseting password
                reset_pass();
                break;
            case 0:
                exit(0);
            default:
                 printf("Wrong choise, Select again or press 0 to exit. ");
                 continue;
        }
    }while(user_choice != 0);

}

void reg(int* logged_in_check){
    struct user student;
    if(*logged_in_check != 1){
        printf("You aren't logged in as admin. You have to login as admin to perform the request, Login instead...\n");
    }else{
        char line_length[150];
        char str[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/,.-+=~`<>:";
        char key[30];

        srand(time(0));
        for(int index = 0; index < 10; index++)
        {
            key[index] = str[rand() % (sizeof str - 1)];

        }

        int user_exist = 0;

        FILE *regFile;
        regFile = fopen("user.txt", "a+");
        if(!regFile)
            printf("Something went wrong");

        printf("Enter user name: "); scanf("%s", student.name);
        printf("Set user password: "); scanf("%s",student.password);
        printf("Enter user roll: "); scanf("%s", student.roll);
        printf("Enter user role(admin:user): "); scanf("%s", student.role);

        while ( fgets( line_length, sizeof( line_length ), regFile ) != NULL ) {
            fscanf(regFile, "name: %s password: %s roll: %s role: %s key: %s", stored_name, stored_pass, stored_roll, stored_role, stored_key);

            if(strcmp(student.name,stored_name)==0){
                user_exist = 1;
                printf("Username already exist. Try different one.");
                break;
            }
        }

        if(user_exist == 0){
            fprintf(regFile,"\nname: %s password: %s roll: %s role: %s key: %s", student.name, student.password, student.roll, student.role, key);

            printf("\n--User created successfully--");
            printf("\n--------Recovery key--------\n");
            printf("-------> %s <-------\n", key);
        }

        fclose(regFile);

    }
}

void login(int* logged_in_check){
    FILE *file;
    file = fopen("user.txt", "r");
    int roll[10];
    int key[10];

    if(!file){
        printf("Something went wrong");
    }else{
        char line_length[110];
        char name[30];
        char pass[30];
        int data_found = 0;
        int usr_choice;
        char search_key[10];
        int search_choice;

        printf("Enter your username: ");
        scanf("%s", name);
        printf("Enter your password: ");
        scanf("%s", pass);

        while ( fgets( line_length, sizeof( line_length ), file ) != NULL ) {
            fscanf(file,"name: %s password: %s roll: %s role: %s key: %d", stored_name, stored_pass, roll, stored_role, key);

            if(strcmp(name,stored_name)==0 && (strcmp(pass,stored_pass)==0) && (strcmp(stored_role,"admin")==0)){
                    *logged_in_check = 1;
                    data_found = 1;
                    system("@cls||clear");
                    printf("- Logged in successfully as admin\n");
                    printf("User: %s\t Role: %s", stored_name, stored_role);
                    printf("\n-----------------------------------");
                        printf("\n\n\n");
                        printf("1.Register user \t2.Suspend user \t3.Register attendence \n4.Download report(All) \t0.Main Menu");
                        printf("\n\n\n");

                        do{
                        printf("=>");
                        scanf("%d", &usr_choice);
                        switch(usr_choice){
                        case 1:
                            reg(logged_in_check);
                            break;
                        case 2:
                            suspend_user();
                            break;
                        case 3:
                            attendance_reg();
                            break;
                        case 4:
                            printf("1. Today \t2. Search with date \t3. Fetch All \t4. Search with roll number\n=>");
                            scanf("%d", &search_choice);
                            switch(search_choice){
                                case 1:
                                    sprintf(search_key, "today");
                                    check_attendance_day_wise(&search_key);
                                    break;
                                case 2:
                                    printf("(d-m-yyyy): ");
                                    scanf("%s", search_key);
                                    check_attendance_day_wise(&search_key);
                                    break;
                                case 3:
                                    fetch_all_att();
                                    break;
                                case 4:
                                    printf("Enter roll number to search with: ");
                                    scanf("%s", roll);
                                    search_att_with_roll(&roll);
                                    break;
                                default:
                                printf("Wrong choice");
                                    break;
                            }
                            break;
                        case 0:
                            system("@cls||clear");
                            auth();
                        default:
                            "Wrong choice.";
                        }
                    }while(usr_choice != 0);

                    break;
                }else if(strcmp(name,stored_name)==0 && (strcmp(pass,stored_pass)==0) && (strcmp(stored_role,"user")==0)){
                    *logged_in_check = 0;
                    data_found = 1;
                    system("@cls||clear");
                    printf("Logged in successfully\n");
                    printf("User: %s\t Role: %s", stored_name, stored_role);
                    printf("\n-----------------------------------");
                        printf("\n\n\n");
                        printf("1.Check your attendance \t0.Main Menu");
                        printf("\n\n\n");

                        do{
                        scanf("%d", &usr_choice);
                        switch(usr_choice){
                        case 1:
                            search_att_with_roll(&roll);
                            break;
                        case 0:
                            system("@cls||clear");
                            auth();
                        default:
                            "Wrong choice.";
                        }
                    }while(usr_choice != 0);

                    break;
                }
        }
        if(data_found == 0){
            printf("You are not authorized. Please try again...\n");
        }
    }
    fclose(file);
}

void reset_pass(){
    char input_key[20];
    printf("-> You are reseting you password.\n");
    printf("-> You will have to use your password recovery key to reset you password.\n\n");
    printf("Please enter your recovery key\n");
    scanf("%s", input_key);

    char roll[30];
    char key[30];
    char line_length[150];
    char new_pass[30];
    char update_data[150] = {0};
    int valid_key = 0;
    int replace_line;
    int count = 0;


    FILE *file;
    file = fopen("user.txt", "r");

    if (file == NULL){
        printf("Something went wrong");
    }

    count = 0;
    replace_line = 0;

    while ( fgets( line_length, sizeof( line_length ), file ) != NULL ) { count++; replace_line++;
        fscanf(file,"name: %s password: %s roll: %s role: %s key: %s", stored_name, stored_pass, roll, stored_role, key);

        if(strcmp(input_key,key) == 0){
            valid_key = 1;
            replace_line = count;
            printf("\nValid key\n");
            printf("User: %s\n", stored_name);
            printf("Roll: %s\n\n", roll);
            break;
        }
    }

        if(valid_key == 0){
            replace_line = -2;
            printf("Invalid key");
        }else{
            replace_line = count;
            printf("Enter new password: ");
            scanf("%s", new_pass);
        }

    fclose(file);


    FILE *usr_file;
    FILE *usr_tmp_file;
    usr_file = fopen("user.txt", "r");
    usr_tmp_file = fopen("backup.tmp", "w");

    if (usr_file == NULL || usr_tmp_file == NULL){
        printf("Something went wrong");
    }

    int trgt_line_counter = 0;
    while ( fgets( line_length, sizeof( line_length ), file ) != NULL ) {
            trgt_line_counter++;
            if(trgt_line_counter == replace_line+1){
                 fprintf(usr_tmp_file,"name: %s password: %s roll: %s role: %s key: %s\n", stored_name, new_pass, roll, stored_role, key);
                 printf("\n-> Password reset successfully\n");
            }else{
                fputs(line_length, usr_tmp_file);
            }
        }
    fclose(usr_file);
    fclose(usr_tmp_file);

    remove("usrBackup.txt");
    rename("user.txt", "usrBackup.txt");
    rename("backup.tmp", "user.txt");
}

void suspend_user(){

    char operation;
    char suspend_roll[30];
    char line_length[150];
    char stored_roll[30];
    char stored_id[30] = "auto";
    int suspend_user_found = 0;
    int line_counter = 0;
    int target;

    FILE *suspend_file;

    suspend_file = fopen("suspend_user.txt", "a+");

    if(!suspend_file){
        printf("Something went wrong");
    }else{
        printf("Please enter roll number to suspend a user: ");
        scanf("%s", suspend_roll);
    }

    while ( fgets( line_length, sizeof( line_length ), suspend_file ) != NULL ) { line_counter++;
        fscanf(suspend_file,"id: %s roll: %s", stored_id, stored_roll);
        if(strcmp(suspend_roll,stored_roll) == 0){
            target = line_counter;
            suspend_user_found = 1;
            break;
        }
    }

    if(suspend_user_found == 1){
    fclose(suspend_file);
        printf("User is already suspended.\n");
            printf("Do you want to cancel this ?\n");
            printf("1. Yes \t2.No");
            scanf("\n%d", &operation);

           switch(operation)
                {
                    case 1:
                        disable_suspend(target);
                        break;

                    case 2:
                        printf("ok");
                        break;

                    default:
                        printf("Wrong choice");
                        break;
                }
    }

    if(suspend_user_found == 0){
        fprintf(suspend_file, "\nid: %s roll: %s", stored_id, suspend_roll);
        printf("Added successfully.");
        fclose(suspend_file);
    }
}

void disable_suspend(int t_line){
    char suspend_roll[30];
    char line_length[150];
    char stored_roll[30];
    char stored_id[30] = "auto";
    int line_counter = 0;

    FILE *suspend_filee;
    FILE *suspend_file_tmp;

    if(suspend_filee == NULL || suspend_file_tmp == NULL){
        printf("Something went wrong");
    }else{
        suspend_filee = fopen("suspend_user.txt", "r");
        suspend_file_tmp = fopen("suspend_user_backup.tmp", "w");

        while(fgets(line_length, sizeof( line_length ), suspend_filee) != NULL){
            line_counter++;

            if(line_counter == t_line+1){
                fprintf(suspend_file_tmp, "");
            }else{
                fputs(line_length, suspend_file_tmp);
            }
        }

        fclose(suspend_filee);
        fclose(suspend_file_tmp);


        remove("suspend_user.txt");
        rename("suspend_user_backup.tmp", "suspend_user.txt");
    }
}

void attendance_reg(){
    char date[12] = {0};
    time_t now;
    time(&now);
    printf("You are registering attendance for:\n");
    printf("Today: %s", ctime(&now));

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%d-%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);

    FILE *usr_file;
    usr_file = fopen("user.txt", "r");
    int counter = 0;
    int counter2 = 0;

    if(!usr_file){
        printf("Something went wrong");
    }else{
        char line_length[150];
        int usr_choice;

        printf("\n||||||||  1=Present | 0=Absent\n");
        while ( fgets( line_length, sizeof( line_length ), usr_file ) != NULL ) { counter++;
        if( feof(usr_file) ) break;
        fscanf(usr_file, "name: %s password: %s roll: %s role: %s key: %s", stored_name, stored_pass, stored_roll, stored_role, stored_key);
            printf("%s\n=>", stored_name);
            scanf("%d", &usr_choice);
            switch(usr_choice){
            case 1:
                usr_is_present(&stored_name, &stored_roll, &stored_role, &date);
                break;
            case 0:
                usr_is_absent(&stored_name, &stored_roll, &stored_role, &date);
                break;
            default:
                printf("Wrong choice\n");
                break;
            }
        }
    }
}


void usr_is_present(char name[30], char roll[30], char role[30], char date[30]){
    char stored_id[30];
    char stored_roll[30];
    char line_length[150];
    char is_suspend;


    FILE *sus_usr;
    FILE *att_file;
    sus_usr = fopen("suspend_user.txt", "r");
    att_file = fopen("attendance.txt", "a+");

    if(sus_usr == NULL || att_file == NULL){
        printf("Something went wrong");
    }else{
        is_suspend = 1;
        while ( fgets( line_length, sizeof( line_length ), sus_usr ) != NULL ) {
            if( feof(sus_usr) ) break;
            fscanf(sus_usr,"id: %s roll: %s", stored_id, stored_roll);
            if(strcmp(roll, stored_roll) == 0){
                is_suspend = 0;
                printf("!This user is suspended\n\n");
            }
        }

        if(is_suspend == 0){
            fprintf(att_file, "name: %s roll: %s status: 0 date: %s\n", name, roll, date);
            printf("\n");
        }

        if(is_suspend == 1){
            fprintf(att_file, "name: %s roll: %s status: 1 date: %s\n", name, roll, date);
            printf("\n");
        }
    }

    fclose(sus_usr);
    fclose(att_file);
}

void usr_is_absent(char name[30], char roll[30], char role[30], char date[30]){
    int is_suspend;
    FILE *sus_usr;
    FILE *att_file;
    sus_usr = fopen("suspend_user.txt", "r");
    att_file = fopen("attendance.txt", "a+");

    if(sus_usr == NULL || att_file == NULL){
        printf("Something went wrong");
    }else{
        is_suspend = 1;
        if(is_suspend == 1){
            fprintf(att_file, "name: %s roll: %s status: 0 date: %s\n", name, roll, date);
            printf("\n");
        }
    }
    fclose(sus_usr);
    fclose(att_file);
}

void check_attendance_day_wise(char search_key[30]){
    char line_length[150];
    char date[12] = {0};
    char date2[12] = {0};
    char name[30];
    char roll[30];
    char status[150];
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%d-%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);

    FILE *att_file;
    att_file = fopen("attendance.txt", "r");
    if(att_file == NULL){
        printf("Something went wrong");
    }else{
        if(strcmp(search_key, "today") == 0){
            while(fgets(line_length, sizeof(line_length), att_file)){
                fscanf(att_file, "name: %s roll: %s status: %s date: %s", name, roll, status, date2);
                if(strcmp(date, date2) == 0){
                    if(strcmp(status, "1") == 0){
                        sprintf(status, "Present");
                    }else if(strcmp(status, "0") == 0){
                        sprintf(status, "Absent");
                    }
                    printf("name: %s roll: %s Status: %s\n", name, roll, status);
                }
            }
        }else{
            while(fgets(line_length, sizeof(line_length), att_file)){
                fscanf(att_file, "name: %s roll: %s status: %s date: %s", name, roll, status, date2);
                if(strcmp(search_key, date2) == 0){
                    if(strcmp(status, "1") == 0){
                        sprintf(status, "Present");
                    }else if(strcmp(status, "0") == 0){
                        sprintf(status, "Absent");
                    }
                    printf("name: %s roll: %s Status: %s\n", name, roll, status);
                }
            }
        }
    }

    fclose(att_file);
}

void fetch_all_att(){
    char line_length[150];
    char date2[12] = {0};
    char name[30];
    char roll[30];
    char status[150];
    int file_name[64];

    FILE *att_file;
    FILE *export_file;

    att_file = fopen("attendance.txt", "r");
    sprintf(file_name, "export-all-%d.txt", (int)time(NULL));
    export_file = fopen(file_name, "w");

    if(att_file == NULL || export_file == NULL){
        printf("Something went wrong");
    }else{

        while(fgets(line_length, sizeof(line_length), att_file)){
                fscanf(att_file, "name: %s roll: %s status: %s date: %s", name, roll, status, date2);
                    if(strcmp(status, "1") == 0){
                        sprintf(status, "Present");
                    }else if(strcmp(status, "0") == 0){
                        sprintf(status, "Absent");
                    }
                    printf("name: %s roll: %s Date: %s Status: %s\n", name, roll, date2, status);
                    fprintf(export_file, "name: %s roll: %s Date: %s Status: %s\n", name, roll, date2, status);
            }
    }

    fclose(att_file);
    fclose(export_file);
}

void search_att_with_roll(int inp_roll[10]){
    char line_length[150];
    char date2[12] = {0};
    char name[30];
    char roll[30];
    char status[150];
    int file_name[64];

    FILE *att_file;
    FILE *export_file;
    att_file = fopen("attendance.txt", "r");

    sprintf(file_name, "export-with_roll-%d.txt", (int)time(NULL));
    export_file = fopen(file_name, "w");

    if(att_file == NULL || export_file == NULL){
        printf("Something went wrong");
    }else{

        while(fgets(line_length, sizeof(line_length), att_file)){
                fscanf(att_file, "name: %s roll: %s status: %s date: %s", name, roll, status, date2);
                    if(strcmp(inp_roll, roll) == 0){
                        if(strcmp(status, "1") == 0){
                            sprintf(status, "Present");
                        }else if(strcmp(status, "0") == 0){
                            sprintf(status, "Absent");
                        }
                        printf("name: %s roll: %s Date: %s Status: %s\n", name, roll, date2, status);
                        fprintf(export_file, "name: %s roll: %s Date: %s Status: %s\n", name, roll, date2, status);
                    }
            }
    }

    fclose(att_file);
    fclose(export_file);
}
