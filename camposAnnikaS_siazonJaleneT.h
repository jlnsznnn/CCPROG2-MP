// User Registration Constants
#define MAX_USERS 100
// +1 for the null terminator ('\0') at the end of the string, 
#define MAX_PASSWORD 11
#define MAX_NAME 21
#define MAX_ADDRESS 31
#define MAX_DATE 11
#define MAX_OTHERS 11
#define MAX_TIME 7
#define MAX_CONTACT 12
#define MAX_FILENAME 31

//For Chatbot
#define MAX_QUESTIONS 100
#define MAX_QUESTION_LENGTH 81
#define MAX_ANSWER_LENGTH 81

// User Struct
typedef struct UserTag
{
    int userID;
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
    char address[MAX_ADDRESS];
    long long int contact; 
    char sex[MAX_OTHERS];
    char firstDose[MAX_DATE];
    char firstDoseVac[MAX_OTHERS];
    char firstDoseLoc[MAX_OTHERS];
    char secondDose[MAX_DATE];
    char secondDoseVac[MAX_OTHERS];
    char secondDoseLoc[MAX_OTHERS];
    char boosterDose[MAX_DATE];
    char boosterDoseVac[MAX_OTHERS];
    char boosterDoseLoc[MAX_OTHERS];
    int loggedIn;
    int requested;
    int reqIndex;
} UsersInfo;

// Appointment Struct
typedef struct AppTag
{
    int userID;
    int appID;
    char name[MAX_NAME];
    char location[MAX_ADDRESS];
    char vaccine[MAX_OTHERS];
    char date[MAX_DATE];
    char time[MAX_TIME];
    char dose[MAX_OTHERS];
    int reqIndex; 
} AppInfo;

// Chatbot Struct
typedef struct ChatTag
{
    char question[MAX_QUESTION_LENGTH];
    char answer[MAX_ANSWER_LENGTH];
} ChatBot; 


// FUNCTION PROTOTYPES

void MainMenu(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// For Vaccination Registration Menu

// Vaccination Registration Menu
void VacRegMenu(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
int VacRegLogIn(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void SuccessVacReg(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); // Vaccination Registration Menu after successfully registrating

// User Registration Menu
UsersInfo UserRegistration(UsersInfo Users[], int* nNumUsers);
void GetPassword(char password[MAX_PASSWORD]);
void AddNewUser(UsersInfo NewUser, UsersInfo Users[], int* nNumUsers);
void RegisterNewUser(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// Appointment Request Menu
AppInfo AppRequest(AppInfo App[], int* nNumApp);
void AddNewApp(AppInfo NewApp, AppInfo App[], int* nNumApp, int userID);
void RequestForApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
AppInfo ModifyApp(AppInfo currentApp);
void ManageApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); // Manage Appointment Menu
void VacApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); // Vaccination Appointment Menu

int readChatFile(char* filename, ChatBot* faqs, int* nNumFaqs);
void ChatBotMenu(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); // ChatBot Menu
void ChatBotAI(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// For Data Management Menu

// Data Management Menu
void DataManMenu(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void DataManLogIn(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void SuccessDataMan(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// Admin User Details
void User(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void AddUser(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void ViewUser(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void EditUser(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void DeleteUser(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// Admin Appointment Details
void Appointment(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void AddApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void ViewApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void EditApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void DeleteApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// Admin Chatbot Details
void readQnA(ChatBot Faq[], int* nNumFaq);
void ChatBotMod(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void AddQnA(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void ViewQnA(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); 
void EditQnA(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void DeleteQnA(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

// Admin Export 
void Export(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); 

// Admin Import 
void ImportUsers(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void ImportApp(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void ImportQnA(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);
void Import(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq); 

void ExitMenu(int nInput, UsersInfo Users[], int* nNumUsers, AppInfo App[], int* nNumApp, ChatBot Faq[], int* nNumFaq);

/*
   GetPassword function changes the input password into asterisks
   @param char password[0][MAX_PASSWORD] - address of the password array used to store the password string on struct Users
   @return void
   Pre-condition: password must contain 10 characters only 
*/
void GetPassword(char password[MAX_PASSWORD])
{
    int i = 0;
    char cInput;
    int nFlag = 0;
    int nBackSpace = 0;
    
    for (i = 0; i < MAX_PASSWORD - 1 && !nFlag; i++) // Minus 1 to get only 10 characters
    {
        cInput = getch(); // get user input

        if (cInput == '\r' || cInput == '\n') // stop when enter key is pressed
        {
            nFlag = 1; // condition to stop the loop
            password[i] = '\0';
        } 
        else if (cInput == '\b' && i > 0) // ignore backspace if not the first character
        {
            i--;
            password[i] = '\0';
            printf("\b \b"); // delete the previous character and moves the cursor back
            nBackSpace++;
        }
        else 
        {
            password[i] = cInput;
            putchar('*'); // converts user input to '*'
        }

        //condition the user nBackSpace
        if (nBackSpace > 0)
        {
            i--; // replaces the deleted character with null character
            nBackSpace--; // so that the previous deleted characters won't count to the maximum input
        }
    }
}

/*
   SearchUserID uses linear search for finding the UserID
   @param UsersInfo Users[] - array of UserInfo struct that holds the information of all users
   @param int* nNumUsers  - stores the number of users in the program
   @param int search - UserID that the function will search
   @return i (index) if found
   @return -1 if not found
   Pre-condition: search must be a valid UserID
*/
int SearchUserID(UsersInfo Users[], 
                int* nNumUsers, 
                int search) 
{
    int i;
    for (i = 0; i < *nNumUsers; i++) 
    {
        if (Users[i].userID == search) 
        {
            return i;  // found at index i
        }
    }
    return -1;  // not found
}

/*
   SearchAppID uses linear search for finding the AppID
   @param  AppInfo App[] - array of AppInfo struct thart holds the information of all the appointments
   @param int* nNumApp - stores the number of appointments in the program
   @param int search - AppID that the function will search
   @return i (index) if found
   @return -1 if not found
   Pre-condition: search must be a valid AppID
*/
int SearchAppID(AppInfo App[], 
                int* nNumApp, 
                int search)
{
    int i;
    for (i = 0; i < *nNumApp; i++) 
    {
        if (App[i].appID == search) 
        {
            return i;  // found at index i
        }
    }
    return -1;  // not found
}

/*
   isValidID function checks if the UserID is valid by comparing it to the AdminID 
   @param int *ID - the UserID that will be compared to the AdminID (1234)
   @return 1 if the ID is valid
   @return 0 if the ID is invalid
   Pre-condition: *ID only contains whole numbers and non negative values
*/
int isValidID(int *ID)
{
    if(*ID != 1234) 
    {
        // admin ID will always be 1234
        return 1; // valid ID
    }
    return 0; // invalid ID
}

/*
   isValidDate function checks if the date is valid by checking its format, length, and inputted date 
   @param char *date - the date being tested
   @return 0 if the date is invalid
   @return 1 if the date is valid
   Pre-condition: *date only contains whole numbers 
*/
int isValidDate(char* date) 
{
    int nYear, nMonth, nDay;

    // check if string has 10 characters
    if (strlen(date) != 10) 
    {
        return 0;
    }
    
    // check if date string has the correct format
    if (sscanf(date, "%4d-%2d-%2d", &nYear, &nMonth, &nDay) != 3) 
    {
        return 0; 
    }
    
    // checking the nYear, nMonth, and nDay values considering that vaccinations started at March 2021
    if ((nYear > 2021 && nYear <= 2023 && nMonth >= 1 && nMonth <= 12 && nDay >= 1 && nDay <= 31) 
        || (nYear == 2021 && nMonth >= 3 && nMonth <= 12 && nDay >= 1 && nDay <= 31)) 
    {
        return 1; // valid date
    } 
    else 
    {
        return 0; // invalid date
    }
}

/*
   isValidAppDate function checks if the date is valid by checking its format, length, and inputted date 
   @param char *date - the date being tested
   @return 0 if the date is invalid
   @return 1 if the date is valid
   Pre-condition: *date only contains whole numbers 
*/
int isValidAppDate(char* date) 
{
    int nYear, nMonth, nDay;

    // Check if string has 10 characters
    if (strlen(date) != 10) 
    {
        return 0;
    }
    
    // check if date string has the correct format
    if (sscanf(date, "%4d-%2d-%2d", &nYear, &nMonth, &nDay) != 3) 
    {
        return 0; // will oly return 3 if the format is correct
    }
    
    // checking the nYear, nMonth, and nDay values considering the date today (April 11, 2023) as user can't book an appointment on date that has already passed
    if ((nYear > 2023 && nMonth >= 1 && nMonth <= 12 && nDay >= 1 && nDay <= 31) 
       || (nYear == 2023 && nMonth > 4 && nMonth <= 12 && nDay >= 1 && nDay <= 31)
       || (nYear == 2023 && nMonth == 4 && nDay >= 11 && nDay <= 30))
    {
        return 1; // valid date
    } 
    else 
    {
        return 0; // invalid date
    }
}

/*
   isValid time checks if the time inputted by the user is valid
   @param char *time - time being compared
   @return 0 if the time is invalid
   @return 1 if the time is valid
   Pre-condition: Time must be on 24-hour format
*/
int isValidTime(char* time)
{
    int nHour, nMinute;

    // check if string has 5 characters
    if (strlen(time) != 5) 
    {
        return 0;
    }

    // check if time string has the correct format
    if (sscanf(time, "%2d:%2d", &nHour, &nMinute) != 2)
    {
        return 0; // will oly return 2 if the format is correct
    }

    // checking if nHour and nMinute values are within valid range
    if (nHour >= 0 && nHour <= 23 && nMinute >= 0 && nMinute <= 59)
    {
        return 1; // valid time
    }
    else
    {
        return 0; //invalid time
    }

}

/*
   AddNewUser function adds a new user to the Users[]
   @param UsersInfo NewUser - new user to be added
   @param UsersInfo Users[] - array of users
   @param int* nNumUsers - number of users currently in the arrray
   @return void
*/
void AddNewUser(UsersInfo NewUser, 
                UsersInfo Users[], 
                int* nNumUsers) 
{
    Users[*nNumUsers] = NewUser;
    (*nNumUsers)++;
}

/*
   IsLoggedIn checks the index of the user who is currently logged in
   @param UsersInfo Users[] - array of users
   @param int* nNumUsers - number of users currently in the arrray
   @return 1 if the user is currently logged in
   @return 0 if the user is not logged in
*/
int IsLoggedIn(UsersInfo Users[], 
                int nNumUsers) 
{
    int i;
    for (i = 0; i < nNumUsers; i++) 
    {
        if (Users[i].loggedIn == 1) 
        {
            return 1; // logged in
        }
    }
    return 0; // not logged in
}

/*
   GetUserIndex checks the index of the user who is currently logged in 
   @param UsersInfo Users[] - array of users
   @param int* nNumUsers - number of users currently in the arrray
   @return i (index) of the user who is currently logged in
   @return -1 if no user is logged in
*/
int GetUserIndex(UsersInfo Users[], 
                int nNumUsers) 
{
    int i;
    for (i = 0; i < nNumUsers; i++) {
        if (Users[i].loggedIn == 1) 
        {
            return i; // index of the logged in user
        }
    }
    return -1; //  no user is logged in
}

/*
   AddNewApp updates the appointment array everytime a new appointment is added
   @param AppInfo NewApp - new appointment struct
   @param AppInfo App[] -array of the appointments
   @param int* nNumApp - number of appointments
   @param int userID - userID of the user who made the appointment
   @return void
*/
void AddNewApp(AppInfo NewApp, 
                AppInfo App[], 
                int* nNumApp, 
                int userID) 
{
    NewApp.userID = userID;
    App[*nNumApp] = NewApp;
    (*nNumApp)++;
}
