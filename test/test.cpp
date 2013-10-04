#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
using namespace std;

string commend = "c:/K-Means.exe c:/test/normal1.mat normal1 2 0.01";
int level = 0;
int s[17];
void func ()
{
    level++;
    if(level == 17){
        int test = 0;
        char ss[50];
        for(int i=1; i<level; i++){
            if(s[i] == 1) test++;
            sprintf(ss + (i-1)*2," %d",s[i]);
            if(i == (level-1)) ss[32] = '\0';

        }
        if(test == 16 || test == 0){
            level--;
            return;
        }
      //  commend += string(ss);
     //   commend += string("  >>d:/1.txt");

        system((commend + string(ss) + string("  >>d:/1.txt")).c_str());
    }
    else{
        s[level] = 1;
        func();
        s[level] = 2;
        func();
    }
    level--;
    return;

}
int main()
{
    func();
    return 0;
}
