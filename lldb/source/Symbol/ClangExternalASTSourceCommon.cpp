//===-- ClangExternalASTSourceCommon.cpp ------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "lldb/Symbol/ClangExternalASTSourceCommon.h"
#include "lldb/Utility/Stream.h"

#include <mutex>

using namespace lldb_private;

char ClangExternalASTSourceCommon::ID;

ClangExternalASTSourceCommon::~ClangExternalASTSourceCommon() {}

ClangASTMetadata *
ClangExternalASTSourceCommon::GetMetadata(const clang::Decl *object) {
  auto It = m_decl_metadata.find(object);
  if (It != m_decl_metadata.end())
    return &It->second;
  return nullptr;
}

ClangASTMetadata *
ClangExternalASTSourceCommon::GetMetadata(const clang::Type *object) {
  auto It = m_type_metadata.find(object);
  if (It != m_type_metadata.end())
    return &It->second;
  return nullptr;
}

void ClangASTMetadata::Dump(Stream *s) {
  lldb::user_id_t uid = GetUserID();

  if (uid != LLDB_INVALID_UID) {
    s->Printf("uid=0x%" PRIx64, uid);
  }

  uint64_t isa_ptr = GetISAPtr();
  if (isa_ptr != 0) {
    s->Printf("isa_ptr=0x%" PRIx64, isa_ptr);
  }

  const char *obj_ptr_name = GetObjectPtrName();
  if (obj_ptr_name) {
    s->Printf("obj_ptr_name=\"%s\" ", obj_ptr_name);
  }

  if (m_is_dynamic_cxx) {
    s->Printf("is_dynamic_cxx=%i ", m_is_dynamic_cxx);
  }
  s->EOL();
}
