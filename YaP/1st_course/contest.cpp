#include <iostream>
#include <array>

using namespace std;

int main() {
    int t;
    cin >> t;
    array<int, 100> buff;
    for (int i=0; i<100; ++i)
        buff[i] = i+1;
    
        
    while (t--) {
        int n;
        cin >> n;
        const int ss = n;
        array<int, 100> arr=buff;

        for (int i=0; i < n-1; ++i) {
            for (int j=0; j < n; ++j) {
                if (j == i) continue;
                if (arr[i] % arr[j])
                 
            }
        }

        while (n--) {
            
        }
    }


}