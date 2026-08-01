/* Practical Example: Text Editor with Undo/Redo
This reinforces the concept and shows how Command handles a richer state-tracking scenario.
The editor supports typing text and deleting the last N characters. 
Both operations are undoable. We use a two-stack approach for full undo/redo. */

#include<iostream>
#include<string>
#include<stack>

using namespace std;

class TextEditorCommand {
    public:
    virtual ~TextEditorCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Document {
    private:
        string content;
    public:
        void insert(string text) {
            content += text;
        }
 
        string removeLast(int count) {
            if (count > (int)content.size()) {
                count = content.size();
            }
            string removed = content.substr(content.size() - count);
            content.erase(content.size() - count);
            return removed;
        }
 
        string getText() {
            return this->content;
        }
};

class InsertTextCommand : public TextEditorCommand {
    private:
        Document *document;
        string text;
    public:
        InsertTextCommand(Document *d, string t) {
            document = d;
            text = t;
        }
        void execute() override {
            document->insert(text);
        }

        void undo() override {
            document->removeLast(text.size());
        }
};

class DeleteTextCommand : public TextEditorCommand {
    private:
    Document *document;
    string removedText;
    int removeCharacterLength;
public:
    DeleteTextCommand(Document *d, int c) {
        document = d;
        removeCharacterLength = c;
    }
    void execute() override {
        removedText = document->removeLast(removeCharacterLength);
    }

    void undo() override {
        document->insert(removedText);
    }
};

class DocumentManager {
    private:
        stack<TextEditorCommand*> undoStack;
        stack<TextEditorCommand*> redoStack;
    public:
    void executeCommand(TextEditorCommand* command) {
        command->execute();
        // for undo purpose, push the command to undo stack
        undoStack.push(command);

        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            TextEditorCommand* command = undoStack.top();
            undoStack.pop();
            command->undo();
            redoStack.push(command);
        } else {
            cout << "Nothing to undo." << endl;
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            TextEditorCommand* command = redoStack.top();
            redoStack.pop();
            command->execute();
            undoStack.push(command);
        } else {
            cout << "Nothing to redo." << endl;
        }
    }
};

int main(){
    Document doc;
 
    InsertTextCommand insertHello(&doc, "Hello");
    InsertTextCommand insertWorld(&doc, ", World");
    DeleteTextCommand deleteSeven(&doc, 7);
    InsertTextCommand insertBang(&doc, "!");

    DocumentManager manager;
 
    cout << "--- Executing Commands ---" << endl;
    manager.executeCommand(&insertHello);
    cout << doc.getText() << endl;
 
    manager.executeCommand(&insertWorld);
    cout << doc.getText() << endl;
 
    manager.executeCommand(&deleteSeven);
    cout << doc.getText() << endl;
 
    cout << "\n--- Undoing Commands ---" << endl;
    manager.undo();
    cout << doc.getText() << endl;
 
    manager.undo();
    cout << doc.getText() << endl;
 
    cout << "\n--- Redoing Commands ---" << endl;
    manager.redo();
    cout << doc.getText() << endl;
 
    cout << "\n--- Executing New Command (clears redo history) ---" << endl;
    manager.executeCommand(&insertBang);
    cout << doc.getText() << endl;
 
    manager.redo();
    cout << doc.getText() << endl;

    manager.undo();
    cout << doc.getText() << endl;

    manager.redo();
    cout << doc.getText() << endl;
    return 0;
}