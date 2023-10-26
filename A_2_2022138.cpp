#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Trie
{
public:
public:
  class node
  {
  public:
    bool end;
    node *next[26];
    node()
    {
      end = false;
      for (int i = 0; i < 26; i++)
      {
        next[i] = NULL;
      }
    }
  };
  node *trie;
  Trie()
  {
    trie = new node();
  }

  void insert(string word)
  {
    int i = 0;
    node *it = trie;
    while (i < word.size())
    {
      if (it->next[word[i] - 'a'] == NULL)
      {
        it->next[word[i] - 'a'] = new node();
      }
      it = it->next[word[i] - 'a'];
      i++;
    }
    it->end = true;
  }
  bool search_word(string word)
  {
    int i = 0;
    node *it = trie;
    while (i < word.size())
    {
      if (it->next[word[i] - 'a'] == NULL)
      {
        return false;
      }
      it = it->next[word[i] - 'a'];
      i++;
    }
    return it->end;
  }
  string reverseString(string word)
  {
    string newWord = "";
    for (int i = word.length() - 1; i > -1; i--)
      newWord = newWord + word[i];
    return newWord;
  }

  void inserting_dictionary_into_trie(Trie trie)
  {
    string word;
    ifstream input;
    input.open("dictionary.txt");
    while (getline(input, word))
    {
      trie.insert(word);
      word = "";
    }

    input.close();
  }
  void search_diagonally(char arr[][12], Trie trie, ofstream &out)
  {
    out << "\n-----------Diagonal Search---------------\n";
    string reverse = "";
    for (int i = 0; i < 7; i++)
    {
      for (int j = 0; j < 12; j++)
      {
        string word = "";

        int k = i;
        int l = j;

        while (k < 7 && l < 12)
        {
          word += arr[k][l];
          reverse = reverseString(word);
          k++;
          l++;
        }

        if (trie.search_word(word))
        {
          out << word << "(" << (i - word.length() + 1) << "," << (j - word.length() + 1) << ")"
              << " (" << i << "," << j << ")";
          out << endl;
        }
        if (trie.search_word(reverse))
        {
          out << word;
          out << endl;
        }
      }
    }
  }

  void vertical_search(char arr[7][12], int rows, int columns, Trie trie, ofstream &out)
  {

    out << "\n------------Vertical Search--------------\n";
    string meaningful_word;
    string reverse = "";
    for (int i = 0; i < columns; i++)
    {
      int k = 0;
      while (k < 7)
      {
        meaningful_word = "";
        for (int j = k; j < rows; j++)
        {
          meaningful_word += arr[j][i];
          reverse = reverseString(meaningful_word);
          if (trie.search_word(meaningful_word))
          {
            out << meaningful_word << " (" << (j - meaningful_word.length() + 1) << "," << i << ") "
                << " (" << j << "," << i << ")";
            out << endl;
          }
          if (trie.search_word(reverse))
          {
            out << reverse << " (" << j << "," << i << ") "
                << " (" << (j - meaningful_word.length() + 1) << "," << i << ")";
            out << endl;
          }
        }
        k++;
      }
    }

  }

  void horizontal_search(char arr[7][12], int rows, int columns, Trie trie, ofstream &out)
  {
    string reverse = "";
    out << "\n----------------Horizontal Search----------\n";
    string meaningful_word;
    for (int i = 0; i < rows; i++)
    {
      int k = 0;
      while (k < 12)
      {
        meaningful_word = "";
        for (int j = k; j < columns; j++)
        {
          meaningful_word += arr[i][j];
          reverse = reverseString(meaningful_word);
          if (trie.search_word(meaningful_word))
          {
            out << meaningful_word << " (" << i << "," << (j - meaningful_word.length() + 1) << ") "
                << " (" << i << "," << j << ")";
            out << endl;
          }
          if (trie.search_word(reverse))
          {
            out << reverse << " (" << i << "," << j << ") "
                << " (" << i << "," << (j - meaningful_word.length() + 1) << ")";
            out << endl;
          }
        }
        k++;
      }
    }
  };
  void searching_words_in_array(char arr[][12], int rows, int columns, Trie trie)
  {
    ofstream out;
    out.open("output.txt");
    horizontal_search(arr, rows, columns, trie, out);
vertical_search(arr, rows, columns, trie, out);
    search_diagonally(arr, trie, out);
    out.close();
  }
};

int main()
{
  Trie trie;
  trie.inserting_dictionary_into_trie(trie);
  char arr[7][12] = {{'d', 'o', 'g', 'x', 'b', 'x', 'x', 'x', 'n', 'o', 'o', 'n'},
                     {'r', 'h', 'e', 'l', 'l', 'o', 't', 'h', 'e', 'r', 'e', 'x'},
                     {'o', 'k', 'c', 'i', 'u', 'q', 'b', 'r', 'o', 'w', 'n', 'm'},
                     {'w', 'x', 'w', 'g', 'e', 'x', 'l', 'x', 'h', 'j', 'i', 'j'},
                     {'o', 'o', 'z', 'o', 'k', 'v', 'u', 'x', 'd', 'r', 'o', 'w'},
                     {'r', 'l', 'x', 'd', 'r', 'x', 'e', 'x', 't', 'x', 'j', 'a'},
                     {'d', 'r', 'o', 'w', 'b', 'l', 'o', 'n', 'k', 'g', 'o', 'd'}};
  cout<<"\nMeaningful words are extracted from following block of words and stored in output.txt file ";
  for(int i=0; i<7; i++){
    cout<<endl;
    for(int j=0; j<12; j++){
      cout<<arr[i][j];
    }
  }
  trie.searching_words_in_array(arr, 7, 12, trie);

  return 0;
}