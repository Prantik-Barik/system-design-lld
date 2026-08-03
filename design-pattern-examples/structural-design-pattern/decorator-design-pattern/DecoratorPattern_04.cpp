/* A text editor with basic functionality of bold, italics and underline */

#include<iostream>
using namespace std;

class TextView {
    public:
        virtual void render() = 0;
        virtual ~TextView() {}
};

class PlainTextView : public TextView {
    string text;
    public:
        PlainTextView(string typedText){
            this->text = typedText;
        }
        void render() override {
            cout<<text;
        }
};

class TextDecorator : public TextView {
    protected:
        TextView *text;
    public:
        TextDecorator(TextView *t){
            this->text = t;
        }
};

class BoldDecorator : public TextDecorator {
    public: 
        BoldDecorator(TextView *t): TextDecorator(t) {}

        void render() override {
            cout<<"<b>";
            text->render();
            cout<<"</b>";
        }
};

class ItalicsDecorator : public TextDecorator {
    public: 
        ItalicsDecorator(TextView *t): TextDecorator(t) {}

        void render() override {
            cout<<"<i>";
            text->render();
            cout<<"</i>";
        }
};

class UnderLineDecorator : public TextDecorator {
    public: 
        UnderLineDecorator(TextView *t): TextDecorator(t) {}

        void render() override {
            cout<<"<u>";
            text->render();
            cout<<"</u>";
        }
};

int main(){
    PlainTextView text("Hello, World!");

    // Plain text
    cout << "Plain:                   ";
    text.render();
    cout << endl;

    // Single decorator: Bold
    cout << "Bold:                    ";
    BoldDecorator boldText(&text);
    boldText.render();
    cout << endl;

    // Two decorators: Italic + Underline
    cout << "Italic + Underline:      ";
    ItalicsDecorator italic(&text);
    UnderLineDecorator italicUnderline(&italic);
    italicUnderline.render();
    cout << endl;

    // Three decorators: Bold + Italic + Underline
    cout << "Bold + Italic + Underline: ";
    BoldDecorator bold(&text);
    ItalicsDecorator italicBold(&bold);
    UnderLineDecorator allStyles(&italicBold);
    allStyles.render();
    cout << endl;
    return 0;    
}