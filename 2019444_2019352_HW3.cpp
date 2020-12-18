/*
    Name: Muhammad Saaim Qureshi
    Reg: 2019444

    Name: Muwahid Asim
    Reg: 2019352
*/

#include<iostream>
#include<fstream>
using namespace std;

#define SIZE 10
#define WORD_END '$'
#define INPUT_FILE "dict.txt"

class Dictionary
{
    struct Node
    {
        char character;
        Node *children[SIZE];
    }*head;

    public:
        Dictionary()
        {
            head = new Node;
            head->character = '\0';
        }

        void dict_init()
        {
            Node *tempNode;
            ifstream file(INPUT_FILE);
            string word;

            while(!file.eof())
            {
                tempNode = head;
                file >> word;
                word += WORD_END; // Adding $ at the end of each word
            
                for(int i = 0; word[i] != '\0'; i++)
                {
                    for(int j = 0; j < SIZE; j++)
                    {
                        if(tempNode->children[j] == NULL)
                        {
                            tempNode->children[j] = new Node;
                            tempNode->children[j]->character = word[i];
                            tempNode = tempNode->children[j];
                            break;
                        }
                        else if(tempNode->children[j]->character == word[i])
                        {
                            tempNode = tempNode->children[j];
                            break;
                        }
                    }
                }
            }

            file.close();
        }

        void search(string word)
        {
            int index = 0;
            Node *tempNode = head;
            cout << "THIS CALLED\n";
            while((tempNode != NULL) && (tempNode->character != WORD_END))
            {
                for(int i = 0; i < SIZE; i++)
                {
                    cout << word[index] << endl;
                    if((tempNode->children[i] == NULL) || ((tempNode->children[i]->character == WORD_END) && (word[index] == '\0')))
                    {
                        tempNode = tempNode->children[i];
                        break;
                    }
                    else if(tempNode->children[i]->character == word[index])
                    {
                        tempNode = tempNode->children[i];
                        index++;
                        break;
                    }
                   /* else if(((tempNode->children[i]->character == WORD_END) && (word[index] == '\0')))
                    {
                        tempNode = tempNode->children[i];
                        break;
                    } */
                }
            }

            if(tempNode)
                cout << word << " found in the dictionary\n";
            else
                cout << word << " NOT FOUND in the dictionary!\n";
        }
};

int main()
{

    Dictionary theDict;
    theDict.dict_init();
    theDict.search("ape");


    return 0;
}
