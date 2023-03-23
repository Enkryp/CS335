#define ll long long
struct vardecid {
    string name;
    ll num=0;
};
struct vardecinit {
    
    vector<ll> dims;
};

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
        vector<pair<vardecid, vardecinit>>  vlist;

 


        bool operator<(const general& other) const{
            return name<other.name;
        }
        
    };

    map<char*, general> generalmap;

    struct methodsig{
        vector <ll>access;
        type rettype;
        vector<type> argtype;
        bool operator<(const methodsig& other) const{
            return rettype.dims<other.rettype.dims;
        }
    };
    struct fieldsig{
        vector <ll>access;
        type typ;  /*CHECK*/
        vector<ll> dims;
        bool operator<(const fieldsig& other) const{
            return typ.dims<other.typ.dims;
        }
    };

    struct varentry{
        type typ;
        vector<ll> dims; /*BOUNDS*/
        ll scope;
        bool operator<(const varentry& other) const{
            return scope<other.scope;
        }
    };
    void printvarentry(varentry v){
    
        cout<<" type: "<<v.typ.name<<" type dims: "<<v.typ.dims<<" bounds: "<<v.dims.size()<<" scope: "<<v.scope<<endl;
        for (ll i=0;i<v.dims.size();i++){
            cout<<v.dims[i]<<" ";
        }
    cout<<endl;
    }



   map<string, methodsig> methods;

    map<string, fieldsig> fields;

    map<string, varentry> symboltable;
        map<pair<string,ll>, varentry> preservedsymboltable;
    map<ll,ll> parentscope;
     map<int, map<string, string>> ds;
     vector <string> code;

     void type_check(string a , string b, string c){};
 string type_conversion(string a , string b, string c){};

 void dbgsymtable(){

for (auto x : symboltable){
    cout<<x.first<<" ";
    printvarentry(x.second);
 }
 cout<<endl;

 for (auto x: fields){
        cout<<x.first<<" ";
        }
 }

 map<ll, map<string,vector<string>>> ds2;

void printmethodstable(){
    for (auto x : methods){
        cout<<x.first<<" ";
        cout<<x.second.rettype.name<<" ";
        for (auto y : x.second.argtype){
            cout<<y.name<<" ";
        }
        cout<<endl;
    }
}

 void type_check_function(string name, vector<string> types){
// return;
 cout<<"type check function"<<endl;
 cout<<name<<endl;
 for(auto x : types){
     cout<<x<<" ";

printmethodstable();

cout<<endl;

    assert(methods.find(name)!=methods.end());
    methodsig m=methods[name];
    assert(m.argtype.size()==types.size());
    for (ll i=0;i<types.size();i++){
        assert(m.argtype[i].name==types[i]);
    }
 }
 }

ll num_var=1;
     string new_var(){
        return "t"+numtostring(num_var++);
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
