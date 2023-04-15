// #include <bits/stdc++.h>
// using namespace std;
char * stringtochar(string s){
    int n=s.size();
    char* c= (char*)malloc(sizeof(char)*(n+1));
    for( int i=0;i<n;i++){  
        c[i]=s[i];
    }
    c[n]='\0';
    return c;
}
char* numtochar( int num){
    string s="";
    if(num<0){
        num=- num;
        while(num>0){
        s.push_back(num%10+'0');
        num/=10;
    }
    reverse(s.begin(),s.end());
    return stringtochar("-" + s);


    }
    else if (num==0){return stringtochar("0");}
    else {
    while(num>0){
        s.push_back(num%10+'0');
        num/=10;
    }
    reverse(s.begin(),s.end());
    return stringtochar(s);}
}
int stringtonum( string s){
    int i=0;
    int num=0;
    while(i!=s.size()){
        num*=10;
        num+=s[i]-'0';
        i++;
    }
    return num;
}
int chartonum(char * c){
    int i=0;
    int num=0;
    while(c[i]!='\0'){
        num*=10;
        num+=c[i]-'0';
        i++;
    }
    return num;
} 
string chartostring(char* c){
    string s;
    int i=0;
    while(c[i]!='\0'){
        s.push_back(c[i]);
        i++;
    }
    return s;
}
string numtostring(int num){
    return chartostring(numtochar(num));
}