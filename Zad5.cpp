#include <iostream>

int main() {
    int val=0;
    int valTemp;
    int valMax;
    int indexMax=0;
    int index=1;

    std::cout << "Wprowadz sekwencje liczb (0 konczy sekwencje)" << "\n";
    for(;;){
        std::cout << "Podaj liczbe: ";
        std::cin>>valTemp;

        if(valTemp==0){
            if(index>indexMax) {
                indexMax = index;
                valMax = val;
            }
            break;
        }

        else{
            if(valTemp==val){
                index++;
            }
            else{
                if(index>indexMax && index>1){
                    indexMax=index;
                    index=1;
                    valMax=val;
                }
                val=valTemp;
            }
        }
    }
    std::cout << "Longest sequence: " << indexMax << " times " << "| " << valMax;
}
