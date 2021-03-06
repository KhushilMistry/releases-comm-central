/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef nsAddbookProtocolHandler_h___
#define nsAddbookProtocolHandler_h___

#include "nscore.h"
#include "nsCOMPtr.h"
#include "nsAddbookProtocolHandler.h"
#include "nsIProtocolHandler.h"
#include "nsIAddbookUrl.h"
#include "nsIAbDirectory.h"

class nsAddbookProtocolHandler : public nsIProtocolHandler {
 public:
  nsAddbookProtocolHandler();
  static nsresult NewURI(const nsACString &aSpec,
                         const char *aOriginCharset,  // ignored
                         nsIURI *aBaseURI, nsIURI **_retval);

  NS_DECL_ISUPPORTS

  //////////////////////////////////////////////////////////////////////////
  // We support the nsIProtocolHandler interface.
  //////////////////////////////////////////////////////////////////////////
  NS_DECL_NSIPROTOCOLHANDLER

 private:
  virtual ~nsAddbookProtocolHandler();
  nsresult GenerateXMLOutputChannel(nsString &aOutput,
                                    nsIAddbookUrl *addbookUrl, nsIURI *aURI,
                                    nsILoadInfo *aLoadInfo,
                                    nsIChannel **_retval);

  nsresult GeneratePrintOutput(nsIAddbookUrl *addbookUrl, nsString &aOutput);

  nsresult BuildDirectoryXML(nsIAbDirectory *aDirectory, nsString &aOutput);

  int32_t mAddbookOperation;
};

#endif /* nsAddbookProtocolHandler_h___ */
