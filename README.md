# cse102
Project Goal
-----------------------------------------------------------------------------------------------------------

→ Attendance Management System <br>
→ User creation(Admin/User)<br>
→ Admin will register new user with role admin or user.<br>
→ Admin will register attendance<br>
→ Admin will suspend user if need.<br>
→ Suspend user’s attendance will not be registered. They will get absent.<br>
→ Admin will able to disable suspension for any user.<br>
→ Admin or user will able to reset password with private reset key. Private key will be 	provided during register.<br>
→ User can log in to portal to check attendance and they can download a copy.<br>
→ Admin can check attendance daily, monthly with roll number.<br>
→ Admin can download attendance data in several way.<br>

Project Description
-----------------------------------------------------------------------------------------------------------


| Name     | Description      | Function / Function Prototype     | Is Library function     |
| ------------- | :------------- | -------- | --------: |
| Authentication           | This function will take user to the dashboard if they put correct information and every function will be called in this function.         | void auth();  | No |
| Registration           | This function will create user         | void reg(int *logged_in_check);  | No |
| Login           | This function will be used to logged in a user to dashboard | void login(int *logged_in_check);  | No |
| Reset Password           | This function will be used to reset a password        | void reset_pass();  | No |
| Suspend User           | This function will be used for suspension        | void suspend_user();  | No |
| Disable suspension           | This function will be used to disable suspension        | void disable_suspend(int t_line); | No |
| Register attendance           | This function will be used to register attendance         | void attendance_reg();  | No |
| Check a user is present or not           | This function can check a user is present or not         | void usr_is_present(char name[30], char roll[30], char role[30], char date[30]);  | No |
| Check a user is absent or not           | This function will check a user is absent or not         | vvoid usr_is_absent(char name[30], char roll[30], char role[30], char date[30]);  | No |
| Check attendance day wise           | This function will perform to check attendance day wise    |void check_attendance_day_wise(char search_key[30]);      | No |
| Fetch all attendance data           | This function will be used to fetch all data        | void fetch_all_att();  | No |
|Check attendance with roll number           | This function can check attendance with roll number           | void search_att_with_roll();          | No          |
| Get the current date          | This function will print the current date        | time();  | `Yes` |
| Compare 2 string          | This function will compare two data         | strcmp();  | `Yes` |
| Print data           | This function will print info         | printf();  | `Yes` |
| Scan data from file          | This function will get data from file         | fscanf();  | `Yes` |
| Print data to file         | This function will write data to file         | fprintf();  |  `Yes` |
| Read all data from file        | This function will be used to read file until new line is encountered or end of the file reached. | fgets();  | `Yes` |
| Local time        | This will uses the time pointed by timer to fill a tm structure with the values that represent the corresponding local time. The value of timer is broken up into the structure tm and expressed in the local time zone. | struct tm *localtime(const time_t *timer)  | `Yes` |

