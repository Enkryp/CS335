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
    
   