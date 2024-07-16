#include <string>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

hash<string> hasher;

void gen_dic_table(const string& name){
    cout << "CREATE TABLE \"" << name << "_dic\" (\"hk\" TEXT NOT NULL UNIQUE, \"dt\" TEXT NOT NULL, \"src\"  TEXT NOT NULL, \"name\"	TEXT NOT NULL, PRIMARY KEY(\"hk\"));" << endl;
}

string gen_dic_rec(const string& name, const string& rec_name) {
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    string hk = to_string(hasher(rec_name));
    cout << "INSERT INTO \"" << name << "_dic\" (\"hk\",\"dt\",\"src\",\"name\") VALUES (\""<< hk <<"\",\""<<ms<<"\",\"1\",\"" << rec_name <<"\");"<< endl;
    return hk;
}

void gen_hub_table(const string& name){
    cout << "CREATE TABLE \"" << name << "_hub\" (\"hk\" TEXT NOT NULL UNIQUE, \"dt\" TEXT NOT NULL, \"src\"  TEXT NOT NULL, \"name\" TEXT NOT NULL, PRIMARY KEY(\"hk\"));" << endl;
}

string gen_hub_rec(const string& name, const string& rec_name) {
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    string hk = to_string(hasher(rec_name));
    cout << "INSERT INTO \"" << name << "_hub\" (\"hk\",\"dt\",\"src\",\"name\") VALUES (\""<< hk <<"\",\""<<ms<<"\",\"1\",\"" << rec_name <<"\");"<< endl;
    return hk;
}

void gen_hub_table_many(const string& name, vector<string>& fields){
    cout << "CREATE TABLE \"" << name << "_hub\" (\"hk\" TEXT NOT NULL UNIQUE, \"dt\" TEXT NOT NULL, \"src\"  TEXT NOT NULL, ";
    
    for (auto& fld: fields) {
        cout << "\"" << fld << "\" TEXT NOT NULL,";
    };

    cout << " PRIMARY KEY(\"hk\"));" << endl;

}

string gen_hub_rec_many(const string& name, vector<string>& fields,  vector<string>& values) {
    
    string rec_name ="";

    for (auto& vls: values) {
        rec_name += vls;
    };

    string hk = to_string(hasher(rec_name));
    cout << "INSERT INTO \"" << name << "_hub\" (\"hk\",\"dt\",\"src\"";
    
    for (auto& fld: fields) {
        cout << ",\"" << fld << "\"";
    };

    cout << ") VALUES (";

    cout << "\"" << hk << "\",";

    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout << "\"" << ms << "\",";

    cout << "\"1\"";

    for (auto& val: values) {
        cout << ",\"" << val << "\"";
    };

    cout <<  ");" << endl;

    return hk;
}

void gen_sat_table(const string& name, vector<string>& fields){
    cout << "CREATE TABLE \"" << name << "_sat\" (\"hk\" TEXT NOT NULL UNIQUE, \"dt\" TEXT NOT NULL, \"src\"  TEXT NOT NULL,"; 
    
    for (auto& fld: fields) {
        cout << "\"" << fld << "\" TEXT,";
    };

    cout << " PRIMARY KEY(\"hk\"));" << endl;
}

void gen_sat_rec(const string& name, const string& hk, const vector<string>& fields, const vector<string>& values){
    cout << "INSERT INTO \"" << name << "_sat\" (\"hk\", \"dt\", \"src\""; 
    
    for (auto& fld: fields) {
        cout << ",\"" << fld << "\"";
    };

    cout << ") VALUES (";

    cout << "\"" << hk << "\",";

    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout << "\"" << ms << "\",";

    cout << "\"1\"";

    for (auto& val: values) {
        cout << ",\"" << val << "\"";
    };

    cout <<  ");" << endl;
}

void gen_link_table(const string& link_1, const string& link_2) {
    cout << "CREATE TABLE \"link_" << link_1<<"_"<<link_2<<"\" (\"hk\" TEXT NOT NULL,\"dt\" TEXT NOT NULL,\"src\" TEXT NOT NULL, \""<<link_1<<"_hk\" TEXT NOT NULL,\"" << link_2 << "_hk\" TEXT);" << endl;
}

void gen_link_rec(const string& link_1, const string& link_2, const string& link_1_hk, const string& link_2_hk) {
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    string hk = to_string(hasher(link_1+link_2));
    cout << "INSERT INTO \"link_" << link_1<<"_"<<link_2<<"\" (\"hk\",\"dt\",\"src\", \""<<link_1<<"_hk\",\"" << link_2 << "_hk\") VALUES (\"" << hk << "\",\"" << ms << "\",\"1\",\"" << link_1_hk << "\",\"" << link_2_hk << "\");" << endl;
}

int main() {

    cout << "Start generate sql" << endl;

    std::ofstream out("init.sql");
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf()); 

    string politic = "politic";
    gen_hub_table(politic);
    string s1 = gen_hub_rec(politic, "POLITIC_1");
    string s2 = gen_hub_rec(politic, "POLITIC_2");

    string rule = "rule";
    gen_hub_table(rule);
    string get_1 = gen_hub_rec(rule, "Правило для GET_1");
    string put_1 =  gen_hub_rec(rule, "Правило для PUT_1");
    string  post_1 = gen_hub_rec(rule, "Правило для POST_1");
    string del_1 = gen_hub_rec(rule, "Правило для DELETE_1");
    string patch_1 = gen_hub_rec(rule, "Правило для PATCH_1"); 
    string head_1 = gen_hub_rec(rule, "Правило для HEAD_1");
    string options_1 = gen_hub_rec(rule, "Правило для OPTIONS_1"); 
    string trace_1 = gen_hub_rec(rule, "Правило для TRACE_1"); 
    string conn_1 = gen_hub_rec(rule, "Правило для CONNECT_1"); 

    string get_2 = gen_hub_rec(rule, "Правило для GET_2");
    string put_2 =  gen_hub_rec(rule, "Правило для PUT_2");
    string  post_2 = gen_hub_rec(rule, "Правило для POST_2");
    string del_2 = gen_hub_rec(rule, "Правило для DELETE_2");
    string patch_2 = gen_hub_rec(rule, "Правило для PATCH_2"); 
    string head_2 = gen_hub_rec(rule, "Правило для HEAD_2");
    string options_2 = gen_hub_rec(rule, "Правило для OPTIONS_2"); 
    string trace_2 = gen_hub_rec(rule, "Правило для TRACE_2"); 
    string conn_2 = gen_hub_rec(rule, "Правило для CONNECT_2"); 
   
    vector<string> politic_sat_flds {"description","recommend"};
    gen_sat_table(politic, politic_sat_flds);
    vector<string> politic_sat_values_1 {"Политика для сервиса 1","Для получения доступа добавьте пользователю роль из политики POLITIC_1: GET_1,PUT_1,POST_1,DELETE_1,PATCH_1,HEAD_1,OPTIONS_1,TRACE_1,CONNECT_1 или полный доступ FULL_ACCESS или выключите безопасность через переменную окружения POLITIC_1=0"};
    gen_sat_rec(politic, s1, politic_sat_flds, politic_sat_values_1);
    
    vector<string> politic_sat_values_2 {"Политика для сервиса 2","Для получения доступа добавьте пользователю роль из политики POLITIC_2: GET_2,PUT_2,POST_2,DELETE_2,PATCH_2,HEAD_2,OPTIONS_2,TRACE_2,CONNECT_2 или полный доступ FULL_ACCESS или выключите безопасность через переменную окружения POLITIC_2=0"};
    gen_sat_rec(politic, s2, politic_sat_flds, politic_sat_values_2);

    gen_link_table(politic, rule);
    gen_link_rec(politic, rule, s1, get_1);
    gen_link_rec(politic, rule, s1, put_1);
    gen_link_rec(politic, rule, s1, post_1);
    gen_link_rec(politic, rule, s1, del_1);
    gen_link_rec(politic, rule, s1, patch_1);
    gen_link_rec(politic, rule, s1, head_1);
    gen_link_rec(politic, rule, s1, options_1);
    gen_link_rec(politic, rule, s1, trace_1);
    gen_link_rec(politic, rule, s1, conn_1);

    gen_link_rec(politic, rule, s2, get_2);
    gen_link_rec(politic, rule, s2, put_2);
    gen_link_rec(politic, rule, s2, post_2);
    gen_link_rec(politic, rule, s2, del_2);
    gen_link_rec(politic, rule, s2, patch_2);
    gen_link_rec(politic, rule, s2, head_2);
    gen_link_rec(politic, rule, s2, options_2);
    gen_link_rec(politic, rule, s2, trace_2);
    gen_link_rec(politic, rule, s2, conn_2);

    string op = "operator";
    gen_dic_table(op);
    string op_or = gen_dic_rec(op, "OR");
    string op_and = gen_dic_rec(op, "AND");

    vector<string> rule_sat_flds {"description","recommendation","obj_operator_hk","subj_operator_hk"};
    gen_sat_table(rule, rule_sat_flds);

    vector<string> rule_sat_values_get_1 {"Правило доступа к методу GET сервиса 1","Для доступа к методу GET сервиса 1 добавьте правило", op_or,op_or};
    gen_sat_rec(rule,get_1,rule_sat_flds,rule_sat_values_get_1);
    vector<string> rule_sat_values_put_1 {"Правило доступа к методу PUT сервиса 1","Для доступа к методу PUT сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,put_1,rule_sat_flds,rule_sat_values_put_1);
    vector<string> rule_sat_values_post_1 {"Правило доступа к методу POST сервиса 1","Для доступа к методу POST сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,post_1,rule_sat_flds,rule_sat_values_post_1);
    vector<string> rule_sat_values_del_1 {"Правило доступа к методу DELETE сервиса 1","Для доступа к методу DELETE сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,del_1,rule_sat_flds,rule_sat_values_del_1);
    vector<string> rule_sat_values_patch_1 {"Правило доступа к методу PATCH сервиса 1","Для доступа к методу PATCH сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,patch_1,rule_sat_flds,rule_sat_values_patch_1);
    vector<string> rule_sat_values_head_1 {"Правило доступа к методу HEAD сервиса 1","Для доступа к методу HEAD сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,head_1,rule_sat_flds,rule_sat_values_head_1);
    vector<string> rule_sat_values_options_1 {"Правило доступа к методу OPTIONS сервиса 1","Для доступа к методу OPTIONS сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,options_1,rule_sat_flds,rule_sat_values_options_1);
    vector<string> rule_sat_values_trace_1 {"Правило доступа к методу TRACE сервиса 1","Для доступа к методу TRACE сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,trace_1,rule_sat_flds,rule_sat_values_trace_1);
    vector<string> rule_sat_values_conn_1 {"Правило доступа к методу CONNECT сервиса 1","Для доступа к методу CONNECT сервиса 1 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,conn_1,rule_sat_flds,rule_sat_values_conn_1);

    vector<string> rule_sat_values_get_2 {"Правило доступа к методу GET сервиса 2","Для доступа к методу GET сервиса 2 добавьте правило", op_or,op_or};
    gen_sat_rec(rule,get_2,rule_sat_flds,rule_sat_values_get_2);
    vector<string> rule_sat_values_put_2 {"Правило доступа к методу PUT сервиса 2","Для доступа к методу PUT сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,put_2,rule_sat_flds,rule_sat_values_put_2);
    vector<string> rule_sat_values_post_2 {"Правило доступа к методу POST сервиса 2","Для доступа к методу POST сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,post_2,rule_sat_flds,rule_sat_values_post_2);
    vector<string> rule_sat_values_del_2 {"Правило доступа к методу DELETE сервиса 2","Для доступа к методу DELETE сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,del_2,rule_sat_flds,rule_sat_values_del_2);
    vector<string> rule_sat_values_patch_2 {"Правило доступа к методу PATCH сервиса 2","Для доступа к методу PATCH сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,patch_2,rule_sat_flds,rule_sat_values_patch_2);
    vector<string> rule_sat_values_head_2 {"Правило доступа к методу HEAD сервиса 2","Для доступа к методу HEAD сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,head_2,rule_sat_flds,rule_sat_values_head_2);
    vector<string> rule_sat_values_options_2 {"Правило доступа к методу OPTIONS сервиса 2","Для доступа к методу OPTIONS сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,options_2,rule_sat_flds,rule_sat_values_options_2);
    vector<string> rule_sat_values_trace_2 {"Правило доступа к методу TRACE сервиса 2","Для доступа к методу TRACE сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,trace_2,rule_sat_flds,rule_sat_values_trace_2);
    vector<string> rule_sat_values_conn_2 {"Правило доступа к методу CONNECT сервиса 2","Для доступа к методу CONNECT сервиса 2 добавьте правило",op_or,op_or};
    gen_sat_rec(rule,conn_2,rule_sat_flds,rule_sat_values_conn_2);

    string obj_name = "object_name";
    gen_dic_table(obj_name);
    string obj_name_id = gen_dic_rec(obj_name, "id");
    string obj_name_name= gen_dic_rec(obj_name, "name");

    string subj_name = "subject_name";
    gen_dic_table(subj_name);
    string subj_name_id = gen_dic_rec(subj_name, "id");
    string subj_name_role = gen_dic_rec(subj_name, "role");
    string subj_name_group = gen_dic_rec(subj_name, "group");

    string comp_op = "comparison_operator";
    gen_dic_table(comp_op);
    string comp_op_equals = gen_dic_rec(comp_op, "equals");
    string comp_op_contains = gen_dic_rec(comp_op, "contain");
    string comp_op_matches = gen_dic_rec(comp_op, "matches");

    string obj_cond = "object_cond";
    vector<string> obj_cond_hub_flds {"object","comparison_operator_hk","value"};
    gen_hub_table_many(obj_cond, obj_cond_hub_flds);
    
    vector<string> obj_cond_hub_vls_get_1 {obj_name_name,comp_op_equals,"GET"};
    string hk_obj_cond_hub_vls_get_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_get_1);
    vector<string> obj_cond_hub_vls_put_1 {obj_name_name,comp_op_equals,"PUT"};
    string hk_obj_cond_hub_vls_put_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_put_1);
    vector<string> obj_cond_hub_vls_post_1 {obj_name_name,comp_op_equals,"POST"};
    string hk_obj_cond_hub_vls_post_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_post_1);
    vector<string> obj_cond_hub_vls_del_1 {obj_name_name,comp_op_equals,"DELETE"};
    string hk_obj_cond_hub_vls_del_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_del_1);
    vector<string> obj_cond_hub_vls_patch_1 {obj_name_name,comp_op_equals,"PATCH"};
    string hk_obj_cond_hub_vls_patch_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_patch_1);
    vector<string> obj_cond_hub_vls_head_1 {obj_name_name,comp_op_equals,"HEAD"};
    string hk_obj_cond_hub_vls_head_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_head_1);
    vector<string> obj_cond_hub_vls_options_1 {obj_name_name,comp_op_equals,"OPTIONS"};
    string hk_obj_cond_hub_vls_options_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_options_1);
    vector<string> obj_cond_hub_vls_trace_1 {obj_name_name,comp_op_equals,"TRACE"};
    string hk_obj_cond_hub_vls_trace_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_trace_1);
    vector<string> obj_cond_hub_vls_conn_1 {obj_name_name,comp_op_equals,"CONNECT"};
    string hk_obj_cond_hub_vls_conn_1 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_conn_1);

    // vector<string> obj_cond_hub_vls_get_2 {obj_name_name,comp_op_matches,"GET"};
    // string hk_obj_cond_hub_vls_get_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_get_2);
    // vector<string> obj_cond_hub_vls_put_2 {obj_name_name,comp_op_matches,"PUT"};
    // string hk_obj_cond_hub_vls_put_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_put_2);
    // vector<string> obj_cond_hub_vls_post_2 {obj_name_name,comp_op_matches,"POST"};
    // string hk_obj_cond_hub_vls_post_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_post_2);
    // vector<string> obj_cond_hub_vls_del_2 {obj_name_name,comp_op_matches,"DELETE"};
    // string hk_obj_cond_hub_vls_del_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_del_2);
    // vector<string> obj_cond_hub_vls_patch_2 {obj_name_name,comp_op_matches,"PATCH"};
    // string hk_obj_cond_hub_vls_patch_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_patch_2);
    // vector<string> obj_cond_hub_vls_head_2 {obj_name_name,comp_op_matches,"HEAD"};
    // string hk_obj_cond_hub_vls_head_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_head_2);
    // vector<string> obj_cond_hub_vls_options_2 {obj_name_name,comp_op_matches,"OPTIONS"};
    // string hk_obj_cond_hub_vls_options_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_options_2);
    // vector<string> obj_cond_hub_vls_trace_2 {obj_name_name,comp_op_matches,"TRACE"};
    // string hk_obj_cond_hub_vls_trace_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_trace_2);
    // vector<string> obj_cond_hub_vls_conn_2 {obj_name_name,comp_op_matches,"CONNECT"};
    // string hk_obj_cond_hub_vls_conn_2 = gen_hub_rec_many(obj_cond, obj_cond_hub_flds, obj_cond_hub_vls_conn_2);

    gen_link_table(rule, obj_cond);
    
    gen_link_rec(rule, obj_cond, get_1, hk_obj_cond_hub_vls_get_1);
    gen_link_rec(rule, obj_cond, put_1, hk_obj_cond_hub_vls_put_1);
    gen_link_rec(rule, obj_cond, post_1, hk_obj_cond_hub_vls_post_1);
    gen_link_rec(rule, obj_cond, del_1, hk_obj_cond_hub_vls_del_1);
    gen_link_rec(rule, obj_cond, patch_1, hk_obj_cond_hub_vls_patch_1);
    gen_link_rec(rule, obj_cond, head_1, hk_obj_cond_hub_vls_head_1);
    gen_link_rec(rule, obj_cond, options_1, hk_obj_cond_hub_vls_options_1);
    gen_link_rec(rule, obj_cond, trace_1, hk_obj_cond_hub_vls_trace_1);
    gen_link_rec(rule, obj_cond, conn_1, hk_obj_cond_hub_vls_conn_1);
 
    gen_link_rec(rule, obj_cond, get_2, hk_obj_cond_hub_vls_get_1);
    gen_link_rec(rule, obj_cond, put_2, hk_obj_cond_hub_vls_put_1);
    gen_link_rec(rule, obj_cond, post_2, hk_obj_cond_hub_vls_post_1);
    gen_link_rec(rule, obj_cond, del_2, hk_obj_cond_hub_vls_del_1);
    gen_link_rec(rule, obj_cond, patch_2, hk_obj_cond_hub_vls_patch_1);
    gen_link_rec(rule, obj_cond, head_2, hk_obj_cond_hub_vls_head_1);
    gen_link_rec(rule, obj_cond, options_2, hk_obj_cond_hub_vls_options_1);
    gen_link_rec(rule, obj_cond, trace_2, hk_obj_cond_hub_vls_trace_1);
    gen_link_rec(rule, obj_cond, conn_2, hk_obj_cond_hub_vls_conn_1);

//
    string subj_cond = "subject_cond";
    vector<string> subj_cond_hub_flds {"subject","comparison_operator_hk","value"};
    gen_hub_table_many(subj_cond, subj_cond_hub_flds);

    vector<string> subj_cond_hub_vls_to_full_access {subj_name_id, comp_op_matches,"полный доступ"};
    string hk_subj_cond_hub_vls_to_full_access = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_full_access);

    vector<string> subj_cond_hub_vls_to_get_1 {subj_name_role,comp_op_contains,"читать 1"};
    string hk_subj_cond_hub_vls_to_get_1 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_get_1);
    vector<string> subj_cond_hub_vls_to_put_1 {subj_name_role,comp_op_contains,"редактировать 1"};
    string hk_subj_cond_hub_vls_to_put_1 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_put_1);
    vector<string> subj_cond_hub_vls_to_post_1 {subj_name_role,comp_op_contains,"создать 1"};
    string hk_subj_cond_hub_vls_to_post_1 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_post_1);
    vector<string> subj_cond_hub_vls_to_del_1 {subj_name_role,comp_op_contains,"удалить 1"};
    string hk_subj_cond_hub_vls_to_del_1 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_del_1);

    vector<string> subj_cond_hub_vls_to_get_2 {subj_name_role,comp_op_contains,"читать 2"};
    string hk_subj_cond_hub_vls_to_get_2 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_get_2);
    vector<string> subj_cond_hub_vls_to_put_2 {subj_name_role,comp_op_contains,"редактировать 2"};
    string hk_subj_cond_hub_vls_to_put_2 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_put_2);
    vector<string> subj_cond_hub_vls_to_post_2 {subj_name_role,comp_op_contains,"создать 2"};
    string hk_subj_cond_hub_vls_to_post_2 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_post_2);
    vector<string> subj_cond_hub_vls_to_del_2 {subj_name_role,comp_op_contains,"удалить 2"};
    string hk_subj_cond_hub_vls_to_del_2 = gen_hub_rec_many(subj_cond, subj_cond_hub_flds, subj_cond_hub_vls_to_del_2);

    gen_link_table(rule, subj_cond);
    
    gen_link_rec(rule, subj_cond, get_1, hk_subj_cond_hub_vls_to_get_1);
    gen_link_rec(rule, subj_cond, get_1, hk_subj_cond_hub_vls_to_full_access);
    
    gen_link_rec(rule, subj_cond, put_1, hk_subj_cond_hub_vls_to_put_1);
    gen_link_rec(rule, subj_cond, put_1, hk_subj_cond_hub_vls_to_full_access);
    
    gen_link_rec(rule, subj_cond, post_1, hk_subj_cond_hub_vls_to_post_1);
    gen_link_rec(rule, subj_cond, post_1, hk_subj_cond_hub_vls_to_full_access);
    
    gen_link_rec(rule, subj_cond, del_1, hk_subj_cond_hub_vls_to_del_1);
    gen_link_rec(rule, subj_cond, del_1, hk_subj_cond_hub_vls_to_full_access);

    gen_link_rec(rule, subj_cond, patch_1, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, head_1, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, options_1, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, trace_1, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, conn_1, hk_subj_cond_hub_vls_to_full_access);

//---
    gen_link_rec(rule, subj_cond, get_2, hk_subj_cond_hub_vls_to_get_2);
    gen_link_rec(rule, subj_cond, get_2, hk_subj_cond_hub_vls_to_full_access);
    
    gen_link_rec(rule, subj_cond, put_2, hk_subj_cond_hub_vls_to_put_2);
    gen_link_rec(rule, subj_cond, put_2, hk_subj_cond_hub_vls_to_full_access);
    
    gen_link_rec(rule, subj_cond, post_2, hk_subj_cond_hub_vls_to_post_2);
    gen_link_rec(rule, subj_cond, post_2, hk_subj_cond_hub_vls_to_full_access);
    
    gen_link_rec(rule, subj_cond, del_2, hk_subj_cond_hub_vls_to_del_2);
    gen_link_rec(rule, subj_cond, del_2, hk_subj_cond_hub_vls_to_full_access);

    gen_link_rec(rule, subj_cond, patch_2, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, head_2, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, options_2, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, trace_2, hk_subj_cond_hub_vls_to_full_access);
    gen_link_rec(rule, subj_cond, conn_2, hk_subj_cond_hub_vls_to_full_access);

    //----   
    string act = "action";
    vector<string> act_hub_flds {"action","effect"};
    gen_hub_table_many(act, act_hub_flds);

    string actions = "actions";
    gen_dic_table(actions);
    string actions_execute = gen_dic_rec(actions, "execute");
    string actions_create = gen_dic_rec(actions, "create");
    string actions_read = gen_dic_rec(actions, "read");
    string actions_update = gen_dic_rec(actions, "update");
    string actions_delete = gen_dic_rec(actions, "delete");


    string effects = "effects";
    gen_dic_table(effects);
    string effects_allow = gen_dic_rec(effects, "allow");
    string effects_deny = gen_dic_rec(effects, "deny");

    string rules_actions = "rules_actions";
    vector<string> rules_actions_hub_flds {"actions","effects"};
    gen_hub_table_many(rules_actions, rules_actions_hub_flds);

    vector<string> rules_actions_hub_vls_execute_allow = {actions_execute, effects_allow};
    string hk_rules_actions_hub_vls_execute_allow = gen_hub_rec_many(rules_actions, rules_actions_hub_flds, rules_actions_hub_vls_execute_allow);


    gen_link_table(rule, rules_actions);
    
    gen_link_rec(rule, rules_actions, get_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, put_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, post_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, del_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, patch_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, head_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, options_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, trace_1, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, conn_1, hk_rules_actions_hub_vls_execute_allow);

    gen_link_rec(rule, rules_actions, get_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, put_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, post_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, del_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, patch_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, head_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, options_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, trace_2, hk_rules_actions_hub_vls_execute_allow);
    gen_link_rec(rule, rules_actions, conn_2, hk_rules_actions_hub_vls_execute_allow);

    std::cout.rdbuf(coutbuf);
    cout << "init.sql updated" << endl;

}

