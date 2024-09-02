#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <ctime>
#include <array>
#include <map>

struct password{
    std::string name;
    std::string psw;
    std::string category;

    password(std::string name, std::string psw, std::string category){
        this -> name = name;
        this -> psw = psw;
        this -> category = category;
    }

};

//Funkcja odczytująca pliki tekstowe
void read(std::vector<password>& passwords, std::string path_name_p, std::string path_name_n, std::string path_name_k){
    auto path_p = std::string(path_name_p);
    auto file_p = std::fstream(path_p);
    auto path_n = std::string(path_name_n);
    auto file_n = std::fstream(path_n);
    auto path_k = std::string(path_name_k);
    auto file_k = std::fstream(path_k);


    auto name = std::string();
    auto psw = std::string();
    auto cat = std::string();
    int index=0;
    while(file_p>>psw){
        index++;
    }
    file_p.clear();
    file_p.seekg(0,std::ios::beg);

    for (int i = 0; i < index; i++) {
        file_n >> name;
        file_p >> psw;
        file_k >> cat;
        passwords.push_back(password(name, psw, cat));
    }
}

//Funkcja szyfrująca
auto encrypt(std::string psw, std::string cipher){
    int j=0;
    for(int i=0;i<psw.length();i++){
        psw.at(i)+=cipher.at(j)%10;
        j++;
        if(j==cipher.length()){
            j=0;
        }
    }
    return psw;
}

//Funkcje rozszyfrowująca
auto decrypt(std::string str, std::string cipher){
    int j=0;
    for(int i=0;i<str.length();i++){
        str.at(i)-=cipher.at(j)%10;
        j++;
        if(j==cipher.length()){
            j=0;
        }
    }
    return str;
}

//Funkcja wyświetlająca zawartość plików
void showpsw(std::string cipher, std::vector<password>& passwords, std::string path_name_p){

        auto path = std::string(path_name_p);
        auto file = std::fstream(path);

        std::cout << "Czy hasla maja byc posortowane alfabetycznie?\n" << "1. Tak\n" << "2. Nie ma takiej potrzeby\n";
        int ifsort;
        std::cin >> ifsort;
        if(ifsort==1) {
            auto str = std::string();
            std::set<std::string> set;
            while (file >> str) {
                str = decrypt(str,cipher);
                set.insert(str);
            }
            for (auto iter = set.begin(); iter != set.end(); ++iter)
                std::cout << *iter << '\n';
        }
        else {
            auto str = std::string();

            for(int i=0;i<passwords.size();i++){
                passwords.at(i).psw = decrypt(passwords.at(i).psw,cipher);
                std::cout << "Nazwa - " << passwords.at(i).name << ",  Haslo - " << passwords.at(i).psw << ", Kategoria - " << passwords.at(i).category << '\n';
            }
        }
}

//Funkcja pozwalająca wybrać akcję
auto choice(){

        std::cout << "Wybierz akcje\n" << "1. odczytanie hasel\n" << "2. edytowanie pliku\n" << "3. wyszukanie hasla po kategorii\n";
        int choice_number;
        std::cin >> choice_number;
        return choice_number;

}

//Funkcja dodająca hasło do pliku
void addpsw(int choice_number, std::string cipher, std::vector<std::string> categories, std::string path_name_p, std::string path_name_n, std::string path_name_k){
    if(choice_number==1){
        auto path_p = std::string(path_name_p);
        auto file_p = std::fstream(path_p, std::ios::out | std::ios::app);
        auto path_n = std::string(path_name_n);
        auto file_n = std::fstream(path_n, std::ios::out | std::ios::app);
        auto path_k = std::string(path_name_k);
        auto file_k = std::fstream(path_k, std::ios::out | std::ios::app);

        std::cout << "Wpisz nazwe: ";
        auto name = std::string();
        std::cin >> name;
        file_n << name << '\n';

        std::cout << "Wpisz haslo: ";
        auto psw = std::string();
        std::cin >> psw;
        psw = encrypt(psw,cipher);
        file_p << psw << '\n';

        std::cout << "Wybierz kategorie:\n";
        for(int i=0;i<categories.size();i++){
            std::cout << i+1 << ". " << categories.at(i) << '\n';
        }
        int categorynr;
        std::cin >> categorynr;
        file_k << categories.at(categorynr-1) << '\n';
    }
}

//Funkcja usuwająca hasło z pliku
void deletepsw(int choice_number, std::string cipher, std::string path_name_p, std::string path_name_n, std::string path_name_k){
    if(choice_number==2){
        auto path_p = std::string(path_name_p);
        auto file_p = std::fstream(path_p, std::ios::in | std::ios::app);
        auto path_n = std::string(path_name_n);
        auto file_n = std::fstream(path_n, std::ios::in | std::ios::app);
        auto path_k = std::string(path_name_k);
        auto file_k = std::fstream(path_k, std::ios::in | std::ios::app);

        auto str = std::string();
        std::vector<std::string> vecp;
        std::vector<std::string> vecn;
        std::vector<std::string> veck;

        while (file_p >> str) {
            str = decrypt(str,cipher);
            vecp.push_back(str);
        }
        while (file_n >> str) {
            vecn.push_back(str);
        }
        while (file_k >> str) {
            veck.push_back(str);
        }

        std::cout << "Ktore haslo chcesz usunac?\n";
        int i=1;
        for(std::string x : vecp){
            std::cout << i << ". " << x << '\n';
            i++;
        }
        int psw;
        std::cin >> psw;
        vecp.erase(vecp.begin()+psw-1);
        vecn.erase(vecn.begin()+psw-1);
        veck.erase(veck.begin()+psw-1);
        auto file2_p = std::fstream(path_p, std::ios::out | std::ios::trunc);
        auto file2_n = std::fstream(path_n, std::ios::out | std::ios::trunc);
        auto file2_k = std::fstream(path_k, std::ios::out | std::ios::trunc);
        for(int j=0;j<vecp.size();j++){
            file2_p << vecp.at(j) << '\n';
            file2_n << vecn.at(j) << '\n';
            file2_k << veck.at(j) << '\n';
        }
    }
}

//Funkcja nadpisująca hasło z pliku
void editpsw(int choice_number, std::string cipher, std::string path_name_p){
    if(choice_number==3){
        auto path = std::string(path_name_p);
        auto file = std::fstream(path, std::ios::in | std::ios::app);
        auto str = std::string();
        std::vector<std::string> vec;
        while (file >> str) {
            str = decrypt(str,cipher);
            vec.push_back(str);
        }
        std::cout << "Ktore haslo chcesz nadpisac?\n";
        int i=1;
        for(std::string x : vec){
            std::cout << i << ". " << x << '\n';
            i++;
        }
        int psw;
        auto new_psw = std::string();
        std::cin >> psw;
        std::cout << "Podaj nowe haslo: \n";
        std::cin >> new_psw;
        vec.at(psw-1)=new_psw;
        auto file2 = std::fstream(path, std::ios::out | std::ios::trunc);
        for(int j=0;j<vec.size();j++){
            vec.at(j) = encrypt(vec.at(j),cipher);
            file2 << vec.at(j) << '\n';
        }
    }
}

//Funkcja szukająca hasło po kategorii
void searchpsw(std::string cipher, std::vector<std::string> categories, std::vector<password> passwords, std::map<std::string,std::string>map){
    std::cout << "Wybierz kategorie:\n";
    for(int i=0;i<categories.size();i++){
        std::cout << i+1 << ". " << categories.at(i) << '\n';
    }
    int categorynr;
    std::cin >> categorynr;
    for(int i=0;i<passwords.size();i++){
        std::pair<std::string, std::string>p1(passwords.at(i).psw, passwords.at(i).category);
        map.insert(p1);
        if(p1.second==categories.at(categorynr-1)){
            passwords.at(i).psw = decrypt(passwords.at(i).psw, cipher);
            std::cout << "Nazwa - " << passwords.at(i).name << ", Haslo - " << passwords.at(i).psw << '\n';
        }
    }
}

//Funkcja edytująca zawartość plikow
auto edit(std::string cipher,std::vector<std::string> categories, std::vector<password>& passwords, std::string path_name_p, std::string path_name_n, std::string path_name_k){
    int choice_number;

        std::cout << "Mozliwe opcje: \n" << "1. dodanie hasla\n" << "2. usuniecie hasla\n" << "3. edytowanie hasla\n";
        std::cin >> choice_number;

            addpsw(choice_number,cipher, categories, path_name_p,path_name_n,path_name_k);
            deletepsw(choice_number,cipher,path_name_p,path_name_n,path_name_k);
            editpsw(choice_number,cipher,path_name_p);
        }



int main() {
    std::vector<std::string> categories {"Gry", "Social_media", "Google"};
    std::vector<password> passwords;
    std::map<std::string, std::string> map;

    auto files = std::array<std::string, 3>{"password1", "password2", "password3"};

    std::cout << "Wybierz plik\n" << "1. password1.txt\n" << "2. password2.txt\n" << "3. password3.txt\n"
              << "4. timestamp\n" << "5. edytowanie dostepnych kategorii\n";
    int nr;
    std::cin >> nr;

    //Uzależnienie ścieżek plików tekstowych od zmiennej
    auto path_name_p = std::string();
    auto path_name_n = std::string();
    auto path_name_k = std::string();
    if(nr==1){
        path_name_p = "..\\password1.txt";
        path_name_n = "..\\nazwy1.txt";
        path_name_k = "..\\kategorie1.txt";
    }
    if(nr==2){
        path_name_p = "..\\password2.txt";
        path_name_n = "..\\nazwy2.txt";
        path_name_k = "..\\kategorie2.txt";
    }
    if(nr==3){
        path_name_p = "..\\password3.txt";
        path_name_n = "..\\nazwy3.txt";
        path_name_k = "..\\kategorie3.txt";
    }

    //Operacje na hasłach
    if (nr<=3) {

        read(passwords,path_name_p,path_name_n,path_name_k);

        std::string cipher;
        std::cout << "Wprowadz haslo odszyfrowujace: ";
        std::cin >> cipher;

        //Zapisywanie do timestampu
        auto path = std::string("..\\timestamp.txt");
        auto file = std::fstream(path, std::ios::out | std::ios::app);
        time_t t = time(0);
        tm *now = localtime(&t);
        file << now->tm_mday << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900) << " Otworzono plik "
             << files[nr - 1] << " szyfrem: " << cipher << "\n";



        //Odczytywanie haseł / edytowanie haseł / wyszukiwanie haseł
        auto choice_number = choice();

        if (choice_number == 1) {
            showpsw(cipher, passwords, path_name_p);
        } else if (choice_number == 2) {
            edit(cipher, categories, passwords, path_name_p, path_name_n, path_name_k);
        }
        else if(choice_number==3){
            searchpsw(cipher, categories, passwords, map);
        }
    }

    //Wyświetlenie timestampu
    else if (nr == 4) {
        auto path = std::string("..\\timestamp.txt");
        auto file = std::fstream(path);

        auto str = std::string();
        while (std::getline(file, str)) {
            std::cout << str << '\n';
        }
    }

    //Usuwanie i dodawanie kategorii(nie działa tak jak powinno. Znaczy działać działa, ale nie wprowadza żadnych zmian do kodu)
    else if(nr==5){
        std::cout << "1. Dodanie kategorii\n" << "2. Usuniecie kategorii\n";
        int choice;
        std::cin >> choice;
        if(choice==1){
            std::cout << "Wprowadz nazwe nowej kategorii: ";
            auto new_cat = std::string();
            std::cin >> new_cat;
            categories.push_back(new_cat);
        }
        else if(choice==2){
            std::cout << "Ktora kategorie chcesz usunac?\n";
            for(int i=0;i<categories.size();i++){
                std::cout << i+1 << ". " << categories.at(i) << '\n';
            }
            int choice;
            std::cin >> choice;
            categories.erase(categories.begin()+choice-1);
        }
    }
}

