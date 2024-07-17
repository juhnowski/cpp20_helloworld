# SQlite
- Запускаем генератор hasher.cpp

- Он генерирует SQL файл БД

- В просмотрщике (DB Browser for SQLite Version 3.12.2) 
Файл-импорт-База данных из файла SQL
создаем abac.db из SQL скрипта

- Проверяем запрос, что он не пустой:
```sql
SELECT 
    "politic_hub"."name" as "politic_hub-name",
    "rule_hub"."name" as "rule_hub-name",
    ob."name" as "object-operator_dic-name",
    "object_name_dic"."name" as "object_name_dic-name",
    o."name" as "object-comparison_operator_dic-name",
    "object_cond_hub"."value" as "object_cond_hub-value",
    su."name" as "subject-operator_dic-name",
    "subject_name_dic"."name" as "subject_name_dic-name",
    "comparison_operator_dic"."name" as "comparison_operator_dic-name",
    "subject_cond_hub"."value" as "subject_cond_hub-value",
    "actions_dic"."name" as "actions_dic-name",
    "effects_dic"."name" as "effects_dic-name" 
FROM "politic_hub" 
	join "link_politic_rule" 
	on "politic_hub"."hk" = "link_politic_rule"."politic_hk"
	join "rule_hub"
	on "rule_hub"."hk" = "link_politic_rule"."rule_hk"
    join "link_rule_object_cond"
    on "link_rule_object_cond"."rule_hk" = "rule_hub"."hk"
    join "object_cond_hub"
    on "object_cond_hub"."hk" = "link_rule_object_cond"."object_cond_hk"
    join "comparison_operator_dic" as o
    on o."hk" = "object_cond_hub"."comparison_operator_hk"
    join "link_rule_subject_cond" 
    on "link_rule_subject_cond"."rule_hk" = "rule_hub"."hk"
    join "subject_cond_hub"
    on "subject_cond_hub"."hk" = "link_rule_subject_cond"."subject_cond_hk"
    join "comparison_operator_dic"
    on "comparison_operator_dic"."hk" = "subject_cond_hub"."comparison_operator_hk"
    join "subject_name_dic"
    on "subject_name_dic"."hk" = "subject_cond_hub"."subject"
    join "object_name_dic"
    on "object_name_dic"."hk" = "object_cond_hub"."object"
    join "link_rule_rules_actions" 
    on "link_rule_rules_actions"."rule_hk" = "rule_hub"."hk"
    join "rules_actions_hub"
    on "rules_actions_hub"."hk" = "link_rule_rules_actions"."rules_actions_hk" 
    join "actions_dic"
    on "actions_dic"."hk" = "rules_actions_hub"."actions"
    join "effects_dic"
    on "effects_dic"."hk" = "rules_actions_hub"."effects"
    join "rule_sat"
    on "rule_sat"."hk" = "rule_hub"."hk"
    join "operator_dic" as ob
    on  ob."hk" = "rule_sat"."obj_operator_hk"
    join "operator_dic" as su
    on  su."hk" = "rule_sat"."obj_operator_hk"
where "politic_hub"."name" is "POLITIC_1" and "object_cond_hub"."value" is "GET"
```
# Keycloal
```
bin\kc.bat start-dev
```

https://developers.redhat.com/blog/authentication-and-authorization-using-the-keycloak-rest-api#

