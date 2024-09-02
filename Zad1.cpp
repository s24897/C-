#include <iostream>

#define  language "ENG" //Miałem mały problem ze zrozumieniem fragmentu zadania o zdefiniowaniu makra preprocesora i nie wiem czy to o to chodziło

int main() {


        int val;
        int possibleValMax;
        int valMax;
        int valMod = 0;
        int valModMax = 0;

        for (;;) {
            if (language == "ENG") {
            std::cout << "Enter natural number (0 if done): ";
            }
            else if(language == "POL"){
                std::cout << "Wprowadz liczbe naturalna(0 aby zakonczyc): ";
            }
            std::cin >> val;
            possibleValMax = val;
            if (val == 0) { break; }
            else {
                for (;;) {
                    if (val == 0) {
                        if (valMod > valModMax) {
                            valMax = possibleValMax;
                            valModMax = valMod;
                            valMod = 0;
                        } else { valMod = 0; }
                        break;
                    } else {
                        valMod += val % 10;
                        val = val / 10;
                    }
                }
            }
        }
    if (language == "ENG") {
        std::cout << "Max sum of digits was: " << valModMax << " for: " << valMax;
        }
    else if(language=="POL"){
        std::cout << "Maksymalna suma liczb to: " << valModMax << " dla: " << valMax;
    }
    }


