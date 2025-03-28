#include<vector>
#include<iostream>
#include<string>
using namespace std;

const int TABLE_SIZE = 10;

struct Student{
    int rollNo;
    string name;
};

Student linearTable[TABLE_SIZE];

bool linearOccupied[TABLE_SIZE] = {false};


int hashFunction(int key) {
    return key % TABLE_SIZE;
}


void insertLinear(Student s){
    int idx = hashFunction(s.rollNo);
    int comparisons = 1;

    while(linearOccupied[idx]){
        idx = (idx + 1) % TABLE_SIZE;
        comparisons++;
    }

    linearTable[idx] = s;
    linearOccupied[idx] = true;

    cout<<"[Linear Probing] Inserted "<<s.name<<" ater "<<comparisons<<endl;

}

void searchLinear(int roll){
    int idx = hashFunction(roll);
    int comparisons = 1;

    while (linearOccupied[idx]){
        if(linearTable[idx].rollNo == roll){
            cout << "[Linear Probing] Found " << linearTable[idx].name << " after " << comparisons << " comparisons.\n";
            return;
        }
        idx = (idx + 1)%TABLE_SIZE;
        comparisons++;

        if(comparisons > TABLE_SIZE){
            cout << "[Linear Probing] Not found after " << comparisons << " comparisons.\n";
            return;
        }
    } 
}

// |=============================================================================|
// |2. Linear Probing + Chaining Without Replacement |
// |=============================================================================|

struct chainEntry{
    Student s;
    bool occupied = false;
    int next = -1;
};

chainEntry chainTable[TABLE_SIZE];

void insertChainingNoReplace(Student s){
    int idx = hashFunction(s.rollNo);

    if (!chainTable[idx].occupied){
        chainTable[idx].s = s;
        chainTable[idx].occupied = true;
        cout << "[Chaining Without Replacement] Inserted " << s.name << " at index " << idx << endl;
        return;
    }

    int i = (idx + 1) % TABLE_SIZE;

    while(chainTable[i].occupied && i!=idx){
        i = (i + 1) % TABLE_SIZE;
    }

    if(!chainTable[i].occupied){
        chainTable[i].s = s;
        chainTable[i].occupied = true;
        
        int ptr = idx;

        while (chainTable[ptr].next != -1){
            ptr = chainTable[ptr].next;
        }
        
        chainTable[ptr].next = i;
        cout << "[Chaining No Replace] Inserted " << s.name << " at " << i << ", chained from " << ptr << ".\n";
    }
    else {
        cout << "[Chaining No Replace] Table full!\n";
    }
}

void searchChainingNoReplace(int roll){
    int idx = hashFunction(roll);
    int comparisons = 1;

    int ptr = idx;
    while(ptr != -1){
        if(chainTable[ptr].occupied && chainTable[ptr].s.rollNo == roll){
            cout << "[Chaining No Replace] Found " << chainTable[ptr].s.name << " after " << comparisons << " comparisons.\n";
            return;
        }
        ptr = chainTable[ptr].next;
        comparisons++;
    }
    cout << "[Chaining No Replace] Student not found after " << comparisons << " comparisons.\n";
}

struct ChainEntry {
    Student s;
    bool occupied = false;
    int next = -1;
};


ChainEntry chainReplaceTable[TABLE_SIZE];

void insertChainingWithReplace(Student s){
    int idx = hashFunction(s.rollNo);

    if (!chainReplaceTable[idx].occupied) {
        chainReplaceTable[idx].s = s;
        chainReplaceTable[idx].occupied = true;
        return;
    }

    int homeIdx = hashFunction(chainReplaceTable[idx].s.rollNo);

    if(homeIdx != idx){
        Student temp = chainReplaceTable[idx].s;
        int tempNext = chainReplaceTable[idx].next;

        chainReplaceTable[idx].s = s;
        chainReplaceTable[idx].next = -1;

        insertChainingWithReplace(temp);
    }
    else{
        int i  = (idx + 1)% TABLE_SIZE;

        while(chainReplaceTable[i].occupied && i != idx)
            i = (i + 1)%TABLE_SIZE;

        if(!chainReplaceTable[i].occupied){
            chainReplaceTable[i].s = s;
            chainReplaceTable[i].occupied = true;

            int ptr = idx;

            while (chainReplaceTable[ptr].next != -1)
            ptr = chainReplaceTable[ptr].next;

            chainReplaceTable[ptr].next = i;    
        }
        else {
            cout << "[Chaining With Replace] Table full!\n";
        }   
    }
}

void searchChainingWithReplace(int roll) {
    int idx = hashFunction(roll);
    int comparisons = 1;

    int ptr = idx;
    while (ptr != -1) {
        if (chainReplaceTable[ptr].occupied && chainReplaceTable[ptr].s.rollNo == roll) {
            cout << "[Chaining With Replace] Found " << chainReplaceTable[ptr].s.name << " after " << comparisons << " comparisons.\n";
            return;
        }
        ptr = chainReplaceTable[ptr].next;
        comparisons++;
    }

    cout << "[Chaining With Replace] Student not found after " << comparisons << " comparisons.\n";
}

int main() {
    cout << "== Linear Probing ==\n";
    insertLinear({101, "Alice"});
    insertLinear({111, "Bob"});
    insertLinear({121, "Charlie"});
    searchLinear(121);
    searchLinear(999);

    cout << "\n== Chaining without Replacement ==\n";
    insertChainingNoReplace({201, "David"});
    insertChainingNoReplace({211, "Eva"});
    insertChainingNoReplace({221, "Frank"});
    searchChainingNoReplace(211);
    searchChainingNoReplace(999);

    cout << "\n== Chaining with Replacement ==\n";
    insertChainingWithReplace({301, "Grace"});
    insertChainingWithReplace({311, "Helen"});
    insertChainingWithReplace({321, "Isaac"});
    searchChainingWithReplace(321);
    searchChainingWithReplace(999);

    return 0;
}