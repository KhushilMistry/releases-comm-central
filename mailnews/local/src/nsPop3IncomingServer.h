/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __nsPop3IncomingServer_h
#define __nsPop3IncomingServer_h

#include "mozilla/Attributes.h"
#include "msgCore.h"
#include "nsIPop3IncomingServer.h"
#include "nsILocalMailIncomingServer.h"
#include "nsMsgIncomingServer.h"
#include "nsIPop3Protocol.h"
#include "nsIMsgWindow.h"
#include "nsIMsgFolder.h"
#include "nsMailboxServer.h"
#include "nsIUrlListener.h"

/* get some implementation from nsMsgIncomingServer */
class nsPop3IncomingServer : public nsMailboxServer,
                             public nsIPop3IncomingServer,
                             public nsILocalMailIncomingServer

{
 public:
  NS_DECL_ISUPPORTS_INHERITED
  NS_DECL_NSIPOP3INCOMINGSERVER
  NS_DECL_NSILOCALMAILINCOMINGSERVER

  nsPop3IncomingServer();

  NS_IMETHOD PerformBiff(nsIMsgWindow *aMsgWindow) override;
  NS_IMETHOD GetDownloadMessagesAtStartup(bool *getMessages) override;
  NS_IMETHOD GetCanBeDefaultServer(bool *canBeDefaultServer) override;
  NS_IMETHOD GetCanSearchMessages(bool *canSearchMessages) override;
  NS_IMETHOD GetOfflineSupportLevel(int32_t *aSupportLevel) override;
  NS_IMETHOD CloseCachedConnections() override;
  NS_IMETHOD GetRootMsgFolder(nsIMsgFolder **aRootMsgFolder) override;
  NS_IMETHOD GetCanFileMessagesOnServer(
      bool *aCanFileMessagesOnServer) override;
  NS_IMETHOD GetCanCreateFoldersOnServer(
      bool *aCanCreateFoldersOnServer) override;
  NS_IMETHOD VerifyLogon(nsIUrlListener *aUrlListener, nsIMsgWindow *aMsgWindow,
                         nsIURI **aURL) override;
  NS_IMETHOD GetNewMessages(nsIMsgFolder *aFolder, nsIMsgWindow *aMsgWindow,
                            nsIUrlListener *aUrlListener) override;

 protected:
  virtual ~nsPop3IncomingServer();
  nsresult GetInbox(nsIMsgWindow *msgWindow, nsIMsgFolder **inbox);

 private:
  uint32_t m_capabilityFlags;
  bool m_authenticated;
  nsCOMPtr<nsIPop3Protocol> m_runningProtocol;
  nsCOMPtr<nsIMsgFolder> m_rootMsgFolder;
  nsTArray<Pop3UidlEntry *> m_uidlsToMark;
};

#endif
