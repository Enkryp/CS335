
struct field_metadata{
    string name;
    Type type;
    map<string,int> modifiers;
    bool is_initialized=0;
};
struct method_argument{
    Type type;
    string name;
    bool is_initialized=0;
};  
struct method_metadata{
    string name;
    map<string,int> modifiers;
    Type return_type;
    bool is_constructor=0;
    vector<method_argument> args;   
};
struct class_metadata{
    string name;
    string inherited_from;
    map<string,int> modifiers;
    vector<field_metadata> fields;
    vector<method_metadata> methods;
    // int constructor=0;
};
