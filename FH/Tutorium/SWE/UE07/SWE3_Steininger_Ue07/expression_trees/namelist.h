#ifndef EXPRESSION_TREE_NAMELIST_H
#define EXPRESSION_TREE_NAMELIST_H
#include <map>
#include <iostream>
#include <string>

namespace xpr{
    template<typename T>
    class NameList{
    public:
        NameList(){}
        virtual ~NameList(){}
        virtual T lookup_var(std::string name)=0;
        virtual void register_var(std::string name, T value)=0;
        virtual void print(std::ostream& out)=0;
    };

    template<typename T>
    class NameListMap : public NameList<T>{
    public:
        NameListMap(){}
        virtual ~NameListMap(){
            //delete every (sbu)tree that is associated with stored values
            for (auto it = name_list.begin();  it != name_list.end(); ++it) {
                delete it->second;
            }
        }
        virtual T lookup_var(std::string name){

            return name_list.count(name)==1 ? name_list[name] : nullptr; //check if key exists in map and return the value; if not return nullptr
        }
        virtual void register_var(std::string name, T value){
            //check if key exists
            //if so delete the corresponding (sub)tree and erase entry from map
            if (name_list.count(name) == 1){
                delete name_list[name];
                name_list.erase(name);
            }
            name_list[name] = value;
        }
        virtual void print(std::ostream& out) {
            for (auto it = name_list.begin();  it != name_list.end(); ++it) {
                out<<it->first << ": "<<it->second<<"\n";
            }

        }
    private:
        std::map<std::string, T> name_list;

    };
}
#endif //EXPRESSION_TREE_NAMELIST_H
