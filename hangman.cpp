#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class HangMan {
private:
    const vector<string> WORD_LIST {
        "angle", "ant", "apple", "arch", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry", "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card", "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house", "island", "jewel", "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
        "toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",
    };

    const vector<string> FIGURE {
        "\n"
        " ------------- \n"
        " | \n"
        " | \n"
        " | \n"
        " | \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | \n"
        " | \n"
        " | \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | O \n"
        " | \n"
        " | \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | O \n"
        " | | \n"
        " | \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | O \n"
        " |/| \n"
        " | \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | O \n"
        " |/|\\ \n"
        " | \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | O \n"
        " |/|\\ \n"
        " |/ \n"
        " | \n"
        " ----- \n",
        "\n"
        " ------------- \n"
        " | | \n"
        " | O \n"
        " |/|\\ \n"
        " |/ \\ \n"
        " | \n"
        " ----- \n"
        };

    const int MAX_BAD_GUESS_COUNT = 7;

    string guessedWord, secretWord, guessedChars;
    int badGuessCount;
    bool isGamePlaying, isPlayerWin;

    void init() {
        srand(time(0));
        generateSecretWord();
        guessedWord = string(secretWord.size(), '-');
        badGuessCount = 0;
        isGamePlaying = true;
        guessedChars = "";
    }

    void generateSecretWord() {
        int randomIndex = rand() % WORD_LIST.size();
        secretWord =  WORD_LIST[randomIndex];
    }

    void renderGame() {
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
        cout << FIGURE[badGuessCount];
        cout << "The current guessed word is " << guessedWord << "\n";
        cout << "You've already guessed " << guessedChars << "\n";
        cout << "Number of wrong guesses: " << badGuessCount << "\n";
    }

    char getPlayerGuess() {
        cout << "Please enter your guess: ";
        char guess;
        cin >> guess;

        if (guessedChars.find(guess) == string::npos) {
            guessedChars.push_back(guess);
        }

        return guess;
    }

    void processPlayerGuess(char guess) {
        bool isCharInWord = false;
        for (int i = 0; i < secretWord.size(); ++i) {
            if (secretWord[i] == guess) {
                guessedWord[i] = guess;
                isCharInWord = true;
            }
        }

        if (!isCharInWord) {
            ++badGuessCount;
        }
    }

    void checkEndGame() {
        if (guessedWord == secretWord) {
            isGamePlaying = false;
            isPlayerWin = true;
        } else if (badGuessCount >= MAX_BAD_GUESS_COUNT) {
            isGamePlaying = false;
            isPlayerWin = false;
        }
    }

    void gameOver() {
        renderGame();

        if (isPlayerWin) {
            cout << "Congratulations! You win! \n";
        } else {
            cout << "You lost. The correct word is " << secretWord << "\n";
        }
    }

public:
    void play() {
        init();

        while (isGamePlaying) {
            renderGame();
            char playerGuess = getPlayerGuess();
            processPlayerGuess(playerGuess);
            checkEndGame();
        }

        gameOver();
    }
};

int main() {
    HangMan().play();
}