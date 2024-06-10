#include <iostream>
#include <string>
#include <vector>
#include <vector>
#include <random>
using namespace std;
#define D 0 // debug


//========================================================================
void EnterShiftKey (long long* k)
{    
    wcin >>*k;             
    if (*k<1 || *k>1000000000000000)
    {
        wcout<<"\nFail! shift-key must be > 0 and <1000000000000000.\n";
        exit(1);
    } 
    else 
    {
        if (*k>32)
            while (*k>10000)
                *k = *k / 100;
            *k = *k % 32;
        
        wcin.ignore(); // очистить символ новой строки из входного буфера 
    }
}
//==#######
void Cesar ()
{
    //// setlocale(LC_ALL, "Russian");
    locale::global(locale("en_US.UTF-8"));  // console to utf82


        // Enter shift-key and sentence
    wcout << "enter shift-key" << endl;
    long long*k = new long long;
    EnterShiftKey (k);


    wcout << "Enter sentence to encrypt" << endl;  
    wstring s; getline(wcin,s);
        
    wchar_t rus[32+*k]{}, Rus[32+*k]{};
        // array init
    for (int i = 0; i < 32/*+k*/; ++i) 
    {
        rus[i] = 1072 + i; // a ...
        Rus[i] = 1040 + i; // A ...


            // print rus alphabet     
        #if D==1 
            if (i<32)
                wcout << rus[i]; 
        #endif
    }
    wcout  << endl;


        //making shift and printing not rus letter symbols
    bool f=0;// symbol snot a rus letter
    wstring s1, ss; // itog 
    for (int j=0; j < s.length(); ++j)
    {    
        for (int i=0; i<32;++i)  
                // is the letter is rus smbl and is it Big   
           if (s[j]==rus[i] || s[j]==Rus[i])
            { 
                #if D==1
                    wcout << "s[j] = " << s[j] << "  " << "rus[i] = "<<rus[i]<< "  "<< "rus[i+k] = "<<rus[i+k]<< endl; 
                    wcout << "rus[i+k]= "<< (int)rus[i+k] << endl;
                #elif D==0
                    if (i+*k>31)
                    {
                        if (s[j]==Rus[i])
                            s1.push_back(Rus[(i+*k)-32]);
                        else
                            s1.push_back(rus[(i+*k)-32]);
                    }
                    else
                    {
                        if (s[j]==Rus[i])
                            s1.push_back(Rus[(i+*k)]);
                        else
                            s1.push_back(rus[i+*k]);
                    }
                #endif
                f=1; // symbol s a rus letter
                continue;                    
            }
        if (f==0) // symbol s not a rus letter
            s1.push_back(s[j]); //just copy 
        else
            f = 0;
        wcout << s1[j]; 
    }
    wcout  << endl;


    delete k;
}


//========================================================================
void Polibii()
{
    locale::global(locale("en_US.UTF-8"));  // console to utf82
wchar_t polybiusSquare[10][8] = 
{
    {L'А', L'Б', L'В', L'Г', L'Д', L'Е', L'Ж', L'З'},
    {L'И', L'К', L'Л', L'М', L'Н', L'О', L'П', L'Р'},
    {L'С', L'Т', L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш'},
    {L'Щ', L'Ъ', L'Ы', L'Ь', L'Э', L'Ю', L'Я', L'а'},
    {L'б', L'в', L'г', L'д', L'е', L'ж', L'з', L'и'},
    {L'к', L'л', L'м', L'н', L'о', L'п', L'р', L'с'},
    {L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш', L'щ'},
    {L'ъ', L'ы', L'ь', L'э', L'ю', L'я', L' ', L'!'},
    {L'@', L'#', L'$', L'%', L',', L'&', L'*', L'('},
    {L')', L'-', L'_', L'+', L'=', L'?', L'<', L'>'},
};


    #if D==1
                for (int i = 0; i < 10; ++i) 
                    for (int j = 0; j < 8; ++j)
                    {
                        wcout<< "polybiusSquare["<<i<<"]["<<j<<"] = "<<polybiusSquare[i][j]<<" "; 
                        wcout<<endl;
                    }
    #else            

    wcout << "print 0, if you want to ENCRYPT message and 1 - to DECRYPT"<<endl;
    bool en0_de1{}; 
    wcin >>  en0_de1;


    if (en0_de1==1)
        wcout << "Enter a message to DECRYPT"<<endl;
    else
        wcout << "Enter a message to ENCRYPT"<<endl;


    wstring  msg;
    wcin.ignore(); getline (wcin, msg); wcout <<'\n';



    bool exitCycle{0}; //to exit cycles in case of matching
    if (en0_de1==1)   
    {
        wcout<< "DECRYPTED message by Polibii:\n";
            ///cheсk each letter in msg on matching i,j in polibii 
        for (int ii=0; ii<msg.length(); ii+=2) // by 2 ij
        {
            if ( ((int)msg[ii]-int('0'))>9 || ((int)msg[ii+1]-int('0'))>7 )
            {
                wcout<< msg[ii]<< msg[ii+1]<<" fail! Entered index is incorrect\n";
                exit(1);
            }
            exitCycle = 0;
            for (int i = 0; i < 10 && !exitCycle; ++i) 
                for (int j = 0; j < 8; ++j)
                {
                    int a = (int)msg[ii]-int('0');
                    int aa = (int)msg[ii+1]-int('0');
                    if (i==a && j==aa)
                    {
                        wcout<< polybiusSquare[i][j];    
                        exitCycle = 1;;
                        break;
                    }
                }
        }
    }     

    else

    {
        wcout<< "ENCRYPTED message by Polibii:\n";
        bool ok{0}; // is there matching
            //cheсk each letter in msg on matching symbols in polibii 
        for (int ii=0; ii<msg.length(); ++ii)
        {
            exitCycle = 0; ok =0;
            for (int i = 0; i < 10 && !exitCycle; ++i) 
                for (int j = 0; j < 8; ++j) 
                        if (msg[ii]==polybiusSquare[i][j])
                        {
                            wcout<< i<<j;  
                            exitCycle = 1;
                            ok=1;
                            break;
                        }
            if (!ok) //=> there is unknown symbol
            {
                wcout<< "\nfail! Unknown symbol in polibii sq is detected\n";
                exit(1);
            }
        }
    }
    wcout<< '\n';
    #endif

}

//========================================================================
wstring generateRandomString(int l) //for fulfilling remaining fields in Kardano square
{   
    wstring s;
    for (int i=0; i<l; ++i)
    {
        wchar_t c = (wchar_t) (L'а' + rand() % 32); // random rus letter
        s += c;
    }
    return s;
}
//==
void Kardano()
{
/*  Kardano 4*4 => message <=16 symbols 

    AA 01 AA 03
    10 AA 12 13
    20 21 22 23
    30 31 AA 33
When rotating  3 times by 90^ "AA" fulfill the square.

    => sequence  to fulfill:

    0  11 2  4 
    14 1  5  15
    7  13 9  6
    12 10 3  8

    remaining symbols will be fulfilled by rand()

Printing all square elements 1 by 1 will be an ENCRYPTED MESSAGE. 
*/

    locale::global(locale("en_US.UTF-8")); 
        // ENCRYPT or DECRYPT ? 
    wcout << "\nPrint 0, if you want to ENCRYPT message and 1 - to DECRYPT"<<endl;
    bool en0_de1{}; 
     
    wcin >>  en0_de1;   
       // message
    if (en0_de1==1)
        wcout << "Enter a message (<=16 symbols!) to DECRYPT"<<endl;
    else
        wcout << "Enter a message (=16 symbols!) to ENCRYPT"<<endl;
    wstring  msg;           wcin.ignore(32767, '\n'); 
    getline (wcin, msg);    wcout <<'\n'; 
    if (msg.length()>16 || msg.length()<16)
    {
        wcout<< "Fail! Message must be <= 16 symbols!"<<endl;
        exit(1);
    }

        // Kardano
    vector<vector<wchar_t>> arr //  Kardano square
    { // for nessecary sequence of fulfilling
        {0,  11, 2,  4},
        {14, 1,  5,  15},
        {7,  13, 9,  6},
        {12, 10, 3,  8}
    };
        // encrpted 
    vector<vector<wchar_t>> itog (4, vector<wchar_t>(4,0)); // ENCRYPT
    wstring itog1; // DECRYPT
        // msg
    
    if (msg.length() < 16) 
    {
        msg.append(generateRandomString(16 - msg.length()));
    }
    
        // DECRYPT
    if (en0_de1==1)
    {
        for (int l=0; l<4; ++l)
            for (int r=0; r<4; ++r)
                itog1[arr[l][r]] = msg[l*4+r];


        wcout<< "DECRYPTED message by Kardano square:\n\n";
        for (int i=0; i<16; ++i)
            wcout<< itog1[i];    
        wcout<<endl;                    
    }

    else
        // ENCRYPT
    {
        for (int l=0; l<4; ++l)
            for (int r=0; r<4; ++r)
                itog[l][r] = msg[arr[l][r]];
        
        wcout<< "ENCRYPTED message by Kardano square:\n\n";
        for (int l=0; l<4; ++l)
            for (int r=0; r<4; ++r)
                wcout<< itog[l][r];


        wcout<< "\n\nOR:\n\n";


        for (int l=0; l<4; ++l)
        {
            for (int r=0; r<4; ++r)
                wcout<< itog[l][r]<< ' ';
            wcout<< endl;
        }
    }

}

//========================================================================
void Decode(vector<int> index,char matrix[5][5]){
    int a = 0, b = 0;
    cout << "encrypted sequence: " << endl;
    for(int i = 0; i <= index.size()-3; i+=4){
        // если на одной строке
        a = index[i + 3] - 1;
        if(index[i] == index[i + 2] && a >= 0){
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] - 1] << matrix[index[i + 2]][a];
        }
        // если на одной строке и у края
        if(index[i] == index[i + 2] && a < 0){
            a = 4;
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] - 1] << matrix[index[i + 2]][a];
        }
        // если в одном столбце
        b = index[i + 2] - 1;
        if(index[i + 1] == index[i + 3] && b >= 0){
            cout.width(5);
            cout << matrix[index[i] - 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        // если в одном столбце и у края
        if(index[i + 1] == index[i + 3] && b < 0){
            b = 4;
            cout.width(5);
            cout << matrix[index[i] - 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        
        if(index[i] != index[i + 2] && index[i + 1] != index[i + 3]){
            cout.width(5);
            cout << matrix[index[i + 2]][index[i + 1]] << matrix[index[i]][index[i + 3]];
        }
    }
}
//==
void Encode(vector<int> index,char matrix[5][5]){
    int a = 0, b = 0;
    cout << "encrypted sequence: " << endl;
    for(int i = 0; i <= index.size()-3; i+=4){
        a = index[i + 3] + 1;
        // если на одной строке
        if(index[i] == index[i+2] && a < 5){
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] + 1] << matrix[index[i + 2]][a];
        }
        // если на одной строке и у края
        if(index[i] == index[i+2] && a >= 5){
            a = 0;
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] + 1] << matrix[index[i + 2]][a];
        }
        b = index[i + 2] + 1;
        // если в одном столбце
        if(index[i + 1] == index[i + 3] && b < 5){
            cout.width(5);
            cout << matrix[index[i] + 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        // если в одном столбце и у края
        if(index[i + 1] == index[i + 3] && b >= 5){
            b = 0;
            cout.width(5);
            cout << matrix[index[i] + 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        
        if(index[i] != index[i + 2] && index[i + 1] != index[i + 3]){
            cout.width(5);
            cout << matrix[index[i + 2]][index[i + 1]] << matrix[index[i]][index[i + 3]];
        }
    }
}
//==#######
void Playfair(){
/* 
matrix 5*5 . 
First squares are fulfilled by the key-word (with no double letters)
Next squares - by english alphabeth (abcdefghijklmnoprstuvwxyz). Remaining letters.
Message to be encrypted is divided into bigrams (if double letters or if odd -> add some letter)
RULES TO ENCRYPT:
a d     ab -> sd 
s b


a b c   ab -> bc
d e g


a d     ab -> bc
b e
c f
 */
    vector<int> index;
    string keyword, code;
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    char matrix[5][5];
    
    char x;
    cout << "enter number encoding(1) or decoding(2)" << endl;
    cin >> x;
    
    if(x != '1' && x != '2'){
        cout << "value entered incorrectly" << endl;
        exit(0);
    }
    
    int q = 0;
    while(q == 0){
        cout << "enter a keyword: ";
        cin >> keyword;
        
        // проверка на верхний регистр
        for(int i = 0; i < keyword.length(); i++){
            if(isupper(keyword[i])) keyword[i] = tolower(keyword[i]);
        }
        
        // проверка на посторонние символы
        for(int i = 0; i < keyword.length(); i++){
            if(isalpha(keyword[i])) q = 1;
            else {
                cout << "symbol " << keyword[i] << " is not appropriate " << i + 1 << " on position" << endl;
                q = 0;
                break;
            }
        }
    }
    
    // удаление дублирования
    for(int i = 1; i < keyword.length(); i++){
        if(keyword[i-1] == keyword[i]){
            keyword.erase(i, 1);
            i--;
        }
    }
    
    // удаление букв ключевого слова из алфавита 
    for(int i = 0; i < keyword.length(); i++){
        for(int j = 0; j < alphabet.length(); j++){
            if(keyword[i] == alphabet[j]) alphabet.erase(j, 1);
        }
    }
    
    // ввод данных в массив
    cout << "key matrix: " << endl;
    int k = 0, m = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(k < keyword.length()){
                matrix[i][j] = keyword[k];
            }
            if(k >= keyword.length()){
                matrix[i][j] = alphabet[m];
                m++;
            }
            k++;
        }
    }
    
    // вывод массива 
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    int p = 0;
    while(p == 0){
        cout << "enter massage: ";
        cin >> code;
        
        // проверка на верхний регистр
        for(int i = 0; i < code.length(); i++){
            if(isupper(code[i])) code[i] = tolower(code[i]);
        }
        
        // проверка на посторонние символы
        for(int i = 0; i < code.length(); i++){
            if(isalpha(code[i])) p = 1;
            else {
                cout << "symbol " << code[i] << " is not appropriate " << i + 1 << " on position" << endl;
                p = 0;
                break;
            }
        }
    }
    
    // обработка дублирования в биграмме 
    for(int i = 0; i < code.length(); i++){
        if(code[i] == code[i + 1]) code.insert(i+1, 1, 'x');
    }
    
    // добавление символа в неполную биграмму 
    if(code.length() % 2 != 0) code.push_back('x');
    
    // формирование биграмм
    for(int i = 0; i < code.length(); i+=2){
        cout.width(5);
        cout << code[i] << code[i + 1];
    }
    cout << endl;
    
    // нахождение индексов в матрице
    for(int i = 0; i < code.length(); i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(code[i] == matrix[j][k]){
                    index.push_back(j);
                    index.push_back(k);
                }
            }
        }
    }
    
  /*   for(int i = 0; i < index.size(); i+=2) cout << index[i] << " " << index[i+1] << "   ";
    cout << endl; */
    
    if(x == '1') Encode(index, matrix);
    if(x == '2') Decode(index, matrix);
    
}


//========================================================================
std::vector<std::vector<char>> createMatrix(const std::string& str) {
    int sideLength = static_cast<int>(std::ceil(std::sqrt(str.length())));
    std::vector<std::vector<char>> matrix(sideLength, std::vector<char>(sideLength, ' '));
    
    int index = 0;
    for (int i = 0; i < sideLength; ++i) {
        for (int j = 0; j < sideLength; ++j) {
            if (index < str.length()) {
                matrix[i][j] = str[index];
            } else {
                // Добавляем рандомный символ английского алфавита
                matrix[i][j] = 'A' + rand() % 26;
            }
            index++;
        }
    }
    
    return matrix;
}
//==#######
std::vector<std::vector<char>> shuffleMatrix(const std::vector<std::vector<char>>& matrix, const std::string& rowOrder, const std::string& colOrder) {
    int size = matrix.size();
    std::vector<std::vector<char>> shuffledMatrix(size, std::vector<char>(size));
    
    // Перемешиваем строки
    for (int i = 0; i < size; ++i) {
        int newRow = rowOrder[i] - '1';
        for (int j = 0; j < size; ++j) {
            shuffledMatrix[newRow][j] = matrix[i][j];
        }
    }
    
    // Создаем временную матрицу для правильного перемешивания столбцов
    std::vector<std::vector<char>> tempMatrix(size, std::vector<char>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tempMatrix[i][j] = shuffledMatrix[i][j];
        }
    }
    
    // Перемешиваем столбцы
    for (int j = 0; j < size; ++j) {
        int newCol = colOrder[j] - '1';
        for (int i = 0; i < size; ++i) {
            shuffledMatrix[i][newCol] = tempMatrix[i][j];
        }
    }
    
    return shuffledMatrix;
}
//==#######
std::vector<std::vector<char>> decipherMatrix(const std::vector<std::vector<char>>& shuffledMatrix, const std::string& rowOrder, const std::string& colOrder) {
    int size = shuffledMatrix.size();
    std::vector<std::vector<char>> decipheredMatrix(size, std::vector<char>(size));
    
    // Расшифровываем столбцы
    for (int j = 0; j < size; ++j) {
        int originalCol = colOrder[j] - '1';
        for (int i = 0; i < size; ++i) {
            decipheredMatrix[i][originalCol] = shuffledMatrix[i][j];
        }
    }
    
    // Создаем временную матрицу для правильного расшифрования строк
    std::vector<std::vector<char>> tempMatrix(size, std::vector<char>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tempMatrix[i][j] = decipheredMatrix[i][j];
        }
    }
    
    // Расшифровываем строки
    for (int i = 0; i < size; ++i) {
        int originalRow = rowOrder[i] - '1';
        for (int j = 0; j < size; ++j) {
            decipheredMatrix[originalRow][j] = tempMatrix[i][j];
        }
    }
    
    return decipheredMatrix;
}
//==#######
void DoubleTransposition() {
    std::string input;
    std::cout << "Введите текст: ";
    std::getline(std::cin, input);
    
    std::vector<std::vector<char>> result = createMatrix(input);
    
    for (const auto& row : result) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    
    int rows = result.size();
    int cols = rows > 0 ? result.at(0).size() : 0;
    
    std::string key_col, key_row;
    std::cout << "Введите ключ для строк (от 1 до "<< rows <<"): ";
    std::getline(std::cin, key_row);
    std::cout << "Введите ключ для столбцов (от 1 до "<< cols <<"): ";
    std::getline(std::cin, key_col);    

    std::cout << "\nЗашифрованное сообщение: ";

    std::vector<std::vector<char>> shuffledMatrix = shuffleMatrix(result, key_row, key_col);
    
    for (const auto& row : shuffledMatrix) 
        for (char c : row) 
            std::cout << c << " ";
    std::cout << std::endl;
    for (const auto& row : shuffledMatrix) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\nРасшифрованное сообщение: ";

    std::vector<std::vector<char>> decipheredMatrix = decipherMatrix(shuffledMatrix, key_row, key_col);
    
    for (const auto& row : decipheredMatrix) 
        for (char c : row) 
            std::cout << c << " ";
    std::cout << std::endl;
    for (const auto& row : decipheredMatrix) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

//#############################################################################
int main ()
{
    ///Cesar () ;

    ///Polibii();

    Kardano();
    
    ///Playfair();
    ///DoubleTransposition();

}
