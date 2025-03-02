#ifndef DATABASE_COMMANDS_H
#define DATABASE_COMMANDS_H

#include "Config/Logger.h"

#include <string>
#include <unordered_map>

/**
 * @file DatabaseCommands.h
 * @brief this file is responsible of collecting important database commands for
 * the ORM.
 */

enum class DatabaseFieldCommands {
  SerialPrimaryKeyField,
  IntField,
  CharField,
  VarChar100Field,
  TextArray,
  UUID
};

enum class DatabaseQueryCommands {
  SelectAll,
  AlterRole,
  AlterColumn,
  AlterTable,
  Update,
  InsertInto,

  CreateTable,
  CreateTableIfNotExists,

  UpdateAdd,
  UpdateDropColumn,
  UpdateRenameColumn,

  DropDrop,
  DropTruncate,
};

const std::unordered_map<DatabaseFieldCommands, std::string>
    DatabaseFieldStrings = {
        {DatabaseFieldCommands::SerialPrimaryKeyField, "serial primary key"},
        {DatabaseFieldCommands::IntField, "int"},
        {DatabaseFieldCommands::CharField, "char"},
        {DatabaseFieldCommands::VarChar100Field, "varchar(100)"},
        {DatabaseFieldCommands::UUID, "uuid DEFAULT gen_random_uuid()"},
        {DatabaseFieldCommands::TextArray, "text[]"}};

const std::unordered_map<DatabaseQueryCommands, std::string>
    DatabaseQueryCommandsStrings = {
        {DatabaseQueryCommands::SelectAll, "select * from "},
        {DatabaseQueryCommands::AlterRole, "alter role "},
        {DatabaseQueryCommands::AlterColumn, "alter column "},
        {DatabaseQueryCommands::AlterTable, "alter table "},
        {DatabaseQueryCommands::Update, "update "},
        {DatabaseQueryCommands::InsertInto, "insert into "},

        {DatabaseQueryCommands::CreateTable, "create table "},
        {DatabaseQueryCommands::CreateTableIfNotExists,
         "create table if not exists "},

        {DatabaseQueryCommands::UpdateAdd, "add "},
        {DatabaseQueryCommands::UpdateDropColumn, "drop column "},
        {DatabaseQueryCommands::UpdateRenameColumn, "rename column "},

        {DatabaseQueryCommands::DropDrop, "drop table "},
        {DatabaseQueryCommands::DropTruncate, "truncate table "}};

template <typename DatabaseCommandType>
constexpr std::string DatabaseCommandToString(DatabaseCommandType Command) {
  if constexpr (std::is_same_v<decltype(Command), DatabaseFieldCommands>) {
    auto it = DatabaseFieldStrings.find(Command);
    if (it != DatabaseFieldStrings.end()) {
      return it->second;
    }
  } else if constexpr (std::is_same_v<decltype(Command),
                                      DatabaseQueryCommands>) {
    auto it = DatabaseQueryCommandsStrings.find(Command);
    if (it != DatabaseQueryCommandsStrings.end()) {
      return it->second;
    }
  }
  APP_ERROR("DATABASE COMMAND ERROR");
  return "NULL";
}

#endif