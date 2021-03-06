// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messageGame.proto

#ifndef PROTOBUF_messageGame_2eproto__INCLUDED
#define PROTOBUF_messageGame_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_messageGame_2eproto();
void protobuf_AssignDesc_messageGame_2eproto();
void protobuf_ShutdownFile_messageGame_2eproto();

class msg_game;

// ===================================================================

class msg_game : public ::google::protobuf::Message {
 public:
  msg_game();
  virtual ~msg_game();

  msg_game(const msg_game& from);

  inline msg_game& operator=(const msg_game& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const msg_game& default_instance();

  void Swap(msg_game* other);

  // implements Message ----------------------------------------------

  msg_game* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const msg_game& from);
  void MergeFrom(const msg_game& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // required string tipo = 2;
  inline bool has_tipo() const;
  inline void clear_tipo();
  static const int kTipoFieldNumber = 2;
  inline const ::std::string& tipo() const;
  inline void set_tipo(const ::std::string& value);
  inline void set_tipo(const char* value);
  inline void set_tipo(const char* value, size_t size);
  inline ::std::string* mutable_tipo();
  inline ::std::string* release_tipo();
  inline void set_allocated_tipo(::std::string* tipo);

  // optional int32 target = 3;
  inline bool has_target() const;
  inline void clear_target();
  static const int kTargetFieldNumber = 3;
  inline ::google::protobuf::int32 target() const;
  inline void set_target(::google::protobuf::int32 value);

  // optional int32 x = 4;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 4;
  inline ::google::protobuf::int32 x() const;
  inline void set_x(::google::protobuf::int32 value);

  // optional int32 y = 5;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 5;
  inline ::google::protobuf::int32 y() const;
  inline void set_y(::google::protobuf::int32 value);

  // optional string nombre = 6;
  inline bool has_nombre() const;
  inline void clear_nombre();
  static const int kNombreFieldNumber = 6;
  inline const ::std::string& nombre() const;
  inline void set_nombre(const ::std::string& value);
  inline void set_nombre(const char* value);
  inline void set_nombre(const char* value, size_t size);
  inline ::std::string* mutable_nombre();
  inline ::std::string* release_nombre();
  inline void set_allocated_nombre(::std::string* nombre);

  // optional string imagen = 7;
  inline bool has_imagen() const;
  inline void clear_imagen();
  static const int kImagenFieldNumber = 7;
  inline const ::std::string& imagen() const;
  inline void set_imagen(const ::std::string& value);
  inline void set_imagen(const char* value);
  inline void set_imagen(const char* value, size_t size);
  inline ::std::string* mutable_imagen();
  inline ::std::string* release_imagen();
  inline void set_allocated_imagen(::std::string* imagen);

  // optional int32 ancho_base = 8;
  inline bool has_ancho_base() const;
  inline void clear_ancho_base();
  static const int kAnchoBaseFieldNumber = 8;
  inline ::google::protobuf::int32 ancho_base() const;
  inline void set_ancho_base(::google::protobuf::int32 value);

  // optional int32 alto_base = 9;
  inline bool has_alto_base() const;
  inline void clear_alto_base();
  static const int kAltoBaseFieldNumber = 9;
  inline ::google::protobuf::int32 alto_base() const;
  inline void set_alto_base(::google::protobuf::int32 value);

  // optional int32 fps = 10;
  inline bool has_fps() const;
  inline void clear_fps();
  static const int kFpsFieldNumber = 10;
  inline ::google::protobuf::int32 fps() const;
  inline void set_fps(::google::protobuf::int32 value);

  // optional int32 delay = 11;
  inline bool has_delay() const;
  inline void clear_delay();
  static const int kDelayFieldNumber = 11;
  inline ::google::protobuf::int32 delay() const;
  inline void set_delay(::google::protobuf::int32 value);

  // optional int32 total_frames_line = 12;
  inline bool has_total_frames_line() const;
  inline void clear_total_frames_line();
  static const int kTotalFramesLineFieldNumber = 12;
  inline ::google::protobuf::int32 total_frames_line() const;
  inline void set_total_frames_line(::google::protobuf::int32 value);

  // optional int32 pixels_dimension = 13;
  inline bool has_pixels_dimension() const;
  inline void clear_pixels_dimension();
  static const int kPixelsDimensionFieldNumber = 13;
  inline ::google::protobuf::int32 pixels_dimension() const;
  inline void set_pixels_dimension(::google::protobuf::int32 value);

  // optional string owner = 14;
  inline bool has_owner() const;
  inline void clear_owner();
  static const int kOwnerFieldNumber = 14;
  inline const ::std::string& owner() const;
  inline void set_owner(const ::std::string& value);
  inline void set_owner(const char* value);
  inline void set_owner(const char* value, size_t size);
  inline ::std::string* mutable_owner();
  inline ::std::string* release_owner();
  inline void set_allocated_owner(::std::string* owner);

  // optional int32 health = 15;
  inline bool has_health() const;
  inline void clear_health();
  static const int kHealthFieldNumber = 15;
  inline ::google::protobuf::int32 health() const;
  inline void set_health(::google::protobuf::int32 value);

  // optional int32 strength = 16;
  inline bool has_strength() const;
  inline void clear_strength();
  static const int kStrengthFieldNumber = 16;
  inline ::google::protobuf::int32 strength() const;
  inline void set_strength(::google::protobuf::int32 value);

  // optional float precition = 17;
  inline bool has_precition() const;
  inline void clear_precition();
  static const int kPrecitionFieldNumber = 17;
  inline float precition() const;
  inline void set_precition(float value);

  // optional bool building = 18;
  inline bool has_building() const;
  inline void clear_building();
  static const int kBuildingFieldNumber = 18;
  inline bool building() const;
  inline void set_building(bool value);

  // @@protoc_insertion_point(class_scope:msg_game)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_tipo();
  inline void clear_has_tipo();
  inline void set_has_target();
  inline void clear_has_target();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_nombre();
  inline void clear_has_nombre();
  inline void set_has_imagen();
  inline void clear_has_imagen();
  inline void set_has_ancho_base();
  inline void clear_has_ancho_base();
  inline void set_has_alto_base();
  inline void clear_has_alto_base();
  inline void set_has_fps();
  inline void clear_has_fps();
  inline void set_has_delay();
  inline void clear_has_delay();
  inline void set_has_total_frames_line();
  inline void clear_has_total_frames_line();
  inline void set_has_pixels_dimension();
  inline void clear_has_pixels_dimension();
  inline void set_has_owner();
  inline void clear_has_owner();
  inline void set_has_health();
  inline void clear_has_health();
  inline void set_has_strength();
  inline void clear_has_strength();
  inline void set_has_precition();
  inline void clear_has_precition();
  inline void set_has_building();
  inline void clear_has_building();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* tipo_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 target_;
  ::google::protobuf::int32 x_;
  ::google::protobuf::int32 y_;
  ::std::string* nombre_;
  ::std::string* imagen_;
  ::google::protobuf::int32 ancho_base_;
  ::google::protobuf::int32 alto_base_;
  ::google::protobuf::int32 fps_;
  ::google::protobuf::int32 delay_;
  ::google::protobuf::int32 total_frames_line_;
  ::google::protobuf::int32 pixels_dimension_;
  ::std::string* owner_;
  ::google::protobuf::int32 health_;
  ::google::protobuf::int32 strength_;
  float precition_;
  bool building_;
  friend void  protobuf_AddDesc_messageGame_2eproto();
  friend void protobuf_AssignDesc_messageGame_2eproto();
  friend void protobuf_ShutdownFile_messageGame_2eproto();

  void InitAsDefaultInstance();
  static msg_game* default_instance_;
};
// ===================================================================


// ===================================================================

// msg_game

// required int32 id = 1;
inline bool msg_game::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void msg_game::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void msg_game::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void msg_game::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 msg_game::id() const {
  // @@protoc_insertion_point(field_get:msg_game.id)
  return id_;
}
inline void msg_game::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:msg_game.id)
}

// required string tipo = 2;
inline bool msg_game::has_tipo() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void msg_game::set_has_tipo() {
  _has_bits_[0] |= 0x00000002u;
}
inline void msg_game::clear_has_tipo() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void msg_game::clear_tipo() {
  if (tipo_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    tipo_->clear();
  }
  clear_has_tipo();
}
inline const ::std::string& msg_game::tipo() const {
  // @@protoc_insertion_point(field_get:msg_game.tipo)
  return *tipo_;
}
inline void msg_game::set_tipo(const ::std::string& value) {
  set_has_tipo();
  if (tipo_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    tipo_ = new ::std::string;
  }
  tipo_->assign(value);
  // @@protoc_insertion_point(field_set:msg_game.tipo)
}
inline void msg_game::set_tipo(const char* value) {
  set_has_tipo();
  if (tipo_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    tipo_ = new ::std::string;
  }
  tipo_->assign(value);
  // @@protoc_insertion_point(field_set_char:msg_game.tipo)
}
inline void msg_game::set_tipo(const char* value, size_t size) {
  set_has_tipo();
  if (tipo_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    tipo_ = new ::std::string;
  }
  tipo_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:msg_game.tipo)
}
inline ::std::string* msg_game::mutable_tipo() {
  set_has_tipo();
  if (tipo_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    tipo_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:msg_game.tipo)
  return tipo_;
}
inline ::std::string* msg_game::release_tipo() {
  clear_has_tipo();
  if (tipo_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = tipo_;
    tipo_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void msg_game::set_allocated_tipo(::std::string* tipo) {
  if (tipo_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete tipo_;
  }
  if (tipo) {
    set_has_tipo();
    tipo_ = tipo;
  } else {
    clear_has_tipo();
    tipo_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:msg_game.tipo)
}

// optional int32 target = 3;
inline bool msg_game::has_target() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void msg_game::set_has_target() {
  _has_bits_[0] |= 0x00000004u;
}
inline void msg_game::clear_has_target() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void msg_game::clear_target() {
  target_ = 0;
  clear_has_target();
}
inline ::google::protobuf::int32 msg_game::target() const {
  // @@protoc_insertion_point(field_get:msg_game.target)
  return target_;
}
inline void msg_game::set_target(::google::protobuf::int32 value) {
  set_has_target();
  target_ = value;
  // @@protoc_insertion_point(field_set:msg_game.target)
}

// optional int32 x = 4;
inline bool msg_game::has_x() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void msg_game::set_has_x() {
  _has_bits_[0] |= 0x00000008u;
}
inline void msg_game::clear_has_x() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void msg_game::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline ::google::protobuf::int32 msg_game::x() const {
  // @@protoc_insertion_point(field_get:msg_game.x)
  return x_;
}
inline void msg_game::set_x(::google::protobuf::int32 value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:msg_game.x)
}

// optional int32 y = 5;
inline bool msg_game::has_y() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void msg_game::set_has_y() {
  _has_bits_[0] |= 0x00000010u;
}
inline void msg_game::clear_has_y() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void msg_game::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline ::google::protobuf::int32 msg_game::y() const {
  // @@protoc_insertion_point(field_get:msg_game.y)
  return y_;
}
inline void msg_game::set_y(::google::protobuf::int32 value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:msg_game.y)
}

// optional string nombre = 6;
inline bool msg_game::has_nombre() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void msg_game::set_has_nombre() {
  _has_bits_[0] |= 0x00000020u;
}
inline void msg_game::clear_has_nombre() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void msg_game::clear_nombre() {
  if (nombre_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    nombre_->clear();
  }
  clear_has_nombre();
}
inline const ::std::string& msg_game::nombre() const {
  // @@protoc_insertion_point(field_get:msg_game.nombre)
  return *nombre_;
}
inline void msg_game::set_nombre(const ::std::string& value) {
  set_has_nombre();
  if (nombre_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    nombre_ = new ::std::string;
  }
  nombre_->assign(value);
  // @@protoc_insertion_point(field_set:msg_game.nombre)
}
inline void msg_game::set_nombre(const char* value) {
  set_has_nombre();
  if (nombre_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    nombre_ = new ::std::string;
  }
  nombre_->assign(value);
  // @@protoc_insertion_point(field_set_char:msg_game.nombre)
}
inline void msg_game::set_nombre(const char* value, size_t size) {
  set_has_nombre();
  if (nombre_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    nombre_ = new ::std::string;
  }
  nombre_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:msg_game.nombre)
}
inline ::std::string* msg_game::mutable_nombre() {
  set_has_nombre();
  if (nombre_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    nombre_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:msg_game.nombre)
  return nombre_;
}
inline ::std::string* msg_game::release_nombre() {
  clear_has_nombre();
  if (nombre_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = nombre_;
    nombre_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void msg_game::set_allocated_nombre(::std::string* nombre) {
  if (nombre_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete nombre_;
  }
  if (nombre) {
    set_has_nombre();
    nombre_ = nombre;
  } else {
    clear_has_nombre();
    nombre_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:msg_game.nombre)
}

// optional string imagen = 7;
inline bool msg_game::has_imagen() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void msg_game::set_has_imagen() {
  _has_bits_[0] |= 0x00000040u;
}
inline void msg_game::clear_has_imagen() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void msg_game::clear_imagen() {
  if (imagen_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    imagen_->clear();
  }
  clear_has_imagen();
}
inline const ::std::string& msg_game::imagen() const {
  // @@protoc_insertion_point(field_get:msg_game.imagen)
  return *imagen_;
}
inline void msg_game::set_imagen(const ::std::string& value) {
  set_has_imagen();
  if (imagen_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    imagen_ = new ::std::string;
  }
  imagen_->assign(value);
  // @@protoc_insertion_point(field_set:msg_game.imagen)
}
inline void msg_game::set_imagen(const char* value) {
  set_has_imagen();
  if (imagen_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    imagen_ = new ::std::string;
  }
  imagen_->assign(value);
  // @@protoc_insertion_point(field_set_char:msg_game.imagen)
}
inline void msg_game::set_imagen(const char* value, size_t size) {
  set_has_imagen();
  if (imagen_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    imagen_ = new ::std::string;
  }
  imagen_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:msg_game.imagen)
}
inline ::std::string* msg_game::mutable_imagen() {
  set_has_imagen();
  if (imagen_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    imagen_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:msg_game.imagen)
  return imagen_;
}
inline ::std::string* msg_game::release_imagen() {
  clear_has_imagen();
  if (imagen_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = imagen_;
    imagen_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void msg_game::set_allocated_imagen(::std::string* imagen) {
  if (imagen_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete imagen_;
  }
  if (imagen) {
    set_has_imagen();
    imagen_ = imagen;
  } else {
    clear_has_imagen();
    imagen_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:msg_game.imagen)
}

// optional int32 ancho_base = 8;
inline bool msg_game::has_ancho_base() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void msg_game::set_has_ancho_base() {
  _has_bits_[0] |= 0x00000080u;
}
inline void msg_game::clear_has_ancho_base() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void msg_game::clear_ancho_base() {
  ancho_base_ = 0;
  clear_has_ancho_base();
}
inline ::google::protobuf::int32 msg_game::ancho_base() const {
  // @@protoc_insertion_point(field_get:msg_game.ancho_base)
  return ancho_base_;
}
inline void msg_game::set_ancho_base(::google::protobuf::int32 value) {
  set_has_ancho_base();
  ancho_base_ = value;
  // @@protoc_insertion_point(field_set:msg_game.ancho_base)
}

// optional int32 alto_base = 9;
inline bool msg_game::has_alto_base() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void msg_game::set_has_alto_base() {
  _has_bits_[0] |= 0x00000100u;
}
inline void msg_game::clear_has_alto_base() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void msg_game::clear_alto_base() {
  alto_base_ = 0;
  clear_has_alto_base();
}
inline ::google::protobuf::int32 msg_game::alto_base() const {
  // @@protoc_insertion_point(field_get:msg_game.alto_base)
  return alto_base_;
}
inline void msg_game::set_alto_base(::google::protobuf::int32 value) {
  set_has_alto_base();
  alto_base_ = value;
  // @@protoc_insertion_point(field_set:msg_game.alto_base)
}

// optional int32 fps = 10;
inline bool msg_game::has_fps() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void msg_game::set_has_fps() {
  _has_bits_[0] |= 0x00000200u;
}
inline void msg_game::clear_has_fps() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void msg_game::clear_fps() {
  fps_ = 0;
  clear_has_fps();
}
inline ::google::protobuf::int32 msg_game::fps() const {
  // @@protoc_insertion_point(field_get:msg_game.fps)
  return fps_;
}
inline void msg_game::set_fps(::google::protobuf::int32 value) {
  set_has_fps();
  fps_ = value;
  // @@protoc_insertion_point(field_set:msg_game.fps)
}

// optional int32 delay = 11;
inline bool msg_game::has_delay() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void msg_game::set_has_delay() {
  _has_bits_[0] |= 0x00000400u;
}
inline void msg_game::clear_has_delay() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void msg_game::clear_delay() {
  delay_ = 0;
  clear_has_delay();
}
inline ::google::protobuf::int32 msg_game::delay() const {
  // @@protoc_insertion_point(field_get:msg_game.delay)
  return delay_;
}
inline void msg_game::set_delay(::google::protobuf::int32 value) {
  set_has_delay();
  delay_ = value;
  // @@protoc_insertion_point(field_set:msg_game.delay)
}

// optional int32 total_frames_line = 12;
inline bool msg_game::has_total_frames_line() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void msg_game::set_has_total_frames_line() {
  _has_bits_[0] |= 0x00000800u;
}
inline void msg_game::clear_has_total_frames_line() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void msg_game::clear_total_frames_line() {
  total_frames_line_ = 0;
  clear_has_total_frames_line();
}
inline ::google::protobuf::int32 msg_game::total_frames_line() const {
  // @@protoc_insertion_point(field_get:msg_game.total_frames_line)
  return total_frames_line_;
}
inline void msg_game::set_total_frames_line(::google::protobuf::int32 value) {
  set_has_total_frames_line();
  total_frames_line_ = value;
  // @@protoc_insertion_point(field_set:msg_game.total_frames_line)
}

// optional int32 pixels_dimension = 13;
inline bool msg_game::has_pixels_dimension() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void msg_game::set_has_pixels_dimension() {
  _has_bits_[0] |= 0x00001000u;
}
inline void msg_game::clear_has_pixels_dimension() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void msg_game::clear_pixels_dimension() {
  pixels_dimension_ = 0;
  clear_has_pixels_dimension();
}
inline ::google::protobuf::int32 msg_game::pixels_dimension() const {
  // @@protoc_insertion_point(field_get:msg_game.pixels_dimension)
  return pixels_dimension_;
}
inline void msg_game::set_pixels_dimension(::google::protobuf::int32 value) {
  set_has_pixels_dimension();
  pixels_dimension_ = value;
  // @@protoc_insertion_point(field_set:msg_game.pixels_dimension)
}

// optional string owner = 14;
inline bool msg_game::has_owner() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void msg_game::set_has_owner() {
  _has_bits_[0] |= 0x00002000u;
}
inline void msg_game::clear_has_owner() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void msg_game::clear_owner() {
  if (owner_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    owner_->clear();
  }
  clear_has_owner();
}
inline const ::std::string& msg_game::owner() const {
  // @@protoc_insertion_point(field_get:msg_game.owner)
  return *owner_;
}
inline void msg_game::set_owner(const ::std::string& value) {
  set_has_owner();
  if (owner_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    owner_ = new ::std::string;
  }
  owner_->assign(value);
  // @@protoc_insertion_point(field_set:msg_game.owner)
}
inline void msg_game::set_owner(const char* value) {
  set_has_owner();
  if (owner_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    owner_ = new ::std::string;
  }
  owner_->assign(value);
  // @@protoc_insertion_point(field_set_char:msg_game.owner)
}
inline void msg_game::set_owner(const char* value, size_t size) {
  set_has_owner();
  if (owner_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    owner_ = new ::std::string;
  }
  owner_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:msg_game.owner)
}
inline ::std::string* msg_game::mutable_owner() {
  set_has_owner();
  if (owner_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    owner_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:msg_game.owner)
  return owner_;
}
inline ::std::string* msg_game::release_owner() {
  clear_has_owner();
  if (owner_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = owner_;
    owner_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void msg_game::set_allocated_owner(::std::string* owner) {
  if (owner_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete owner_;
  }
  if (owner) {
    set_has_owner();
    owner_ = owner;
  } else {
    clear_has_owner();
    owner_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:msg_game.owner)
}

// optional int32 health = 15;
inline bool msg_game::has_health() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void msg_game::set_has_health() {
  _has_bits_[0] |= 0x00004000u;
}
inline void msg_game::clear_has_health() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void msg_game::clear_health() {
  health_ = 0;
  clear_has_health();
}
inline ::google::protobuf::int32 msg_game::health() const {
  // @@protoc_insertion_point(field_get:msg_game.health)
  return health_;
}
inline void msg_game::set_health(::google::protobuf::int32 value) {
  set_has_health();
  health_ = value;
  // @@protoc_insertion_point(field_set:msg_game.health)
}

// optional int32 strength = 16;
inline bool msg_game::has_strength() const {
  return (_has_bits_[0] & 0x00008000u) != 0;
}
inline void msg_game::set_has_strength() {
  _has_bits_[0] |= 0x00008000u;
}
inline void msg_game::clear_has_strength() {
  _has_bits_[0] &= ~0x00008000u;
}
inline void msg_game::clear_strength() {
  strength_ = 0;
  clear_has_strength();
}
inline ::google::protobuf::int32 msg_game::strength() const {
  // @@protoc_insertion_point(field_get:msg_game.strength)
  return strength_;
}
inline void msg_game::set_strength(::google::protobuf::int32 value) {
  set_has_strength();
  strength_ = value;
  // @@protoc_insertion_point(field_set:msg_game.strength)
}

// optional float precition = 17;
inline bool msg_game::has_precition() const {
  return (_has_bits_[0] & 0x00010000u) != 0;
}
inline void msg_game::set_has_precition() {
  _has_bits_[0] |= 0x00010000u;
}
inline void msg_game::clear_has_precition() {
  _has_bits_[0] &= ~0x00010000u;
}
inline void msg_game::clear_precition() {
  precition_ = 0;
  clear_has_precition();
}
inline float msg_game::precition() const {
  // @@protoc_insertion_point(field_get:msg_game.precition)
  return precition_;
}
inline void msg_game::set_precition(float value) {
  set_has_precition();
  precition_ = value;
  // @@protoc_insertion_point(field_set:msg_game.precition)
}

// optional bool building = 18;
inline bool msg_game::has_building() const {
  return (_has_bits_[0] & 0x00020000u) != 0;
}
inline void msg_game::set_has_building() {
  _has_bits_[0] |= 0x00020000u;
}
inline void msg_game::clear_has_building() {
  _has_bits_[0] &= ~0x00020000u;
}
inline void msg_game::clear_building() {
  building_ = false;
  clear_has_building();
}
inline bool msg_game::building() const {
  // @@protoc_insertion_point(field_get:msg_game.building)
  return building_;
}
inline void msg_game::set_building(bool value) {
  set_has_building();
  building_ = value;
  // @@protoc_insertion_point(field_set:msg_game.building)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_messageGame_2eproto__INCLUDED
