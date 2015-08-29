#ifndef TYPE_COMMON_
#define TYPE_COMMON_

#include <string>
#include <vector>
#include "PbCommon.h"

namespace proto {
namespace ProtoParser {

class PbType {
  public:
  PbType(std::string name, std::string package);
  PbType(std::string name, std::string package, std::string message_);
  virtual ~PbType() {}

  virtual void Print() {}
  virtual FIELD_TYPE type() = 0;

  std::string name() const { return name_; }
  std::string package() const { return package_; }
  std::string message() const { return message_; }
  const std::vector<std::string>& pkg_stack() const { return pkg_stack_; }

  std::string PackagePrefix(LANGUAGE lang) const;
  std::string FullNameWithPackagePrefix(LANGUAGE lang) const;

 protected:
  std::string name_;
  std::string package_;
  std::string message_ = "";
  std::vector<std::string> pkg_stack_;
};

}  // namespace ProtoParser
}  // namespace Proto

#endif /* TYPE_COMMON_ */