#pragma once

#include <memory>
#include <string>
#include <vector>

#include "int_helper.hpp"

// Defines what behavior is expected i.e. (Read/Import or Write/Export)
enum class BehaviorType {
    IMPORT,
    EXPORT,
    NONE,
};

// Defines what format the data is expected to be in
enum class MarkerFormat {
    XML,
    GUILDPOINT,
    NONE,
};

class BaseCommand {
 public:
    virtual ~BaseCommand() = default;
};

class InputTacoCommand : public BaseCommand {
 public:
    InputTacoCommand();
    explicit InputTacoCommand(std::string path);
    std::string path;
};

class InputGuildpointCommand : public BaseCommand {
 public:
    InputGuildpointCommand();
    explicit InputGuildpointCommand(std::string path);
    std::string path;
};

class OutputTacoCommand : public BaseCommand {
 public:
    OutputTacoCommand();
    explicit OutputTacoCommand(std::string path);
    std::string path;
};

class OutputGuildpointCommand : public BaseCommand {
 public:
    OutputGuildpointCommand();
    OutputGuildpointCommand(std::string path, OptionalInt split_by_category_depth, bool split_by_map_id);
    std::string path;
    OptionalInt split_by_category_depth;
    bool split_by_map_id;
    bool output_full_category_list;
};

class ParsedArguments {
 public:
    std::vector<BaseCommand*> marker_pack_configs;
    bool allow_duplicates = false;
    bool is_valid = false;

    ~ParsedArguments();
};

ParsedArguments parse_arguments(int argc, char* argv[]);
