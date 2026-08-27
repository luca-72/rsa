#include "bigint.h"

#include "primality.h"

#include "rsa.h"

#include<iostream>

#include<vector>

using namespace std;

int main() {

   NrMare pt, ct;
   setup();
   string s;
   while (true) {

      cout << "enter the message : ";
      getline(cin, s);

      if (s.size() < 4000)
         break;

      cout << "the message can't be longer than 400 characters. try again\n";

   }

   cout << "\n";

   vector < string > vmes;
   string aux;
   int i, j, lg;

   lg = s.size();

   for (i = 0; i < lg; i++) {

      aux.clear();

      for (j = i; j < i + 4 && j < lg; j++) {

         aux.push_back(s[j]);

      }

      i = j - 1;

      vmes.push_back(aux);

   }

   NrMare vct[1002], vpt[1002];
   NrMare auxct, auxpt;
   int lgvct = 0, lgvpt = 0;

   for (auto ee: vmes) {

      encrypt(auxct, ee);

      AtribMare(vct[++lgvct], auxct);

   }

   cout << "encrypted message : ";
   for (i = 1; i <= lgvct; i++) {
      Afis(vct[i]);
   }
   cout << endl;

   display();

   for (i = 1; i <= lgvct; i++) {

      decrypt(auxpt, vct[i]);
      AtribMare(vpt[++lgvpt], auxpt); 

   }

   cout << "decrypted message : ";
   for (i = 1; i <= lgvpt; i++)
      write(vpt[i]);
   cout << "\n\n";

}