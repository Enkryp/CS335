

struct scope{
    string type;
    class_metadata class_meta;
    method_metadata method_meta;
    vector<field_metadata> field_meta;
    vector<scope*> children;
    scope* parent;
    bool is_static=0;
    map<string,Type> entries;
    int line_number=0;
};

map<char*,scope*> scopes;
void addentry(char* c,string id,string type,bool is_static,int width){  // adds entry to scope
    scope* s=scopes[c];
    if(s->entries.find(id)!=s->entries.end()){
        yyerror(stringtochar("Previously declared at "+ numtostring(s->entries[id].line_number)+" redeclared "));
    }
    // if(is_static){
    //     if(type!="class")yyerror("cannot declare static int ");
    // // }
    // s->entries[id];
    // s->entries[id]["width"]=numtostring(width);
    // s->entries[id]["type"]=type;
    // s->entries[id]["dec_line"]=chartostring(numtochar(yylineno));
    // s->entries[id]["is_static"]=numtostring((int)is_static);
}
void add_child(char * a, char * b){
    if(scopes.find(b)!=scopes.end())return;
    scopes[a]->children.push_back(scopes[b]);
    scopes[b]->parent=scopes[a];
}
void merge(char * a,char  *b){
    if(scopes.find(a)!=scopes.end())swap(a,b);
    if(scopes.find(b)!=scopes.end())return;
    for(auto e: scopes[b]->children){
        scopes[a]->children.push_back(e);
    }
    for(auto e: scopes[b]->entries){
        if(scopes[a]->entries.find(e.first)!=scopes[a]->entries.end()){
            yyerror("redeclaration");
        }
        scopes[a]->entries[e.first]=e.second;
    }
}