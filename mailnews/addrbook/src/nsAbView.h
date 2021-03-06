/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _nsAbView_H_
#define _nsAbView_H_

#include "nsISupports.h"
#include "nsString.h"
#include "nsIAbView.h"
#include "nsITreeView.h"
#include "mozilla/dom/XULTreeElement.h"
#include "nsITreeSelection.h"
#include "nsTArray.h"
#include "nsIAbDirectory.h"
#include "nsICollation.h"
#include "nsIAbListener.h"
#include "nsIObserver.h"
#include "nsServiceManagerUtils.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "nsIStringBundle.h"

typedef struct AbCard {
  explicit AbCard(nsIAbCard *c) : card(c) {}
  nsCOMPtr<nsIAbCard> card;
  nsTArray<uint8_t> primaryCollationKey;
  nsTArray<uint8_t> secondaryCollationKey;
} AbCard;

class nsAbView : public nsIAbView,
                 public nsITreeView,
                 public nsIAbListener,
                 public nsIObserver {
 public:
  nsAbView();

  NS_DECL_ISUPPORTS
  NS_DECL_NSIABVIEW
  NS_DECL_NSITREEVIEW
  NS_DECL_NSIABLISTENER
  NS_DECL_NSIOBSERVER

  int32_t CompareCollationKeys(const nsTArray<uint8_t> &key1,
                               const nsTArray<uint8_t> &key2);

 private:
  virtual ~nsAbView();
  nsresult Initialize();
  int32_t FindIndexForInsert(AbCard *abcard);
  int32_t FindIndexForCard(nsIAbCard *card);
  nsresult GenerateCollationKeysForCard(const nsAString &colID, AbCard *abcard);
  nsresult InvalidateTree(int32_t row);
  nsresult RemoveCardAt(int32_t row);
  nsresult AddCard(AbCard *abcard, bool selectCardAfterAdding, int32_t *index);
  nsresult RemoveCardAndSelectNextCard(nsISupports *item);
  nsresult EnumerateCards();
  nsresult SetGeneratedNameFormatFromPrefs();
  nsresult GetSelectedCards(nsCOMPtr<nsIMutableArray> &aSelectedCards);
  nsresult ReselectCards(nsIArray *aCards, nsIAbCard *aIndexCard);
  nsresult GetCardValue(nsIAbCard *card, const nsAString &colID,
                        nsAString &_retval);
  nsresult RefreshTree();

  RefPtr<mozilla::dom::XULTreeElement> mTree;
  nsCOMPtr<nsITreeSelection> mTreeSelection;
  nsCOMPtr<nsIAbDirectory> mDirectory;
  nsTArray<AbCard *> mCards;
  nsString mSortColumn;
  nsString mSortDirection;
  nsCOMPtr<nsICollation> mCollationKeyGenerator;
  nsCOMPtr<nsIAbViewListener> mAbViewListener;
  nsCOMPtr<nsIStringBundle> mABBundle;

  bool mInitialized;
  bool mIsAllDirectoryRootView;
  bool mSuppressSelectionChange;
  bool mSuppressCountChange;
  int32_t mGeneratedNameFormat;
};

#endif /* _nsAbView_H_ */
