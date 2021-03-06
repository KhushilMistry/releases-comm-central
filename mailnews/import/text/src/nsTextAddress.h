/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef nsTextAddress_h__
#define nsTextAddress_h__

#include "nsCOMPtr.h"
#include "nsString.h"
#include "nsIImportFieldMap.h"
#include "nsIImportService.h"

class nsIAbDirectory;
class nsIFile;
class nsIInputStream;
class nsIUnicharLineInputStream;

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class nsTextAddress {
 public:
  nsTextAddress();
  virtual ~nsTextAddress();

  nsresult ImportAddresses(bool *pAbort, const char16_t *pName, nsIFile *pSrc,
                           nsIAbDirectory *pDirectory,
                           nsIImportFieldMap *fieldMap, nsString &errors,
                           uint32_t *pProgress);

  nsresult DetermineDelim(nsIFile *pSrc);
  char16_t GetDelim(void) { return m_delim; }

  static nsresult ReadRecordNumber(nsIFile *pSrc, nsAString &aLine,
                                   int32_t rNum);
  static bool GetField(const nsAString &aLine, int32_t index, nsString &field,
                       char16_t delim);

 private:
  nsresult ProcessLine(const nsAString &aLine, nsString &errors);

  static int32_t CountFields(const nsAString &aLine, char16_t delim);
  static nsresult ReadRecord(nsIUnicharLineInputStream *pSrc, nsAString &aLine,
                             bool *aMore);
  static nsresult GetUnicharLineStreamForFile(
      nsIFile *aFile, nsIInputStream *aInputStream,
      nsIUnicharLineInputStream **aStream);

  char16_t m_delim;
  int32_t m_LFCount;
  int32_t m_CRCount;
  nsCOMPtr<nsIAbDirectory> m_directory;
  nsCOMPtr<nsIImportFieldMap> m_fieldMap;
  nsCOMPtr<nsIImportService> m_pService;
};

#endif /* nsTextAddress_h__ */
