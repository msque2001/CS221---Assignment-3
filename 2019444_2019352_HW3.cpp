/*
    Name: Muhammad Saaim Qureshi
    Reg: 2019444

    Name: Muwahid Asim
    Reg: 2019352
*/

#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;



#define SIZE 27
#define ROW 7             //row size defined to 7
#define Column 13        //column size defined to 12, 13 is /0 in string
#define WORD_END '$'
#define INPUT_FILE "dict.txt"




class Dictionary
{
    struct Node
    {
        char character;
        Node* children[SIZE];
        Node() : children() {}
    }*head;

    void addWord(string word)
    {
        Node *tempNode = head;
        word += WORD_END; // Adding $ at the end of each word

        for (int i = 0; word[i] != '\0'; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (tempNode->children[j] == NULL)
                {
                        tempNode->children[j] = new Node;
                        tempNode->children[j]->character = word[i];
                        tempNode = tempNode->children[j];
                        break;
                }
                else if (tempNode->children[j]->character == word[i])
                {
                    tempNode = tempNode->children[j];
                    break;
                }

            }
        }
    }

public:
    Dictionary()
    {
        head = new Node;
        head->character = '\0';
    }

    void dict_init()
    {
        ifstream file(INPUT_FILE);
        string word;

        while (!file.eof())
        {
            file >> word;
            addWord(word);
        }

        file.close();
    }

    bool search(string word)
    {
        int index = 0;
        Node* tempNode = head;
        while ((tempNode != NULL) && (tempNode->character != WORD_END))
        {
            for (int i = 0; i < SIZE; i++)
            {
                if ((tempNode->children[i] == NULL) || ((tempNode->children[i]->character == WORD_END) && (word[index] == '\0')))
                {
                    tempNode = tempNode->children[i];
                    break;
                }
                else if (tempNode->children[i]->character == word[index])
                {
                    tempNode = tempNode->children[i];
                    index++;
                    break;
                }
            }
        }

        if (tempNode)
        {
            
            return true;
        }
        else
        {
            
            return false;

        }
        }

};

Dictionary theDict;


void horizontal_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    bool word=false;
    int start[2];
    int end[2];
   
    fout << "\nHORIZONTAL FORWARD WORDS: \n";
    for (int i = 0;i < ROW;i++)
    {
        for (int j = 0;j < Column-1;j++)
        {
            start[1] = j+1;
            start[0] = i+1;
            possible_word = array[i][j];  //makes all possible combination of words horizontally and checks if it is sored in tries
            for (int k = j+1;k < Column-1;k++)
            {
                
                possible_word = possible_word + array[i][k];
                end[1] = k+1;
                end[0] = i+1;
                word=theDict.search(possible_word);
                if (word)
                {
                 
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }


            }
            
            
        }

    }
    fout.close();
}

void reverse_horizontal_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);      //opens file
    string possible_word;                
    bool word = false;
    int start[2];                             //start and end position stored here
    int end[2];
    fout << "\nHORIZONTAL BACKWARDS WORDS: \n";
    for (int i = 0;i < ROW;i++)
    {
        for (int j = Column-2;j >=0 ;j--)
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = j-1;k >= 0;k--)
            {

                possible_word = possible_word + array[i][k];                         //makes all possible words
                end[1] = k + 1;
                end[0] = i + 1;
                word = theDict.search(possible_word);
                if (word)                                      //checks if word is found
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }


            }


        }
    }
    fout.close();
}

void vertical_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    bool word = false;                          //makes all possible combination of words vertically and checks if it is sored in tries
    int start[2];
    int end[2];
    fout << "\nVERTICAL FORWARD WORDS: \n";
    for (int j = 0;j < Column-1;j++)
    {
        for (int i = 0;i < ROW;i++)
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = i + 1;k < ROW; k++)
            {
                possible_word = possible_word + array[k][j];
                end[1] = start[1];
                end[0] = k + 1;
                word = theDict.search(possible_word);
                if (word)
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }
            }
        }
    }
    fout.close();
}
void reverse_vertical_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    bool word = false;
    int start[2];
    int end[2];
    fout << "\nVERTICAL REVERSE WORDS: \n";
    for (int j = 0;j < Column-1;j++)                        //makes all possible combination of words vertically backwards and checks if it is sored in tries
    {
        for (int i = ROW-1;i >= 0;i--)
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = i-1 ;k >=0 ; k--)
            {
                possible_word = possible_word + array[k][j];
                end[1] = start[1];
                end[0] = k+1;
                word = theDict.search(possible_word);
                if (word)
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }
            }
        }
    }
    fout.close();
}

void right_diagnol_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    string reverse;
    bool word = false;
    int start[2];
    int end[2];
    fout << "\nRIGHT DIAGNOL FORWARD WORDS: \n";
    for (int i = 0;i < ROW;i++)
    {
        for (int j = 0;j < Column;j++)                              //makes all possible combination of words diagnollay rightwards and checks if it is sored in tries
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = j+1, l=i+1 ;k < Column-1 && l < ROW;k++,l++)
            {
                
                possible_word = possible_word + array[l][k];
                end[1] = k + 1;
                end[0] = l + 1;
                word = theDict.search(possible_word);
                if (word)
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }


            }


        }
    }
    fout.close();
}

void reverse_right_diagnol_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    string reverse;
    bool word = false;
    int start[2];
    int end[2];
    fout << "\nRIGHT DIAGNOL REVERSE WORDS: \n";                             //makes all possible combination of words diagnolly rightwards in backward direction and checks if it is sored in tries
    for (int i = ROW;i >= 0;i--)
    {
        for (int j = Column-1;j >=0;j--)
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = j - 1, l = i - 1;k >= 0 && l >=0;k--, l--)
            {

                possible_word = possible_word + array[l][k];
                end[1] = k + 1;
                end[0] = l + 1;
                word = theDict.search(possible_word);
                if (word)
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }


            }


        }
    }
    fout.close();
}


void left_diagnol_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    string reverse;
    bool word = false;
    int start[2];
    int end[2];
    fout << "\nLEFT DIAGNOL FORWARD WORDS: \n";
    for (int i = 0;i < ROW;i++)                                                  //makes all possible combination of words diagnolly in left direction and checks if it is sored in tries
    {
        for (int j = Column-2;j >= 0;j--)
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = j - 1, l = i + 1;k >= 0 && l < ROW;k--, l++)
            {

                possible_word = possible_word + array[l][k];
                end[1] = k + 1;
                end[0] = l + 1;
                word = theDict.search(possible_word);
                if (word)
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }


            }


        }
    }
    fout.close();
}


void reverse_left_diagnol_words(char array[ROW][Column])
{
    ofstream fout;
    fout.open("word_found.txt", ios::app);
    string possible_word;
    string reverse;
    bool word = false;
    int start[2];
    int end[2];
    fout << "\nLEFT DIAGNOL REVERSE WORDS: \n";
    for (int i = ROW-1;i >=0;i--)                                                  //makes all possible combination of words diagnolly in left direction backwards and checks if it is sored in tries
    {
        for (int j = 0;j <Column-1;j++)
        {
            start[1] = j + 1;
            start[0] = i + 1;
            possible_word = array[i][j];
            for (int k = j + 1, l = i - 1;k < Column-1 && l >= 0;k++, l--)
            {

                possible_word = possible_word + array[l][k];
                end[1] = k + 1;
                end[0] = l + 1;
                word = theDict.search(possible_word);
                if (word)
                {
                    fout << endl << possible_word << "(" << start[0] << "," << start[1] << ") (" << end[0] << "," << end[1] << ")";
                }


            }


        }
    }
    fout.close();
}


int main()
{
    // char array[ROW][Column] = {"godxxxxxbcat","txxxapplexxx","baxxxpuxlxxx","lxcxxeedxape","agoodxoxxxbu","cxxxxoxxxxxl","kxxxgxxkcalb"};//array declared
    char array[ROW][Column] = {"dogxbxxxnoon","rhellotherex","okciuqbrownm","wxwgexlxhjij","oozokvuxdrow","lxdrxextxja","drowblonkgod"};//array declared
    cout << "\nThe array is:\n";
    for (int i = 0;i < ROW;i++)
    {
        for (int j = 0;j < Column;j++)    //displays the hard coded array
        {
            cout<< array[i][j];

        }
        cout << endl;
    }

 
    theDict.dict_init();   //function call for storing all the data of text file in tries
    horizontal_words(array);      //function call for searchig horizontal
    reverse_horizontal_words(array);
    vertical_words(array);          //function call for searching vertical
    reverse_vertical_words(array);
    right_diagnol_words(array);         //function call for searching diagnol
    reverse_right_diagnol_words(array);  
    left_diagnol_words(array);
    reverse_left_diagnol_words(array);
    cout << "\n ALL POSSIBLE WORDS STORED IN TEXT FILE!!!!\n";
   


    return 0;
}
