#include "gym_management.h"

int main()
{
    int choice;

    load_records();

    do
    {
        printf("\n===== GYM MEMBERSHIP MANAGEMENT =====\n");

        printf("1. Register New Member\n");
        printf("2. View All Members\n");
        printf("3. Search Member\n");
        printf("4. View Membership Plans\n");
        printf("5. Assign Membership\n");
        printf("6. Record Payment\n");
        printf("7. Renew Membership\n");
        printf("8. Generate Reports\n");
        printf("9. Save and Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                register_member();
                break;

            case 2:
                view_all_members();
                break;

            case 3:
                search_member();
                break;

            case 4:
                display_plans();
                break;

            case 5:
                assign_membership();
                break;

            case 6:
                record_payment();
                break;

            case 7:
                renew_membership();
                break;

            case 8:
                generate_reports();
                break;

            case 9:
                save_records();
                printf("Records saved successfully!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 9);

    return 0;
}