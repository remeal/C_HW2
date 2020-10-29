//
// Created by Dashik on 29.10.2020.
//

#include "gtest/gtest.h"


extern "C" {
#include "DZ2/utils.h"
}

TEST(create_list, ok){
    struct List *list = nullptr;
    list = create_list(sizeof(struct Staffs));
    EXPECT_NE(list, nullptr);
}

TEST(create_database, ok){
    FILE* input_file = fopen("../../test1.txt", "r+");
    struct List *list = create_database(input_file);
    EXPECT_NE(list, nullptr);
    remote_database(list);
}

TEST(create_staff, ok){
    char string_helper_ptr[MAX_STRING_SIZE] = "";
    FILE* input_file = fopen("../../test1.txt", "r+");
    struct Staffs *new_staff = static_cast<Staffs *>(malloc(sizeof(struct Staffs)));
    new_staff->name = input_info_ptr(input_file, string_helper_ptr);
    std::string name = new_staff->name;
    EXPECT_EQ(name, "Ivan");
    new_staff->surname = input_info_ptr(input_file, string_helper_ptr);
    std::string surname = new_staff->surname;
    EXPECT_EQ(surname, "Ivanov");
    new_staff->gender = input_info_value(input_file, string_helper_ptr);
    EXPECT_EQ(new_staff->gender, 'm');
    new_staff->age = input_info_value(input_file, string_helper_ptr);
    EXPECT_EQ(new_staff->age, 50);
    new_staff->salary = input_info_int(input_file, string_helper_ptr);
    int salary = new_staff->salary;
    EXPECT_EQ(salary, 45000);
    new_staff->position = input_info_ptr(input_file, string_helper_ptr);
    std::string position = new_staff->position;
    EXPECT_EQ(position, "headmanager");
    new_staff->experience = input_info_value(input_file, string_helper_ptr);
    EXPECT_EQ(new_staff->experience, 8);
}

TEST