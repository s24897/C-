#include <iostream>


int strlen(const char *pass) {
    int i = 0;
    while (pass[i] != '\0') {
        i++;
    }
    return i;
}

int unique(const char *pass) {
    int counter=0;
    for(int i = 0;i < strlen(pass);i++){
        int ct=0;
        for(int j = i+1;j< strlen(pass);j++){
            if(pass[i]==pass[j]) ct++;
        }
        if(ct==0) counter++;
    }
    return counter;
}

int isnum(const char *pass)
{
    int i =0;
    while(pass[i]!='\0')
    {
        if(pass[i]>=48 && pass[i]<=57) return 1;
        i++;
    }
    return 0;
}

int isbig(const char *pass)
{
    int i =0;
    while(pass[i]!='\0')
    {
        if(pass[i]>=65 && pass[i]<=90) return 1;
        i++;
    }
    return 0;
}

int issmall(const char *pass)
{
    int i =0;
    while(pass[i]!='\0')
    {
        if(pass[i]>=97 && pass[i]<=122) return 1;
        i++;
    }
    return 0;
}

int isalpha(const char *pass)
{
    int i =0;
    while(pass[i]!='\0')
    {
        if(pass[i]>=33 && pass[i]<=47 || pass[i]>=58 && pass[i]<=64 || pass[i]>=91 && pass[i]<=96 || pass[i]>=123 && pass[i]<=126) return 1;
        i++;
    }
    return 0;
}


//main methode
bool checkpass(const char *pass) {


    if (strlen(pass) < 8) {
        std::cout << "Too short\n";
    }

    if(unique(pass)<6){
        std::cout << "Too few different characters\n";
    }

    if(isnum(pass)==0){
        std::cout << "No digit\n";
    }
    if(issmall(pass)==0){
        std::cout << "No lowercase letter\n";
    }
    if(isbig(pass)==0){
        std::cout << "No uppercase letter\n";
    }
    if(isalpha(pass)==0){
        std::cout << "No non-alphanumeric character\n";
    }
    if(strlen(pass)>=8 && unique(pass)>=6 && isnum(pass)==1 && issmall(pass)==1 && isbig(pass)==1 && isalpha(pass)==1){
        std::cout << "OK\n";
    }
}


int main() {
    using std::cout; using std::endl;
    const char *passes[] =
            {
                    "AbcDe93", "A1b:A1b>", "Ab:Acb<",
                    "abc123><", "Zorro@123", nullptr
            };
    for (int i = 0; passes[i] != nullptr; ++i) {
        cout << "checking " << passes[i] << endl;
        if (checkpass(passes[i])) cout << "OK" << endl;
        cout << endl;
    }


}
