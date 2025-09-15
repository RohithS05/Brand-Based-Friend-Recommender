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
#include<assert.h>

/**
 * You may modify this file however you wish as it will not be submitted on
 * Quercus. Please ensure that your code still works and does not depend on this
 * file as the automarker will be using a different main().
 */

void basic() {
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
    add_friend(angela, brian);

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
    printf("Num add = %d\n", add_suggested_friends(mustafa, 2));

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

    delete_user(william);
    delete_user(brian);
    delete_user(mustafa);
    delete_user(angela);

}

bool find_name_in_friend_list(User *user, char *name) {
    for (FriendNode *i = user->friends; i != NULL; i = i->next) {
        if (strcmp(i->user->name, name) == 0)
            return 1;
    }
    return 0;
}

void print_name(User *user) {
    for (FriendNode *i = user->friends; i != NULL; i = i->next) {
        printf("%s\n", i->user->name);
    }
}

void test_delete_user() {
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");

    add_friend(william, angela);
    add_friend(william, mustafa);
    add_friend(mustafa, william);
    add_friend(mustafa, angela);
    add_friend(brian, angela);
    
    delete_user(angela);

    FriendNode *p = william->friends;
    while (p!=NULL){
        printf("Name:%s\n", p->user->name);
        p = p->next;
    }

    assert(find_name_in_friend_list(william, "Mustafa"));
    assert(find_name_in_friend_list(mustafa, "William"));
    assert(!find_name_in_friend_list(brian, "Angela"));
    assert(!find_name_in_friend_list(mustafa, "Angela"));
    assert(!find_name_in_friend_list(william, "Angela"));

    delete_user(mustafa);
    delete_user(william);
    delete_user(brian);

    william = create_user("William");
    angela = create_user("Angela");
    mustafa = create_user("Mustafa");
    brian = create_user("Brian");

    add_friend(william, angela);
    add_friend(william, mustafa);
    add_friend(angela, brian);
    add_friend(mustafa, angela);

    delete_user(angela);
    assert(!find_name_in_friend_list(william, "Angela"));
    assert(!find_name_in_friend_list(brian, "Angela"));
    assert(!find_name_in_friend_list(mustafa, "Angela"));
    assert(find_name_in_friend_list(mustafa, "William"));
    assert(!find_name_in_friend_list(brian, "William"));
    assert(!find_name_in_friend_list(brian, "Mustafa"));

    assert(delete_user(angela) == -1);
    delete_user(william);
    assert(delete_user(angela) == -1);
    assert(!find_name_in_friend_list(mustafa, "William"));
    delete_user(mustafa);
    delete_user(brian);
    printf("W0mp W0mp.. Pass all test cases for delete_user()\n");
}

void test_remove_user() {
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");

    add_friend(william, angela);
    add_friend(william, mustafa);
    add_friend(mustafa, brian);
    add_friend(brian, william);
    assert(add_friend(brian, william) == -1);
    assert(add_friend(mustafa, william) == -1);
    assert(add_friend(brian, mustafa) == -1);

    remove_friend(william, angela);
    assert(!in_friend_list(william->friends, angela));
    assert(!in_friend_list(angela->friends, william));
    assert(in_friend_list(william->friends, mustafa));
    assert(in_friend_list(william->friends, brian));
    assert(remove_friend(william, angela) == -1);

    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    printf("W0mp W0mp.. Pass all test cases for remove_user()\n");
}

void test_get_degrees_of_connection() {
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *b0m1n = create_user("Bomin");
    User *taemin = create_user("Taemin");
    User *delvin = create_user("Delvin");
    User *zaylinaung = create_user("Zay Lin Aung");
    User *shon = create_user("Shawn");

    add_friend(william, angela);
    add_friend(mustafa, b0m1n);
    add_friend(mustafa, taemin);
    add_friend(b0m1n, zaylinaung);
    add_friend(delvin, shon);
    add_friend(delvin, angela);
    add_friend(william, brian);
    add_friend(mustafa, delvin);
    add_friend(brian, shon);
    add_friend(zaylinaung, shon);
    add_friend(b0m1n, shon);
    add_friend(mustafa, brian);
    add_friend(delvin, william);

    assert(get_degrees_of_connection(delvin, delvin) == 0);
    assert(get_degrees_of_connection(delvin, shon) == 1);
    assert(get_degrees_of_connection(mustafa, shon) == 2);
    assert(get_degrees_of_connection(taemin, zaylinaung) == 3);
    assert(get_degrees_of_connection(zaylinaung, b0m1n) == 1);
    assert(get_degrees_of_connection(william, zaylinaung) == 3);
    assert(get_degrees_of_connection(angela, zaylinaung) == 3);

    remove_friend(delvin, shon);
    assert(get_degrees_of_connection(angela, zaylinaung) == 4);

    remove_friend(delvin, william);
    assert(get_degrees_of_connection(delvin, william) == 2);

    remove_friend(angela, william);
    assert(get_degrees_of_connection(delvin, william) == 3);
    assert(get_degrees_of_connection(angela, william) == 4);
    assert(get_degrees_of_connection(angela, zaylinaung) == 4);

    remove_friend(shon, zaylinaung);
    remove_friend(mustafa, b0m1n);
    assert(get_degrees_of_connection(angela, zaylinaung) == 6);

    remove_friend(mustafa, brian);
    assert(get_degrees_of_connection(angela, zaylinaung) == -1);
    assert(get_degrees_of_connection(brian, zaylinaung) == 3);
    assert(get_degrees_of_connection(brian, taemin) == -1);
    assert(get_degrees_of_connection(delvin, william) == -1);
    assert(get_degrees_of_connection(angela, taemin) == 3);
    assert(get_degrees_of_connection(b0m1n, taemin) == -1);
    printf("W0mp W0mp.. Pass all test cases for get_degrees_of_connection()\n");

    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    delete_user(b0m1n);
    delete_user(taemin);
    delete_user(delvin);
    delete_user(zaylinaung);
    delete_user(shon);
}

// MANUALLY TESTING
void test_add_suggested_friend() {
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *charles = create_user("Charles");
    User *paco = create_user("Paco");

    populate_brand_matrix("brand1.txt");

    add_friend(charles, paco);
    follow_brand(charles, "B");
    follow_brand(charles, "D");
    follow_brand(charles, "E");
    follow_brand(charles, "F");
    follow_brand(william, "D");
    follow_brand(angela, "B");
    follow_brand(angela, "E");
    follow_brand(mustafa, "C");
    follow_brand(mustafa, "F");
    follow_brand(brian, "A");
    follow_brand(brian, "C");
    follow_brand(paco, "B");
    follow_brand(paco, "D");
    follow_brand(paco, "E");
    // Angela - William - Mustafa - Brian
    assert(add_suggested_friends(charles, 5) == 4);

    delete_user(paco);
    delete_user(charles);
    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);

    william = create_user("William");
    angela = create_user("Angela");
    mustafa = create_user("Mustafa");
    brian = create_user("Brian");
    charles = create_user("Charles");
    paco = create_user("Paco");

    populate_brand_matrix("brand1.txt");
    add_friend(charles, paco);
    follow_brand(william, "D");
    follow_brand(angela, "B");
    follow_brand(angela, "E");
    follow_brand(mustafa, "C");
    follow_brand(mustafa, "F");
    follow_brand(brian, "A");
    follow_brand(brian, "C");
    follow_brand(paco, "B");
    follow_brand(paco, "D");
    follow_brand(paco, "E");

    // William - Mustafa - Brian - Angela
    assert(add_suggested_friends(charles, 5) == 4);

    delete_user(paco);
    delete_user(charles);
    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    printf("W0mp W0mp.. Pass all test cases for test_add_suggested_friend()\n");
}

// MANUALLY TESTING
void test_follow_suggested_brands() {
    User *paul = create_user("Paul");
    follow_brand(paul, "A");
    follow_brand(paul, "B");
    
    assert(follow_suggested_brands(paul, 6) == 4);
    delete_user(paul);

    paul = create_user("Paul");
    follow_brand(paul, "A");
    follow_brand(paul, "B");
    connect_similar_brands("D", "A");
    // F-E-D-C
    assert(follow_suggested_brands(paul, 6) == 4);
    delete_user(paul);
    remove_similar_brands("D", "A");

    paul = create_user("Paul");
    follow_brand(paul, "A");
    follow_brand(paul, "B");
    assert(follow_suggested_brands(paul, 1) == 1);
    assert(follow_suggested_brands(paul, 1) == 1);
    assert(follow_suggested_brands(paul, 1) == 1);
    assert(follow_suggested_brands(paul, 1) == 1);
    // F-C-E-D
    delete_user(paul);

    paul = create_user("Paul");
    follow_brand(paul, "A");
    follow_brand(paul, "B");
    assert(follow_suggested_brands(paul, 2) == 2);
    assert(follow_suggested_brands(paul, 1) == 1);
    assert(follow_suggested_brands(paul, 1) == 1);
    //F-E-C-D
    assert(follow_suggested_brands(paul, 2) == 0);
    delete_user(paul);

    paul = create_user("Paul");
    assert(follow_suggested_brands(paul, 3) == 3);
    assert(follow_suggested_brands(paul, 1) == 1);
    assert(follow_suggested_brands(paul, 2) == 2);
    //F-E-D-C-A-B
    assert(follow_suggested_brands(paul, 2) == 0);
    delete_user(paul);
    printf("W0mp W0mp.. Pass all test cases for test_follow_suggested_brands()\n");
}

int main() {
//    basic();
    test_delete_user();
    test_remove_user();
    test_get_degrees_of_connection();
    test_add_suggested_friend();
    test_follow_suggested_brands();
}
