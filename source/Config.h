#ifndef __NAMELINT_CONFIG__H__
#define __NAMELINT_CONFIG__H__

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace namelint {
typedef enum _RULETYPE {
  RULETYPE_DEFAULT = 0,
  RULETYPE_UPPER_CAMEL,
  RULETYPE_LOWER_CAMEL,
  RULETYPE_LOWER_SNAKE,
  RULETYPE_HUNGARIAN,
  RULETYPE_UPPER_SNAKE,
  RULETYPE_NA,
} RULETYPE;

typedef enum _SNAKETYPE {
  SNAKETYPE_LOWER = 1,
  SNAKETYPE_UPPER = 2,
} SNAKETYPE;

struct GeneralOptions {
  vector<string> FileExtNameList;
  bool bCheckVariableName;
  bool bCheckFunctionName;
  bool bCheckFileName;
  bool bAllowedUnderscopeChar;
  bool bAllowedArrayAffected;
};

struct GeneralRules {
  RULETYPE FileName;
  RULETYPE FunctionName;
  RULETYPE VariableName;
  RULETYPE ClassName;
  RULETYPE EnumTagName;
  RULETYPE EnumValueName;
  RULETYPE StructTagName;
  RULETYPE StructValueName;
};

struct GeneralIgnoredList {
  vector<string> FunctionPrefix;
  vector<string> VariablePrefix;
  vector<string> FunctionName;
  vector<string> EnumTagName;
  vector<string> StructTagName;
};

struct General {
  GeneralRules Rules;
  GeneralOptions Options;
  GeneralIgnoredList IgnoredList;
};

struct HungarianOthers {
  bool PreferUpperCamelIfMissed;
};

struct MappingPair {
  string Key;
  string Value;
  MappingPair(string &Key, string &Value) {
    this->Key = Key;
    this->Value = Value;
  }
  MappingPair(const char *szKey, const char *szValue) {
    this->Key = szKey;
    this->Value = szValue;
  }
};
typedef std::map<std::string, std::string> HungarianMap;

struct Hungarian {
  HungarianOthers Others;
  vector<MappingPair> NullStringList;
  HungarianMap ArrayList;
  HungarianMap WordList;
};

struct ConfigData {
  struct General General;
  struct Hungarian Hungarian;
};

class Config {
private:
  shared_ptr<ConfigData> m_pConfig = std::make_shared<ConfigData>();

public:
  Config();
  bool LoadFile(string ConfigFilePath, string &errorReason);
  bool LoadStream(string ConfigContent, string &errorReason);
  bool Save(string DstPath);
  shared_ptr<ConfigData> GetData() const;
};
} // namespace namelint

#endif // __NAMELINT_CONFIG__H__