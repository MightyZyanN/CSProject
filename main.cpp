#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

int getConsoleWidth();

void positionText(const string &text, bool center, bool nextline, bool typeText, int offset);

void validateInput(string &input, string prompttext, string invalidprompttext, int min, int max, bool typetext, int offset);

void validateInput(string &input, string prompttext, string invalidprompttext, string str_array[], int str_array_s, bool upper, bool typetext, int offset);

class Player
{
	private:
        string name;
        string gender;
        string school;
        int cash;
        int gpa;
        int social;
        string location;

    public:
        Player(string name_val, string genderval, string schoolval)
        {
            name = name_val;
            gender = genderval;
            school = schoolval;
        }

        string getLocation()
        {
            return location;
        }

        string setLocation(string location_val)
        {
            location = location_val;

            return location;
        }

        void printStats()
        {
            positionText(name, false, true, false, -19);
            positionText(gender, false, true, false, -19);
            positionText(location, false, true, false, -19);
            // positionText(name, false, true, false, -19);
        }   

};

class School
{
    private:
        string name;
        int location;

    public:
        School(string name_val, int location_val)
        {
            name = name_val;
            location = location_val;
        }

};

class Input
{
    private:
        string type;

    public:
        Input(string type_val)
        {
            type = type_val;
        }

    string takeInput(Player &player)
    {

        const int INPUTARRAYLENGTH = 2;

        string input;

        string inputarray[INPUTARRAYLENGTH] = {"LOCATION", "STATS"};

        while (true)
        {
            validateInput(input, "What's Your Move", "Invalid Move. What's Your Move", inputarray, 3, true, false, -19);

            for (int i = 0; i < INPUTARRAYLENGTH; i++)
            {
                if (input == inputarray[0])
                {
                    inputLocation(player);
                }
                else if (input == inputarray[1])
                {
                    player.printStats();
                }
                break;

            }

        }

        return input;

    }

    void inputLocation(Player &player)
    {
        const int LOCATIONARRAYLENGTH = 3;

        string input;

        bool run = true;

        string locationarray[LOCATIONARRAYLENGTH] = {"SSE", "SDSB", "BACK"};

        while (run)
            {
                validateInput(input, "Which Location Do You Want To Go To", "Invalid Location", locationarray, 3, true, false, -19);

                for (int i = 0; i < LOCATIONARRAYLENGTH; i++)
                {
                    if (input == locationarray[LOCATIONARRAYLENGTH - 1])
                    {
                        run = false;
                        break;
                    }
                    else
                    {
                        player.setLocation(input);
                        string text = "Moving to " + input;
                        positionText(text, false, true, false, -19);
                        run = false;
                        break;
                    }
                }

            }
    }


};

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
        if (nextline)
        {
            cout << string(spaces, ' ');
            typeText(text, TYPEDELAY, true);
        }
        else
        {
            cout << string(spaces, ' ');
            typeText(text, TYPEDELAY, false);
        }
    }
    else
    {
        if (nextline)
        {
            cout << string(spaces, ' ') << text << endl;
        }
        else
        {
            cout << string(spaces, ' ') << text;
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
        bool stop = false;

        for (int i = 0; i < str_array_s; i++)
        {
            if (input == str_array[i])
            {
                stop = true;
                break;
            }
        }

        if (stop)
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

int gameLoop(Player &player)
{
    Input input = Input("");

    input.takeInput(player);

    return 1;
}

int main()
{

    string game_info[3] = {"Zyan", "Male", "SSE"}; 

    Player player = Player(game_info[0], game_info[1], game_info[2]);

    School sse = School("SSE", 0);
    School sdsb = School("SDSB", 0);

    gameLoop(player);


}