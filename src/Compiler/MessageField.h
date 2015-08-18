#ifndef MESSAGE_FIELD_
#define MESSAGE_FIELD_

#include <string>
#include "PbCommon.h"
#include "Type.h"
#include "EnumType.h"

namespace proto {
namespace ProtoParser {

class MessageField {
 public:
  enum FIELD_MODIFIER {
    UNKNOWN_MODIFIER,
    OPTIONAL,
    REQUIRED,
    REPEATED,
  };

  MessageField(FIELD_MODIFIER modifier, FIELD_TYPE type, PbType* type_class,
               std::string name, int tag, std::string default_value);
  virtual ~MessageField();

  static FIELD_MODIFIER GetMessageFieldModifier(std::string modifier);
  static std::string GetModifierAsString(MessageField::FIELD_MODIFIER modifier);

  FIELD_MODIFIER modifier() const { return modifier_; }
  FIELD_TYPE type() const { return type_; }
  PbType* type_class() const { return type_class_; }
  std::string name() const { return name_; }
  int tag() const { return tag_; }
  std::string default_value() const { return default_value_; }
  std::string type_name() const { return type_name_; }
  int field_offset() const { return field_offset_; }
  bool has_user_default_value() const { return has_user_default_value_; }

  void set_field_offset(const int offset) { field_offset_ = offset; }
  void set_type_name(std::string type_name) { type_name_ = type_name; }

  bool IsPrimitiveType() const;
  bool IsSingularNumericType() const;
  bool IsSingularStringType() const;
  bool IsSingularMessageType() const;
  bool IsRepeatedNumericType() const;
  bool IsRepeatedStringType() const;
  bool IsRepeatedMessageType() const;

 private:
  FIELD_MODIFIER modifier_;
  FIELD_TYPE type_;
  PbType* type_class_;
  std::string name_;
  int tag_;
  std::string default_value_;
  std::string type_name_;
  bool has_user_default_value_ = false;
  int field_offset_ = -1;
};

}  // namespace ProtoParser
}  // namespace Proto

#endif /* MESSAGE_FIELD_ */