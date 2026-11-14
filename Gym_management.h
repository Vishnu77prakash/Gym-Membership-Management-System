#ifndef GYM_MANAGEMENT_H
#define GYM_MANAGEMENT_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 100
#define MAX_PAYMENTS 200
#define MAX_HISTORY 200

typedef struct
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char reg_date[11];
    int plan_id;
    char start_date[11];
    char expiry_date[11];

} Member;

typedef struct
{
    int payment_id;
    int member_id;
    int plan_id;
    int amount;
    char mode[10];
    char payment_date[11];

} Payment;

typedef struct
{
    int member_id;
    int old_plan_id;
    char old_start_date[11];
    char old_expiry_date[11];

} History;

/* Function declarations */

void register_member(void);
void view_all_members(void);
void search_member(void);
void display_plans(void);
void assign_membership(void);
void record_payment(void);
void renew_membership(void);
void generate_reports(void);
void save_records(void);
void load_records(void);

#endif