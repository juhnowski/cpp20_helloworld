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

"politic_hub"."name"


politic_hub"
hk	dt	src	name	
15153832979968222410	1721166509124ms	1	POLITIC_1	

"link_politic_rule"
hk	dt	src	politic_hk	rule_hk	
14571885770585164942	1721166509125ms	1	15153832979968222410	8271281792137018304	

"rule_hub"
hk	dt	src	name	
8271281792137018304	1721166509124ms	1	Правило для GET_1	

"link_rule_object_cond"
hk	dt	src	rule_hk	object_cond_hk	
6925901350692268517	1721166509125ms	1	8271281792137018304	15538174937159163044	

"object_cond_hub"
hk	dt	src	object	comparison_operator_hk	value	
15538174937159163044	1721166509125ms	1	10420554295983197538	7500597097087108110	GET	

"link_rule_subject_cond" 
hk	dt	src	rule_hk	subject_cond_hk	
15800794003243926296	1721166509125ms	1	8271281792137018304	9982533303612718950	

join "subject_cond_hub"
hk	dt src	subject	comparison_operator_hk	value	
9982533303612718950	1721166509125ms 1	8515376505552316133	10812924833742122732	читать 1	

"comparison_operator_dic"
hk	dt	src	name	
10812924833742122732	1721166509125ms	1	contain	

"subject_name_dic"
hk	dt	src	name	
8515376505552316133	1721166509125ms	1	role	

"object_name_dic"
hk	dt	src	name	
10420554295983197538	1721166509125ms	1	name	

"link_rule_rules_actions"
hk	dt	src	rule_hk	rules_actions_hk	
17750765900810368899	1721166509126ms	1	8271281792137018304	217292581564671277	

"rules_actions_hub"
hk	dt	src	actions	effects	
217292581564671277	1721166509126ms	1	9257799126414257590	907323904081373410	

"actions_dic"
hk	dt	src	name	
9257799126414257590	1721166509126ms	1	execute	

"effects_dic"
hk	dt	src	name
907323904081373410	1721166509126ms	1	allow

----------------------------------------------------------------

"politic_hub"."name"				POLITIC_1	
"rule_hub"."name",				Правило для GET_1

"object_name_dic"."name"			name
"object_cond_hub"."value"			GET

"subject_name_dic"."name"			role
"comparison_operator_dic"."name"		contain	
"subject_cond_hub"."value"			читать 1

"actions_dic"."name" 				execute	
"effects_dic"."name" 				allow


----------------------------------------------------------------



SELECT "rule_hk" FROM "politic_hub" 
join "link_politic_rule" on "politic_hub"."hk" = "link_politic_rule"."politic_hk"
where "politic_hub"."name" is "POLITIC_1"

SELECT * FROM "politic_hub" 
join "link_politic_rule" on "politic_hub"."hk" = "link_politic_rule"."politic_hk",

where "politic_hub"."name" is "POLITIC_1"
join "rule_hub" on "rule_hub"."hk" = "link_politic_rule"."rule_hk"



SELECT * FROM "politic_hub" where "politic_hub"."hk" is "15153832979968222410";
SELECT * FROM "link_politic_rule" where "link_politic_rule"."politic_hk" is "15153832979968222410";
SELECT * FROM "politic_hub" where "politic_hub"."name" is "POLITIC_1";


SELECT customerName, customercity, customermail, salestotal
FROM onlinecustomers AS oc
   INNER JOIN
   orders AS o
   ON oc.customerid = o.customerid
   INNER JOIN
   sales AS s
   ON o.orderId = s.orderId