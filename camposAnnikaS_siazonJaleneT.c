/************************************************************************************************************************
 This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts 
 learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The program 
 was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or otherwise 
 plagiarized the work of other students and/or persons.
                                                                                Annika Dominique S. Campos, ID 12206512
                                                                                Jalene Graciella T. Siazon, ID 12209244
*************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "camposAnnikaS_siazonJaleneT.h"

int 
main()
{
    printf("                       _               \n");
    printf("    /\\   /\\__ _  ___  /_\\  _ __  _ __  \n");
    printf("    \\ \\ / / _` |/ __|//_\\\\| '_ \\| '_ \\ \n");
    printf("     \\ V / (_| | (__/  _  \\|_) | |_) |\n");
    printf("      \\_/ \\__,_|\\___\\_/ \\_/ .__/| .__/ \n");
    printf("                          |_|   |_|    \n");

    int nInput = 0; 

    UsersInfo Users[MAX_USERS];
    int nNumUser = 0;

    AppInfo App[MAX_USERS];
    int nNumApp = 0;

    ChatBot Faq[MAX_USERS];
    int nNumFaq = 0; 
    readQnA(Faq, &nNumFaq);

    printf("\n%s",
    " -----------------------------------------\n"
    "|       VACCINATION REGISTRATION APP      |\n"
    " -----------------------------------------\n");
    MainMenu(nInput, Users, &nNumUser, App, &nNumApp, Faq, &nNumFaq);
    return 0;
}

/*
   This function is the program's Main Menu wherein the user could either go to the primary menu, or exit to terminate the program
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
MainMenu(int nInput, 
         UsersInfo Users[], 
         int* nNumUser, 
         AppInfo App[], 
         int* nNumApp, 
         ChatBot Faq[], 
         int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|               MAIN MENU                 |\n"
        "|                                         |\n"
        "|    [1] Vaccination Registration Menu    |\n"
        "|    [2] Data Management Menu             |\n"
        "|    [3] Exit                             |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            VacRegMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);// First primary menu
            break;
        case 2:
            DataManMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Second primary menu
            break;
        case 3:
            printf("\n%s",
            "         ----------------------\n"
            "        |  Exiting Program...  |\n"
            "         ----------------------\n\n"); // the program will terminate if the user exits in the Main Menu
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            MainMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   UserRegistration asks the users to input all necessary information about them. 
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @return tempUser which contains all the information input by user
*/
UsersInfo UserRegistration(UsersInfo Users[], 
                           int* nNumUser)
{
    UsersInfo tempUser; // Temporary variable to store the user's information
    int nUnique = 0; // Variable that identifies if UserID is nUnique
    int nDate1 = 0; // First Dose date Checker
    int nDate2 = 0; // Second Dose date Checker
    int nDate3 = 0; // Booster Dose date Checker
    
    // UserID
    while(nUnique == 0) // Loop to identify if UserID is nUnique
    {
        printf("* UserID: ");
        scanf("%10d", &tempUser.userID);

        // Condition to check if the input UserID is valid or nUnique
        if(isValidID(&tempUser.userID) == 0 || SearchUserID(Users, nNumUser, tempUser.userID) != -1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "| UserID has been taken! Please Try Again |\n"
            " -----------------------------------------\n\n");
        }
        else
        {
            nUnique = 1; // User ID is nUnique and valid
        }
    }

    // Password
    printf("* Password: ");
    GetPassword(tempUser.password); // Calling function that could turn input into asterisks
    tempUser.password[MAX_PASSWORD - 1] = '\0';
    
    // Name
    printf("\n* Name: ");
    scanf(" %20[^\n]", tempUser.name);

    // Address
    printf("* Address: ");
    scanf(" %30[^\n]", tempUser.address);

    // contact Number
    printf("* Contact Number: ");
    scanf("%lld", &tempUser.contact);


    //Sex
    printf("* Sex: ");
    scanf("%10s", tempUser.sex);

    // First Dose
    while(nDate1 == 0)
    {
        // dates below March 2021 is considered invalid (COVID-19 Vaccinations started at March 2021 in the Philippines)
        printf("\n* First Dose date");
        printf("\n  (YYYY-MM-DD): ");
        scanf("%11s", tempUser.firstDose);

        if(isValidDate(tempUser.firstDose) == 1)
        {
            nDate1 = 1; // Stops the loop
        }
        else
        {
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid date!   |\n"
            "           -------------------\n\n");
        }
    }

    printf("* First Dose Vaccine: ");
    scanf("%10s", tempUser.firstDoseVac);
    printf("* First Dose Location: ");
    scanf("%10s", tempUser.firstDoseLoc);

    printf("\n  ~The following questions are optional~\n");
    printf("  Please enter 'N/A' if you have no answer\n" );

    // Second Dose
    while(nDate2 == 0)
    {
        printf("\n* Second Dose date");
        printf("\n  (YYYY-MM-DD): ");
        scanf("%11s", tempUser.secondDose);

        // validating the date if the answer is not N/A
        if(strcmp(tempUser.secondDose, "N/A") != 0)
        {
            if(isValidDate(tempUser.secondDose) == 1)
            {
                nDate2 = 1;
            }
            else
            {
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid date!   |\n"
                "           -------------------\n\n");
            }
        }
        else
        {
            nDate2 = 1;
        }
    }

    printf("* Second Dose Vaccine: ");
    scanf("%10s", tempUser.secondDoseVac);
    printf("* Second Dose Location: ");
    scanf("%10s", tempUser.secondDoseLoc);
    
    // Booster Dose
    while(nDate3 == 0)
    {
        printf("\n* Booster Dose date");
        printf("\n  (YYYY-MM-DD): ");
        scanf("%11s", tempUser.boosterDose);
        
        // validating the date if the answer is not N/A
        if(strcmp(tempUser.boosterDose, "N/A") != 0)
        {
            if(isValidDate(tempUser.boosterDose) == 1)
            {
                nDate3 = 1;
            }
            else
            {
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid date!   |\n"
                "           -------------------\n\n");
            }
        }
        else
        {
            nDate3 = 1;
        }
    }
    
    printf("* Booster Dose Vaccine: ");
    scanf("%10s", tempUser.boosterDoseVac);
    printf("* Booster Dose Location: ");
    scanf("%10s", tempUser.boosterDoseLoc);

    return tempUser;
}

/*
   RegisterNewUser allow the user to register as a new user and add their information to the Users[]
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void RegisterNewUser(int nInput, 
                     UsersInfo Users[], 
                     int* nNumUser, 
                     AppInfo App[], 
                     int* nNumApp, 
                     ChatBot Faq[], 
                     int* nNumFaq)
{
    printf("\n%s",
    " -----------------------------------------\n"
    "|            USER REGISTRATION            |\n"
    " -----------------------------------------\n\n");

    // Checks if the maximum number of users is still not met
    if (*nNumUser < MAX_USERS) 
    {
        // New variable that stores the UserRegistration() function that asks the users for their information
        UsersInfo newUser = UserRegistration(Users, nNumUser);
        AddNewUser(newUser, Users, nNumUser); // Calls the function that adds the new user to the array and updates the new users number
        printf("\n%s",
        " -----------------------------------------\n"
        "|    You Have Successfully Registered!!   |\n"
        " -----------------------------------------\n\n");
        // Redirect to Vaccination Registration Menu
        VacRegMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
    } 
    else 
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|    Maximum Number of Users Reached!!!   |\n"
        " -----------------------------------------\n\n");
    }
}

/*
   VacRegMenu is one of the two primary menu options and is composed of four main sub-menu options.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
VacRegMenu(int nInput, 
           UsersInfo Users[], 
           int* nNumUser, 
           AppInfo App[], 
           int* nNumApp, 
           ChatBot Faq[], 
           int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|      VACCINATION REGISTRATION MENU      |\n"
        "|                                         |\n"
        "|    [1] User Registration                |\n"
        "|    [2] Vaccination Appointment          |\n"
        "|    [3] Chatbot FAQs                     |\n"
        "|    [4] Exit                             |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            RegisterNewUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // User Registration Menu
            break;
        case 2:
            VacRegLogIn(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Log-in option before accessing Vaccination Appointment Menu
            break;
        case 3:
            ChatBotMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // ChatBot FAQs
            break;
        case 4:
            MainMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);// Redirect to Main Menu
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            VacRegMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   VacRegLogIn is where other users who had previously registered before can log-in to proceed to Vaccination Appointment Menu.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return i (index) if user log-in successfully
   @return -1 if user fails to log-in 
   Pre-condition: input is a whole whole number and a non-negative value
*/
int
VacRegLogIn(int nInput, 
            UsersInfo Users[], 
            int* nNumUser, 
            AppInfo App[], 
            int* nNumApp, 
            ChatBot Faq[], 
            int* nNumFaq)
{
    int i; // UserID index
    int nTempID; // UserID input by user in the log-in menu
    int nIsCorrect = 0; // Flag if UserID or Password input is correct
    int nAttempts = 3; // nAttempts each user has in order to log-in
    char cTempPass[MAX_PASSWORD]; // Password input by user in the log-in menu

    while (nAttempts > 0 && !nIsCorrect)
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|               USER LOG-IN               |\n"
        " -----------------------------------------\n\n");

        printf("* UserID: ");
        scanf("%d", &nTempID);
        printf("* Password: ");
        GetPassword(cTempPass);
        cTempPass[MAX_PASSWORD - 1] = '\0';
        printf("\n");

        i = SearchUserID(Users, nNumUser, nTempID);

        if(SearchUserID(Users, nNumUser, nTempID) != -1) // If UserID is found
        {
            if (strcmp(Users[i].password, cTempPass) == 0) // Password match
            { 
                nIsCorrect = 1; // Updates flag if both UserID and password is correct
                printf("\n%s",
                "         ------------------------\n"
                "        |   Log-in Successful!   |\n"
                "         ------------------------\n\n");
                Users[i].loggedIn = 1; // User is logged in
            }
            else if (strcmp(Users[i].password, cTempPass) != 0) // Password does not match
            {
                nAttempts--; // nAttempts decreased 
                printf("\n%s",
                "       ----------------------------\n"
                "      |  (!) Invalid Password (!)  |\n"
                "       ----------------------------\n\n");
            }
        }
        else if(SearchUserID(Users, nNumUser, nTempID) == -1) // If UserID is not found
        {
            nAttempts--; // nAttempts decreased 
            printf("\n%s",
            "         ------------------------\n"
            "        |     User not found     |\n"
            "         ------------------------\n\n");
        }
    }
    if (nIsCorrect == 1) // If both the UserID and Password is correct
    {
        SuccessVacReg(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to Vaccination Registration Menu
        return i;
    } else 
    {
        return -1;
    }
}

/*
   SucessVacRegMenu shows once the user successfully logged-in. It will ask the user if they want to proceed to the Vaccination Appointment Menu or log-out.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
SuccessVacReg(int nInput, 
              UsersInfo Users[], 
              int* nNumUser, 
              AppInfo App[], 
              int* nNumApp, 
              ChatBot Faq[], 
              int* nNumFaq)
{
    int nUpdateUserIndex = GetUserIndex(Users, *nNumUser); // Checks if user is logged in

    printf("%s",
        " -----------------------------------------\n"
        "|  [1] Proceed to Vaccination Appointment |\n"
        "|  [2] Log-out                            |\n"
        " -----------------------------------------\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            VacApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Vaccination Appointment Menu
            break;
        case 2:
            // Updating user index so that the program can track the user who is currently logged in
            if (nUpdateUserIndex != -1)
            {
                Users[nUpdateUserIndex].loggedIn = 0; // Changing it to 0 to signify that the user will log out
                printf("\n%s",
                "      ----------------------------\n"
                "     |   Logged out successfully   |\n"
                "      ----------------------------\n\n");
            }
            VacRegMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to Main Menu once logged out
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            SuccessVacReg(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   VaccApp function is the Vacciination Appointment Menu where user can request for an appointment or manage their existing appointment.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
VacApp(int nInput, 
       UsersInfo Users[], 
       int* nNumUser, 
       AppInfo App[], 
       int* nNumApp, 
       ChatBot Faq[], 
       int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|         VACCINATION APPOINTMENT         |\n"
        "|                                         |\n"
        "|    [1] Appointment Request              |\n"
        "|    [2] Manage Appointment Menu          |\n"
        "|    [3] Exit Menu                        |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            RequestForApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Appointment Request Menu
            break;
        case 2:
            ManageApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Manage Appointment Menu
            break;
        case 3:
            SuccessVacReg(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect here when exiting
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            VacApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   AppRequest asks the user about the details of their vaccination appointment.
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @return tempApp which contains all the information input by user
   Pre-condition: 
*/
AppInfo AppRequest(AppInfo App[], 
                   int* nNumApp)
{
    AppInfo tempApp; // Temporary variable that stores the appointment details
    int nUnique = 0; // Variable that identifies if AppID is nUnique
    int nDate = 0; // date Checker
    int nTime = 0; // Time Checker

    // AppID
    while(nUnique == 0)
    {
        printf("* AppID: ");
        scanf("%10d", &tempApp.appID);

        // Condition to check if the inputted appID is valid or nUnique
        if(SearchAppID(App, nNumApp, tempApp.appID) != -1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|  AppID has been taken! Please Try Again |\n"
            " -----------------------------------------\n\n");
        }
        else
        {
            nUnique = 1;
        }
    }

    printf("* Name: ");
    scanf(" %20[^\n]", tempApp.name);
    printf("* Vaccination Center Location: ");
    scanf(" %10s", tempApp.location);
    printf("* Vaccination Brand: ");
    scanf(" %10s", tempApp.vaccine);

    // Appointment date
    while(nDate == 0)
    {
        // dates below April 2023 is considered  invalid 
        printf("* Date (YYYY-MM-DD): ");
        scanf(" %11s", tempApp.date);

        if(isValidAppDate(tempApp.date) == 1)
        {
            nDate = 1; // Stops the loop
        }
        else
        {
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid date!   |\n"
            "           -------------------\n\n");
        }
    }

    while(nTime == 0)
    {
        // 00:00 - 23:59
        printf("* Time (24-hour format): ");
        scanf(" %6s", tempApp.time);

        if(isValidTime(tempApp.time) == 1)
        {
            nTime = 1; // Stops the loop
        }
        else
        {
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Time!   |\n"
            "           -------------------\n\n");
        }
    }
    
    printf("* Dose: ");
    scanf(" %10s", tempApp.dose);

    return tempApp;
}

/*
   RequestForApp function checks if the user logged in has already placed an appointment before letting it request for an appointment
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void RequestForApp(int nInput, 
                   UsersInfo Users[], 
                   int* nNumUser, 
                   AppInfo App[], 
                   int* nNumApp, 
                   ChatBot Faq[], 
                   int* nNumFaq)
{
    int tracker = -1;

    if(IsLoggedIn(Users, *nNumUser)) // check if a user is already logged in
    {
        tracker = GetUserIndex(Users, *nNumUser); // get the index of the logged in user
        printf("Logged in as User %d\n", Users[tracker].userID);
    }

    if(tracker != -1)
    {
        if (Users[tracker].requested == 1) 
        {
            printf("\n%s",
            "   ------------------------------------\n"
            "  | Sorry, you have already  requested |\n" 
            "  |          for an appointment        |\n"
            "   ------------------------------------\n\n");
        } 
        else 
        {
             printf("\n%s",
            " -----------------------------------------\n"
            "|            APPOINTMENT REQUEST          |\n"
            " -----------------------------------------\n\n");

            AppInfo newApp = AppRequest(App, nNumApp);
            AddNewApp(newApp, App, nNumApp, Users[tracker].userID);
            Users[tracker].requested = 1;

            printf("\n%s",
            "   ------------------------------------\n"
            "  |  You have successfully  requested  |\n" 
            "  |           an appointment!          |\n"
            "   ------------------------------------\n\n");
        }
    }

    if (*nNumApp > MAX_USERS) 
    {
        printf("\n%s",
        " ------------------------------------------------\n"
        "|    Maximum Number of Appointments Reached!!!   |\n"
        " ------------------------------------------------\n\n");
    }

    printf("Redirecting to Vaccination Registration Menu\n\n");
    VacApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
}


/*
   ModifyApp asks for the details that will be modified on the Manage Appointment Menu 
   @param currentApp - contains the current appointment details
   @return newApp - the details that was modified
   Pre-condition: not yet final
*/
AppInfo ModifyApp(AppInfo currentApp)
{
    AppInfo newApp = currentApp; // Stores the newly modified value to the current value
    int date = 0; // date Checker
    int time = 0; // Time Checker

    // Appointment date
    while(date == 0)
    {
        // dates below April 2023 is considered  invalid 
        printf("* Reschedule the date (YYYY-MM-DD): ");
        scanf("%11s", newApp.date);

        if(isValidAppDate(newApp.date) == 1)
        {
            date = 1; // Stops the loop
        }
        else
        {
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid date!   |\n"
            "           -------------------\n\n");
        }
    }

    while(time == 0)
    {
        // 00:00 - 23:59
        printf("* Reschedule the time (24-hour format): ");
        scanf("%6s", newApp.time);

        if(isValidTime(newApp.time) == 1)
        {
            time = 1; // Stops the loop
        }
        else
        {
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Time!   |\n"
            "           -------------------\n\n");
        }
    }

    printf("* Change Vaccination Center Location: ");
    scanf("%10s", newApp.location);
 
    printf("* Change Preferred Vaccination Brand: ");
    scanf("%10s", newApp.vaccine);

    return newApp;
}

/*
   ManageApp function is the Manage Appointment Menu wherein the users can cancel their appointment or modify the appointment details (date, time, location, vaccine)
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void ManageApp(int nInput, 
               UsersInfo Users[], 
               int* nNumUser, 
               AppInfo App[], 
               int* nNumApp, 
               ChatBot Faq[], 
               int* nNumFaq)
{
    int i;
    int userID; 
    int AppIndex; // Index of the appointment in App[] that belongs to the currently logged in user
    int UserIndex = GetUserIndex(Users, *nNumUser); // Index of the user who is currently logged in
    int flag = 0; // Flag for loop
    int flag2 = 0; // Flag for loop

    if(IsLoggedIn(Users, *nNumUser)) // if user is logged in, do this condition
    {
        userID = Users[UserIndex].userID; // user at index in the array
        AppIndex = -1; // for tracking

        // checks if the currently logged in userID is the same as the userID of the appointment
        for(i = 0; i < *nNumApp && flag2 == 0; i++)
        {
            if(App[i].userID == userID)
            {
                AppIndex = i; // setting AppIndex to the index of the appointment  int array
                flag2 = 1;
            }
        }

        // if matching appointment was found for the specified user ID and the user has already made an appointment request
        if (AppIndex != -1 && Users[UserIndex].requested == 1)
        {
            printf("%s",
                " -----------------------------------------\n"
                "|            MANAGE APPOINTMENT          |\n"
                " ----------------------------------------\n\n");

            printf("\nHere are your current appointment details: \n\n");
            printf("  * AppID: %d\n", App[AppIndex].appID);
            printf("  * Name: %s\n", App[AppIndex].name);
            printf("  * Location: %s\n", App[AppIndex].location);
            printf("  * Vaccine: %s\n", App[AppIndex].vaccine);
            printf("  * date: %s\n", App[AppIndex].date);
            printf("  * Time: %s\n", App[AppIndex].time);
            printf("  * Dose: %s\n", App[AppIndex].dose);
            printf("\n\n");

            while(flag != 1)
            {
                printf("%s",
                "__________________________________________\n"
                "|        What would you like to do?       |\n"
                "|                                         |\n"
                "|    [1] Cancel Appointment               |\n"
                "|    [2] Edit Appointment Details         |\n"
                "|    [3] Save Current Changes and Exit    |\n"
                "|_________________________________________|\n\n");

                printf("Input Choice: ");
                scanf("%d", &nInput);

                switch(nInput)
                {
                case 1:
                    printf("\n%s",
                    " ---------------------------------------\n"
                    "|    Are you sure you want to cancel    |\n"
                    "|            your appointment?          |\n"
                    "|                                       |\n"
                    "|         [1] Yes, I am Sure            |\n"
                    "|         [2] Cancel Deletion           |\n"
                    " ---------------------------------------\n\n");

                    printf("Input Choice: ");
                    scanf("%d", &nInput);

                    if(nInput == 1)
                    {
                        // loop starts from AppIndex and iterates up to the second last element of the array
                        for(i = AppIndex; i < *nNumApp - 1; i++)
                        {
                            App[i] = App[i + 1]; // move each in the App array one index to the left to remove the appointment at the AppIndex in the array
                        }
                        (*nNumApp)--; //  decrement number of appointment since an appointment has been removed
                        Users[UserIndex].requested = 0; // user has no longer appoint request
                        printf("\n%s",
                        " ---------------------------------------\n"
                        "| Cancelling your Appointment Request...|\n"
                        " ---------------------------------------\n\n");
                    }
                    else if(nInput == 2)
                    {
                        printf("\n%s",
                        " -----------------------------------------\n"
                        "|   Appointment Cancellation Cancelled!  |\n"
                        " -----------------------------------------\n\n");
                    }
                    break;
                case 2:
                    printf("\nPlease Enter Your New Appointment Details:\n\n");
                    AppInfo newApp = ModifyApp(App[AppIndex]); // calling the ModifyApp where the details will be modified
                    newApp.userID = userID; // setting appointment to current user
                    App[AppIndex] = newApp; // strong updated information to the array
                    Users[UserIndex].requested = 1; // user has requested
                    printf("\n%s",
                    "   -------------------------------------\n"
                    "  | Updating your Appointment Details...|\n"
                    "   -------------------------------------\n\n");
                    break;
                case 3:
                    flag = 1;
                    printf("\n%s",
                    "          -------------------\n"
                    "         |   Changes Saved   |\n" 
                    "          -------------------\n\n");
                    VacApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to Vaccination Appointment Menu
                    break;
                default:
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
                }
            }
        }
        else
        {
            printf("\n%s",
                "   ------------------------------------\n"
                "  |     You do not have any previous    |\n"
                "  |      appointments to manage.        |\n"
                "   ------------------------------------\n\n");
                VacApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to Vaccination Appointment Menu
        }
    }
}

/*
   ChatBotMenu gives the user to ask questions or to exit
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
ChatBotMenu(int nInput, 
            UsersInfo Users[], 
            int* nNumUser, 
            AppInfo App[], 
            int* nNumApp, 
            ChatBot Faq[], 
            int* nNumFaq)
{
    printf("\n%s",
    " _________________________________________\n"
    "|               CHATBOT (FAQs)            |\n"
    "|                                         |\n"
    "|    [1] Ask Questions                    |\n"
    "|    [2] Exit                             |\n"
    "|_________________________________________|\n\n");
   
    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            ChatBotAI(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 2:
            VacRegMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            ChatBotMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   readChatFile function reads the exisiting file for ChatBot. 
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct that holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
int readChatFile(char* filename, 
                 ChatBot* faqs, 
                 int* nNumFaqs) 
{
    char line[MAX_QUESTION_LENGTH + MAX_ANSWER_LENGTH];
    int ctr = 0;
    FILE* fp;
    
    fp = fopen("TempChat.txt", "r");

    if (fp == NULL) {
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Remove the newline character at the end of the string
        line[strlen(line) - 1] = '\0';

        // Check if the line is a question or an answer
        if (ctr % 2 == 0) { // 
            strcpy(faqs[ctr / 2].question, line);
        } else {
            strcpy(faqs[ctr / 2].answer, line);
        }

        ctr++;
    }

    *nNumFaqs = ctr / 2;

    fclose(fp);
    return 1;
}

/*
   ChatBotAI function allows the user to ask to a simple chatbot related to COVID-19. 
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct that holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
void
ChatBotAI(int nInput, 
          UsersInfo Users[], 
          int* nNumUser, 
          AppInfo App[], 
          int* nNumApp, 
          ChatBot Faq[], 
          int* nNumFaq)
{
    char ques[MAX_QUESTION_LENGTH];
    char filename[MAX_QUESTION_LENGTH];
    int nNumFaqs;
    int i;
    int bflag = 0;

    printf("\n%s",
        "       -------------------------------\n"
        "      | Welcome to VacApp Chabot AI!  |\n"
        "       --------------------------------\n\n");

    ChatBot* faqs = malloc(MAX_QUESTIONS * sizeof(ChatBot)); // Allocate memory for the faqs array

    if (faqs == NULL) 
    {
        printf("\n(!) Error allocating memory for the FAQs array (!)\n");
    }

    else if (!readChatFile(filename, faqs, &nNumFaqs)) 
    { // Pass the Faq[] to the readChatfile()
        printf("\n     (!) Error reading FAQs from file (!)%s\n", filename);
        free(faqs); // Free the memory allocated for the faqs array
        faqs = NULL;
    }

    if(faqs != NULL)
    {
        printf("\n    Hi there! How can I assist you today?: \n\n");
        while (!bflag) 
        {
            int found = 0; // initialize found
            printf("\n  Enter your question (type 'exit' to quit):\n\n ");
            printf("    * ");
            fflush(stdin); // clear input buffer
            fgets(ques, MAX_QUESTION_LENGTH, stdin); // store input in the ques[]

            ques[strlen(ques) - 1] = '\0'; // replace '\n' with null terminator

            // Check if the user wants to exit the chatbot
            if (strcmp(ques, "exit") == 0)
            {
                bflag = 1; // user exit
                VacRegMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            }
            else 
            {
                // Search  question in the Faq[]
                for (i = 0; i < nNumFaqs && !found; i++) 
                {
                    if (strcmp(ques, faqs[i].question) == 0) // question found
                    {
                        printf("\n     >> %s\n", faqs[i].answer); // display answer
                        found = 1;
                    }
                }

                if (!found)  // question not found
                printf("\n%s",
                "  ------------------------------------------\n"
                " |  Sorry, I don't know the answer to your  |\n"
                " |  question. Please type another question. |\n"
                "  ------------------------------------------\n");
           }
        }
        // Free the memory allocated for the Faq[]
        free(faqs);
        faqs = NULL;
    }
}

/*
   This function is a menu wherein the user/admin will be given an option to log-in to proceed in the Data Management Menu or exit
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
DataManMenu(int nInput, 
            UsersInfo Users[], 
            int* nNumUser, 
            AppInfo App[], 
            int* nNumApp, 
            ChatBot Faq[], 
            int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|           DATA MANAGEMENT MENU          |\n"
        "|                                         |\n"
        "|    [1] Log-in                           |\n"
        "|    [2] Exit                             |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            DataManLogIn(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Log-in option to access Data Management Menu
            break;
        case 2:
            MainMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to Main Menu 
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            DataManMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   Log-in Menu that will redirect those who successfully logged-in in theData Management Menu
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void DataManLogIn(int nInput, 
                  UsersInfo Users[], 
                  int* nNumUser, 
                  AppInfo App[], 
                  int* nNumApp, 
                  ChatBot Faq[], 
                  int* nNumFaq)
{
    int nIsCorrect = 0; // Flag
    int nAttempts = 3; // Number of nAttempts the user has to log-in

    int AdminID = 1234; // AdminID
    char AdminPass[MAX_PASSWORD] = "adminLog"; // Admin Password

    int tempAdminID; // AdminID input by user
    char cTempPass[MAX_PASSWORD]; // Password input by user

    while (nAttempts > 0 && !nIsCorrect)
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|              ADMIN LOG-IN               |\n"
        " -----------------------------------------\n\n");

        printf("* AdminID: ");
        scanf("%d", &tempAdminID);
        printf("* Password: ");
        GetPassword(cTempPass);

        printf("\n");

        if(tempAdminID == AdminID) // If AdminID matched
        {
            if(strcmp(cTempPass, AdminPass) == 0) // If password matched
            {
                nIsCorrect = 1;
                printf("\n%s",
                "         ------------------------\n"
                "        |   Log-in Successful!   |\n"
                "         ------------------------\n\n");
                SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to this menu
            }
            else // If wrong password
            {
                nAttempts--; // Decrease nAttempts
                printf("\n%s",
                "   -------------------------------------\n"
                "  | Unauthorized Accesss is not allowed |\n"
                "   -------------------------------------\n\n");
            }
        }
        else // Invalid AdminID
        {
            nAttempts--;
            printf("\n%s",
                "   -------------------------------------\n"
                "  | Unauthorized Accesss is not allowed |\n"
                "   -------------------------------------\n\n");
        }
    }
}

/*
   SuccessDataManMenu is the Data Management Menu which is one of the two primary menus. It is for the administrator who will manage the Vaccination Registration with Chatbot Application.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void SuccessDataMan(int nInput, 
                    UsersInfo Users[], 
                    int* nNumUser, 
                    AppInfo App[], 
                    int* nNumApp, 
                    ChatBot Faq[], 
                    int* nNumFaq)
{
        printf("%s",
        "__________________________________________\n"
        "|           DATA MANAGEMENT MENU          |\n"
        "|                                         |\n"
        "|    [1] User                             |\n"
        "|    [2] Appointment                      |\n"
        "|    [3] Chatbot                          |\n"
        "|    [4] Export                           |\n"
        "|    [5] Import                           |\n"
        "|    [6] Exit                             |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // User Menu
            break;
        case 2:
            Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Appointment Menu
            break;
        case 3:
            ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Chatbot Menu
            break;
        case 4:
            Export(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Export Menu
            break;
        case 5:
            Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Import Meny
            break;
        case 6:
            ExitMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Save all data into a file and redirect to Main Menu
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid nInput!  |\n"
            "           -------------------\n\n");
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); //Call recursively so the program won't terminate when the nInput is invalid
            break;
        }
}
/*
   User function allows the administrator to add,view, edit and delete the user details.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
User(int nInput, 
     UsersInfo Users[], 
     int* nNumUser, 
     AppInfo App[], 
     int* nNumApp, 
     ChatBot Faq[], 
     int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|                  USER                   |\n"
        "|                                         |\n"
        "|    [1] Add New User                     |\n"
        "|    [2] View All Users                   |\n"
        "|    [3] Edit User Details                |\n"
        "|    [4] Delete User                      |\n"
        "|    [5] Exit                             |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            AddUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 2:
            ViewUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 3:
            EditUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 4:
            DeleteUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 5:
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); //Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}


/*
   AddUser function allows the administrator to add new user details
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void 
AddUser(int nInput, 
        UsersInfo Users[], 
        int* nNumUser, 
        AppInfo App[], 
        int* nNumApp, 
        ChatBot Faq[], 
        int* nNumFaq)
{
    int flag = 0;

    while(flag != 1)
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|              ADD NEW USER               |\n"
        " -----------------------------------------\n");

        // new variable that stores the UserRegistration() function that asks the users for their information
        UsersInfo newUser = UserRegistration(Users, nNumUser);

        // checks if the maximum number of users is still not met
        if (*nNumUser < MAX_USERS) 
        {
            AddNewUser(newUser, Users, nNumUser);
            printf("\n%s",
            " -----------------------------------------\n"
            "|          Successfully added a           |\n" 
            "|                new user!                |\n"
            "|                                         |\n"
            "|        [1] Add another user             |\n"
            "|        [2] Go back to User Menu         |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag = 1;
                    AddUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                case 2:
                    flag = 1;
                    User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
            }
        } 
        else 
        {
            flag = 1;
            printf("\n%s",
            " -----------------------------------------\n"
            "|    Maximum number of users reached!!!   |\n"
            " -----------------------------------------\n\n");
            // redirect to this menu
            User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
        }
    }
}

/*
   ViewUser function allows the administrator to view all users arranged by User ID.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/

void ViewUser(int nInput, 
              UsersInfo Users[], 
              int* nNumUser, 
              AppInfo App[], 
              int* nNumApp, 
              ChatBot Faq[], 
              int* nNumFaq)
{
    int i; 
    int j;
    UsersInfo tempUser;

    // Using bubble sort to sort the array of users based on User ID 
    for (i = 0; i < *nNumUser - 1; i++) 
    {
        for (j = 0; j < *nNumUser - i - 1; j++) 
        {
            if (Users[j].userID > Users[j + 1].userID) 
            {
                // Swapping the users
                tempUser = Users[j];
                Users[j] = Users[j + 1];
                Users[j + 1] = tempUser;
            }
        }
    }

    printf("\n%s\n",
    " -----------------------------------------\n"
    "|             VIEW ALL USERS              |\n"
    " -----------------------------------------\n");

    // Loop through all the users and print their details
    for (i = 0; i < *nNumUser; i++) 
    {
        printf("============ USER INFORMATION ============\n\n");
        printf("User ID:                %d\n", Users[i].userID);
        printf("Password:               %s\n", Users[i].password);
        printf("Name:                   %s\n", Users[i].name);
        printf("Address:                %s\n", Users[i].address);
        printf("Contact Number:         0%lld\n", Users[i].contact);
        printf("Sex:                    %s\n\n", Users[i].sex);
        printf("========= FIRST DOSE INFORMATION =========\n\n");
        printf("First Dose Date: \t%s\n", Users[i].firstDose);
        printf("First Dose Vaccine: \t%s\n", Users[i].firstDoseVac);
        printf("First Dose Location: \t%s\n\n", Users[i].firstDoseLoc);
        printf("======== SECOND DOSE INFORMATION =========\n\n");
        printf("Second Dose Date: \t%s\n", Users[i].secondDose);
        printf("Second Dose Vaccine: \t%s\n", Users[i].secondDoseVac);
        printf("Second Dose Location: \t%s\n\n", Users[i].secondDoseLoc);
        printf("======== BOOSTER DOSE INFORMATION =========\n\n");
        printf("Booster Dose Date: \t%s\n", Users[i].boosterDose);
        printf("Booster Dose Vaccine: \t%s\n", Users[i].boosterDoseVac);
        printf("Booster Dose Location: \t%s\n\n", Users[i].boosterDoseLoc);
        printf("===========================================\n");
        printf("\n\n");
    }
    User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to User Menu after viewing all users
}


/*
   EditUser function allows the administrator to edit new user details.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: inputis a whole whole number and a non-negative value
*/
void 
EditUser(int nInput, 
         UsersInfo Users[], 
         int* nNumUser,
         AppInfo App[], 
         int* nNumApp, 
         ChatBot Faq[], 
         int* nNumFaq)
{
    int editUser;
    int find;

    // Flag for loop
    int flag1 = 0;
    int flag2 = 0;

    printf("\nUserID you want to edit the details for: ");
    scanf("%d", &editUser);

    // Checks if UserID exists. If it does, the user's index will be assigned to find
    find = SearchUserID(Users, nNumUser, editUser); 

    // Compares it to the inputted UserID  
    if(Users[find].userID == editUser) // If UserID matches
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|            EDIT USER DETAILS            |\n"
        " -----------------------------------------\n");
        Users[find] = UserRegistration(Users, nNumUser); // Calling UserRegistration function to update the details
        while(flag1 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|    User details updated successfully!   |\n"
            "|                                         |\n"
            "|    [1] Edit another UserID details      |\n"
            "|    [2] Go back to User Menu             |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag1 = 1;
                    EditUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                case 2:
                    flag1 = 1;
                    User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
                break;
            }
        }
    }
    else // If UserID does not match
    {
        while(flag2 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|           UserID DOES NOT EXIST         |\n"
            "|                                         |\n"
            "|             [1] Try Again               |\n"
            "|             [2] Exit Menu               |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag2 = 1;
                    EditUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                case 2:
                    flag2 = 1;
                    User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
               break;
            }
        }
    }

}

/*
   DeleteUser function allows the administrator to delete user details from the text file.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void 
DeleteUser(int nInput, 
           UsersInfo Users[], 
           int* nNumUser, 
           AppInfo App[], 
           int* nNumApp, 
           ChatBot Faq[], 
           int* nNumFaq)
{
    int i;
    int deleteUser;
    int find;

    // Flags for while loop when input is invalid
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;

    printf("\nUserID you want to delete the details for: ");
    scanf("%d", &deleteUser);

    // Checks if UserID exists. If it does, the user's index will be assigned to find
    find = SearchUserID(Users, nNumUser, deleteUser); 

    // Compares it to the inputted UserID  
    if(Users[find].userID == deleteUser) // If UserID matches
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|               DELETE USER               |\n"
        " -----------------------------------------\n\n");
        while(flag1 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|     Are you sure you want to delete     |\n"
            "|           this User's details?          |\n"
            "|                                         |\n"
            "|          [1] Yes, I am sure             |\n"
            "|          [2] Cancel Deletion            |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);
            switch(nInput)
            {
                case 1:
                flag1 =1;
                    for(i = find; i < *nNumUser - 1; i++)
                    {
                        // loop starts from find and iterates up to the second last element of the array
                        Users[i] = Users[i+1]; // delete user by shifting elements one index to the left
                    }
                    (*nNumUser)--; // decrement number of users since a user has been deleted

                    while(flag2 != 1)
                    {
                         printf("\n%s",
                        " -----------------------------------------\n"
                        "|    User details deleted successfully!   |\n"
                        "|                                         |\n"
                        "|    [1] Delete another UserID details    |\n"
                        "|    [2] Go back to User Menu             |\n"
                        " -----------------------------------------\n\n");

                        printf("Input Choice: ");
                        scanf("%d", &nInput);

                        switch(nInput)
                        {
                            case 1:
                                flag2 = 1;
                                DeleteUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Calling the function recursively to repeat
                                break;
                            case 2:
                                flag2 = 1;
                                User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to User Menu
                                break;
                            default:
                            printf("\n%s",
                            "           -------------------\n"
                            "          |   Invalid Input!  |\n"
                            "           -------------------\n\n");
                        }
                    }
                break;
                case 2:
                    flag1 = 1;
                        printf("\n%s",
                        " -----------------------------------------\n"
                        "|     User details deletion cancelled!    |\n"
                        "|      Redirecting to to User Menu...     |\n"
                        " -----------------------------------------\n\n");
                        User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                    printf("\n%s",
                   "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
            }
        }
    }
    // If UserID does not match
    else
    { 
        while(flag3 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|           UserID DOES NOT EXIST         |\n"
            "|                                         |\n"
            "|             [1] Try Again               |\n"
            "|             [2] Exit Menu               |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag3 = 1;
                    DeleteUser(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Calls this function recursively
                    break;
                case 2:
                    flag3 = 1;
                    User(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirect to User Menu
                    break;
                default:
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
                break;
            }
        }
    }
}

/*
   Appointment function allows the administrator to add,view, edit and delete the appointments
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void
Appointment(int nInput, 
           UsersInfo Users[], 
           int* nNumUser, 
           AppInfo App[], 
           int* nNumApp, 
           ChatBot Faq[], 
           int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|               APPOINTMENT               |\n"
        "|                                         |\n"
        "|    [1] Add New Appointment              |\n"
        "|    [2] View All Appointment             |\n"
        "|    [3] Edit User Appointment            |\n"
        "|    [4] Delete Appointment               |\n"
        "|    [5] Exit                             |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            AddApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 2:
            ViewApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 3:
            EditApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 4:
            DeleteApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 5:
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); //Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}

/*
   AddApp function allows the administrator to add new appointment as many as they want. 
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void 
AddApp(int nInput, 
       UsersInfo Users[], 
       int* nNumUser, 
       AppInfo App[], 
       int* nNumApp, 
       ChatBot Faq[], 
       int* nNumFaq)
{
    int adminID = 1234; // admin ID will always be 1234
    int flag = 0; // flag for invalid input

    while(flag != 1)
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|           ADD NEW APPOINTMENT           |\n"
        " -----------------------------------------\n\n");
        AppInfo newApp = AppRequest(App, nNumApp); // Calling App Request to add appointment details
        AddNewApp(newApp, App, nNumApp, adminID); // Add new appointment but instead of UserID, AdminID will be stored

        if (*nNumApp < MAX_USERS) 
        {
        printf("\n%s",
        " -----------------------------------------\n"
        "|          Successfully added a           |\n" 
        "|            new appointment!             |\n"
        "|                                         |\n"
        "|     [1] Add another appointment         |\n"
        "|     [2] Go back to Appointment Menu     |\n"
        " -----------------------------------------\n\n");
        printf("Input Choice: ");
        scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag = 1;
                    AddApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Calling this function recursively
                    break;
                case 2:
                    flag = 1;
                    Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirecting to Appointment Menu
                    break;
                default:
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
           }
        }
        else
        {
            printf("\n%s",
            " ------------------------------------------------\n"
            "|    Maximum Number of Appointments Reached!!!   |\n"
            " ------------------------------------------------\n\n");
        }
    }
}

/*
   ViewApp function allows the administrator to view all appointments by users.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void 
ViewApp(int nInput, 
        UsersInfo Users[], 
        int* nNumUser, 
        AppInfo App[], 
        int* nNumApp, 
        ChatBot Faq[], 
        int* nNumFaq)
{
    int i; 
    int j;
    AppInfo tempUser;

    // Using bubble sort to sort the array of users based on User ID 
    for (i = 0; i < *nNumApp - 1; i++) 
    {
        for (j = 0; j < *nNumApp - i - 1; j++) 
        {
            if (App[j].userID > App[j + 1].userID) 
            {
                // Swapping the users
                tempUser = App[j];
                App[j] = App[j + 1];
                App[j + 1] = tempUser;
            }
        }
    }

    printf("\n%s",
    " -----------------------------------------\n"
    "|           VIEW ALL APPOINTMENT          |\n"
    " -----------------------------------------\n\n");
    for (i = 0; i < *nNumApp; i++) 
    {
        printf("==========================================\n\n");
        printf("AppID: %d\n", App[i].appID);
        printf("UserID: %d\n", App[i].userID);
        printf("Name: %s\n", App[i].name);
        printf("City Location: %s\n", App[i].location);
        printf("Vaccine: %s\n", App[i].vaccine);
        printf("Date: %s\n", App[i].date);
        printf("Time: %s\n", App[i].time);
        printf("Dose: %s\n\n", App[i].dose);
        printf("==========================================\n\n");
        printf("\n");
    }
    Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Redirecting to Appointment Menu afterviewing all details
}

/*
   EditApp function allows the administrator to edit appointment details.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole whole number and a non-negative value
*/
void 
EditApp(int nInput, 
        UsersInfo Users[], 
        int* nNumUser, 
        AppInfo App[], 
        int* nNumApp, 
        ChatBot Faq[], 
        int* nNumFaq)
{
    int editApp;
    int find;
    int flag1 = 0;
    int flag2 = 0;

    printf("\nAppID you want to edit the details for: ");
    scanf("%d", &editApp);
    
    // Checks if AppID exists. If it does, the AppID's index will be assigned to find
    find = SearchAppID(App, nNumApp, editApp);

    // Compares it to the inputted AppID
    if(App[find].appID == editApp) // If AppID matches
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|             EDIT APPOINTMENT            |\n"
        " -----------------------------------------\n\n");
        
        AppInfo newApp = AppRequest(App, nNumApp); // New struct that will store the edited details

        // Replacing the current details with the edited  details
        App[find].appID = newApp.appID;
        strcpy(App[find].name, newApp.name);
        strcpy(App[find].location, newApp.location);
        strcpy(App[find].vaccine, newApp.vaccine);
        strcpy(App[find].date, newApp.date);
        strcpy(App[find].time, newApp.time);
        strcpy(App[find].dose, newApp.dose);

        while(flag1 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|       Appointment details updated       |\n"
            "|              successfully!              |\n"
            "|                                         |\n"
            "|    [1] Edit another appID details       |\n"
            "|    [2] Go back to Appointment Menu      |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);
            switch(nInput)
            {
                case 1:
                    flag1 = 1;
                    EditApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                case 2:
                    flag1 = 1;
                    Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
                break;
            }
        }
    }
    else // If AppID doesn't match
    {
        while(flag2 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|           AppID DOES NOT EXIST          |\n"
            "|                                         |\n"
            "|             [1] Try Again               |\n"
            "|             [2] Exit Menu               |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag2 = 1;
                    EditApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                case 2:
                    flag2 = 1;
                    Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
               break;
            }
        }
    }
}

/*
   DeleteApp function allows the administrator to cancel an appointment.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole number and a non-negative value
*/
void DeleteApp(int nInput, 
               UsersInfo Users[], 
               int* nNumUser, 
               AppInfo App[], 
               int* nNumApp, 
               ChatBot Faq[], 
               int* nNumFaq)
{
    int i, j;
    int userID;
    int deleteApp;
    int find;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;

    printf("\nAppID you want to delete: ");
    scanf("%d", &deleteApp);

    // Checks if AppID exists. If it does, the AppID's index will be assigned to find
    find = SearchAppID(App, nNumApp, deleteApp);

    // Compares it to the inputted AppID
    if(App[find].appID == deleteApp) // If AppID matches
    {
        printf("\n%s",
        " -----------------------------------------\n"
        "|             DELETE APPOINTMENT          |\n"
        " -----------------------------------------\n\n");
        while(flag1 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|     Are you sure you want to delete     |\n"
            "|           this Appointment?             |\n"
            "|                                         |\n"
            "|          [1] Yes, I am sure             |\n"
            "|          [2] Cancel Deletion            |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);
            switch(nInput)
            {
                case 1:
                    flag1 = 1;
                    for(i = find; i < *nNumApp - 1; i++)
                    {
                        // loop starts from find and iterates up to the second last element of the array
                        App[i] = App[i+1]; // delete appointment by shifting elements one index to the left
                    }
                    (*nNumApp)--; // decrement number of appointments since am appointment has been deleted
                    
                    // finding the user whose appointment is getting deleted
                    userID = App[find].userID;
                    
                    for (j = 0; j < *nNumUser && !flag4; j++)
                    {
                        if (Users[j].userID == userID)
                        {
                            Users[j].requested = 0;
                            flag4 = 1;
                        }
                    }

                    while(flag2 != 1)
                    {
                        printf("\n%s",
                        " -----------------------------------------\n"
                        "|    Appointment deleted successfully!    |\n"
                        "|                                         |\n"
                        "|  [1] Delete another AppID Appointment   |\n"
                        "|  [2] Go back to Appointment Menu        |\n"
                        " -----------------------------------------\n\n");
                        printf("Input Choice: ");
                        scanf("%d", &nInput);

                        switch(nInput)
                        {
                            case 1:
                                flag2 = 1;
                                DeleteApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                                break;
                            case 2:
                                flag2 = 1;
                                Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                                break;
                            default:
                            printf("\n%s",
                            "           -------------------\n"
                            "          |   Invalid Input!  |\n"
                            "           -------------------\n\n");
                        }
                    }
                    break;
                    case 2:
                    flag1 = 1;
                        printf("\n%s",
                        " -----------------------------------------\n"
                        "|     Appointment deletion cancelled!    |\n"
                        "|  Redirecting to to Appointment Menu... |\n"
                        " -----------------------------------------\n\n");
                        Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                    printf("\n%s",
                   "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
            }
        }
    }
    else
    { 
        while(flag3 != 1)
        {
            printf("\n%s",
            " -----------------------------------------\n"
            "|           AppID DOES NOT EXIST         |\n"
            "|                                         |\n"
            "|             [1] Try Again               |\n"
            "|             [2] Exit Menu               |\n"
            " -----------------------------------------\n\n");
            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    flag3 = 1;
                    DeleteApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                case 2:
                    flag3 = 1;
                    Appointment(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
                    break;
                default:
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
                break;
            }
        }
    }
}

/*
   ChatBotMod function allows the admin  to add,view, edit and delete questions and answers.
   @param int nInput - the users input everytime the program asks what to do
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUser  - stores the number of users in the program
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param ChatBot Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param int* nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: input is a whole number and a non-negative value
*/
void
ChatBotMod(int nInput, 
           UsersInfo Users[], 
           int* nNumUser, 
           AppInfo App[], 
           int* nNumApp, 
           ChatBot Faq[], 
           int* nNumFaq)
{
    printf("%s",
        "__________________________________________\n"
        "|                 CHATBOT                 |\n"
        "|                                         |\n"
        "|   [1] Add New Question and Answer       |\n"
        "|   [2] View All Questions and Answers    |\n"
        "|   [3] Edit User Questions and Answers   |\n"
        "|   [4] Delete Questions and Answers      |\n"
        "|   [5] Exit                              |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput) 
    {
        case 1:
            AddQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 2:
            ViewQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 3:
            EditQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 4:
            DeleteQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 5:
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); //Call recursively so the program won't terminate when the input is invalid
            break;
    }
}

/*
   AddQnA function allows the administrator to add new Chatbot questions and answers as many as they want. 
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct that holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
void 
AddQnA(int nInput, 
       UsersInfo Users[], 
       int* nNumUser, 
       AppInfo App[], 
       int* nNumApp, 
       ChatBot Faq[], 
       int* nNumFaq)
{
    int bFlag = 1;
    char question[MAX_QUESTION_LENGTH];
    char answer[MAX_ANSWER_LENGTH];
    
    if (*nNumFaq < MAX_QUESTIONS)
    {
        while (bFlag == 1) // start loop
        {
            printf("\n%s",
            "__________________________________________\n"
            "|             Add a New QnA?              |\n"
            "|                                         |\n"
            "|   [1] Yes                               |\n"
            "|   [2] No                                |\n"
            "|_________________________________________|\n\n");

            printf("Input Choice: ");
            scanf("%d", &nInput);

            if (nInput == 1)
            {
                // Ask the user to enter new QnA
                printf("\nEnter New Question (must not be over 80 characters):\n");
                fflush(stdin);

                fgets(question, MAX_QUESTION_LENGTH, stdin); // store question in the question[]
                if (strlen(question) > MAX_QUESTION_LENGTH - 1 || question[strlen(question) - 1] != '\n') // length > 80
                {
                    printf("\n%s",
                        " -----------------------------------------\n"
                        "|   Error: Question must not exceed 80    |\n"
                        "|    characters. Please restart again.    |\n"
                        " -----------------------------------------\n\n");
                    while (getchar() != '\n'); // clear input buffer
                }
                else
                {
                    printf("\nEnter New Answer (must not be over 80 characters):\n");
                    fflush(stdin);

                    fgets(answer, MAX_ANSWER_LENGTH, stdin); // store answer in the question[]
                    if (strlen(answer) > MAX_ANSWER_LENGTH - 1 || answer[strlen(answer) - 1] != '\n') // length > 80
                    {
                        printf("\n%s",
                            " -----------------------------------------\n"
                            "|    Error: Answer must not exceed 80     |\n"
                            "|    characters. Please restart again.    |\n"
                            " -----------------------------------------\n\n");
                        while (getchar() != '\n'); // clear input buffer
                    }
                    else
                    {
                        question[strlen(question) - 1] = '\0'; // replace '\n' with null terminator
                        answer[strlen(answer) - 1] = '\0'; // replace '\n' with null terminator

                        // Store the new QnA in the Faq[]
                        strcpy(Faq[*nNumFaq].question, question);
                        strcpy(Faq[*nNumFaq].answer, answer);

                        printf("\nSuccessfully Added!\n");
                        (*nNumFaq)++; // increments the total number of QnAs

                        bFlag = 0; // end loop
                    }
                }
            }
            else if (nInput == 2) 
            {
                bFlag = 0; // end loop
            }
            else
            {
                printf("\n%s",
                    " -----------------------------------------\n"
                    "|  Error: Invalid input. Please try again.|\n"
                    " -----------------------------------------\n\n");
            }
        }
    }
    else 
    {
    printf("\n%s",
            "    -------------------------------------------\n"
            "   |      Maximum Number of FAQs Reached!!!    |\n"
            "    -------------------------------------------\n\n");
    }

    ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
}


/*
   ViewQnA function allows the administrator to view all the set of questions and answer.
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
void 
ViewQnA(int nInput, 
        UsersInfo Users[], 
        int* nNumUser, 
        AppInfo App[], 
        int* nNumApp, 
        ChatBot Faq[], 
        int* nNumFaq)
{
    int i;

    printf("\n%s",
    " -----------------------------------------\n"
    "|      VIEW ALL QUESTIONS AND ANSWERS      |\n"
    " -----------------------------------------\n");
    printf("\n");

    for (i = 0; i < * nNumFaq; i++) // loop the current number of QnAs
    {
        printf("(%d) Question: %s\n", i + 1, Faq[i].question); // + 1 index starts at 0
        printf("    Answer: %s\n", Faq[i].answer);
        printf("\n");
    }

    if (*nNumFaq == 0) // total of 0 QnA
        printf("No questions and answers found.\n"); // not found
}


/*
   EditQnA function allows the admin to edit a specific question and answer.
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
void 
EditQnA(int nInput, 
        UsersInfo Users[], 
        int* nNumUser, 
        AppInfo App[], 
        int* nNumApp, 
        ChatBot Faq[], 
        int* nNumFaq)
{
    int bFlag = 1;
    char question[MAX_QUESTION_LENGTH];
    char answer[MAX_ANSWER_LENGTH];

    ViewQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // call the ViewQnA() for view all QnAs

    while (bFlag == 1) // start loop
    {
        printf("\nInput the QnA code: ");
        scanf("%d", &nInput);

        printf("QnA [%d]\nQuestion: %s\nAnswer: %s\n", nInput, Faq[nInput - 1].question, Faq[nInput - 1].answer);

        if (nInput > 0 && nInput <= *nNumFaq)
        {
            printf("\nEdit Question (must not be over 80 characters):\n");
            fflush(stdin); // clear input buffer
            fgets(question, MAX_QUESTION_LENGTH, stdin); // store input in the question[]

            if (strlen(question) > MAX_QUESTION_LENGTH - 1 || question[strlen(question) - 1] != '\n') // length > 80
            {
                printf("\n%s",
                " -----------------------------------------\n"
                "|   Error: Question must not exceed 80    |\n"
                "|    characters. Please restart again.    |\n"
                " -----------------------------------------\n\n");
                while (getchar() != '\n'); // clear input buffer
            }
            else
            {
                printf("\nEdit Answer (must not be over 80 characters):\n");
                fflush(stdin); // clear input buffer
                fgets(answer, MAX_ANSWER_LENGTH, stdin); // store input in the answer[]
                
                if (strlen(answer) > MAX_ANSWER_LENGTH - 1 || answer[strlen(answer) - 1] != '\n')  // length > 80
                {
                    printf("\n%s",
                    " -----------------------------------------\n"
                    "|    Error: Answer must not exceed 80     |\n"
                    "|    characters. Please restart again.    |\n"
                    " -----------------------------------------\n\n");
                    while (getchar() != '\n'); // clear input buffer
                }
                else
                {
                    question[strlen(question) - 1] = '\0'; // replace '\n' with null terminator
                    answer[strlen(answer) - 1] = '\0'; // replace '\n' with null terminator

                    // Update the Edited QnA in the Faq[]
                    strcpy(Faq[nInput - 1].question, question);
                    strcpy(Faq[nInput - 1].answer, answer);

                    printf("\nQnA [%d] has been updated!\n", nInput);
                    bFlag = 0;
                }
            }
        }
        else // nInput < 0 && nInput > *nNumFaq
        {
            printf("\nInvalid index.\n");
        }
    }
    ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // redirect back to ChatBot Menu
}

/*
   readQnA function stores the QnA stored in the chatbot text file in the Faq[].
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
void 
readQnA(ChatBot Faq[], 
        int* nNumFaq) 
{
    FILE *fp;
    char question[MAX_QUESTION_LENGTH];
    char answer[MAX_ANSWER_LENGTH];

    fp = fopen("TempChat.txt", "r"); // open file

    if (fp == NULL) // if the file does not exist
    {
        printf("Error: filename does not exist.\n"); // display error
    }

    else
    {
        while (fgets(question, MAX_QUESTION_LENGTH, fp) != NULL)  // read each line
        {
            fgets(answer, MAX_ANSWER_LENGTH, fp);

            question[strlen(question) - 1] = '\0'; // replace '\n' with null terminator
            answer[strlen(answer) - 1] = '\0'; // replace '\n' with null terminator

            // Store the chatbot.txt data in the Faq[]
            strcpy(Faq[*nNumFaq].question, question);
            strcpy(Faq[*nNumFaq].answer, answer);
            (*nNumFaq)++; // increment the number of QnAs
        }
    }

    fclose(fp); // close the file
}

/*
   DeleteQnA function allows the administrator to delete a specific question and answer.
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the TempChat.txt file already exists and contains all the QnA
*/
void DeleteQnA(int nInput, 
               UsersInfo Users[], 
               int* nNumUser, 
               AppInfo App[], 
               int* nNumApp, 
               ChatBot Faq[], 
               int* nNumFaq)
{
    int i;
    int nChoice;

    ViewQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // call the ViewQnA() to view all QnA
    
    printf("\n%s",
    " -----------------------------------------\n"
    "|               DELETE QnA                |\n"
    " -----------------------------------------\n\n");
    printf("Input QnA code: ");
    scanf("%d", &nInput);

    if (nInput < 0 || nInput > *nNumFaq) // invalid index
    {
        printf("Invalid index.\n");
        DeleteQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); 
    }
    else
    {
        // Display QnA before deleting
        printf("QnA [%d]:\nQuestion: %s\nAnswer: %s\n", nInput, Faq[nInput - 1].question, Faq[nInput - 1].answer);
    
        printf("\n"
            " -----------------------------------------\n"
            "|     Are you sure you want to delete     |\n"
            "|               QnA [%d]?                 |\n"
            "|                                         |\n"
            "|          [1] Yes, I am sure             |\n"
            "|          [2] Cancel Deletion            |\n"
            " -----------------------------------------\n\n", nInput);
        printf("Input choice: ");
        scanf("%d", &nChoice);

        switch(nChoice)
        {
            case 1: // user inputs 1
                for (i = nInput - 1; i < *nNumFaq - 1; i++) // QnA deleted; array shifts to the left
                {
                    strcpy(Faq[i].question, Faq[i + 1].question); // + 1 overwrite the previous element of the array 
                    strcpy(Faq[i].answer, Faq[i + 1].answer); // + 1 overwrite the previous element of the array 
                }

                Faq[*nNumFaq - 1].question[0] = '\0'; // replace '\n' with null terminator
                Faq[*nNumFaq - 1].answer[0] = '\0'; // replace '\n' with null terminator
                (*nNumFaq)--; // decrements the total number of QnAs

                printf("\n"
                    " -----------------------------------------\n"
                    "|      QnA [%d] deleted successfully!     |\n"
                    "|                                         |\n"
                    "|    [1] Delete another QnA               |\n"
                    "|    [2] Go back to ChatBot Menu          |\n"
                    " -----------------------------------------\n\n", nInput);
                printf("Input choice: ");
                scanf("%d", &nChoice); // ask the user if they want to delete another QnA

                switch(nChoice)
                {
                    case 1:
                        DeleteQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // call the DeleteQnA() to restart the deletion
                        break;
                    case 2:
                        ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // redirect back to the ChatBot Menu
                        break;
                    default: // invalid nInput
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    DeleteQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // restart the deletion process if invalid nInput
                    break;
                }
                break;
            case 2:
                    printf("\n%s",
                    " -----------------------------------------\n"
                    "|        ChatBot deletion cancelled!      |\n"
                    "|      Redirecting to ChatBot Menu...     |\n"
                    " -----------------------------------------\n\n");
                ChatBotMod(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // redirects back to the ChatBot Menu
                break;
            default: // invalid Input
                printf("\n%s",
                "           -------------------\n"
                "          |   Invalid Input!  |\n"
                "           -------------------\n\n");
                DeleteQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // restart the deletion process if invalid nInput
                break;
        }
    }
}

/*
   Export function allows the administrator to export/save data from Users[], App[], and Faq[] in a text file.
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the user stored data into the Users[], App[], and Faq[] while running the program.
*/
void
Export(int nInput, 
       UsersInfo Users[], 
       int* nNumUser, 
       AppInfo App[], 
       int* nNumApp, 
       ChatBot Faq[], 
       int* nNumFaq)
{
    int i;
    char userfilename[MAX_FILENAME]; // User Filename
    char appfilename[MAX_FILENAME]; // Appointment Filename
    char chatfilename[MAX_FILENAME]; // Chatbot Filename
    FILE *fp = NULL; // users.txt
    FILE *fp2 = NULL; // appointment.xt
    FILE *fp3 = NULL; // chatbot.txt

    printf("%s",
        "__________________________________________\n"
        "|   Choose data that you want to export   |\n"
        "|                                         |\n"
        "|   [1] User Data                         |\n"
        "|   [2] Appointment Data                  |\n"
        "|   [3] ChatBot Data                      |\n"
        "|   [4] Exit                              |\n"
        "|_________________________________________|\n\n");

        printf("Input Choice: ");
        scanf("%d", &nInput);

    switch(nInput)
    {
        case 1:
            // Ask user for filename
            printf("\nEnter filename (30 characters max): "); // admin allowed to specify the filename
            scanf("%s", userfilename);

            if ( (fp = fopen(userfilename, "w")) == NULL) // if the file exists, file wil be erased and will be overwritten
            {
                printf("\n     Error: %s does not exist. \n\n", userfilename);
            }
            else
            {
                printf("\n     %s was opened successfully. \n\n", userfilename);

                printf("\n%s",
                " -----------------------------------------\n"
                "|             EXPORTING USERS             |\n"
                " -----------------------------------------\n");
                for (i = 0; i < * nNumUser; i++)
                {
                    fprintf(fp, "%d %s\n", Users[i].userID, Users[i].password); // userID, password
                    fprintf(fp, "%s\n", Users[i].name); // name
                    fprintf(fp, "%s\n", Users[i].address); // address
                    fprintf(fp, "0%lld\n", Users[i].contact); // contact
                    fprintf(fp, "%s\n", Users[i].sex); // sex
                    fprintf(fp, "%s %s %s\n", Users[i].firstDoseLoc, Users[i].firstDose, Users[i].firstDoseVac); // 1st dose location, date, vaccine
                    fprintf(fp, "%s %s %s\n", Users[i].secondDoseLoc, Users[i].secondDose, Users[i].secondDoseVac); // 2nd dose location, date, vaccine
                    fprintf(fp, "%s %s %s\n", Users[i].boosterDoseLoc, Users[i].boosterDose, Users[i].boosterDoseVac); // 3rd dose location, date, vaccine
                    if (i != *nNumUser - 1) 
                    {
                        fprintf(fp, "\n"); // new line
                    }
                } // end  loop
                printf("\n           Export Success!\n\n");
            }
            fclose(fp); // close the file
            Export(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 2:
            // Ask user for filename
            printf("\nEnter filename (30 characters max): "); // admin allowed to specify the filename
            scanf("%s", appfilename);

            if ( (fp2 = fopen(appfilename, "w")) == NULL) // if the file exists, file wil be erased and will be overwritten
            {
                printf("\n     Error: %s does not exist. \n", appfilename);
            }
            else
            {
                printf("\n     %s was opened successfully. \n", appfilename);

                printf("\n%s",
                " -----------------------------------------\n"
                "|          EXPORTING APPOINTMENT          |\n"
                " -----------------------------------------\n");
                for (i = 0; i < * nNumApp; i++)
                {
                    fprintf(fp2, "%d %d\n", App[i].appID, App[i].userID); // AppID, userID
                    fprintf(fp2, "%s\n", App[i].name); // name
                    fprintf(fp2, "%s\n", App[i].location); // location
                    fprintf(fp2, "%s\n", App[i].vaccine); // vaccine
                    fprintf(fp2, "%s\n", App[i].date); // date
                    fprintf(fp2, "%s\n", App[i].time); // time
                    fprintf(fp2, "%s\n", App[i].dose); // dose
                    if (i != *nNumApp - 1) 
                    {
                        fprintf(fp2, "\n"); // new  line
                    }
                } // end loop
                printf("\n           Export Success!\n\n");
            }
            fclose(fp2); // close the file
            Export(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 3:
            // Ask user for filename
            printf("\nEnter filename (30 characters max): "); // admin allowed to specify the filename
            scanf("%s", chatfilename);

           if ( (fp3 = fopen(chatfilename, "w")) == NULL) // if the file exists, file wil be erased and will be overwritten
            {
                printf("\n    Error: %s does not exist. \n", chatfilename);
            }
            else
            {
                printf("\n%s",
                " -----------------------------------------\n"
                "|        EXPORTING CHATBOT Q&A's          |\n"
                " -----------------------------------------\n");
                for (i = 0; i < * nNumFaq; i++)
                {
                    fprintf(fp3, "%s\n", Faq[i].question);
                    fprintf(fp3, "%s\n", Faq[i].answer);
                } // end loop
                printf("\n           Export Success!\n\n");
            }
            fclose(fp3); // close the file
            Export(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 4:
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // redirect back to the Data Management Menu
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            Export(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); //Call recursively so the program won't terminate when the input is invalid
            break;
    }
}

/*
   Import function allows the administrator to import data to Users[], App[], and Faq[] from a text file depending on their choice.
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
*/
void
Import(int nInput, 
       UsersInfo Users[], 
       int* nNumUser, 
       AppInfo App[], 
       int* nNumApp, 
       ChatBot Faq[], 
       int* nNumFaq)
{
    printf("\n%s",
    " -----------------------------------------\n"
    "|               IMPORT FILE               |\n"
    " -----------------------------------------\n");

    printf("%s",
        "__________________________________________\n"
        "|   Choose data that you want to import   |\n"
        "|                                         |\n"
        "|   [1] User Data                         |\n"
        "|   [2] Appointment Data                  |\n"
        "|   [3] ChatBot Data                      |\n"
        "|   [4] Exit                              |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput)
    {
        case 1: 
            ImportUsers(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 2:
            ImportApp(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 3:
            ImportQnA(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        case 4:
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
             // Call recursively so the program won't terminate when the Input is invalid
            break;
    }
}

/*
   ImportUsers imports users from the text file to the program 
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
*/
void
ImportUsers(int nInput,
            UsersInfo Users[], 
            int* nNumUser, 
            AppInfo App[], 
            int* nNumApp, 
            ChatBot Faq[], 
            int* nNumFaq)
{
    int index;
    char line[100]; // character array for fgets to read
    char userFile[MAX_FILENAME]; // file inputted
    FILE* fp = NULL; // initial value

    index = *nNumUser; // the index is the current number of users

    printf("\nEnter filename to import users from: ");
    scanf("%s", userFile);
    
    printf("\n");

    fp = fopen(userFile, "r"); // open file

    if(fp == NULL) 
    {
        printf("\n   (!) ERROR: File not found (!)\n");
        Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
        fclose(fp);
    }
    else
    {
        while(!feof(fp)) // scan until the end of the file
        {
            // UserID, Password
            fgets(line, sizeof(line), fp); // reads the line ans store it in line[]
            sscanf(line, "%d %s", &Users[index].userID, Users[index].password); // extract userID and password
            // Name
            fgets(line, sizeof(line), fp);
            strtok(line, "\n"); // find the new line and replace it with '\0'
            strcpy(Users[index].name, line); // copy line to user struct
            // Address
            fgets(line, sizeof(line), fp);
            strtok(line, "\n");
            strcpy(Users[index].address, line);
            // contact Number
            fgets(line, sizeof(line), fp);
            sscanf(line, "%lld", &Users[index].contact);
            // Sex
            fgets(line, sizeof(line), fp);
            strcpy(Users[index].sex, line);
            // Location 1, date 1, Vaccine 1
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s %s %s", Users[index].firstDoseLoc, Users[index].firstDose, Users[index].firstDoseVac);
            // Location 2, date 2, Vaccine 2
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s %s %s", Users[index].secondDoseLoc, Users[index].secondDose, Users[index].secondDoseVac);
            // Location 3, date 3, Vaccine 3
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s %s %s", Users[index].boosterDoseLoc, Users[index].boosterDose, Users[index].boosterDoseVac);
            // New line
            fgets(line, sizeof(line), fp);

            printf("============ USER INFORMATION ============\n\n");
            printf("User ID:         %d\n", Users[index].userID);
            printf("Password:        %s\n", Users[index].password);
            printf("Name:            %s\n", Users[index].name);
            printf("Address:         %s\n", Users[index].address);
            printf("Contact Number:  0%lld\n", Users[index].contact);
            printf("Sex:             %s\n\n", Users[index].sex);
            printf("========= FIRST DOSE INFORMATION =========\n\n");
            printf("Location:        %s\n", Users[index].firstDoseLoc);
            printf("Date:            %s\n", Users[index].firstDose);
            printf("Vaccine:         %s\n\n", Users[index].firstDoseVac);
            printf("======== SECOND DOSE INFORMATION =========\n\n");
            printf("Location:        %s\n", Users[index].secondDoseLoc);
            printf("Date:            %s\n", Users[index].secondDose);
            printf("Vaccine:         %s\n\n", Users[index].secondDoseVac);
            printf("======== BOOSTER DOSE INFORMATION =========\n\n");
            printf("Location:        %s\n", Users[index].boosterDoseLoc);
            printf("Date:            %s\n", Users[index].boosterDose);
            printf("Vaccine:         %s\n\n", Users[index].boosterDoseVac);
            printf("===========================================\n\n");

            printf("\n%s",
            " -----------------------------------------\n"
            "|     Do you want to import this user?    |\n"
            "|                                         |\n"
            "|                [1] Yes                  |\n"
            "|                [2] No                   |\n"
            " -----------------------------------------\n\n");

            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                    if(*nNumUser < MAX_USERS)
                    {
                        index++; // increment index to be added in the array
                        (*nNumUser)++; // increment number of users
                        printf("\n%s",
                        "        -----------------------\n"
                        "       |   Import Successful!  |\n"
                        "        -----------------------\n\n");
                    }
                    else
                    {
                        printf("\n%s",
                        " -----------------------------------------\n"
                        "|    Maximum Number of Users Reached!!!   |\n"
                        " -----------------------------------------\n\n");
                    }
                    break;
                case 2:
                    break;
                default:
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
        } 
    }
    }
    fclose(fp); // close the file
    Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
}

/*
   ImportApp imports appointments from the text file to the program 
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
*/
void
ImportApp(int nInput, 
          UsersInfo Users[], 
          int* nNumUser, 
          AppInfo App[], 
          int* nNumApp, 
          ChatBot Faq[], 
          int* nNumFaq)
{
    int index;
    char line[100]; // character array for fgets to read
    char appFile[MAX_FILENAME]; // file inputted
    FILE* fp = NULL; // initial value

    index = *nNumApp; // the index is the current number of appointments

    printf("\nEnter filename to import appointments from: ");
    scanf("%s", appFile);
    
    printf("\n");

    fp = fopen(appFile, "r"); // open file

    if(fp == NULL)
    {
        printf("\n   (!) ERROR: File not found (!)\n");
        Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
        fclose(fp);
    }
    else
    {
        while(!feof(fp)) // scan until the end of the file
        {
            // UserID, Password
            fgets(line, sizeof(line), fp); // reads the line ans store it in line[]
            sscanf(line, "%d %d", &App[index].appID, &App[index].userID); // extract appID and userID
            // Name
            fgets(line, sizeof(line), fp);
            strtok(line, "\n"); // find the new line and replace it with '\0'
            strcpy(App[index].name, line); // copy line to user struct
            // Location
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s", App[index].location);
            // Vaccine
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s", App[index].vaccine);
            // date
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s", App[index].date);
            // Time
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s", App[index].time);
            // Dose
            fgets(line, sizeof(line), fp);
            sscanf(line, "%s", App[index].dose);
            // New line
            fgets(line, sizeof(line), fp);

            printf("==========================================\n\n");
            printf("AppID: %d\n", App[index].appID);
            printf("UserID: %d\n", App[index].userID);
            printf("Name: %s\n", App[index].name);
            printf("City Location: %s\n", App[index].location);
            printf("Vaccine: %s\n", App[index].vaccine);
            printf("date: %s\n", App[index].date);
            printf("Time: %s\n", App[index].time);
            printf("Dose: %s\n\n", App[index].dose);
            printf("==========================================\n\n");

            printf("\n%s",
            " -----------------------------------------\n"
            "| Do you want to import this appointment? |\n"
            "|                                         |\n"
            "|                [1] Yes                  |\n"
            "|                [2] No                   |\n"
            " -----------------------------------------\n\n");

            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                if(*nNumApp < MAX_USERS)
                    {
                    index++; // increment index to be added in the array
                    (*nNumApp)++; // increment number of appointments
                    printf("\n%s",
                    "        -----------------------\n"
                    "       |   Import Successful!  |\n"
                    "        -----------------------\n\n");
                    }
                    else
                    {
                        printf("\n%s",
                        " --------------------------------------------\n"
                        "|  Maximum Number of Appointments Reached!!! |\n"
                        " --------------------------------------------\n\n");
                    }
                    break;
                case 2:
                    break;
                default:
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
            } 
       }
        fclose(fp); // close the file
        Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
    }
}

/*
   ImportQnA imports FAQs from the text file to the program 
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
*/
void
ImportQnA(int nInput, 
          UsersInfo Users[], 
          int* nNumUser, 
          AppInfo App[], 
          int* nNumApp, 
          ChatBot Faq[], 
          int* nNumFaq)
{
    int index;
    char line[100]; // character array for fgets to read
    char cbFile[MAX_FILENAME];
    FILE* fp = NULL; // initial value

    index = *nNumFaq; // current number of FAQs

    printf("\nEnter filename to import Chabot Q&As from: ");
    scanf("%s", cbFile);
    
    printf("\n");

    fp = fopen(cbFile, "r"); // open file

    if(fp == NULL)
    {
        printf("\n   (!) ERROR: File not found (!)\n");
        Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
        fclose(fp);
    }
    else
    {
        while(!feof(fp)) // scan until the end of the file
        {
            // Questions
            fgets(line, sizeof(line), fp); // reads the line ans store it in line[]
            strtok(line, "\n"); // find the new line and replace it with '\0'
            strcpy(Faq[index].question, line); // copy line to user struct
            // Answer
            fgets(line, sizeof(line), fp);
            strtok(line, "\n");
            strcpy(Faq[index].answer, line);

            printf("Question: %s\n", Faq[index].question);
            printf("Answer: %s\n", Faq[index].answer);
            printf("\n");

            printf("\n%s",
            " -----------------------------------------\n"
            "|     Do you want to import this Q&A?     |\n"
            "|                                         |\n"
            "|                [1] Yes                  |\n"
            "|                [2] No                   |\n"
            " -----------------------------------------\n\n");

            printf("Input Choice: ");
            scanf("%d", &nInput);

            switch(nInput)
            {
                case 1:
                if(*nNumFaq < MAX_USERS)
                    {
                    index++; // increment index to be added in the array
                    (*nNumFaq)++; // increment number of FAQs
                    printf("\n%s",
                    "        -----------------------\n"
                    "       |   Import Successful!  |\n"
                    "        -----------------------\n\n");
                    }
                    else
                    {
                        printf("\n%s",
                        "      -----------------------------------\n"
                        "     | Maximum Number of FAQs Reached!!! |\n"
                        "      -----------------------------------\n\n");
                    }
                    break;
                case 2:
                    break;
                default:
                    printf("\n%s",
                    "           -------------------\n"
                    "          |   Invalid Input!  |\n"
                    "           -------------------\n\n");
                    break;
            } 
       }
        fclose(fp); // close the file
        Import(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq);
    }
}

/*
   Exit function allows the administrator to save all current data on set of users, appointments, and chatbot into text files.
   @param nInput - the users input everytime the program asks what to do
   @param Users[] - array of UserInfo struct that holds the information of all users
   @param nNumUser  - stores the number of users in the program
   @param App[] - array of AppInfo struct thart holds the information of all the appointments
   @param nNumApp - stores the number of appointments in the program
   @param Faq[] - array of ChatBot struct that holds the information of all the questions and answers.
   @param nNumFaq - stores the number of questions and answers in the program
   @return void 
   Pre-condition: the user stored data into the Users[], App[], and Faq[] while running the program.
*/
void
ExitMenu(int nInput, 
         UsersInfo Users[], 
         int* nNumUser, 
         AppInfo App[], 
         int* nNumApp, 
         ChatBot Faq[], 
         int* nNumFaq)
{
    int i;
    FILE *fp;
    FILE *fp2;
    FILE *fp3;

    printf("%s",
        "__________________________________________\n"
        "|      Are you sure you want to exit      |\n"
        "|            and save all data?           |\n"
        "|                                         |\n"
        "|   [1] Yes I am Sure                     |\n"
        "|   [2] Go back                           |\n"
        "|_________________________________________|\n\n");

    printf("Input Choice: ");
    scanf("%d", &nInput);

    switch (nInput)
    {
        case 1:
            fp = fopen("Users.txt", "w"); // open fp file

                for (i = 0; i < * nNumUser; i++)
                {
                    fprintf(fp, "%d %s\n", Users[i].userID, Users[i].password);
                    fprintf(fp, "%s\n", Users[i].name);
                    fprintf(fp, "%s\n", Users[i].address);
                    fprintf(fp, "0%lld\n", Users[i].contact);
                    fprintf(fp, "%s\n", Users[i].sex);
                    fprintf(fp, "%s %s %s\n", Users[i].firstDoseLoc, Users[i].firstDose, Users[i].firstDoseVac);
                    fprintf(fp, "%s %s %s\n", Users[i].secondDoseLoc, Users[i].secondDose, Users[i].secondDoseVac);
                    fprintf(fp, "%s %s %s\n", Users[i].boosterDoseLoc, Users[i].boosterDose, Users[i].boosterDoseVac);
                    if (i != *nNumUser - 1) 
                    {
                        fprintf(fp, "\n"); // newline
                    }
                }

            fclose(fp); // close the file

            fp2 = fopen("Appointments.txt", "w"); //open fp2 file

                for (i = 0; i < * nNumApp; i++)
                {
                    fprintf(fp2, "%d %d\n", App[i].appID, App[i].userID);
                    fprintf(fp2, "%s\n", App[i].name);
                    fprintf(fp2, "%s\n", App[i].location);
                    fprintf(fp2, "%s\n", App[i].vaccine);
                    fprintf(fp2, "%s\n", App[i].date);
                    fprintf(fp2, "%s\n", App[i].time);
                    fprintf(fp2, "%s\n", App[i].dose);
                    if (i != *nNumApp - 1) 
                    {
                        fprintf(fp2, "\n"); // new line
                    }
                }

            fclose(fp2); // close the file

           fp3 = fopen("Chatbot.txt", "w"); // open  fp3 file

                for (i = 0; i < * nNumFaq; i++)
                {
                    fprintf(fp3, "%s\n", Faq[i].question);
                    fprintf(fp3, "%s\n", Faq[i].answer);
                }

            fclose(fp3); // close the file

                printf("%s",
                " --------------------------------------\n"
                "|             Data Saved!              |\n"
                "|      Redirecting to Main Menu...     |\n"
                " --------------------------------------\n\n");
                MainMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // redirect back to Main Menu
        break;

        case 2:
            SuccessDataMan(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // redirect back to data management menu
            break;
        default:
            printf("\n%s",
            "           -------------------\n"
            "          |   Invalid Input!  |\n"
            "           -------------------\n\n");
            ExitMenu(nInput, Users, nNumUser, App, nNumApp, Faq, nNumFaq); // Call recursively so the program won't terminate when the nInput is invalid
            break;
    }
}