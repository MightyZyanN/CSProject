#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

class Player;
class School;
class Eatery;

int getConsoleWidth();

void positionText(const string &text, bool center, bool nextline, bool typeText, int offset);

void validateInput(string &input, string prompttext, string invalidprompttext, int min, int max, bool typetext, int offset);

void validateInput(string &input, string prompttext, string invalidprompttext, string str_array[], int str_array_s, bool upper, bool typetext, int offset);

void inputLocation(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize);


class Eatery
{
    private:
        string name;
        int location;

        vector<vector<string>> menuarray;
        int menusize;

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
            vector<string> oneitem = {itemname, itemprice};
            menuarray.push_back(oneitem);
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

};

class Player
{
	private:
        string name;
        string gender;
        string school;
        double cash = 1000.0;
        float gpa = 4.0f;
        int hunger = 10;
        string location = "ENTRANCE";

        vector<string> inventoryarray = {"BACK"};

    public:
        Player(string nameval, string genderval, string schoolval)
        {
            name = nameval;
            gender = genderval;
            school = schoolval;
        }

        void buyFoodItem(Eatery &eatery, string itemname);

        string getName()
        {
            return name;
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
            positionText("Inventory", false, true, false, -19);
            positionText("", false, false, false, -19);
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
                validateInput(input1, "What Do You Want To Access", "Invalid Item. What Do You Want To Access", inventoryarray.data(), inventoryarray.size(), true, false, -19);

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

                        validateInput(input2, "What Do You Want To Do", "Invalid Item. What Do You Want To Do", optionarray, OPTIONARRAYSIZE, true, false, -19);

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
                                positionText(text1, false, true, false, -19);
                                positionText(text2, false, true, false, -19);
                                removeInventoryItem(input1);
                            }
                            else
                            {
                                positionText(text3, false, true, false, -19);
                            }
                            
                            run2 = false;
 
                        }
                    }
                }
            }
        }

        string getInventoryItem(int itemnumber)
        {
            return inventoryarray[itemnumber];
        }

        void printStats()
        {
            positionText(name, false, true, false, -19);
            positionText(gender, false, true, false, -19);
            positionText(location, false, true, false, -19);

            positionText(to_string(cash), false, true, false, -19);
            positionText(to_string(hunger), false, true, false, -19);
            // positionText(name, false, true, false, -19);

        }

};

class School
{
    private:
        string name;
        int location;

    public:
        School(string nameval, int locationval)
        {
            name = nameval;
            location = locationval;
        }

        string getName()
        {
            return name;
        }

        void atSchool()
        {
            string text = "At " + name;
            positionText(text, false, true, false, -19);
        }

};

void Eatery::atEatery(Player &player)
{
    bool run = true;
    string input;

    string text;

    text = "At " + name;

    positionText(text, false, true, false, -19);

    vector<string> menuarray1d(menusize);

    for (int i = 0; i < menusize; i++) {
        menuarray1d[i] = menuarray[i][0];
    }

    while (run)
    {
        validateInput(input, "What Do You Want To Buy", "Invalid Item. What Do You Want To Buy", menuarray1d.data(), menusize, true, false, -19);

        for (int i = 0; i < menusize; i++)
        {

            if (input == menuarray1d[menusize - 1])
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
                        string text1 = "Buying " + itemname;
                        string text2 = itemname + " Added To Inventory";
                        positionText(text1, false, true, false, -19);
                        positionText(text2, false, true, false, -19);
                        cash -= menuitemprice;
                    }
                    else
                    {
                        string text = "Not Enough Money";
                        positionText(text, false, true, false, -19);
                    }

                }
            }
}
    
void takeInput(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize)
{

    const int INPUTARRAYLENGTH = 4;

    string input;

    bool run = true;

    string inputarray[INPUTARRAYLENGTH] = {"LOCATION", "INVENTORY", "STATS", "ENDDAY"};

    while (run)
    {
        validateInput(input, "What's Your Move", "Invalid Move. What's Your Move", inputarray, 4, true, false, -19);

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
                    inputLocation(player, schoolarray, schoolarraysize, eateryarray, eateryarraysize);
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

void inputLocation(Player &player, School *schoolarray[], int schoolarraysize, Eatery *eateryarray[], int eateryarraysize)
{
    const int INPUTARRAYLENGTH = 5;

    string input;

    bool run = true;

    bool printtext = true;

    string inputarray[INPUTARRAYLENGTH][2] = 
    {
    {"ENTRANCE", "MAIN"}, 
    {"SSE", "SCHOOL"}, 
    {"SDSB", "SCHOOL"},
    {"PDC", "EATERY"},
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

        validateInput(input, "Which Location Do You Want To Go To", "Invalid Location", inputarray1d, INPUTARRAYLENGTH, true, false, -19);

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
                    string text = "Moving to " + input;
                    positionText(text, false, true, false, -19);
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

void typeText(string text, int typedelay, bool nextline)
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

void positionText(const string &text, bool center, bool nextline, bool typetext, int offset)
{
    const int TYPEDELAY = 250;

    int consoleWidth = getConsoleWidth();
    int textLength = text.length();
    int spaces;

    if (center)
    {
        spaces = ((consoleWidth - textLength) / 2) + offset;
    }
    else
    {
        spaces = ((consoleWidth) / 2) + offset;
    }

    if (typetext)
    {
        cout << string(spaces, ' ');
        typeText(text, TYPEDELAY, nextline);
    }
    else
    {
        cout << string(spaces, ' ') << text;

        if (nextline)
        {
            cout << endl;
        }

    }

}

void validateInput(string &input, string prompttext, string invalidprompttext, int min, int max, bool typetext, int offset)
{
    positionText(prompttext, false, true, typetext, offset);

    positionText("", false, false, typetext, offset);

    while((getline(cin, input)) && ((input.length() < min) || (input.length() > max)))
    {
        positionText(invalidprompttext, false, true, typetext, offset);
        positionText("", false, false, typetext, offset);
    }

}

void validateInput(string &input, string prompttext, string invalidprompttext, string str_array[], int str_array_s, bool upper, bool typetext, int offset)
{
    positionText(prompttext, false, true, typetext, offset);

    positionText("", false, false, typetext, offset);

    cin >> input;

    bool run;

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
        // cout << "Written: " << input << endl;
        run = true;

        for (int i = 0; i < str_array_s; i++)
        {
            if (input == str_array[i])
            {
                run = false;
                break;
            }
        }

        if (!run)
        {
            break;
        }

        positionText(invalidprompttext, false, true, typetext, offset);

        positionText("", false, false, typetext, offset);

        cin >> input;

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

int gameStart(string game_info[], int s)
{
    string name;
    string gender;
    string school;

    string gender_validation[3] = {"male", "female", "other"};
    string school_validation[3] = {"SSE", "SDSB", "HSS"};

    const int NAMEMIN = 3;
    const int NAMEMAX = 10;

    const int TEXTOFFSET = -19;

    const int TYPETEXT = true;

    positionText("Welcome to LUMS Student Life Simulator", true, true, true, 0);

    cout << endl;

    positionText("Design Your Player", false, true, true, TEXTOFFSET);

    cout << endl;

    validateInput(name, "Choose Your Name", "The Chosen Name Must be Between 2 and 10 Characters", 2, 15, TYPETEXT, TEXTOFFSET);

    validateInput(gender, "Choose Your Gender", "The Chosen Gender Must Either be Male, Female OR Other", gender_validation, 3, false, TYPETEXT, TEXTOFFSET);

    validateInput(school, "Choose Your School", "The Chosen School Must Either be SSE, SDSB, OR HSS", school_validation, 3, true, TYPETEXT, TEXTOFFSET);

    game_info[0] = name;
    game_info[1] = gender;
    game_info[2] = school;

    return 1;
}

void gameLoop()
{
    const int SEMESTERDURATION = 40;

    const int OPTIONSARRAYLENGTH = 2;

    string optionsarray[OPTIONSARRAYLENGTH] = {"YES", "NO"};

    bool run = true;

    string input;

    while (run)
    {

        string game_info[3] = {"Zyan", "Male", "SSE"}; 

        Player player = Player(game_info[0], game_info[1], game_info[2]);

        School sse = School("SSE", 0);
        School sdsb = School("SDSB", 1);

        School *schoolarray[2] = {&sse, &sdsb};

        Eatery pdc = Eatery("PDC", 2);

        Eatery *eateryarray[] = {&pdc};

        pdc.addMenuItem("BIRYANI", "500");

        pdc.addMenuItem("WAFFLE", "190");

        pdc.addMenuItem("PARATHA", "300");

        pdc.addMenuItem("BACK", "-1");

        for (int i = 1; i <= SEMESTERDURATION; i++)
        {
            string text1 = "Day " + to_string(i);
            string text2 = player.getName() + " Starved to Death";

            positionText(text1, false, true, false, -19);

            if (i != 1)
            {
                player.setHunger(player.getHunger() - 1);
            }

            if (player.getHunger() == 0)
            {
                positionText(text2, false, true, false, -19);
                break;
            }

            player.printStats();
        
            takeInput(player, schoolarray, 2, eateryarray, 1);

        }

        validateInput(input, "Do You Want to Retry", "Invalid Input. Do You Want To Retry", optionsarray, OPTIONSARRAYLENGTH, true, false, -19);

        if (input == optionsarray[1])
        {
            run = false;
        }

    }


}

int main()
{
    gameLoop();

    // gameStart(game_info, 3);

    // pdc.atEatery(player);

}