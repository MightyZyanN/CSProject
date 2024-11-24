#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player;
class School;
class Eatery;
class TimeLocation;
class NPC;
class MainWindow;

int getConsoleWidth();

void setConsoleColor(int color);

void resetConsoleColor();

void positionText(const string text, bool nextline, bool typeText);

void validateInput(string &input, string prompttext, string invalidprompttext, int min, int max, bool typetext);

void validateInput(string &input, string prompttext, string invalidprompttext, string str_array[], int str_array_s, bool upper, bool typetext);

void inputLocation(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize, NPC *npcarray[], int npcarraysize, vector<vector<string>> &locationarray, int locationarraylength);

void takeInput(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize, NPC *npcarray[], int npcarraysize, vector<vector<string>> &locationarray, int locationarraylength);

void displayOptions(string inputarray[], int s);

void mainMenu(int state);

void gameLoop(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize, NPC *npcarray[], int npcarraysize, vector<vector<string>> &locationarray, int locationarraylength, MainWindow &mainwindow, int semesterduration);

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
        int social = 0;
        int schoolindex;
        double cash = 1000.0f;
        float gpa = 4.0f;
        float studyloss = 0.0f;

        const int MAXHUNGER = 3;
        int hunger = MAXHUNGER;
        string location = "ENTRANCE";

        vector<string> inventoryarray = {"BACK"};

        vector<string> classestaken;

    public:
        Player(string nameval, string genderval, string schoolval, int schoolindexval)
        {
            name = nameval;
            gender = genderval;
            school = schoolval;
            schoolindex = schoolindexval;
        }

        void buyFoodItem(Eatery &eatery, string itemname);

        void setSocial(int amount)
        {
            social = amount;
        }

        int getSocial()
        {
            return social;
        }

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
            if (gpa <= 0)
            {
                gpa = 0;
            }
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

        void addClassTaken(const string &classtaken)
        {
            classestaken.push_back(classtaken);
        }

        vector<string> getClassesTaken()
        {
            return classestaken;
        }

        void removeClassesTaken()
        {
            for (int i = classestaken.size() - 1; i >= 0; i--)
            {
                classestaken.pop_back();
            }
        }

        void printClassesTaken()
        {
            positionText("CLASSES TAKEN", true, false);
            if (classestaken.size() == 0)
            {
                cout << "NONE";
            }
            else
            {
                for (int i = 0; i < classestaken.size(); i++)
                {   
                    cout << classestaken[i];
                    if (i != classestaken.size() - 1)
                    {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
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

                        displayOptions(optionarray, OPTIONARRAYSIZE);

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
                            if (hunger < MAXHUNGER)
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
                positionText("-", false, false);
            }
            cout << endl;
        }

        string getHungerString()
        {
            string input = "";
            for (int i = 0; i < hunger; i++)
            {
                input = input + "-";
            }

            return input;
        }

        void printStats()
        {

            string cashtext = "Your Cash: ";

            string gpatext = "Your GPA: ";

            string socialtext = "Your Social Factor: ";

            positionText(cashtext, false, false);

            cout << fixed << setprecision(1) << cash << endl;

            printHunger(hunger);

            positionText(gpatext, false, false);

            cout << fixed << setprecision(1) << gpa << endl;

            positionText(socialtext, false, false);

            cout << social << endl;

        }

};

class School
{
    private:
        string name;
        int location;

        vector<string> coursearray;

        const int TIME1 = 11;
        const int TIME2 = 14;
        const int TIME3 = 17;

        int timearray[3] = {TIME1, TIME2, TIME3}; 

    public:
        School(string nameval, int locationval)
        {
            name = nameval;
            location = locationval;
        }

        void startCourse(Player &player, TimeLocation &timelocation, NPC *npcarray[], bool npccheck);

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

        void printCourses(bool showtime)
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
                    if (showtime)
                    {
                        cout << " @ Time: " << timearray[i];
                    }
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

            printCourses(true);
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
            if (time <= 24)
            {
                updateTime(amount);
                positionText("Progressing Time...", true, false);
                positionText(timetext, true, false);
            }
            else
            {
                positionText("Day Has Ended. Please Type ENDDAY", true, false);
                time = 24;
            }

        }

        int getTime()
        {
            return time;
        }

        void atTimeLocation(Player &player, School &school, NPC *npcarray[])
        {
            bool run = true;

            string input;

            const int INPUTARRAYLENGTH = 2;
            string inputarray[INPUTARRAYLENGTH] = {"PASSTIME", "BACK"};

            timetext = "Current Time: " + to_string(time);

            positionText(timetext, true, false);

            while (run)
            {

                displayOptions(inputarray, INPUTARRAYLENGTH);

                validateInput(input, "What Do You Want To Do", "Invalid Input. What Do You Want To Do", inputarray, INPUTARRAYLENGTH, true, false);

                for (int i = 0; i < INPUTARRAYLENGTH; i++)
                {

                    if (input == inputarray[1])
                    {
                        run = false;
                        break;
                    }
                    else
                    {
                        progressTime(1);
                        school.startCourse(player, *this, npcarray, true);
                        break;
                    }
                
                }
            }
        }

    
};

class NPC
{
    private:
        string name;
        int time;
        int social;

    public:
        NPC(string nameval, int timeval)
        {
            name = nameval;
            time = timeval;
        }

        int getTime()
        {
            return time;
        }

        void run(Player &player, TimeLocation &timelocation)
        {
            const int INPUTARRAYLENGTH = 2;
            string inputarray[INPUTARRAYLENGTH] = {"YES", "NO"};

            string input;

            int timeamount = 2;
            int socialamount = 1;

            string npctext1 = name + " Has Approached You";
            string npctext2 = "Do You Want To Hangout With " + name;

            string socialtext1 = "Social Increased";

            positionText(npctext1, true, false);
            positionText(npctext2, true, false);

            validateInput(input, "Yes/No", "Invalid Input. Do You Want To Hangout", inputarray, INPUTARRAYLENGTH, true, false);

            if (input == inputarray[0])
            {
                timelocation.progressTime(timeamount);
                setConsoleColor(FOREGROUND_GREEN);
                positionText(socialtext1, true, false);
                player.setSocial(player.getSocial() + socialamount);
                social += socialamount;
            }
            resetConsoleColor();

        }
};

class MainWindow
{
    private:
        RenderWindow window;

        const int WIDTH = 1280;
        const int HEIGHT = 1280;

        Font font;
        Text titletext;
        Text inputfield;
        Text timetext;
        Text cashtext;
        Text hungertext;
        Text gpatext;

        const int TEXTFONTSIZE = 48;

        double cash;
        float gpa;
        string hungerstring;

        atomic<bool> running;

        string input;
        bool istyping = true;

        Player &player;

        School *schoolarray[2];
        int schoolarraysize;

        Eatery *eateryarray[1];
        int eateryarraysize;

        TimeLocation &library;

        NPC *npcarray[3];
        int npcarraysize;

        vector<ConvexShape> mapcells;
        vector<Text> maplabels;

        vector<string> locationarray;

        void handleEvents()
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
        }

        void update()
        {
            cash = player.getCash();
            gpa = player.getGPA();

            ostringstream oss;

            oss.precision(1);

            oss << fixed << cash;

            string cashstr = oss.str();

            oss.str("");
            oss.clear();
            oss.precision(1);

            oss << fixed << gpa;

            string gpastr = oss.str();

            cashtext.setString("Cash: " + cashstr);

            timetext.setString("Time: " + to_string(library.getTime()));

            hungerstring = player.getHungerString();

            hungertext.setString("Hunger: " + hungerstring);

            gpatext.setString("GPA: " + gpastr);

        }

        void render()
        {
            window.clear();
            window.draw(titletext);
            window.draw(timetext);
            window.draw(cashtext);
            window.draw(gpatext);
            window.draw(hungertext);

            for (const auto &cell : mapcells)
            {
                window.draw(cell);
            }
            for (auto &label : maplabels)
            {
                window.draw(label);
                if (player.getLocation() == label.getString())
                {
                    label.setFillColor(Color::Green);
                }
                else
                {
                    label.setFillColor(Color::White);
                }
            }

            window.display();
        }

    void centerTitleText()
    {
        FloatRect textRect = titletext.getLocalBounds();
        titletext.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        titletext.setPosition(Vector2f(window.getSize().x / 2.0f, 50));
    }   

    public:
        MainWindow(Player &playerval, School *schooarrayval[], int schoolarraysizeval, Eatery *eateryarrayval[], int eateryarraysizeval, TimeLocation &libraryval,  NPC *npcarrayval[], int npcarraysizeval) 
        : player(playerval), schoolarraysize(schoolarraysizeval), eateryarraysize(eateryarraysizeval), library(libraryval), npcarraysize(npcarraysizeval), running(true)
        {

            window.create(VideoMode(1280, 720), "LUMS STUDENT LIFE SIMULATOR");

            Image icon;

            if (!icon.loadFromFile("logo.png"))
            {
                cerr << "Could Not Load Icon" << endl;
            }
            else
            {
                window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
            }

            if (!font.loadFromFile("Roboto/Roboto-Bold.ttf"))
            {
                cerr << "Could Not Load Font" << endl;
            }

            titletext.setFont(font);
            titletext.setCharacterSize(46);
            titletext.setFillColor(Color::White);
            titletext.setString("LUMS STUDENT LIFE SIMULATOR");
            centerTitleText();
            
            timetext.setFont(font);
            timetext.setCharacterSize(TEXTFONTSIZE);
            timetext.setPosition(20, 200);
            timetext.setFillColor(Color::White);
            timetext.setString("Time: " + to_string(library.getTime()));

            cashtext.setFont(font);
            cashtext.setCharacterSize(TEXTFONTSIZE);
            cashtext.setPosition(20, 300);
            cashtext.setFillColor(Color::White);

            gpatext.setFont(font);
            gpatext.setCharacterSize(TEXTFONTSIZE);
            gpatext.setPosition(20, 400);
            gpatext.setFillColor(Color::White);

            hungertext.setFont(font);
            hungertext.setCharacterSize(TEXTFONTSIZE);
            hungertext.setPosition(20, 500);
            hungertext.setFillColor(Color::White);

        }

        void run()
        {

            while (running && window.isOpen())
            {
                HWND hwnd = window.getSystemHandle();
                SetWindowPos(hwnd, HWND_TOPMOST, 600, 100, 1280, 720, SWP_NOSIZE);
                handleEvents();
                render();
                update();
            
            }

            window.close();
        }

        void setLocationArray(string locationarray1d[], int locationarray1dlength)
        {
            for (int i = 0; i < locationarray1dlength; i++)
            {
                locationarray.push_back(locationarray1d[i]);
            }

        }

        void createMap()
        {
            const int cellSize = 150;
            const int rows = 3;
            const int cols = 3;

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++) {
                    ConvexShape cell;
                    cell.setPointCount(8);

                    cell.setPoint(0, Vector2f(0, 20));
                    cell.setPoint(1, Vector2f(20, 0));
                    cell.setPoint(2, Vector2f(cellSize - 20, 0));
                    cell.setPoint(3, Vector2f(cellSize, 20));

                    cell.setPoint(4, Vector2f(cellSize, cellSize - 20));
                    cell.setPoint(5, Vector2f(cellSize - 20, cellSize));
                    cell.setPoint(6, Vector2f(20, cellSize));
                    cell.setPoint(7, Vector2f(0, cellSize - 20));

                    cell.setPosition(WIDTH - 500 + col * cellSize, 160 + row * cellSize);
                    cell.setFillColor(Color::Blue);
                    cell.setOutlineColor(Color::Black);
                    cell.setOutlineThickness(2);
                    mapcells.push_back(cell);

                    Text label;
                    label.setFont(font);
                    label.setString(locationarray[row * cols + col]);
                    label.setCharacterSize(22);
                    label.setFillColor(Color::White);
                    FloatRect textRect = label.getLocalBounds();
                    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    label.setPosition(cell.getPosition().x + cellSize / 2, cell.getPosition().y + cellSize / 2);
                    maplabels.push_back(label);

                }
            }
        }

        void stop()
        {
            running = false;
        }

        string getInput()
        {
            return input;
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
    
void School::startCourse(Player &player, TimeLocation &timelocation, NPC *npcarray[], bool npccheck)
{
    const int INPUTARRAYLENGTH = 2;
    string inputarray[INPUTARRAYLENGTH] = {"YES", "NO"};

    string input;

    int amount = 2;

    string classtaken;

    string attendtext1 = "Do You Want To Attend " + coursearray[0];
    string attendtext2 = "Do You Want To Attend " + coursearray[1];
    string attendtext3 = "Do You Want To Attend " + coursearray[2];

    string missedtext1 = "You Missed The Class";

    int time1 = 11;
    int time2 = 14;
    int time3 = 17;

    int time = timelocation.getTime();

    for (int i = 0; i < 3; i++)
    {
        if (npcarray[i]->getTime() == time && npccheck)
        {
            npcarray[i]->run(player, timelocation);
            startCourse(player, timelocation, npcarray, false);
        }
    }

    if (time == time1)
    {
        positionText(attendtext1, true, false);
        validateInput(input, "Yes/No", "Invalid Input. Do You Want To Attend", inputarray, INPUTARRAYLENGTH, true, false);
        classtaken = coursearray[0];
    }
    else if (time == time2)
    {
        positionText(attendtext2, true, false);
        validateInput(input, "Yes/No", "Invalid Input. Do You Want To Attend", inputarray, INPUTARRAYLENGTH, true, false);
        classtaken = coursearray[1];
    }
    else if (time == time3)
    {
        positionText(attendtext3, true, false);
        validateInput(input, "Yes/No", "Invalid Input. Do You Want To Attend", inputarray, INPUTARRAYLENGTH, true, false);
        classtaken = coursearray[2];
    }

    if (input == "YES")
    {
        timelocation.progressTime(amount);
        player.addClassTaken(classtaken);
        time = timelocation.getTime();
        startCourse(player, timelocation, npcarray, true);
    }
    else if (input == "NO")
    {
        setConsoleColor(FOREGROUND_RED);
        positionText(missedtext1, true, false);
        resetConsoleColor();
    }
    
}

void atMain()
{
    string input;

    const int OPTIONSARRAYLENGTH = 2;

    string optionsarray[OPTIONSARRAYLENGTH] = {"YES", "NO"};

    displayOptions(optionsarray, OPTIONSARRAYLENGTH);

    validateInput(input, "Do You Want To Leave LUMS?", "Invalid Input. YES/NO", optionsarray, OPTIONSARRAYLENGTH, true, false);

    if (input == optionsarray[0])
    {
        const int ENDPROMTARRAYLENGTH = 3;
        string endpromptarray[ENDPROMTARRAYLENGTH] = {"Looks Like You Couldn't Withstand LUMS... Sad", "Leaving So Soon...", "Why Did You Even Come Here..."};

        srand(static_cast<unsigned int>(time(0)));

        int randendpromptindex = rand() % ENDPROMTARRAYLENGTH;

        string randendprompt = endpromptarray[randendpromptindex];

        positionText(randendprompt, true, true);

        Sleep(1);
        
        exit(0);
    }
}

void mainMenu(int state)
{
    string titletext = "LUMS Student Life Simulator";
    string menutext1 = "- START";
    string menutext2 = "- RESUME";
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

        if (input == inputarray[1])
        {
            string goodbyetext = "See You Later. Good Bye";
            positionText(goodbyetext, true, false);
            Sleep(1000);
            exit(0);
        }

    }
    else if (state == 1)
    {
        string inputarray[2] = {"RESUME", "EXIT"};
        positionText(pausemenutext, true, false);
        positionText(menutext2, true, false);
        positionText(menutext3, true, false);
        validateInput(input, "What Do You Want To Do", "Invalid Input. Resume Or Exit", inputarray, 2, true, false);
        if (input == inputarray[1])
        {
            string goodbyetext = "See You Later. Good Bye";
            positionText(goodbyetext, true, false);
            Sleep(1000);
            exit(0);
        }
    }
}

void displayOptions(string inputarray[], int s)
{
    cout << endl;
    positionText("POSSIBLE OPTIONS", true, false);
    for (int i = 0; i < s; i++)
    {
        cout << "- " << inputarray[i] << endl;
    }

}

void takeInput(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize, NPC *npcarray[], int npcarraysize, vector<vector<string>> &locationarray, int locationarraylength)
{

    const int INPUTARRAYLENGTH = 5;

    string input;

    bool run = true;

    string inputarray[INPUTARRAYLENGTH] = {"LOCATION", "INVENTORY", "STATS", "PAUSE", "ENDDAY"};

    while (run)
    {

        displayOptions(inputarray, INPUTARRAYLENGTH);

        validateInput(input, "What's Your Move", "Invalid Move. What's Your Move", inputarray, INPUTARRAYLENGTH, true, false);

        for (int i = 0; i < INPUTARRAYLENGTH; i++)
        {
            if (input == inputarray[INPUTARRAYLENGTH - 1])
            {
                run = false;
                break;
            }
            else if (input == inputarray[INPUTARRAYLENGTH - 2])
            {
                mainMenu(1);
                input = "";
            }
            else
            {
                if (input == inputarray[0])
                {
                    inputLocation(player, schoolarray, schoolarraysize, eateryarray, eateryarraysize, timelocationarray, timelocationarraysize, npcarray, npcarraysize, locationarray, locationarraylength);
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

void inputLocation(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize, NPC *npcarray[], int npcarraysize, vector<vector<string>> &locationarray, int locationarraylength)
{

    string input;

    bool run = true;

    bool printtext = true;

    vector<string> locationarray1d;

    for (int i = 0; i < locationarraylength; i++)
    {
        locationarray1d.push_back(locationarray[i][0]);
    }

    while (run)
    {
        printtext = true;

        displayOptions(locationarray1d.data(), locationarraylength);

        validateInput(input, "Which Location Do You Want To Go To", "Invalid Location. Which Location Do You Want To Go To", locationarray1d.data(), locationarraylength, true, false);

        for (int i = 0; i < locationarraylength; i++)
        {

            if (input == locationarray[locationarraylength - 1][0])
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

                if (locationarray[i][1] == "SCHOOL")
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
                else if (locationarray[i][1] == "EATERY")
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
                else if (locationarray[i][1] == "TIMELOCATION")
                {
                    for (int j = 0; j < timelocationarraysize; j++)
                    {
                        if (input == timelocationarray[j] -> getName())
                        {
                            timelocationarray[j] -> atTimeLocation(player, *schoolarray[player.getSchoolIndex()], npcarray);
                            run = false;
                            break;
                        }
                    }
                }
                else if (locationarray[i][1] == "MAIN")
                {
                    if (input == locationarray[i][0])
                    {
                        atMain();
                        run = false;
                        break;
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
    const int TYPEDELAY = 100;

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

void gameStart(string game_info[], int s, int semesterduration)
{
    string name;
    string gender;
    string school;
    
    const int GENDERVALIDATIONARRAYLENGTH = 2;
    string gendervalidationarray[GENDERVALIDATIONARRAYLENGTH] = {"MALE", "FEMALE"};

    const int SCHOOLVALIDATIONARRAYLENGTH = 2;
    string schoolvalidationarray[SCHOOLVALIDATIONARRAYLENGTH] = {"SSE", "SDSB"};

    const int NAMEMIN = 2;
    const int NAMEMAX = 10;

    const int TYPETEXT = true;

    string titletext = "WELCOME TO LUMS STUDENT LIFE SIMULATOR";
    string infotext = "Your Goal Is To Survive " + to_string(semesterduration) + " Days With a GPA of 3.7 and a Social Factor of 3";

    int titletextlength = titletext.length();

    int spaces = (getConsoleWidth() - titletextlength) / 2;

    for (int i = 0; i < spaces; i++)
    {
        cout << ' ';
    }

    positionText("WELCOME TO LUMS STUDENT LIFE SIMULATOR", true, TYPETEXT);

    cout << endl;

    positionText(infotext, true, TYPETEXT);

    cout << endl;

    string nameinvalidprompttext = "The Written Name Must Be Between " + to_string(NAMEMIN) + " And " + to_string(NAMEMAX) + " Chararcters";

    validateInput(name, "What Is Your Name", nameinvalidprompttext, NAMEMIN, NAMEMAX, TYPETEXT);

    positionText("What Is Your Gender", true, TYPETEXT);

    displayOptions(gendervalidationarray, GENDERVALIDATIONARRAYLENGTH);

    validateInput(gender, "", "The Chosen Gender Must Either Be Male, Or Female", gendervalidationarray, GENDERVALIDATIONARRAYLENGTH, true, false);

    positionText("Choose Your School", true, TYPETEXT);

    displayOptions(schoolvalidationarray, SCHOOLVALIDATIONARRAYLENGTH);

    validateInput(school, "", "The Chosen School Must Either Be SSE, Or SDSB", schoolvalidationarray, SCHOOLVALIDATIONARRAYLENGTH, true, false);

    cout << endl;

    game_info[0] = name;
    game_info[1] = gender;
    game_info[2] = school;

    int schoolindex = schoolvalidationarray->find(school);

    game_info[3] = to_string(schoolindex);

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
        else if (schoolname == "SDSB")
        {
            schoolindex = i;
            schoolarray[schoolindex]->addCourse("ACCT-100");
            schoolarray[schoolindex]->addCourse("MECO-111");
            schoolarray[schoolindex]->addCourse("MGMT-142");
        }
    }

    string scheduletext1 = "Design Your Schedule";
    string scheduletext2 = "Your New Schedule";

    positionText(scheduletext1, true, false);

    schoolarray[schoolindex]->printCourses(false);

    validateInput(input1, "Which Course Do You Want At Position 1", "Invalid Course. Which Course Do You Want At Position 1", schoolarray[schoolindex]->getCourseArray().data(), schoolarray[schoolindex]->getCourseArray().size(), true, false);

    schoolarray[schoolindex]->removeCourse(input1);

    validateInput(input2, "Which Course Do You Want At Position 2", "Invalid Course. Which Course Do You Want At Position 2", schoolarray[schoolindex]->getCourseArray().data(), schoolarray[schoolindex]->getCourseArray().size(), true, false);

    schoolarray[schoolindex]->removeCourse(input2);

    validateInput(input3, "Which Course Do You Want At Position 3", "Invalid Course. Which Course Do You Want At Position 3", schoolarray[schoolindex]->getCourseArray().data(), schoolarray[schoolindex]->getCourseArray().size(), true, false);
    
    schoolarray[schoolindex]->removeCourse(input3);

    schoolarray[schoolindex]->addCourse(input1);
    schoolarray[schoolindex]->addCourse(input2);
    schoolarray[schoolindex]->addCourse(input3);

    positionText(scheduletext2, true, false);

    schoolarray[schoolindex]->printCourses(true);

}

void initializeEatery(Eatery *eateryarray[], int s)
{
    for (int i = 0; i < s; i++)
    {
        if (eateryarray[i] -> getName() == "PDC")
        {
            eateryarray[i] -> addMenuItem("BIRYANI", "200");

            eateryarray[i] -> addMenuItem("PULAO", "175");

            eateryarray[i] -> addMenuItem("CHICKENTIKKA", "300");
        }

        if (eateryarray[i] -> getName() == "JJ")
        {
            eateryarray[i] -> addMenuItem("BURGER", "500");

            eateryarray[i] -> addMenuItem("SANDWHICH", "250");

            eateryarray[i] -> addMenuItem("PASTA", "325");
        }

        if (eateryarray[i] -> getName() == "BAITHAK")
        {
            eateryarray[i] -> addMenuItem("ALOOPARATHA", "200");

            eateryarray[i] -> addMenuItem("ANDASHAMI", "250");

            eateryarray[i] -> addMenuItem("KULFI", "100");
        }

        if (eateryarray[i] -> getName() == "GREENOLIVE")
        {
            eateryarray[i] -> addMenuItem("FALAFEL", "200");

            eateryarray[i] -> addMenuItem("GYRORICE", "250");

            eateryarray[i] -> addMenuItem("SHAWARMA", "200");
        }

    }
}

void playLoopingSound(const std::wstring& soundfile)
{
    PlaySoundW(soundfile.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void stopSound()
{
    PlaySound(NULL, 0, 0);
}

void inititializeClasses(int semsterduration)
{
    string game_info[4];

    gameStart(game_info, 4, semsterduration);
    
    thread soundThread(playLoopingSound, L"music.wav");

    Player player = Player(game_info[0], game_info[1], game_info[2], stoi(game_info[3]));

    School sse = School("SSE", 0);
    School sdsb = School("SDSB", 1);

    const int SCHOOLARRAYLENGTH = 2;
    School *schoolarray[SCHOOLARRAYLENGTH] = {&sse, &sdsb};

    initializeSchool(game_info[2], schoolarray, SCHOOLARRAYLENGTH);

    Eatery pdc = Eatery("PDC", 2);

    Eatery jj = Eatery("JJ", 3);

    Eatery baithak = Eatery("BAITHAK", 4);

    Eatery greenolive = Eatery("GREENOLIVE", 5);

    const int EATERYARRAYLENGTH = 3;
    Eatery *eateryarray[EATERYARRAYLENGTH] = {&pdc, &jj, &baithak};

    initializeEatery(eateryarray, EATERYARRAYLENGTH);

    TimeLocation library = TimeLocation("LIBRARY", 6);

    const int TIMELOCATIONARRAYLENGTH = 1;

    TimeLocation *timelocationarray[TIMELOCATIONARRAYLENGTH] = {&library};

    srand(static_cast<unsigned int>(time(0)));

    int randomtime = rand() % 6 + 9;

    // cout << "Random Time " << randomtime << endl;

    NPC ahmed = NPC("AHMED", randomtime);

    NPC ali = NPC("ALI", randomtime + 3);

    NPC ayaan = NPC("AYAAN", randomtime + 6);

    const int NPCARRAYLENGTH = 3;

    NPC *npcarray[NPCARRAYLENGTH] = {&ahmed, &ali, &ayaan};

    const int LOCATIONARRAYLENGTH = 10;

    vector<vector<string>> locationarray = 
    {
    {"ENTRANCE", "MAIN"}, 
    {"SSE", "SCHOOL"}, 
    {"SDSB", "SCHOOL"},
    {"PDC", "EATERY"},
    {"JJ", "EATERY"},
    {"BAITHAK", "EATERY"},
    {"GREENOLIVE", "EATERY"},
    {"LIBRARY", "TIMELOCATION"},
    {"EXIT", "MAIN"},
    {"BACK", "MAIN"}
    };

    vector<string> locationarray1d;

    for (int i = 0; i < LOCATIONARRAYLENGTH; i++)
    {
        locationarray1d.push_back(locationarray[i][0]);
    }

    MainWindow mainwindow(player, schoolarray, SCHOOLARRAYLENGTH, eateryarray, EATERYARRAYLENGTH, library, npcarray, NPCARRAYLENGTH);

    mainwindow.setLocationArray(locationarray1d.data(), LOCATIONARRAYLENGTH);

    mainwindow.createMap();

    thread gameThread(gameLoop, ref(player), schoolarray, SCHOOLARRAYLENGTH, eateryarray, EATERYARRAYLENGTH, timelocationarray, TIMELOCATIONARRAYLENGTH, npcarray, NPCARRAYLENGTH, ref(locationarray), LOCATIONARRAYLENGTH, ref(mainwindow), semsterduration);

    mainwindow.run();

    gameThread.join();

}

void gameLoop(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize, TimeLocation *timelocationarray[], int timelocationarraysize, NPC *npcarray[], int npcarraysize, vector<vector<string>> &locationarray, int locationarraylength, MainWindow &mainwindow, const int SEMESTERDURATION)
{

    const int OPTIONSARRAYLENGTH = 2;

    double cashtobeadded = 100.0;

    string optionsarray[OPTIONSARRAYLENGTH] = {"YES", "NO"};

    bool run = true;

    bool won = false;

    string input;

    mainMenu(0);

    while (run)
    {

        for (int i = 1; i <= SEMESTERDURATION; i++)
        {
            string day = "Day " + to_string(i);
            string deathtext = player.getName() + " Starved to Death";
            string cashtobeaddedtext = " Added to Account";

            string missedtext1 = "You Missed 1 Class";
            string missedtext2 = "You Missed 2 Classes";
            string missedtext3 = "You Missed 3 Classes";
            string missedtext4 = "GPA Affected";
            string takentext1 = "You Took All Classes";

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
                setConsoleColor(FOREGROUND_RED);
                positionText(deathtext, true, false);
                resetConsoleColor();
                break;
            }

            player.printStats();
        
            takeInput(player, schoolarray, schoolarraysize, eateryarray, eateryarraysize, timelocationarray, timelocationarraysize, npcarray, npcarraysize, locationarray, locationarraylength);

            player.printClassesTaken();

            if (player.getClassesTaken().size() == 3)
            {
                setConsoleColor(FOREGROUND_GREEN);
                positionText(takentext1, true, false);
            }
            else
            {
                setConsoleColor(FOREGROUND_RED);
                if (player.getClassesTaken().size() == 2)
                {
                    positionText(missedtext1, true, false);
                    player.setStudyLoss(player.getStudyLoss() + 0.1);
                }
                else if (player.getClassesTaken().size() == 1)
                {
                    positionText(missedtext2, true, false);
                    player.setStudyLoss(player.getStudyLoss() + 0.2);
                }
                else if (player.getClassesTaken().size() == 0)
                {
                    positionText(missedtext3, true, false);
                    player.setStudyLoss(player.getStudyLoss() + 0.3);
                }
                
                positionText(missedtext4, true, false);

            }

            player.setGPA(player.getGPA() - player.getStudyLoss());

            player.setStudyLoss(0);

            player.removeClassesTaken();

            if (i == SEMESTERDURATION && player.getGPA() >= 3.7 && player.getSocial() >= 3)
            {
                won = true;
            }

            resetConsoleColor();

        }

        if (!won)
        {

            positionText("You Failed!!!", true, true);
            validateInput(input, "Do You Want to Retry", "Invalid Input. Do You Want To Retry", optionsarray, OPTIONSARRAYLENGTH, true, false);

            if (input == optionsarray[1])
            {
                string goodbyetext = "See You Later. Good Bye";
                positionText(goodbyetext, true, false);
                Sleep(1000);
                exit(0);
            }
            else
            {
                mainwindow.stop();
                inititializeClasses(SEMESTERDURATION);
            }

        }
        else
        {
            positionText("Congratulations!!! You Won!!!", true, true);
            positionText("Thanks For Playing!!!", true, true);
            Sleep(1);
            exit(0);
        }
    }

}

int main()
{

    const int SEMESTERDURATION = 5;

    resetConsoleColor();

    inititializeClasses(SEMESTERDURATION);

    return 0;

}