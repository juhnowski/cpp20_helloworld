/*
     This file is part of libhttpserver
     Copyright (C) 2011, 2012, 2013, 2014, 2015 Sebastiano Merlino

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
     USA
*/
#include <sqlite3.h> 
#include <iostream>
#include <httpserver.hpp>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<string> mySharedWork = {};
mutex mutex_;
condition_variable condVar;
bool dataReady{false};


static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);


   for(i = 0; i<argc; i++){
        char buff[100];
        snprintf(buff, sizeof(buff), "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        std::string buffAsStdStr = buff;
        mySharedWork.push_back(buffAsStdStr);
    //   printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   }
   
   printf("\n");

    //    mySharedWork = {1,0,3};
    {
        lock_guard<mutex> lck(mutex_);
        dataReady = true;
    }
    cout << "Data prepared" << endl;
    condVar.notify_one();

   return 0;
}


class hello_world_resource : public httpserver::http_resource {
 public:
     std::shared_ptr<httpserver::http_response> render(const httpserver::http_request&);
     void set_some_data(const std::string &s) {data = s;}
     std::string data;
};

// Using the render method you are able to catch each type of request you receive
std::shared_ptr<httpserver::http_response> hello_world_resource::render(const httpserver::http_request& req) {
    // It is possible to store data inside the resource object that can be altered through the requests
    std::cout << "Data was: " << data << std::endl;
    std::string_view datapar = req.get_arg("data");
    set_some_data(datapar == "" ? "no data passed!!!" : std::string(datapar));
    std::cout << "Now data is:" << data << std::endl;

    // прочитать политику из окружения
    const char *p1 = "POLITIC_1";
    const char *p2 = "POLITIC_2";

    const char *env_p1 = getenv(p1);
    const char *env_p2 = getenv(p2);

    if (env_p1) {
        printf("%s = %s\n", p1, env_p1);
    }
    if (env_p2) {
        printf("%s = %s\n", p2, env_p2);
    }
    // запросить БД
       sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
//    string sql;
   const char* data1 = "Callback function called";

   /* Open database */
   rc = sqlite3_open("abac.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   char *sql = "SELECT \
    \"politic_hub\".\"name\" as \"politic_hub-name\",\
    \"rule_hub\".\"name\" as \"rule_hub-name\",\
    ob.\"name\" as \"object-operator_dic-name\",\
    \"object_name_dic\".\"name\" as \"object_name_dic-name\",\
    o.\"name\" as \"object-comparison_operator_dic-name\",\
    \"object_cond_hub\".\"value\" as \"object_cond_hub-value\",\
    su.\"name\" as \"subject-operator_dic-name\",\
    \"subject_name_dic\".\"name\" as \"subject_name_dic-name\",\
    \"comparison_operator_dic\".\"name\" as \"comparison_operator_dic-name\",\
    \"subject_cond_hub\".\"value\" as \"subject_cond_hub-value\",\
    \"actions_dic\".\"name\" as \"actions_dic-name\",\
    \"effects_dic\".\"name\" as \"effects_dic-name\" \ 
FROM \"politic_hub\" \ 
	join \"link_politic_rule\" \
	on \"politic_hub\".\"hk\" = \"link_politic_rule\".\"politic_hk\"\
	join \"rule_hub\"\
	on \"rule_hub\".\"hk\" = \"link_politic_rule\".\"rule_hk\"\
    join \"link_rule_object_cond\"\
    on \"link_rule_object_cond\".\"rule_hk\" = \"rule_hub\".\"hk\"\
    join \"object_cond_hub\"\
    on \"object_cond_hub\".\"hk\" = \"link_rule_object_cond\".\"object_cond_hk\"\
    join \"comparison_operator_dic\" as o\
    on o.\"hk\" = \"object_cond_hub\".\"comparison_operator_hk\"\
    join \"link_rule_subject_cond\" \
    on \"link_rule_subject_cond\".\"rule_hk\" = \"rule_hub\".\"hk\"\
    join \"subject_cond_hub\"\
    on \"subject_cond_hub\".\"hk\" = \"link_rule_subject_cond\".\"subject_cond_hk\"\
    join \"comparison_operator_dic\"\
    on \"comparison_operator_dic\".\"hk\" = \"subject_cond_hub\".\"comparison_operator_hk\"\
    join \"subject_name_dic\"\
    on \"subject_name_dic\".\"hk\" = \"subject_cond_hub\".\"subject\"\
    join \"object_name_dic\"\
    on \"object_name_dic\".\"hk\" = \"object_cond_hub\".\"object\"\
    join \"link_rule_rules_actions\" \ 
    on \"link_rule_rules_actions\".\"rule_hk\" = \"rule_hub\".\"hk\"\
    join \"rules_actions_hub\"\
    on \"rules_actions_hub\".\"hk\" = \"link_rule_rules_actions\".\"rules_actions_hk\"\ 
    join \"actions_dic\"\
    on \"actions_dic\".\"hk\" = \"rules_actions_hub\".\"actions\"\
    join \"effects_dic\"\
    on \"effects_dic\".\"hk\" = \"rules_actions_hub\".\"effects\"\
    join \"rule_sat\"\
    on \"rule_sat\".\"hk\" = \"rule_hub\".\"hk\"\
    join \"operator_dic\" as ob\
    on  ob.\"hk\" = \"rule_sat\".\"obj_operator_hk\"\
    join \"operator_dic\" as su\
    on  su.\"hk\" = \"rule_sat\".\"obj_operator_hk\"\
where \"politic_hub\".\"name\" is \"POLITIC_1\" and \"object_cond_hub\".\"value\" is \"GET\"";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data1, &zErrMsg);
   string res = "Access denied by abac";
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
      cout << "Waiting callback" << endl;
      unique_lock<mutex> lck(mutex_);
      condVar.wait(lck, []{return dataReady;});
      std::ostringstream stringStream={};
      bool result = false;
      for (auto v:mySharedWork) {
        cout << v;
        stringStream << v;
      // получить роль из jwt, метод из запроса, политика принадлежит сервису
      //object_cond_hub-value = GET - это как пример, надо анализировать всю строку 
        if (v.find("object_cond_hub-value") != std::string::npos) 
        {
            if (v.find(data) != std::string::npos) {
                result = true;
            }            
        } 
      }

        mySharedWork.clear();

        if (result==true) {
            stringStream << "Access allow by abac";
        } else {
            stringStream << "Access denied by abac";
        };
      res = stringStream.str();
      stringStream.clear();

   }
   sqlite3_close(db);
    

    // It is possible to send a response initializing an http_string_response that reads the content to send in response from a string.
    // return std::shared_ptr<httpserver::http_response>(new httpserver::string_response("Hello World!!!", 200));
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(res, 200));
}



int main() {
    // It is possible to create a webserver passing a great number of parameters. In this case we are just passing the port and the number of thread running.
    httpserver::webserver ws = httpserver::create_webserver(8081).start_method(httpserver::http::http_utils::INTERNAL_SELECT).max_threads(5);

    hello_world_resource hwr;
    // This way we are registering the hello_world_resource to answer for the endpoint
    // "/hello". The requested method is called (if the request is a GET we call the render_GET
    // method. In case that the specific render method is not implemented, the generic "render"
    // method is called.
    ws.register_resource("/hello", &hwr, true);

    // This way we are putting the created webserver in listen. We pass true in order to have
    // a blocking call; if we want the call to be non-blocking we can just pass false to the method.
    ws.start(true);
    return 0;
}
