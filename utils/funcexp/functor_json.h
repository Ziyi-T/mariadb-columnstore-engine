#pragma once

#include <string>
#define PREFER_MY_CONFIG_H
#include <mariadb.h>
#include <mysql.h>
#include <my_sys.h>
#include <json_lib.h>

#include "collation.h"
#include "functor_bool.h"
#include "functor_int.h"
#include "functor_str.h"

namespace funcexp
{
class json_path_with_flags
{
 public:
  json_path_t p;
  bool constant;
  bool parsed;
  json_path_step_t* cur_step;
  void set_constant_flag(bool s_constant)
  {
    constant = s_constant;
    parsed = false;
  }
};

class Json_engine_scan : public json_engine_t
{
 public:
  Json_engine_scan(CHARSET_INFO* cs, const uchar* str, const uchar* end)
  {
    json_scan_start(this, cs, str, end);
  }
  Json_engine_scan(const std::string& str, CHARSET_INFO* cs)
   : Json_engine_scan(cs, (const uchar*)str.c_str(), (const uchar*)str.c_str() + str.size())
  {
  }
  bool check_and_get_value_scalar(std::string& res, int* error);
  bool check_and_get_value_complex(std::string& res, int* error);
};

class Json_path_extractor : public json_path_with_flags
{
 protected:
  virtual ~Json_path_extractor()
  {
  }
  virtual bool check_and_get_value(Json_engine_scan* je, std::string& ret, int* error) = 0;
  bool extract(std::string& ret, rowgroup::Row& row, execplan::SPTP& funcParamJs,
               execplan::SPTP& funcParamPath);
};
/** @brief Func_json_valid class
 */
class Func_json_valid : public Func_Bool
{
 public:
  Func_json_valid() : Func_Bool("json_valid")
  {
  }
  ~Func_json_valid()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  bool getBoolVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                  execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_depth class
 */
class Func_json_depth : public Func_Int
{
 public:
  Func_json_depth() : Func_Int("json_depth")
  {
  }
  virtual ~Func_json_depth()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  int64_t getIntVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                    execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_length class
 */
class Func_json_length : public Func_Int
{
 protected:
  json_path_with_flags path;

 public:
  Func_json_length() : Func_Int("json_length")
  {
  }
  virtual ~Func_json_length()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  int64_t getIntVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                    execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_equals class
 */
class Func_json_equals : public Func_Bool
{
 public:
  Func_json_equals() : Func_Bool("json_equals")
  {
  }
  ~Func_json_equals()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  bool getBoolVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                  execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_normalize class
 */
class Func_json_normalize : public Func_Str
{
 public:
  Func_json_normalize() : Func_Str("json_normalize")
  {
  }
  virtual ~Func_json_normalize()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_type class
 */
class Func_json_type : public Func_Str
{
 public:
  Func_json_type() : Func_Str("json_type")
  {
  }
  virtual ~Func_json_type()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_object class
 */
class Func_json_object : public Func_Str
{
 public:
  Func_json_object() : Func_Str("json_object")
  {
  }
  virtual ~Func_json_object()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_array class
 */
class Func_json_array : public Func_Str
{
 public:
  Func_json_array() : Func_Str("json_array")
  {
  }
  virtual ~Func_json_array()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};
/** @brief Func_json_keys class
 */
class Func_json_keys : public Func_Str
{
 protected:
  json_path_with_flags path;

 public:
  Func_json_keys() : Func_Str("json_keys")
  {
  }
  virtual ~Func_json_keys()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};
/** @brief Func_json_exists class
 */
class Func_json_exists : public Func_Bool
{
 protected:
  json_path_with_flags path;

 public:
  Func_json_exists() : Func_Bool("json_exists")
  {
  }
  ~Func_json_exists()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  bool getBoolVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                  execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_quote class
 */
class Func_json_quote : public Func_Str
{
 protected:
  json_path_with_flags path;

 public:
  Func_json_quote() : Func_Str("json_quote")
  {
  }
  virtual ~Func_json_quote()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_unquote class
 */
class Func_json_unquote : public Func_Str
{
 protected:
  json_path_with_flags path;

 public:
  Func_json_unquote() : Func_Str("json_unquote")
  {
  }
  virtual ~Func_json_unquote()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_format class
 */
class Func_json_format : public Func_Str
{
 public:
  enum FORMATS
  {
    NONE,
    COMPACT,
    LOOSE,
    DETAILED
  };

 protected:
  FORMATS fmt;

 public:
  Func_json_format() : Func_Str("json_detailed"), fmt(DETAILED)
  {
  }
  Func_json_format(FORMATS format) : fmt(format)
  {
    assert(format != NONE);
    switch (format)
    {
      case DETAILED: Func_Str::Func::funcName("json_detailed"); break;
      case LOOSE: Func_Str::Func::funcName("json_loose"); break;
      case COMPACT: Func_Str::Func::funcName("json_compact"); break;
      default: break;
    }
  }
  virtual ~Func_json_format()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};
/** @brief Func_json_merge_preserve class
 */
class Func_json_merge : public Func_Str
{
 public:
  Func_json_merge() : Func_Str("json_merge_preserve")
  {
  }
  virtual ~Func_json_merge()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_merge_patch class
 */
class Func_json_merge_patch : public Func_Str
{
 public:
  Func_json_merge_patch() : Func_Str("json_merge_patch")
  {
  }
  virtual ~Func_json_merge_patch()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};

/** @brief Func_json_value class
 */
class Func_json_value : public Func_Str, public Json_path_extractor
{
 public:
  Func_json_value() : Func_Str("json_value")
  {
  }
  virtual ~Func_json_value()
  {
  }

  bool check_and_get_value(Json_engine_scan* je, string& res, int* error) override
  {
    return je->check_and_get_value_scalar(res, error);
  }

  execplan::CalpontSystemCatalog::ColType operationType(
      FunctionParm& fp, execplan::CalpontSystemCatalog::ColType& resultType) override;

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type) override;
};

/** @brief Func_json_query class
 */
class Func_json_query : public Func_Str, public Json_path_extractor
{
 public:
  Func_json_query() : Func_Str("json_query")
  {
  }
  virtual ~Func_json_query()
  {
  }

  bool check_and_get_value(Json_engine_scan* je, string& res, int* error) override
  {
    return je->check_and_get_value_complex(res, error);
  }

  execplan::CalpontSystemCatalog::ColType operationType(
      FunctionParm& fp, execplan::CalpontSystemCatalog::ColType& resultType) override;

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type) override;
};
/** @brief Func_json_contains class
 */
class Func_json_contains : public Func_Bool
{
 protected:
  json_path_with_flags path;
  bool arg2Const;
  bool arg2Parsed;  // argument 2 is a constant or has been parsed
  std::string_view arg2Val;

 public:
  Func_json_contains() : Func_Bool("json_contains")
  {
  }
  virtual ~Func_json_contains()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  bool getBoolVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                  execplan::CalpontSystemCatalog::ColType& type);
};
/** @brief Func_json_array_append class
 */
class Func_json_array_append : public Func_Str
{
 protected:
  vector<json_path_with_flags> paths;

 public:
  Func_json_array_append() : Func_Str("json_array_append")
  {
  }
  virtual ~Func_json_array_append()
  {
  }

  execplan::CalpontSystemCatalog::ColType operationType(FunctionParm& fp,
                                                        execplan::CalpontSystemCatalog::ColType& resultType);

  std::string getStrVal(rowgroup::Row& row, FunctionParm& fp, bool& isNull,
                        execplan::CalpontSystemCatalog::ColType& type);
};
}  // namespace funcexp