#include <iostream>
#include <string>
using namespace std;

int main(){
    string tweet;
    int arroba = 0;
    int hashtag = 0;
    string a[3], h[3];

    while (cin >> tweet){
        if(tweet[0] == '@' && arroba < 3){
            a[arroba] = tweet;
            arroba++;
        }
        if(tweet[0] == '#' && hashtag < 3){
            h[hashtag] = tweet;
            hashtag++;
        }
    }

    if(hashtag>0){
        cout << "Hashtags:";
        for(int i=0; i<hashtag; i++){cout << " " << h[i];}
    }else{
        cout << "O tweet não possui hashtags.";
    }
    
    if(arroba>2){
        cout << "\nTweet inválido.";
    }else if(arroba==0){
        cout << "\nO tweet não possui arrobas.";
    }else{
        cout << "\nArrobas:";
        for(int i=0; i<arroba; i++){cout << " " << a[i];}
    }

    return 0;
}