// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SESSIONS_CORE_TAB_RESTORE_SERVICE_HELPER_H_
#define COMPONENTS_SESSIONS_CORE_TAB_RESTORE_SERVICE_HELPER_H_

#include <set>
#include <vector>

#include "base/macros.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "components/sessions/core/session_id.h"
#include "components/sessions/core/session_types.h"
#include "components/sessions/core/sessions_export.h"
#include "components/sessions/core/tab_restore_service.h"

namespace sessions {

class TabRestoreService;
class TabRestoreServiceClient;
class LiveTabContext;
class TabRestoreServiceObserver;
class TimeFactory;

// Helper class used to implement InMemoryTabRestoreService and
// PersistentTabRestoreService. See tab_restore_service.h for method-level
// comments.
class SESSIONS_EXPORT TabRestoreServiceHelper {
 public:
  typedef TabRestoreService::Entries Entries;
  typedef TabRestoreService::Entry Entry;
  typedef TabRestoreService::Tab Tab;
  typedef TabRestoreService::TimeFactory TimeFactory;
  typedef TabRestoreService::Window Window;

  // Provides a way for the client to add behavior to the tab restore service
  // helper (e.g. implementing tabs persistence).
  class Observer {
   public:
    // Invoked before the entries are cleared.
    virtual void OnClearEntries();

    // Invoked before the entry is restored. |entry_iterator| points to the
    // entry corresponding to the session identified by |id|.
    virtual void OnRestoreEntryById(SessionID::id_type id,
                                    Entries::const_iterator entry_iterator);

    // Invoked after an entry was added.
    virtual void OnAddEntry();

   protected:
    virtual ~Observer();
  };

  enum {
    // Max number of entries we'll keep around.
    kMaxEntries = 25,
  };

  // Creates a new TabRestoreServiceHelper and provides an object that provides
  // the current time. The TabRestoreServiceHelper does not take ownership of
  // |time_factory| and |observer|. Note that |observer| can also be NULL.
  TabRestoreServiceHelper(TabRestoreService* tab_restore_service,
                          Observer* observer,
                          TabRestoreServiceClient* client,
                          TimeFactory* time_factory);

  ~TabRestoreServiceHelper();

  // Helper methods used to implement TabRestoreService.
  void AddObserver(TabRestoreServiceObserver* observer);
  void RemoveObserver(TabRestoreServiceObserver* observer);
  void CreateHistoricalTab(LiveTab* live_tab, int index);
  void BrowserClosing(LiveTabContext* context);
  void BrowserClosed(LiveTabContext* context);
  void ClearEntries();
  const Entries& entries() const;
  std::vector<LiveTab*> RestoreMostRecentEntry(LiveTabContext* context,
                                               int host_desktop_type);
  Tab* RemoveTabEntryById(SessionID::id_type id);
  std::vector<LiveTab*> RestoreEntryById(LiveTabContext* context,
                                         SessionID::id_type id,
                                         int host_desktop_type,
                                         WindowOpenDisposition disposition);

  // Notifies observers the tabs have changed.
  void NotifyTabsChanged();

  // Notifies observers the service has loaded.
  void NotifyLoaded();

  // Adds |entry| to the list of entries and takes ownership. If |prune| is true
  // |PruneAndNotify| is invoked. If |to_front| is true the entry is added to
  // the front, otherwise the back. Normal closes go to the front, but
  // tab/window closes from the previous session are added to the back.
  void AddEntry(Entry* entry, bool prune, bool to_front);

  // Prunes |entries_| to contain only kMaxEntries, and removes uninteresting
  // entries.
  void PruneEntries();

  // Returns an iterator into |entries_| whose id matches |id|. If |id|
  // identifies a Window, then its iterator position will be returned. If it
  // identifies a tab, then the iterator position of the Window in which the Tab
  // resides is returned.
  Entries::iterator GetEntryIteratorById(SessionID::id_type id);

  // Calls either ValidateTab or ValidateWindow as appropriate.
  static bool ValidateEntry(Entry* entry);

 private:
  friend class PersistentTabRestoreService;

  // Populates the tab's navigations from the LiveTab, and its browser_id and
  // pinned state from the context.
  void PopulateTab(Tab* tab,
                   int index,
                   LiveTabContext* context,
                   LiveTab* live_tab);

  // This is a helper function for RestoreEntryById() for restoring a single
  // tab. If |context| is NULL, this creates a new window for the entry. This
  // returns the LiveTabContext into which the tab was restored.
  // |disposition| will be respected, but if it is UNKNOWN then the tab's
  // original attributes will be respected instead. If a new
  // LiveTabContext needs to be created for this tab,
  // |host_desktop_type| will be passed to
  // TabRestoreServiceClient::CreateLiveTabContext(). If present,
  // |live_tab| will be populated with the LiveTab of the restored tab.
  LiveTabContext* RestoreTab(const Tab& tab,
                             LiveTabContext* context,
                             int host_desktop_type,
                             WindowOpenDisposition disposition,
                             LiveTab** live_tab);

  // Returns true if |tab| has more than one navigation. If |tab| has more
  // than one navigation |tab->current_navigation_index| is constrained based
  // on the number of navigations.
  static bool ValidateTab(Tab* tab);

  // Validates all the tabs in a window, plus the window's active tab index.
  static bool ValidateWindow(Window* window);

  // Returns true if |tab| is one we care about restoring.
  bool IsTabInteresting(const Tab* tab);

  // Checks whether |window| is interesting --- if it only contains a single,
  // uninteresting tab, it's not interesting.
  bool IsWindowInteresting(const Window* window);

  // Validates and checks |entry| for interesting.
  bool FilterEntry(Entry* entry);

  // Finds tab entries with the old browser_id and sets it to the new one.
  void UpdateTabBrowserIDs(SessionID::id_type old_id,
                           SessionID::id_type new_id);

  // Gets the current time. This uses the time_factory_ if there is one.
  base::Time TimeNow() const;

  TabRestoreService* const tab_restore_service_;

  Observer* const observer_;

  TabRestoreServiceClient* client_;

  // Set of entries. They are ordered from most to least recent.
  Entries entries_;

  // Are we restoring a tab? If this is true we ignore requests to create a
  // historical tab.
  bool restoring_;

  base::ObserverList<TabRestoreServiceObserver> observer_list_;

  // Set of contexts that we've received a BrowserClosing method for but no
  // corresponding BrowserClosed. We cache the set of contexts closing to
  // avoid creating historical tabs for them.
  std::set<LiveTabContext*> closing_contexts_;

  TimeFactory* const time_factory_;

  DISALLOW_COPY_AND_ASSIGN(TabRestoreServiceHelper);
};

}  // namespace sessions

#endif  // COMPONENTS_SESSIONS_CORE_TAB_RESTORE_SERVICE_HELPER_H_
