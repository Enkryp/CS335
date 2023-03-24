struct Type{
    string name;
    bool is_array=0;
    string type;
    int width;
    int line_number;
    int offset;
    Type* next=NULL; 
    Type* prev=NULL; 
};
// Type* merge(Type* a, Type* b){
//     auto c=a;
//     while(a->is_array){
//         a=a-
//     }
// }