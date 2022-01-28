#include <iostream>

using namespace std;

int main() {
    
    cout << "State options \n1 Running \n2 Ready \n3 Blocked" << endl;
    
    while(1) {
    
        cout << "Enter a state choice: ";
    
        int state;
        cin >> state;
    
        bool blocked = false;
    
        switch(state) {
        
            case 1:
                cout << "STATUS: Runnning\n" << endl;
                break;
            
            case 2:
                cout << "STATUS: Ready\n" << endl;
                break;
        
            case 3:
                cout << "STATUS: Blocked\n" << endl;
                break;
        }
    
    }
    
    
    return 0;
}
