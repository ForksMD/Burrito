#include "../src/argument_parser.hpp"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>


class ParseArgumentsTest : public ::testing::Test {};

TEST_F(ParseArgumentsTest, ValidInputPaths){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--output-taco-path",
        (char*)"output1"
    };
    int argc = sizeof(argv) / sizeof(char*);

    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    EXPECT_FALSE(parsed_arguments.allow_duplicates);

    ASSERT_EQ(parsed_arguments.marker_pack_configs.size(), 2);

    InputTacoCommand* command_0 = dynamic_cast<InputTacoCommand*>(parsed_arguments.marker_pack_configs[0]);
    EXPECT_NE(command_0, nullptr);
    EXPECT_EQ(command_0->path, "input1");

    OutputTacoCommand* command_1 = dynamic_cast<OutputTacoCommand*>(parsed_arguments.marker_pack_configs[1]);
    EXPECT_NE(command_1, nullptr);
    EXPECT_EQ(command_1->path, "output1");
}

TEST_F(ParseArgumentsTest, ValidSplitMapID){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-guildpoint-path",
        (char*)"input1",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-map-id",
    };
    int argc = sizeof(argv) / sizeof(char*);

    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    EXPECT_FALSE(parsed_arguments.allow_duplicates);

    ASSERT_EQ(parsed_arguments.marker_pack_configs.size(), 2);

    InputGuildpointCommand* command_0 = dynamic_cast<InputGuildpointCommand*>(parsed_arguments.marker_pack_configs[0]);
    EXPECT_NE(command_0, nullptr);
    EXPECT_EQ(command_0->path, "input1");

    OutputGuildpointCommand* command_1 = dynamic_cast<OutputGuildpointCommand*>(parsed_arguments.marker_pack_configs[1]);
    EXPECT_NE(command_1, nullptr);
    EXPECT_EQ(command_1->path, "output1");
    EXPECT_TRUE(command_1->split_by_map_id);
    EXPECT_FALSE(command_1->split_by_category_depth.has_value());
}

TEST_F(ParseArgumentsTest, ValidSplitCategory){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-guildpoint-path",
        (char*)"input1",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-category",
    };
    int argc = sizeof(argv) / sizeof(char*);

    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    EXPECT_FALSE(parsed_arguments.allow_duplicates);

    ASSERT_EQ(parsed_arguments.marker_pack_configs.size(), 2);

    InputGuildpointCommand* command_0 = dynamic_cast<InputGuildpointCommand*>(parsed_arguments.marker_pack_configs[0]);
    EXPECT_NE(command_0, nullptr);
    EXPECT_EQ(command_0->path, "input1");

    OutputGuildpointCommand* command_1 = dynamic_cast<OutputGuildpointCommand*>(parsed_arguments.marker_pack_configs[1]);
    EXPECT_NE(command_1, nullptr);
    EXPECT_EQ(command_1->path, "output1");
    EXPECT_FALSE(command_1->split_by_map_id);
    EXPECT_TRUE(command_1->split_by_category_depth.has_value());
    EXPECT_EQ(command_1->split_by_category_depth.get_value(), 0);
}

TEST_F(ParseArgumentsTest, ValidSplitCategoryWithDepth){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-guildpoint-path",
        (char*)"input1",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-category",
        (char*)"2",
    };
    int argc = sizeof(argv) / sizeof(char*);

    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    EXPECT_FALSE(parsed_arguments.allow_duplicates);

    ASSERT_EQ(parsed_arguments.marker_pack_configs.size(), 2);

    InputGuildpointCommand* command_0 = dynamic_cast<InputGuildpointCommand*>(parsed_arguments.marker_pack_configs[0]);
    EXPECT_NE(command_0, nullptr);
    EXPECT_EQ(command_0->path, "input1");

    OutputGuildpointCommand* command_1 = dynamic_cast<OutputGuildpointCommand*>(parsed_arguments.marker_pack_configs[1]);
    EXPECT_NE(command_1, nullptr);
    EXPECT_EQ(command_1->path, "output1");
    EXPECT_FALSE(command_1->split_by_map_id);
    EXPECT_TRUE(command_1->split_by_category_depth.has_value());
    EXPECT_EQ(command_1->split_by_category_depth.get_value(), 2);
}

TEST_F(ParseArgumentsTest, ValidMultipleInputPaths){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--allow-duplicates",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"input2",
        (char*)"input3",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-map-id"
    };
    int argc = sizeof(argv) / sizeof(char*);

    ParsedArguments parsed_arguments = parse_arguments(argc, argv);

    ASSERT_EQ(parsed_arguments.marker_pack_configs.size(), 4);
    EXPECT_TRUE(parsed_arguments.allow_duplicates);

    InputTacoCommand* command_0 = dynamic_cast<InputTacoCommand*>(parsed_arguments.marker_pack_configs[0]);
    EXPECT_NE(command_0, nullptr);
    EXPECT_EQ(command_0->path, "input1");

    InputTacoCommand* command_1 = dynamic_cast<InputTacoCommand*>(parsed_arguments.marker_pack_configs[1]);
    EXPECT_NE(command_1, nullptr);
    EXPECT_EQ(command_1->path, "input2");

    InputTacoCommand* command_2 = dynamic_cast<InputTacoCommand*>(parsed_arguments.marker_pack_configs[2]);
    EXPECT_NE(command_2, nullptr);
    EXPECT_EQ(command_2->path, "input3");

    OutputGuildpointCommand* command_3 = dynamic_cast<OutputGuildpointCommand*>(parsed_arguments.marker_pack_configs[3]);
    EXPECT_NE(command_3, nullptr);
    EXPECT_EQ(command_3->path, "output1");
    EXPECT_TRUE(command_3->split_by_map_id);
    EXPECT_FALSE(command_3->split_by_category_depth.has_value());
}

TEST_F(ParseArgumentsTest, InvalidSplitMapIDAfterInput){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--split-by-map-id",
        (char*)"--output-taco-path",
        (char*)"output1"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: Unknown argument --split-by-map-id"), std::string::npos);
}

TEST_F(ParseArgumentsTest, InvalidNoPathAfterInput){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"--output-taco-path",
        (char*)"output1"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: --input-taco-path is missing a path"), std::string::npos);
}

TEST_F(ParseArgumentsTest, InvalidNoPathAfterOutput){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--output-taco-path"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: --output-taco-path is missing a path"), std::string::npos);
}

TEST_F(ParseArgumentsTest, InvalidFileAfterWrongArgument){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-map-id",
        (char*)"output2"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: Unknown argument output2"), std::string::npos);
}

TEST_F(ParseArgumentsTest, InvalidArgument){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--output-taco-path",
        (char*)"output1",
        (char*)"--ERROR"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: Unknown argument --ERROR"), std::string::npos);
}

TEST_F(ParseArgumentsTest, InvalidTypeAfterSplitCategory){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-category",
        (char*)"output2"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: expected an integer after --split-by-category but received output2"), std::string::npos);
}

TEST_F(ParseArgumentsTest, InvalidMultipleIntsAfterSplitCategory){
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--input-taco-path",
        (char*)"input1",
        (char*)"--output-guildpoint-path",
        (char*)"output1",
        (char*)"--split-by-category",
        (char*)"1",
        (char*)"2",
        (char*)"3"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStderr();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_err = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_err.find("Error: Unknown argument 2"), std::string::npos);
}

TEST_F(ParseArgumentsTest, HelpFlag) {
    char* argv[] = {
        (char*)"./burrito_converter",
        (char*)"--help"
    };
    int argc = sizeof(argv) / sizeof(char*);

    testing::internal::CaptureStdout();
    ParsedArguments parsed_arguments = parse_arguments(argc, argv);
    std::string std_output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(parsed_arguments.marker_pack_configs.empty());
    EXPECT_NE(std_output.find("usage: ./burrito_converter"), std::string::npos);
}

