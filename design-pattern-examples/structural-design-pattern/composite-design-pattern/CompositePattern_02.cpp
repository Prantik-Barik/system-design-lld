/* Problem: Organization Hierarchy System. 
An OrgComponent interface is shared by Employee (leaf) and Manager (composite). 
Managers can contain employees and other managers, forming a tree that represents the company structure.

The system supports three operations: 
getSalary() computes the total salary for a node and everything below it, 
getHeadcount() counts all people in the subtree, and 
printHierarchy() displays the org chart with indentation. */

#include<iostream>
using namespace std;

class OrgComponent{
    public:
        virtual ~OrgComponent() = default;
        virtual int getSalary() = 0;            
        virtual void printHierarchy(string indent) = 0;      
        virtual int getHeadCount() = 0;
};

class Employee : public OrgComponent {
    private:
        string name, title;
        int salary;

    public:
        Employee(string name, string title, int empSalary){
            this->name = name;
            this->title = title;
            this->salary = empSalary;
        }

        int getSalary() override {
            return salary;
        }

        int getHeadCount() override {
            return 1;
        }

        void printHierarchy(string indent) override {
            cout << indent << "- " << name << " (" << title << ", $" << salary << ")" << endl;
        }
};

class Manager : public OrgComponent {
    private:
        string name, title;
        int salary;
        vector<OrgComponent*> members;
    public:
        Manager(string name, string title, int empSalary){
            this->name = name;
            this->title = title;
            this->salary = empSalary;
        }
        void addEmployee(OrgComponent *emp){
            members.push_back(emp);
        }

        void removeEmployee(OrgComponent *emp){
            members.erase(remove(members.begin(), members.end(), emp), members.end());
        }

        int getSalary() override {
            int totalSalary = salary;
            for(OrgComponent* emp : members){
                totalSalary += emp->getSalary();
            }

            return totalSalary;
        }

        int getHeadCount() override {
            int totalHeadCount = 1;
            for(OrgComponent* emp : members){
                totalHeadCount += emp->getHeadCount();
            }

            return totalHeadCount;
        }

        void printHierarchy(string indent) override {
            cout << indent << "+ " << name << " (" << title << ", $" << salary << ")" << endl;
            for (OrgComponent* member : members) member->printHierarchy(indent + "  ");
        }
};

int main(){
    Employee dev1("Alice", "Senior Engineer", 120000);
    Employee dev2("Bob", "Engineer", 95000);
    Employee dev3("Charlie", "Engineer", 90000);
    Employee designer("Diana", "Designer", 100000);

    Manager techLead("Eve", "Tech Lead", 140000);
    techLead.addEmployee(&dev1);
    techLead.addEmployee(&dev2);

    Manager vpEng("Frank", "VP Engineering", 200000);
    vpEng.addEmployee(&techLead);
    vpEng.addEmployee(&dev3);

    Manager vpProduct("Grace", "VP Product", 190000);
    vpProduct.addEmployee(&designer);

    Manager ceo("Hank", "CEO", 300000);
    ceo.addEmployee(&vpEng);
    ceo.addEmployee(&vpProduct);

    cout << "---- Organization Chart ----" << endl;
    ceo.printHierarchy("");

    cout << "\nTotal Payroll: $" << ceo.getSalary() << endl;
    cout << "Total Headcount: " << ceo.getHeadCount() << endl;
    cout << "\nEngineering Payroll: $" << vpEng.getSalary() << endl;
    cout << "Engineering Headcount: " << vpEng.getHeadCount() << endl;

    return 0;
}