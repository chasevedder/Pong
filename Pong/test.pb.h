// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_test_2eproto__INCLUDED
#define PROTOBUF_test_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_test_2eproto();
void protobuf_AssignDesc_test_2eproto();
void protobuf_ShutdownFile_test_2eproto();

class Test;

// ===================================================================

class Test : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Test) */ {
 public:
  Test();
  virtual ~Test();

  Test(const Test& from);

  inline Test& operator=(const Test& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Test& default_instance();

  void Swap(Test* other);

  // implements Message ----------------------------------------------

  inline Test* New() const { return New(NULL); }

  Test* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Test& from);
  void MergeFrom(const Test& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Test* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated string message = 1;
  int message_size() const;
  void clear_message();
  static const int kMessageFieldNumber = 1;
  const ::std::string& message(int index) const;
  ::std::string* mutable_message(int index);
  void set_message(int index, const ::std::string& value);
  void set_message(int index, const char* value);
  void set_message(int index, const char* value, size_t size);
  ::std::string* add_message();
  void add_message(const ::std::string& value);
  void add_message(const char* value);
  void add_message(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& message() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_message();

  // @@protoc_insertion_point(class_scope:Test)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::std::string> message_;
  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static Test* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Test

// repeated string message = 1;
inline int Test::message_size() const {
  return message_.size();
}
inline void Test::clear_message() {
  message_.Clear();
}
inline const ::std::string& Test::message(int index) const {
  // @@protoc_insertion_point(field_get:Test.message)
  return message_.Get(index);
}
inline ::std::string* Test::mutable_message(int index) {
  // @@protoc_insertion_point(field_mutable:Test.message)
  return message_.Mutable(index);
}
inline void Test::set_message(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:Test.message)
  message_.Mutable(index)->assign(value);
}
inline void Test::set_message(int index, const char* value) {
  message_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:Test.message)
}
inline void Test::set_message(int index, const char* value, size_t size) {
  message_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Test.message)
}
inline ::std::string* Test::add_message() {
  // @@protoc_insertion_point(field_add_mutable:Test.message)
  return message_.Add();
}
inline void Test::add_message(const ::std::string& value) {
  message_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:Test.message)
}
inline void Test::add_message(const char* value) {
  message_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:Test.message)
}
inline void Test::add_message(const char* value, size_t size) {
  message_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:Test.message)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Test::message() const {
  // @@protoc_insertion_point(field_list:Test.message)
  return message_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Test::mutable_message() {
  // @@protoc_insertion_point(field_mutable_list:Test.message)
  return &message_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_2eproto__INCLUDED