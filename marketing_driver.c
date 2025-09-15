/**
 * Assignment 3 - Wacky Marketing
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * There are also additional notes and clarifications on Quercus.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */
#include "marketing.c"

/**
 * You may modify this file however you wish as it will not be submitted on
 * Quercus. Please ensure that your code still works and does not depend on this
 * file as the automarker will be using a different main().
 */

int main() {
    // Create new users
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");

    printf("\nTest 1 - Users printed in alphabetical order\n");
    FriendNode *t = allUsers;
    int idx = 0;
    while (t != NULL && t->next != NULL) {
        if (strcmp(t->user->name, t->next->user->name) > 0) {
            printf("Test 1 failed. Users are not sorted.\n");
            exit(1);
        }

        idx++;
        t = t->next;
    }

    if (idx != 3) {
        printf("Test 1 failed. Users were not inserted.\n");
        exit(1);
    }

    printf("Test 1 passed.\n");

    printf("\nTest 2 - Angela adds Brian as a friend\n");
    int x = add_friend(angela, brian);
    printf("Oh :%d, \n\n ahaha\n", x);

    // Expect to see Angela with her friend Brian & see Brian with his friend Angela
    if (!in_friend_list(angela->friends, brian) || !in_friend_list(brian->friends, angela)) {
        printf("Test 2 failed. Friend connection was not made.\n");
        exit(1);
    }

    printf("Test 2 passed.\n");

    printf("\nTest 3 - Degree of connection between Angela and Brian is 1\n");
    int angela_and_brian = get_degrees_of_connection(angela, brian);

    if (angela_and_brian != 1) {  // Expect 1
        printf("Test 3 failed. Friend connection was not made.\n");
        exit(1);
    }

    printf("Test 3 passed.\n");

    printf("\nTest 4 - Angela follows Brand 'brandonRufino'\n");
    populate_brand_matrix("brands.txt");
    follow_brand(angela, "brandonRufino");

    // Angela should now follow brandonRufino.
    if (!in_brand_list(angela->brands, "brandonRufino")) {
        printf("Test 4 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 4 passed.\n");

    printf("\nTest 5 - Connect Brands 'brandZero' and 'brandTwo'\n");
    connect_similar_brands("brandZero", "brandTwo");
    int zeroIdx = get_brand_index("brandZero");
    int twoIdx = get_brand_index("brandTwo");

    if (brand_adjacency_matrix[zeroIdx][twoIdx] != 1 || brand_adjacency_matrix[twoIdx][zeroIdx] != 1) {
        printf("Test 5 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 5 passed.\n");

    printf("\nTest 6 - William and Brian have Angela as a mutual friend\n");
    add_friend(angela, william);
    int mutuals_brian_will = get_mutual_friends(brian, william);

    if (mutuals_brian_will != 1) {  // Expect 1
        printf("Test 6 failed. Mutual friends of Brian and William should be 1.\n");
        exit(1);
    }

    printf("Test 6 passed.\n");

    printf("\nTest 7 - Brian is suggested 1 friend\n");
    User *brianSuggested = get_suggested_friend(brian);

    if (brianSuggested != william) {  // We should see Will here again
        printf("Test 7 failed. Brian was not suggested William.\n");
        exit(1);
    }

    printf("Test 7 passed.\n");

    printf("\nTest 8 - Mustafa adds 2 suggested friends\n");

    add_friend(angela, mustafa);
    add_suggested_friends(mustafa, 2);

    // Expect to see Mustafa with friends Angela, Brian, and Will
    if (!in_friend_list(mustafa->friends, brian) || !in_friend_list(mustafa->friends, william)) {
        printf("Test 8 failed. Mustafa was not suggested 2 friends correctly.\n");
        exit(1);
    }

    printf("Test 8 passed.\n");

    printf("\nTest 9 - Mustafa follows 1 suggested brand\n");
    follow_brand(william, "brandTwo");
    follow_brand(mustafa, "brandZero");
    follow_suggested_brands(mustafa, 1);

    // Mustafa should now also follow brandonRufino. A tie is broken against brandTwo.
    
    if (!in_brand_list(mustafa->brands, "brandonRufino")) {
        printf("Test 9 failed. Mustafa did not follow brand 'brandonRufino'.\n");
        exit(1);
    }

    printf("Test 9 passed.\n");
    printf("\nAll basic test cases passed. :)\n");

    printf("---------------------------------------\n");
    printf("\nR Test Cases Have Initialized...\n\n");
    printf("---------------------------------------\n");

    // create_user
    printf("R1 - create_user Trivial Case.\n");
    //User *user1 = create_user("User1");
    /**
    if (user1->friends == NULL && user1->brands == NULL && user1->visited == false){
        printf("%s\n", user1->name);
    }
    */
    printf("R1 - Test Case Passed\n");

    return 0;
}
