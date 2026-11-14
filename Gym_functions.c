#include "gym_management.h"

Member members[MAX_MEMBERS];
Payment payments[MAX_PAYMENTS];
History history[MAX_HISTORY];

int member_count = 0;
int payment_count = 0;
int history_count = 0;

int find_member(int id)
{
    int i;

    for(i = 0; i < member_count; i++)
    {
        if(members[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

int get_plan(int plan_id, int *days)
{
    switch(plan_id)
    {
        case 101:
            *days = 30;
            return 1500;

        case 102:
            *days = 90;
            return 4000;

        case 103:
            *days = 180;
            return 7000;

        case 104:
            *days = 365;
            return 12000;

        default:
            return 0;
    }
}

void get_dates(int days, char start[], char expiry[])
{
    time_t now;
    struct tm today;

    now = time(NULL);
    today = *localtime(&now);

    strftime(start, 11, "%Y-%m-%d", &today);

    today.tm_mday = today.tm_mday + days;

    mktime(&today);

    strftime(expiry, 11, "%Y-%m-%d", &today);
}

void register_member()
{
    Member m;

    if(member_count >= MAX_MEMBERS)
    {
        printf("Member storage is full!\n");
        return;
    }

    m.id = 1001 + member_count;

    printf("Member ID: %d\n", m.id);

    printf("Enter Name: ");
    scanf(" %49[^\n]", m.name);

    printf("Enter Age: ");
    scanf("%d", &m.age);

    printf("Enter Gender: ");
    scanf("%9s", m.gender);

    printf("Enter Phone Number: ");
    scanf("%14s", m.phone);

    if(strlen(m.phone) != 10)
    {
        printf("Invalid phone number!\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    strftime(m.reg_date, 11, "%Y-%m-%d", today);

    m.plan_id = 0;

    strcpy(m.start_date, "Not assigned");
    strcpy(m.expiry_date, "Not assigned");

    members[member_count] = m;

    member_count++;

    printf("Member Registered Successfully!\n");
}

void view_all_members()
{
    int i;

    if(member_count == 0)
    {
        printf("No members found!\n");
        return;
    }

    printf("\nID   Name          Age   Gender   Phone\n");

    for(i = 0; i < member_count; i++)
    {
        printf("%-5d %-13s %-5d %-8s %s\n",
        members[i].id,
        members[i].name,
        members[i].age,
        members[i].gender,
        members[i].phone);
    }
}

void search_member()
{
    int id, pos;

    printf("Enter Member ID: ");
    scanf("%d", &id);

    pos = find_member(id);

    if(pos == -1)
    {
        printf("Member Not Found!\n");
        return;
    }

    printf("\nMember ID: %d\n", members[pos].id);
    printf("Name: %s\n", members[pos].name);
    printf("Age: %d\n", members[pos].age);
    printf("Gender: %s\n", members[pos].gender);
    printf("Phone: %s\n", members[pos].phone);
    printf("Registration Date: %s\n", members[pos].reg_date);
    printf("Plan ID: %d\n", members[pos].plan_id);
    printf("Start Date: %s\n", members[pos].start_date);
    printf("Expiry Date: %s\n", members[pos].expiry_date);
}

void display_plans()
{
    printf("\n===== MEMBERSHIP PLANS =====\n");

    printf("101  Monthly       30 Days   Rs.1500\n");
    printf("102  Quarterly     90 Days   Rs.4000\n");
    printf("103  Half-Yearly  180 Days   Rs.7000\n");
    printf("104  Yearly       365 Days   Rs.12000\n");
}

void make_payment(int pos, int renewal)
{
    int plan_id, days, fee, mode;

    char start[11], expiry[11];

    display_plans();

    printf("Enter Plan ID: ");
    scanf("%d", &plan_id);

    fee = get_plan(plan_id, &days);

    if(fee == 0)
    {
        printf("Invalid Plan ID!\n");
        return;
    }

    printf("Membership Fee: Rs.%d\n", fee);

    printf("1. Cash\n");
    printf("2. UPI\n");
    printf("3. Card\n");

    printf("Enter Payment Mode: ");
    scanf("%d", &mode);

    if(mode < 1 || mode > 3)
    {
        printf("Invalid Payment Mode!\n");
        return;
    }

    if(payment_count >= MAX_PAYMENTS)
    {
        printf("Payment storage is full!\n");
        return;
    }

    get_dates(days, start, expiry);

    if(renewal == 1 && history_count < MAX_HISTORY)
    {
        history[history_count].member_id = members[pos].id;

        history[history_count].old_plan_id = members[pos].plan_id;

        strcpy(history[history_count].old_start_date,
        members[pos].start_date);

        strcpy(history[history_count].old_expiry_date,
        members[pos].expiry_date);

        history_count++;
    }

    members[pos].plan_id = plan_id;

    strcpy(members[pos].start_date, start);
    strcpy(members[pos].expiry_date, expiry);

    payments[payment_count].payment_id = payment_count + 1;
    payments[payment_count].member_id = members[pos].id;
    payments[payment_count].plan_id = plan_id;
    payments[payment_count].amount = fee;

    if(mode == 1)
        strcpy(payments[payment_count].mode, "Cash");

    else if(mode == 2)
        strcpy(payments[payment_count].mode, "UPI");

    else
        strcpy(payments[payment_count].mode, "Card");

    strcpy(payments[payment_count].payment_date, start);

    payment_count++;

    if(renewal == 1)
        printf("Membership Renewed Successfully!\n");

    else
        printf("Membership Assigned Successfully!\n");

    printf("Start Date: %s\n", start);
    printf("Expiry Date: %s\n", expiry);
    printf("Payment Received: Rs.%d\n", fee);
}

void assign_membership()
{
    int id, pos;

    printf("Enter Member ID: ");
    scanf("%d", &id);

    pos = find_member(id);

    if(pos == -1)
    {
        printf("Member Not Found!\n");
        return;
    }

    if(members[pos].plan_id != 0)
    {
        printf("Membership already assigned. Use renewal.\n");
        return;
    }

    make_payment(pos, 0);
}

void record_payment()
{
    int i;

    if(payment_count == 0)
    {
        printf("No Payment Records!\n");
        return;
    }

    printf("\nPayment ID  Member ID  Plan ID  Amount  Mode  Date\n");

    for(i = 0; i < payment_count; i++)
    {
        printf("%-11d %-10d %-8d %-7d %-6s %s\n",
        payments[i].payment_id,
        payments[i].member_id,
        payments[i].plan_id,
        payments[i].amount,
        payments[i].mode,
        payments[i].payment_date);
    }
}

void renew_membership()
{
    int id, pos;

    printf("Enter Member ID: ");
    scanf("%d", &id);

    pos = find_member(id);

    if(pos == -1)
    {
        printf("Member Not Found!\n");
        return;
    }

    if(members[pos].plan_id == 0)
    {
        printf("Assign Membership First!\n");
        return;
    }

    printf("Current Plan: %d\n", members[pos].plan_id);

    printf("Current Expiry Date: %s\n", members[pos].expiry_date);

    make_payment(pos, 1);
}

void generate_reports()
{
    int choice, i, active, expired;

    char today[11];

    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    strftime(today, 11, "%Y-%m-%d", current);

    printf("\n1. All Members\n");
    printf("2. Active Members\n");
    printf("3. Expired Members\n");
    printf("4. Payment Report\n");

    printf("Enter Choice: ");
    scanf("%d", &choice);

    if(choice == 4)
    {
        record_payment();
        return;
    }

    if(choice < 1 || choice > 3)
    {
        printf("Invalid Choice!\n");
        return;
    }

    active = 0;
    expired = 0;

    for(i = 0; i < member_count; i++)
    {
        int is_active = 0;

        if(members[i].plan_id != 0 &&
           strcmp(members[i].expiry_date, today) >= 0)
        {
            is_active = 1;
            active++;
        }
        else if(members[i].plan_id != 0)
        {
            expired++;
        }

        if(choice == 1 ||
           (choice == 2 && is_active == 1) ||
           (choice == 3 && is_active == 0 &&
            members[i].plan_id != 0))
        {
            printf("\nID: %d\n", members[i].id);
            printf("Name: %s\n", members[i].name);
            printf("Plan ID: %d\n", members[i].plan_id);
            printf("Expiry: %s\n", members[i].expiry_date);

            if(is_active)
                printf("Status: Active\n");
            else
                printf("Status: Expired\n");
        }
    }

    printf("\nActive Members: %d\n", active);
    printf("Expired Members: %d\n", expired);
}

void save_records()
{
    FILE *fp;

    fp = fopen("members.dat", "wb");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    fwrite(&member_count, sizeof(int), 1, fp);
    fwrite(members, sizeof(Member), member_count, fp);

    fclose(fp);

    fp = fopen("payments.dat", "wb");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    fwrite(&payment_count, sizeof(int), 1, fp);
    fwrite(payments, sizeof(Payment), payment_count, fp);

    fclose(fp);

    fp = fopen("history.dat", "wb");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    fwrite(&history_count, sizeof(int), 1, fp);
    fwrite(history, sizeof(History), history_count, fp);

    fclose(fp);
}

void load_records()
{
    FILE *fp;

    fp = fopen("members.dat", "rb");

    if(fp != NULL)
    {
        fread(&member_count, sizeof(int), 1, fp);

        if(member_count < 0 || member_count > MAX_MEMBERS)
            member_count = 0;

        fread(members, sizeof(Member), member_count, fp);

        fclose(fp);
    }

    fp = fopen("payments.dat", "rb");

    if(fp != NULL)
    {
        fread(&payment_count, sizeof(int), 1, fp);

        if(payment_count < 0 || payment_count > MAX_PAYMENTS)
            payment_count = 0;

        fread(payments, sizeof(Payment), payment_count, fp);

        fclose(fp);
    }

    fp = fopen("history.dat", "rb");

    if(fp != NULL)
    {
        fread(&history_count, sizeof(int), 1, fp);

        if(history_count < 0 || history_count > MAX_HISTORY)
            history_count = 0;

        fread(history, sizeof(History), history_count, fp);

        fclose(fp);
    }
}