/* Practical Example: Document Workflow
Let us work through a second example to reinforce the pattern.
This time, we are building a document management system where documents move through a workflow: Draft, Under Review, and Published.
Each state has different rules for what operations are allowed.
In Draft state, authors can edit the document and submit it for review.
In Review state, reviewers can approve or reject it.
In Published state, the document is read-only and can only be unpublished to go back to Draft. */


/* krna kya hai -> 
create an abstract class of state and define the state change functions here
create the concrete state classes and implemet the non state change classes and define the signature of the state change function
create the main working class with a constructor -> init the intial state into current state
define set state and getstate that will be helpful in moving the context
define all the working related functionalities here and use current state to do it
then for the deffred implemetations perform state change by using current->setState(new RequiredState())
*/

#include<iostream>
#include<string>

using namespace std;

//Forward Declaration
class Document;

class DocumentState {
public:
    virtual ~DocumentState() = default;
    virtual void edit(Document *document, const string &content) = 0;
    virtual void submitForReview(Document *document) = 0;
    virtual void approve(Document *document) = 0;
    virtual void reject(Document *document) = 0;
    virtual void unpublish(Document *document) = 0;
    virtual string getStateName() = 0;
};

class DraftState : public DocumentState {
    public:
        void edit(Document* context, const string& content) override;
        void submitForReview(Document* context) override;
        void approve(Document* context) override {
            cout << "Cannot approve a draft. Submit for review first." << endl;
        }
        void reject(Document* context) override {
            cout << "Cannot reject a draft. Submit for review first." << endl;
        }
        void unpublish(Document* context) override {
            cout << "Document is already a draft." << endl;
        }
        string getStateName() override {
            return "Draft";
        }
};
    
class UnderReviewState : public DocumentState {
    public:
        void edit(Document* context, const string& content) override {
            cout << "Cannot edit while under review." << endl;
        }
        void submitForReview(Document* context) override {
            cout << "Document is already under review." << endl;
        }
        void approve(Document* context) override;
        void reject(Document* context) override;
        void unpublish(Document* context) override {
            cout << "Document is not published yet." << endl;
        }
        string getStateName() override {
            return "Under Review";
        }
};
    
class PublishedState : public DocumentState {
    public:
        void edit(Document* context, const string& content) override {
            cout << "Cannot edit a published document. Unpublish first." << endl;
        }
        void submitForReview(Document* context) override {
            cout << "Document is already published." << endl;
        }
        void approve(Document* context) override {
            cout << "Document is already published." << endl;
        }
        void reject(Document* context) override {
            cout << "Cannot reject a published document." << endl;
        }
        void unpublish(Document* context) override;
        string getStateName() override {
            return "Published";
        }
};


class Document {
    private:
        DocumentState *currentState;
        string content;

    public:

        Document(){
           currentState = new DraftState(); //initial start state
           content = "";
        }
        ~Document(){
            delete currentState;
        }
        void setContent(const string& c) { 
            content = c; 
        }
        string getContent() { 
            return content; 
        }

        void setState(DocumentState* state){
            delete currentState;
            currentState = state;
        }

        DocumentState* getState(){
            return currentState;
        }

        void edit(const string& c) { currentState->edit(this, c); }
        void submitForReview() { currentState->submitForReview(this); }
        void approve() { currentState->approve(this); }
        void reject() { currentState->reject(this); }
        void unpublish() { currentState->unpublish(this); }
};

// Deferred implementations
void DraftState::edit(Document* context, const string& content) {
    cout << "Editing document: " << content << endl;
    context->setContent(content);
}

void DraftState::submitForReview(Document* context) {
    cout << "Document submitted for review." << endl;
    context->setState(new UnderReviewState());
}

void UnderReviewState::approve(Document* context) {
    cout << "Document approved and published." << endl;
    context->setState(new PublishedState());
}

void UnderReviewState::reject(Document* context) {
    cout << "Document rejected. Returning to draft." << endl;
    context->setState(new DraftState());
}

void PublishedState::unpublish(Document* context) {
    cout << "Document unpublished. Returning to draft." << endl;
    context->setState(new DraftState());
}

int main()
{
    Document doc;

    doc.edit("First draft of the article.");
    doc.approve();               // Cannot approve a draft
    doc.submitForReview();
    doc.edit("Trying to edit");  // Cannot edit while under review
    doc.reject();                // Back to draft
    doc.edit("Revised draft.");
    doc.submitForReview();
    doc.approve();               // Published
    doc.edit("Trying to edit");  // Cannot edit a published document
    doc.unpublish();      
    return 0;
}