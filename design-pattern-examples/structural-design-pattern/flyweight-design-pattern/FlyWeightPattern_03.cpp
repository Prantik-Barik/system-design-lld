/*Implement Word Processor
Problem: Build a word processor where characters share FontStyle flyweight objects. 
Each FontStyle stores the font family, size, and whether it is bold or italic. 
The position (line, column) is extrinsic state that varies per character.

Requirements:

Flyweight interface: FontStyle with a method format(int line, int column, char character)
Concrete flyweight: ConcreteFontStyle storing fontFamily (String), fontSize (int), bold (boolean), italic (boolean)
Factory: FontStyleFactory with getFontStyle(fontFamily, fontSize, bold, italic) and getStyleCount()
Client code creates multiple characters sharing styles, then prints them */

#include<iostream>
#include <unordered_map>
using namespace std;

//Flyweight class
class FontStyleFlyweight{
    private:
        // Intrinsic properties (shared among characters using the same style)
        string fontFamily;
        int fontSize;
        bool isBold;
        bool isItalic;
    public:
        FontStyleFlyweight(string family, int size, bool bold, bool italic) {
            this->fontFamily = family;
            this->fontSize = size;
            this->isBold = bold;
            this->isItalic = italic;
        }

        void format(int line, int column, char character) {
            cout << "Char '" << character << "' at (line " << line << ", col " << column
             << ") -> " << fontFamily << ", " << fontSize << "pt"
             << (isBold ? ", Bold" : "") << (isItalic ? ", Italic" : "") << endl;
        }
};

//Context class
class CharacterContext {
    private:
        FontStyleFlyweight* flyweight;
        int line, column;
        char character;
    
    public:
        CharacterContext(FontStyleFlyweight* fw, int line, int column, char character) {
            this->flyweight = fw;
            this->line = line;
            this->column = column;
            this->character = character;
        }
    
        void render() {
            flyweight->format(line, column, character);
        }
};

//Factory calss
class FontStyleFactory {
    private:
    static unordered_map<string, FontStyleFlyweight*> flyweights;
    public:
    static FontStyleFlyweight* getFontStyle(string fontFamily, int fontSize, bool bold, bool italic) {

        string key = fontFamily + "_" + to_string(fontSize) + "_" +
                    to_string(bold) + "_" + to_string(italic);

        //new object created here
                    if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new FontStyleFlyweight(fontFamily, fontSize, bold, italic);
        }

        return flyweights[key];
    }

    static int getStyleCount() {
        return flyweights.size();
    }

    static void cleanup() {
        flyweights.clear();
    }
};

unordered_map<string, FontStyleFlyweight*> FontStyleFactory::flyweights;

//Client class
class WordProcessor {
    private:
        vector<CharacterContext*> characters;
    
    public:
        void addCharacter(int line, int column, char character, string fontFamily,
                            int fontSize, bool bold, bool italic) {
    
            FontStyleFlyweight* flyweight = FontStyleFactory::getFontStyle(
                fontFamily, fontSize, bold, italic
            );
    
            characters.push_back(new CharacterContext(flyweight, line, column, character));
        }
    
        void render() {
            for (int i = 0; i < (int)characters.size(); i++) {
                characters[i]->render();
            }
    
            cout << "\nTotal characters: " << characters.size() << endl;
            cout << "Unique font styles created: " << FontStyleFactory::getStyleCount() << endl;
        }
};

int main(){
    WordProcessor* doc = new WordProcessor();

    // "Hi" in Arial 12 Bold
    doc->addCharacter(1, 1, 'H', "Arial", 12, true, false);
    doc->addCharacter(1, 2, 'i', "Arial", 12, true, false);

    // " there" in Arial 12 regular
    doc->addCharacter(1, 3, ' ', "Arial", 12, false, false);
    doc->addCharacter(1, 4, 't', "Arial", 12, false, false);
    doc->addCharacter(1, 5, 'h', "Arial", 12, false, false);

    // "Bye" in Times New Roman 14 Italic
    doc->addCharacter(2, 1, 'B', "Times New Roman", 14, false, true);
    doc->addCharacter(2, 2, 'y', "Times New Roman", 14, false, true);
    doc->addCharacter(2, 3, 'e', "Times New Roman", 14, false, true);

    doc->render();

    return 0;
}