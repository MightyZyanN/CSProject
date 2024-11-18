#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <thread>
#include <chrono>
#include <atomic>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

class Player;
class School;
class Eatery;
class TimeLocation;

int getConsoleWidth();

void setConsoleColor(int color);

void resetConsoleColor();

void positionText(const string text, bool nextline, bool typeText);

void validateInput(string &input, string prompttext, string invalidprompttext, int min, int max, bool typetext);

void validateInput(string &input, string prompttext, string invalidprompttext, string str_array[], int str_array_s, bool upper, bool typetext);

void inputLocation(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize);

void gameLoop();

class Eatery
{
    private:
        string name;
        int location;

        vector<vector<string>> menuarray = {{"BACK", "-1"}};
        int menusize = menuarray.size();

    public:
        Eatery(string nameval, int locationval)
        {
            name = nameval;
            location = locationval;
        }

        void atEatery(Player &player);

        string getName()
        {
            return name;
        }

        void addMenuItem(string itemname, string itemprice)
        {
            menuarray.push_back({itemname, itemprice});
            menusize = menuarray.size();
        }

        int getMenuSize()
        {
            return menusize;
        }

        string getMenuItemName(int menuitem)
        {
            return menuarray[menuitem][0];
        }

        string getMenuItemPrice(int menuitem)
        {
            return menuarray[menuitem][1];
        }

        void printMenu()
        {
            positionText("TODAY'S MENU", true, false);
            if (menusize == 1)
            {
                cout << "NONE";
            }
            else
            {
                for (int i = 1; i < menusize; i++)
                {   
                    cout << menuarray[i][0] << " - " << menuarray[i][1];
                    if (i != menusize - 1)
                    {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
        }

};

class Player
{
	private:
        string name;
        string gender;
        string school;
        int schoolindex;
        double cash = 1000.0;
        float gpa = 4.0f;
        float studyloss = 0.0f;
        int hunger = 10;
        string location = "ENTRANCE";

        vector<string> inventoryarray = {"BACK"};

    public:
        Player(string nameval, string genderval, string schoolval, int schoolindexval)
        {
            name = nameval;
            gender = genderval;
            school = schoolval;
            schoolindex = schoolindexval;
        }

        void buyFoodItem(Eatery &eatery, string itemname);

        void setStudyLoss(float studylossval)
        {
            studyloss = studylossval;
        }

        float getStudyLoss()
        {
            return studyloss;
        }

        void setGPA(float amount)
        {
            gpa = amount;
        }

        float getGPA()
        {
            return gpa;
        }

        void setSchoolIndex(int index)
        {
            schoolindex = index;
        }

        int getSchoolIndex()
        {
            return schoolindex;
        }

        string getName()
        {
            return name;
        }

        void setCash(double cashval)
        {
            cash = cashval;
        }

        double getCash()
        {
            return cash;
        }

        string getLocation()
        {
            return location;
        }

        string setLocation(string locationval)
        {
            location = locationval;

            return location;
        }

        void addInventoryItem(const string &item)
        {
            inventoryarray.push_back(item);
        }

        void removeInventoryItem(const string &item)
        {
            auto it = find(inventoryarray.begin(), inventoryarray.end(), item);
            if (it != inventoryarray.end())
            {
                inventoryarray.erase(it);
            }
        }

        void setHunger(int hungerval)
        {
            hunger = hungerval;
        }

        int getHunger()
        {
            return hunger;
        }

        void printInventory()
        {
            positionText("INVENTORY", true, false);
            if (inventoryarray.size() == 1)
            {
                cout << "NONE";
            }
            else
            {
                for (int i = 1; i < inventoryarray.size(); i++)
                {   
                    cout << inventoryarray[i];
                    if (i != inventoryarray.size() - 1)
                    {
                        cout << ", ";
                    }
                }
            }
            cout << endl;

        }   

        void accessInventory()
        {
            string input1;

            string input2;

            bool run1 = true;

            bool run2 = true;

            while (run1)
            {
                run2 = true;

                printInventory();
                validateInput(input1, "What Do You Want To Access", "Invalid Item. What Do You Want To Access", inventoryarray.data(), inventoryarray.size(), true, false);

                if (input1 == "BACK")
                {
                    run1 = false;
                }
                else
                {
                    while (run2)
                    {
                        const int OPTIONARRAYSIZE = 3;
                        string optionarray[OPTIONARRAYSIZE] = {"EAT", "REMOVE", "BACK"};

                        validateInput(input2, "What Do You Want To Do", "Invalid Item. What Do You Want To Do", optionarray, OPTIONARRAYSIZE, true, false);

                        if (input2 == optionarray[OPTIONARRAYSIZE - 1])
                        {
                            run2 = false;
                        }
                        else if (input2 == optionarray[1])
                        {
                            removeInventoryItem(input1);
                            run2 = false;
                        }
                        else if (input2 == optionarray[0])
                        {
                            string text1 = "Eating " + input1;
                            string text2 = "Removed " + input1 + " From Inventory";
                            string text3 = "Hunger Full";
                            if (hunger < 10)
                            {
                                hunger++;
                                setConsoleColor(FOREGROUND_GREEN);
                                positionText(text1, true, false);
                                setConsoleColor(FOREGROUND_BLUE);
                                positionText(text2, true, false);
                                removeInventoryItem(input1);
                            }
                            else
                            {
                                setConsoleColor(FOREGROUND_RED);
                                positionText(text3, true, false);
                            }
                            
                            run2 = false;
                            resetConsoleColor();
 
                        }
                    }
                }
            }
        }

        string getInventoryItem(int itemnumber)
        {
            return inventoryarray[itemnumber];
        }

        void printHunger(int hunger)
        {
            string hungertext = "Your Hunger: ";
            positionText(hungertext, false, false);

            for (int i = 0; i < hunger; i++)
            {
                positionText("-", false, true);
            }
            cout << endl;
        }

        void printStats()
        {

            string cashtext = "Your Cash: ";

            string gpatext = "Your GPA: ";

            positionText(cashtext, false, false);

            cout << fixed << setprecision(1) << cash << endl;

            printHunger(hunger);

            positionText(gpatext, false, false);

            cout << fixed << setprecision(1) << gpa << endl;

        }

};

class School
{
    private:
        string name;
        int location;

        vector<string> coursearray;

    public:
        School(string nameval, int locationval)
        {
            name = nameval;
            location = locationval;
        }

        void startCourse(Player &player, TimeLocation &timelocation);

        string getName()
        {
            return name;
        }

        vector<string> getCourseArray()
        {
            return coursearray;
        }

        void addCourse(const string &course)
        {
            coursearray.push_back(course);
        }

        void removeCourse(const string &course)
        {
            auto it = find(coursearray.begin(), coursearray.end(), course);

            if (it != coursearray.end())
            {
                coursearray.erase(it);
            }

        }

        void printCourses()
        {
            positionText("YOUR COURSES", true, false);
            if (coursearray.size() == 0)
            {
                cout << "NONE";
            }
            else
            {
                for (int i = 0; i < coursearray.size(); i++)
                {   
                    cout << coursearray[i];
                    if (i != coursearray.size() - 1)
                    {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
        }

        void atSchool()
        {
            string positiontext = "At " + name;
            positionText(positiontext, true, false);

            printCourses();
        }

};

class TimeLocation
{
    private:
        string name;
        int location;
        int time = 8;

        string timetext = "Current Time: " + to_string(time);

    public:
        TimeLocation(string nameval, int locationval)
        {
            name = nameval;
            location = locationval;
        }

        string getName()
        {
            return name;
        }

        void setTime(int timeval)
        {
            time = timeval;
            timetext = "Current Time: " + to_string(time);
            positionText(timetext, true, false);
        }

        void updateTime(int amount)
        {
            time += amount;
            timetext = "Current Time: " + to_string(time);
        }

        void progressTime(int amount)
        {
            updateTime(amount);
            positionText("Progressing Time...", true, false);
            positionText(timetext, true, false);
        }

        int getTime()
        {
            return time;
        }

        void atTimeLocation(Player &player, School school)
        {
            bool run = true;

            string input;

            int inputarraylength = 2;
            string inputarray[2] = {"PASS TIME", "BACK"};

            timetext = "Current Time: " + to_string(time);

            positionText(timetext, true, false);

            while (run)
            {
                validateInput(input, "What Do You Want To Do", "Invalid Input. What Do You Want To Do", inputarray, inputarraylength, true, false);

                for (int i = 0; i < inputarraylength; i++)
                {

                    if (input == inputarray[1])
                    {
                        run = false;
                        break;
                    }
                    else
                    {
                        progressTime(1);
                        school.startCourse(player, *this);
                        break;
                    }
                
                }
            }
        }

    
};

void Eatery::atEatery(Player &player)
{
    bool run = true;
    string input;

    string positiontext;

    positiontext = "At " + name;

    positionText(positiontext, true, false);

    vector<string> menuarray1d(menusize);

    for (int i = 0; i < menusize; i++) {
        menuarray1d[i] = menuarray[i][0];
    }

    printMenu();

    while (run)
    {
        validateInput(input, "What Do You Want To Buy", "Invalid Item. What Do You Want To Buy", menuarray1d.data(), menusize, true, false);

        for (int i = 0; i < menusize; i++)
        {

            if (input == menuarray1d[0])
            {
                run = false;
                break;
            }
            else
            {
                player.buyFoodItem(*this, input);
                break;
            }
        
        }
    }

}

void Player::buyFoodItem(Eatery &eatery, string itemname)
        {
            int menusize = eatery.getMenuSize();
            double menuitemprice = 0.0;

            for (int i = 0; i < menusize; i++)
            {
                if (itemname == eatery.getMenuItemName(i))
                {
                    menuitemprice = stod(eatery.getMenuItemPrice(i));
                    if (cash >= menuitemprice)
                    {
                        addInventoryItem(eatery.getMenuItemName(i));
                        setConsoleColor(FOREGROUND_GREEN);
                        string buyingtext = "Buying " + itemname;
                        string inventorytext = itemname + " Added To Inventory";
                        string cashtoberemovedtext = " Removed From Account";
                        positionText(buyingtext, true, false);
                        setConsoleColor(FOREGROUND_RED);
                        cout << fixed << setprecision(1) << menuitemprice;
                        positionText(cashtoberemovedtext, true, false);
                        setConsoleColor(FOREGROUND_BLUE);
                        positionText(inventorytext, true, false);
                        resetConsoleColor();
                        cash -= menuitemprice;
                    }
                    else
                    {
                        setConsoleColor(FOREGROUND_RED);
                        string lessmoneytext = "Not Enough Money";
                        positionText(lessmoneytext, true, false);
                        resetConsoleColor();
                    }

                }
            }
}
    
void School::startCourse(Player &player, TimeLocation &timelocation)
{
    const int INPUTARRAYLENGTH = 2;
    string inputarray[INPUTARRAYLENGTH] = {"YES", "NO"};

    string input;

    int amount = 2;

    string attendtext1 = "Do You Want To Attend " + coursearray[0];
    string attendtext2 = "Do You Want To Attend " + coursearray[1];
    string attendtext3 = "Do You Want To Attend " + coursearray[2];

    string missedtext = "You Missed The Class";

    int time = timelocation.getTime();

    if (time == 11)
    {
        positionText(attendtext1, true, false);
        validateInput(input, "Yes/No", "Invalid Input. Do You Want To Attend", inputarray, INPUTARRAYLENGTH, true, false);
    }
    else if (time == 14)
    {
        positionText(attendtext2, true, false);
        validateInput(input, "Yes/No", "Invalid Input. Do You Want To Attend", inputarray, INPUTARRAYLENGTH, true, false);
    }
    else if (time == 17)
    {
        positionText(attendtext3, true, false);
        validateInput(input, "Yes/No", "Invalid Input. Do You Want To Attend", inputarray, INPUTARRAYLENGTH, true, false);
    }

    if (input == "YES")
    {
        timelocation.progressTime(amount);
    }
    else if (input == "NO")
    {
        positionText(missedtext, true, false);
        player.setStudyLoss(player.getStudyLoss() + 0.1);
        player.setGPA(player.getGPA() - player.getStudyLoss());
    }
    
}

void mainMenu(int state)
{
    string titletext = "LUMS Student Life Simulator";
    string menutext1 = "- START";
    string menutext2 = "Resume";
    string menutext3 = "- EXIT";
    string pausemenutext = "Pause Menu";

    string input;

    positionText(titletext, true, false);

    cout << endl;

    if (state == 0)
    {
        string inputarray[2] = {"START", "EXIT"};
        positionText(menutext1, true, false);
        positionText(menutext3, true, false);
        validateInput(input, "What Do You Want To Do", "Invalid Input. Start Or Exit", inputarray, 2, true, false);

        if (input == inputarray[0])
        {
            gameLoop();
        }
        else
        {
            string goodbyetext = "See You Later. Good Bye";
            positionText(goodbyetext, true, false);
        }

    }
}

void takeInput(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize)
{

    const int INPUTARRAYLENGTH = 5;

    string input;

    bool run = true;

    string inputarray[INPUTARRAYLENGTH] = {"LOCATION", "INVENTORY", "STATS", "ENDDAY"};

    while (run)
    {
        validateInput(input, "What's Your Move", "Invalid Move. What's Your Move", inputarray, INPUTARRAYLENGTH, true, false);

        for (int i = 0; i < INPUTARRAYLENGTH; i++)
        {
            if (input == inputarray[INPUTARRAYLENGTH - 1])
            {
                run = false;
                break;
            }
            else
            {
                if (input == inputarray[0])
                {
                    inputLocation(player, schoolarray, schoolarraysize, eateryarray, eateryarraysize, timelocationarray, timelocationarraysize);
                }
                else if (input == inputarray[1])
                {
                    player.accessInventory();
                }
                else if (input == inputarray[2])
                {
                    player.printStats();
                }
                break;
            }

        }

    }

}

void inputLocation(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize)
{
    const int INPUTARRAYLENGTH = 6;

    string input;

    bool run = true;

    bool printtext = true;

    string inputarray[INPUTARRAYLENGTH][2] = 
    {
    {"ENTRANCE", "MAIN"}, 
    {"SSE", "SCHOOL"}, 
    {"SDSB", "SCHOOL"},
    {"PDC", "EATERY"},
    {"LIBRARY", "TIMELOCATION"},
    {"BACK", "MAIN"}
    };

    string inputarray1d[INPUTARRAYLENGTH];

    for (int i = 0; i < INPUTARRAYLENGTH; i++)
    {
        inputarray1d[i] = inputarray[i][0];
    }
    

    while (run)
    {
        printtext = true;

        validateInput(input, "Which Location Do You Want To Go To", "Invalid Location. Which Location Do You Want To Go To", inputarray1d, INPUTARRAYLENGTH, true, false);

        for (int i = 0; i < INPUTARRAYLENGTH; i++)
        {

            if (input == inputarray[INPUTARRAYLENGTH - 1][0])
            {
                run = false;
                break;
            }
            else
            {
                if (printtext)
                {
                    printtext = false;
                    player.setLocation(input);
                    string movingtext = "Moving to " + input;
                    positionText(movingtext, true, false);
                }
                if (inputarray[i][1] == "SCHOOL")
                {
                    for (int j = 0; j < schoolarraysize; j++)
                    {
                        if (input == schoolarray[j] -> getName())
                        {
                            schoolarray[j] -> atSchool();
                            run = false;
                            break;
                        }
                    }
                }
                else if (inputarray[i][1] == "EATERY")
                {
                    for (int j = 0; j < eateryarraysize; j++)
                    {
                        if (input == eateryarray[j] -> getName())
                        {
                            eateryarray[j] -> atEatery(player);
                            run = false;
                            break;
                        }
                    }
                }
                else if (inputarray[i][1] == "TIMELOCATION")
                {
                    for (int j = 0; j < timelocationarraysize; j++)
                    {
                        if (input == timelocationarray[j] -> getName())
                        {
                            timelocationarray[j] -> atTimeLocation(player, *schoolarray[player.getSchoolIndex()]);
                            run = false;
                            break;
                        }
                    }
                }
                if (!run)
                {
                    break;
                }
            }
        }
    }
}

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}

void setConsoleColor(int color)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, color);
}

void resetConsoleColor()
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, 7);
}

void typeText(const string text, int typedelay, bool nextline)
{
    const int SOUNDDURATION = 500;

    PlaySound(TEXT("type-writing.wav"), NULL, SND_FILENAME | SND_ASYNC);

    for (int i = 0; i < text.length(); i++)
    {
        cout << text[i];

        Sleep(typedelay);

        if (i == text.length() - 1)
        {
            PlaySound(NULL, 0, 0);
        }

    }

    if (nextline)
    {
        cout << endl;
    }

}

void positionText(const string text, bool nextline, bool typetext)
{
    const int TYPEDELAY = 250;

    int textLength = text.length();

    if (typetext)
    {
        typeText(text, TYPEDELAY, nextline);
    }
    else
    {

        cout << text;
        if (nextline)
        {
            cout << endl;
        }

    }

}

void validateInput(string &input, string prompttext, string invalidprompttext, int min, int max, bool typetext)
{
    positionText(prompttext, true, typetext);

    bool run = true;

    cin.ignore();

    getline(cin, input);

   while (true)
    {

        run = true;

        if (input.length() >= min && input.length() <= max)
        {
            run = false;
        }
        

        if (!run)
        {
            break;
        }

        positionText(invalidprompttext, true, typetext);

        getline(cin, input);

    }

}

void validateInput(string &input, string prompttext, string invalidprompttext, string strarray[], int strarrays, bool upper, bool typetext)
{
    positionText(prompttext, true, typetext);

    getline(cin, input);

    bool run = true;

    if (upper)
    {
        for (int i = 0; i < input.length(); i++)
        {
            input[i] = toupper(input[i]);
        }
    }
    else
    {
        for (int i = 0; i < input.length(); i++)
        {
            input[i] = tolower(input[i]);
        }
    }

    while (true)
    {

        run = true;

        for (int i = 0; i < strarrays; i++)
        {
            if (input == strarray[i])
            {
                run = false;
                break;
            }
        }

        if (!run)
        {
            break;
        }

        positionText(invalidprompttext, true, typetext);

        getline(cin, input);

        if (upper)
        {
            for (int i = 0; i < input.length(); i++)
            {
                input[i] = toupper(input[i]);
            }
        }
        else
        {
            for (int i = 0; i < input.length(); i++)
            {
                input[i] = tolower(input[i]);
            }
        }

    }

}

void gameStart(string game_info[], int s)
{
    string name;
    string gender;
    string school;

    string gendervalidation[2] = {"MALE", "FEMALE"};
    string schoolvalidation[3] = {"SSE", "SDSB", "HSS"};

    const int NAMEMIN = 2;
    const int NAMEMAX = 10;

    const int TYPETEXT = false;

    positionText("Welcome to LUMS Student Life Simulator", true, TYPETEXT);

    cout << endl;

    positionText("Design Your Player", true, TYPETEXT);

    cout << endl;

    string nameinvalidprompttext = "The Written Name Must Be Between " + to_string(NAMEMIN) + " And " + to_string(NAMEMAX) + " Chararcters";

    validateInput(name, "What Is Your Name", nameinvalidprompttext, NAMEMIN, NAMEMAX, TYPETEXT);

    validateInput(gender, "What is Your Gender", "The Chosen Gender Must Either be Male, Or Female", gendervalidation, 2, true, TYPETEXT);

    validateInput(school, "Choose Your School", "The Chosen School Must Either be SSE, SDSB, OR HSS", schoolvalidation, 3, true, TYPETEXT);

    game_info[0] = name;
    game_info[1] = gender;
    game_info[2] = school;

}

void initializeSchool(string schoolname, School *schoolarray[], int s)
{
    int schoolindex = 0;

    bool run1 = true;
    bool run2 = true;

    string input1;
    string input2;
    string input3;

    for (int i = 0; i < s; i++)
    {
        if (schoolname == "SSE")
        {
            schoolindex = i;
            schoolarray[schoolindex]->addCourse("CAL-101");
            schoolarray[schoolindex]->addCourse("PHY-101");
            schoolarray[schoolindex]->addCourse("CS-100");
            break;
        }
    }

    // string scheduletext1 = "Design Your Schedule";
    // string scheduletext2 = "Your New Schedule";

    // positionText(scheduletext1, true, false);

    // schoolarray[schoolindex]->printCourses();

    // validateInput(input1, "Which Course Do You Want At Position 1", "Invalid Course. Which Course Do You Want At Position 1", schoolarray[schoolindex]->getCourseArray().data(), schoolarray[schoolindex]->getCourseArray().size(), true, false);

    // schoolarray[schoolindex]->removeCourse(input1);

    // validateInput(input2, "Which Course Do You Want At Position 2", "Invalid Course. Which Course Do You Want At Position 2", schoolarray[schoolindex]->getCourseArray().data(), schoolarray[schoolindex]->getCourseArray().size(), true, false);

    // schoolarray[schoolindex]->removeCourse(input2);

    // validateInput(input3, "Which Course Do You Want At Position 3", "Invalid Course. Which Course Do You Want At Position 3", schoolarray[schoolindex]->getCourseArray().data(), schoolarray[schoolindex]->getCourseArray().size(), true, false);
    
    // schoolarray[schoolindex]->removeCourse(input3);

    // schoolarray[schoolindex]->addCourse(input1);
    // schoolarray[schoolindex]->addCourse(input2);
    // schoolarray[schoolindex]->addCourse(input3);

    // positionText(scheduletext2, true, false);

    // schoolarray[schoolindex]->printCourses();

}

void initializeEatery(Eatery *eateryarray[], int s)
{
    for (int i = 0; i < s; i++)
    {
        if (eateryarray[i]->getName() == "PDC")
        {
            eateryarray[i] -> addMenuItem("BIRYANI", "500");

            eateryarray[i] -> addMenuItem("WAFFLE", "190");

            eateryarray[i] -> addMenuItem("PARATHA", "300");

        }

    }
}

void gameLoop()
{
    const int SEMESTERDURATION = 40;

    const int OPTIONSARRAYLENGTH = 2;

    double cashtobeadded = 100.0;

    string optionsarray[OPTIONSARRAYLENGTH] = {"YES", "NO"};

    bool run = true;

    string input;

    while (run)
    {
        // string game_info[3];

        string game_info[4] = {"Zyan", "Male", "SSE", "0"}; 

        // gameStart(game_info, 3);

        Player player = Player(game_info[0], game_info[1], game_info[2], stoi(game_info[3]));

        School sse = School("SSE", 0);
        School sdsb = School("SDSB", 1);

        School *schoolarray[2] = {&sse, &sdsb};

        initializeSchool(game_info[2], schoolarray, 2);

        Eatery pdc = Eatery("PDC", 2);

        Eatery *eateryarray[1] = {&pdc};

        initializeEatery(eateryarray, 1);

        TimeLocation library = TimeLocation("LIBRARY", 3);

        TimeLocation *timelocationarray[1] = {&library};

        for (int i = 1; i <= SEMESTERDURATION; i++)
        {
            string day = "Day " + to_string(i);
            string deathtext = player.getName() + " Starved to Death";
            string cashtobeaddedtext = " Added to Account";

            positionText(day, true, false);

            for (int i = 0; i < 1; i++)
            {
                timelocationarray[i]->setTime(8);
            }

            if (i != 1)
            {
                player.setHunger(player.getHunger() - 1);

                setConsoleColor(FOREGROUND_GREEN);

                cout << fixed << setprecision(1) << cashtobeadded;
                positionText(cashtobeaddedtext, true, false);

                player.setCash(player.getCash() + cashtobeadded);

                resetConsoleColor();
            }

            if (player.getHunger() == 0)
            {
                positionText(deathtext, true, false);
                break;
            }

            player.printStats();
        
            takeInput(player, schoolarray, 2, eateryarray, 1, timelocationarray, 1);

        }

        validateInput(input, "Do You Want to Retry", "Invalid Input. Do You Want To Retry", optionsarray, OPTIONSARRAYLENGTH, true, false);

        if (input == optionsarray[1])
        {
            run = false;
        }

    }

}

int main()
{
    resetConsoleColor();

    mainMenu(0);

    // gameStart(game_info, 3);

    // pdc.atEatery(player);

}