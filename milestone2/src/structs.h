#define ll long long
ll gbdimid=1000;


set <string> listofclasses; 
map<string, ll> tempinitval;

ll curoffset=0;
stack <ll>scopeoffset;

map<ll, string> dimtoid;
struct vardecid {
    string name;
    ll num=0;
};
struct vardecinit {
    
    vector<ll> dims;
    bool isnewclass=false;
    string classname = "";
};



void object_error(string name1, string name2, int lineno){

    cout<<"Illegal attribute "+name2+" of object "+name1+" at line "<<lineno<<"\n";
    exit(0);

}

void object_error_func(string name1, string name2, int lineno){

    cout<<"Illegal function "+name2+" of object "+name1+" at line "<<lineno<<"\n";
    exit(0);

}



struct type{
    string name;
    ll dims=0;
    
};

struct formalarg
{
    type typ;
    vardecid vid;
};




 struct general{
        formalarg farg;
        vector<formalarg> farglist;
        string name;
        ll num=0;
        type typ;
        vector<ll> arrayinit;
        vardecid vid;
        vardecinit vinit;
        bool isnewclass=false;
        string classname = "";
        vector<pair<vardecid, vardecinit>>  vlist;
        vector <string> dimexpaddrs;
        vector <string> modifiers;
 


        bool operator<(const general& other) const{
            return name<other.name;
        }
        
    };

    map<char*, general> generalmap;
    map<string, string> pref; 

    struct methodsig{
        vector <string> access;
        type rettype;
        ll lineno;
        vector<type> argtype;
        bool operator<(const methodsig& other) const{
            return rettype.dims<other.rettype.dims;
        }
    };
    struct fieldsig{
        vector <string>access;
        type typ;  /*CHECK*/
        ll lineno;
        vector<ll> dims;
        bool operator<(const fieldsig& other) const{
            return typ.dims<other.typ.dims;
        }
    };

    struct varentry{
        ll lineno;
        string token;
        type typ;
        vector<ll> dims; /*BOUNDS*/
        ll scope;
        ll offset=0;
        string objof; 
        bool operator<(const varentry& other) const{
            return scope<other.scope;
        }
    };
    void printvarentry(varentry v){
        if(v.dims.size() && v.typ.dims && v.dims.size()!=v.typ.dims)  assert(0 && "array init error");
        if(v.typ.dims && v.dims.size()==0) {for(int i=0; i<v.typ.dims; i++) v.dims.push_back(1000);}
        // cout<<" type: "<<v.typ.name<<" type dims: "<<v.typ.dims<<" bounds: "<<v.dims.size()<<" scope: "<<v.scope<<" offset "<<v.offset<<endl;
        for (ll i=0;i<v.dims.size();i++){
            // cout<<v.dims[i]<<" ";
        }
    // cout<<endl;
    }


    map<pair<string,string>, methodsig> preservedmethods;
map<pair<string,string>, fieldsig> preservedfields;


map<string , map<string, fieldsig>> classfields;
map<string , map<string, methodsig>> classmethods;

   map<string, methodsig> methods;

    map<string, fieldsig> fields;

    map<string, varentry> symboltable;
        map<pair<string,ll>, varentry> preservedsymboltable;
    map<ll,ll> parentscope;
     map<int, map<string, string>> ds;
     vector <string> code;

    //  void type_check(string a , string b, string c){};
//  string type_conversion(string a , string b, string c){};

 void dbgsymtable(){

for (auto x : symboltable){
    // cout<<x.first<<" ";
    printvarentry(x.second);
 }
//  cout<<endl;

 for (auto x: fields){
        // cout<<x.first<<" ";
        }
 }

 map<ll, map<string,vector<string>>> ds2;

void printmethodstable(){
    for (auto x : methods){
        // cout<<x.first<<" ";
        // cout<<x.second.rettype.name<<" ";
        for (auto y : x.second.argtype){
            // cout<<y.name<<" ";
        }
        // cout<<endl;
    }
}
vector <pair<string, vector <string>>> to_check_functions;


 void type_check_function(string name, vector<string> types){

if(methods.find(name)==methods.end()){
    to_check_functions.push_back({name,types});
    return;
}

    methodsig m=methods[name];
    // cout<<name<<endl;
    // for (auto x : types){
    //     cout<<x<<" ";
    // }
    assert(m.argtype.size()==types.size());
    for (ll i=0;i<types.size();i++){
        assert(m.argtype[i].name==types[i]);
    }
 }

 void type_check_function_obj(vector<type> argtype, vector<string> types){
    
    assert(argtype.size()==types.size());
    for (ll i=0;i<types.size();i++){
        assert(argtype[i].name==types[i]);
    }
 }

  void type_check_function_strong(){

for(auto x : to_check_functions){
    string name=x.first;
    vector<string> types=x.second;
    assert(methods.find(name)!=methods.end());
    methodsig m=methods[name];
    assert(m.argtype.size()==types.size());
    for (ll i=0;i<types.size();i++){
        assert(m.argtype[i].name==types[i]);
    }
 }
 }


ll num_var=1, num_var2=1;
     string new_var(){
        return "t"+numtostring(num_var++);
    }

    string new_var2(){
        return "c"+numtostring(num_var2++);
    }

    void backpatch(vector<int> &lines,int go){
        for(int i=0;i<lines.size();i++){
            code[lines[i]] += " "+numtostring(go);
        }
        lines.clear();
    }

    vector<int> merge(vector<int> &v1, vector<int> &v2){
        vector<int> v3;
        for(int i=0;i<v1.size();i++)
        v3.push_back(v1[i]);
        for(int i=0;i<v2.size();i++)
        v3.push_back(v2[i]);
        v1.clear();
        v2.clear();
        return v3;
    }

    void type_check_unary(string a, string b){}
   
   map<ll, map<string, vector<int>>> ds3;

vector<vector<ll>> arithmetics = {
{1,2,3,4,1,1,1,},
{2,2,3,4,2,2,2,},
{3,3,3,4,3,3,3,},
{4,4,4,4,4,4,4,},
{1,2,3,4,1,1,1,},
{1,2,3,4,1,1,1,},
{1,2,3,4,1,1,1,}
};
vector<vector<ll>> bitwise_shifts = {
    {1,1,-1,-1,1,1,1,},
{2,2,-1,-1,2,2,2,},
{-1,-1,-1,-1,-1,-1,-1,},
{-1,-1,-1,-1,-1,-1,-1,},
{1,1,-1,-1,1,1,1,},
{1,1,-1,-1,1,1,1,},
{1,1,-1,-1,1,1,1,}
};
vector<vector<ll>> bitwise_operators ={
    {1,2,-1,-1,1,1,1,},
{2,2,-1,-1,2,2,2,},
{-1,-1,-1,-1,-1,-1,-1,},
{-1,-1,-1,-1,-1,-1,-1,},
{1,2,-1,-1,1,1,1,},
{1,2,-1,-1,1,1,1,},
{1,2,-1,-1,1,1,1,}
};
vector<vector<ll>> conversions = {
    {1,1,1,1,0,0,0,0},
{0,1,1,1,0,0,0,0},
{0,0,1,1,0,0,0,0},
{0,0,0,1,0,0,0,0},
{1,1,1,1,1,0,0,0},
{1,1,1,1,0,1,1,0},
{1,1,1,1,0,0,1,0},
{0,0,0,0,0,0,0,1}
};
map<string,ll> typetonum={{"int",1},{"long",2},{"float",3},{"double",4},{"char",5},{"byte",6},{"short",7},{"boolean",8}};;
vector<string> numtotype ={"int","long","float","double","char","byte","short","boolean"};
void error_report_type(string s1, string s2, string op){
    cout<<"Bad operator types "<<s1<<" and "<<s2<<" for operator "<<op<<"\n";
    exit(0);
}
void type_check(string a,string b,string c){
    // cout<<a<<b;
    int arg1=typetonum[a];
    int arg2=typetonum[b];
    if(arg1==0||arg1==0){
        // reference type
        return ;
    }
    arg1--;
    arg2--;
    if(arg1==7||arg2==7){
        if(arg1!=7||arg2!=7){
            error_report_type(a,b,c);
        }
        else{
            if(c!="=="&&c!="!="&&c!="&&"&&c!="||"){
                error_report_type(a,b,c);
            }
        }
    }
    else{
        set<string> arithmetic={"+","-","/","*","%"};
        set<string> bitwise_shift={"<<",">>"};
        set<string> bitwise_operator ={"&","|"};
        set<string> relational ={"==", "!=", ">", "<", ">=", "<="};
        // set<string> relational ={"==", "!=", ">", "<", ">=", "<="};
        set<string> operator_double ={"+=", "-=", "*=", "/=", "&="};
        if(c=="="&&!conversions[arg2][arg1]){
            error_report_type(a,b,c);
        }
        if(operator_double.find(c)!=operator_double.end()){
            string s={c[0]};
            type_check(a,b,s);
            if(s[0]=='&')
            type_check(a,numtotype[bitwise_operators[arg1][arg2]-1],"=");
            else 
            type_check(a,numtotype[arithmetics[arg1][arg2]-1],"=");
        }
        else if(relational.find(c)!=relational.end()){
            
        }
        else if(bitwise_operator.find(c)!=bitwise_operator.end()){
            if(bitwise_operators[arg1][arg2]==-1)error_report_type(a,b,c);
        }
        else if(bitwise_shift.find(c)!=bitwise_shift.end()){

            if(bitwise_shifts[arg1][arg2]==-1)error_report_type(a,b,c);
        }
        else if(arithmetic.find(c)!=arithmetic.end()){

        }
        else {
            // opertor not find;
        }

    }
}

string type_conversion(string a,string b,string c){
    int arg1=typetonum[a];
    int arg2=typetonum[b];
    if(arg1==0||arg1==0){
        // reference type
        return "" ;
    }
    arg1--;
    arg2--;
    if(arg1==7||arg2==7){
        return "boolean";
    }
    else{
        set<string> arithmetic={"+","-","/","*","%"};
        set<string> bitwise_shift={"<<",">>"};
        set<string> bitwise_operator ={"&","|"};
        set<string> relational ={"==", "!=", ">", "<", ">=", "<="};
        // set<string> relational ={"==", "!=", ">", "<", ">=", "<="};
        set<string> operator_double ={"+=", "-=", "*=", "/=", "&="};
        if(c=="="){
            if(arg2!=arg1){
                // add command var(b) = to_cast(a) var(b)
            }
            return a;
        }
        else if(operator_double.find(c)!=operator_double.end()){
            return type_conversion(a,b,"="); 
        }
        else if(relational.find(c)!=relational.end()){
            if(conversions[arg2][arg1])
            return type_conversion(a,b,"=");
            else
            return type_conversion(b,a,"=");
            
        }
        else if(bitwise_operator.find(c)!=bitwise_operator.end()){
            if(conversions[arg2][arg1])
            return type_conversion(a,b,"=");
            else
            return type_conversion(b,a,"=");
        }
        else if(bitwise_shift.find(c)!=bitwise_shift.end()){

            if(conversions[arg2][arg1])
            return type_conversion(a,b,"=");
            else
            return type_conversion(b,a,"=");
        }
        else if(arithmetic.find(c)!=arithmetic.end()){
            if(conversions[arg2][arg1])
            return type_conversion(a,b,"=");
            else
            return type_conversion(b,a,"=");
        }
        else {
            // opertor not find;
        }

    }
}

vector<pair<string,string>> object_list;

bool isnum(string s){
    for(int i=0;i<s.size();i++){
        if(s[i]<'0'||s[i]>'9')return false;
    }
    return true;
}

ll varaddrstoint (string s){
    gbdimid++;
    dimtoid[gbdimid]=s;
    return -gbdimid;
}
struct objdetails{
    bool ismethod = false;
    bool isfield = false;
    methodsig method;
    fieldsig field;
};

objdetails getobjdetails(string obj, string name){
    string cls = symboltable[obj].typ.name;     /* two objects with same name in different class*/
    objdetails o;

    // if()
    if(classfields[cls].find(name) != classfields[cls].end()){
        
        o.isfield = true;
        o.field = classfields[cls][name];
        return o;
    }
    else if(classmethods[cls].find(name) != classmethods[cls].end()){
        
        o.ismethod = true;
        o.method = classmethods[cls][name];
        return o;
    }
    
    return o;
    }

struct method_copy{

    int start;
    int end;

};

map<string, map<string, method_copy>> method_det;

vector <string> getallfields(string obj){
    string cls = symboltable[obj].typ.name;
    vector <string> v;
    if(classfields.find(cls)==classfields.end()){
        for (auto x:fields){
            v.push_back(x.first);
        }
    }
    else {
    for(auto x:classfields[cls]){
        v.push_back(x.first);
    }}
    return v;
}

bool not_static_check(vector<string> access){
    for(auto i:access)
    {
        if(i=="static")
        return 0;
    }
    return 1;
}

vector<string> getallmethods(string obj, string cls){
    // string cls = symboltable[obj].typ.name;
    vector<string> methods;
    for(auto names: classmethods[cls]){
        int flag = 0;
        // for(auto j:names.second.access){
        //     cout<<"access"<<j<<"\n";
        //     if(j=="static")
        //     {
        //         flag = 1;
        //         break;
        //     }
        // }
        if(not_static_check(names.second.access))
        methods.push_back(names.first);
    }
    return methods;
}

vector<string> split_line(string & line){

    vector<string> words;
    string prev = "";
    for(int i=0;i<line.size();i++){

        if(line[i]==' '){
            words.push_back(prev);
            prev = "";
        }else prev += line[i];

    }
    words.push_back(prev);
    return words;

}

void add_func(vector<string> &code, string pref, int start, int end){

    // cout<<"srt"<<start<<" "<<end<<"\n";
    set<string> reservedwords = {"goto", "array", "begin", "func", "pop", "push", "param,","end", "call,","return", "if", "stackpointer"};
    // set<string> reservedwords;
    int currline = code.size();
    for(int i=start;i<=end;i++){
        string line = code[i];
        vector<string> words = split_line(line);
        vector<string> newline;
        // string newline;
        for(auto word: words){
            if(((word[0]>='a'&&word[0]<='z')||(word[0]>='A'&&word[0]<='Z')) && reservedwords.find(word)==reservedwords.end()){
                newline.push_back(pref+word);
            }else{
                newline.push_back(word);
                if(word == "goto"){
                    int next = stringtonum(words.back());
                    string go = numtostring(next-i+currline);
                    newline.push_back(go);
                    break;
                }
            }
        }
        string nextline = "";
        for(int j=0;j<newline.size()-1;j++){
            nextline += newline[j]+" ";
        }
        nextline += newline.back();
        code.push_back(nextline);
        currline++;
    }

}
ll gettypesize(string s){
    // cout<<"TPYESIZEINV"<<s<<"NO"<<endl;
    // TODO bool boolean
    //  get type size of a variable of java, s stores type
    if(s=="byte") return 1;
    else if(s=="short") return 2;
    else if(s=="int") return 4;
    else if(s=="long") return 8;
    else if(s=="float") return 4;
    else if(s=="double") return 8;
    else if(s=="boolean") return 1;
    else if(s=="bool") return 1;
    else if(s=="char") return 2;
    else if(s=="void") return 0;
    else return 4;

}

