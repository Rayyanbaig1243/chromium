// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_FRAME_NAVIGATE_PARAMS_H_
#define CONTENT_PUBLIC_COMMON_FRAME_NAVIGATE_PARAMS_H_
#pragma once

#include <string>
#include <vector>

#include "content/common/content_export.h"
#include "content/public/common/page_transition_types.h"
#include "googleurl/src/gurl.h"
#include "net/base/host_port_pair.h"
#include "webkit/glue/password_form.h"

namespace content {

// Struct used by TabContentsObserver.
struct CONTENT_EXPORT FrameNavigateParams {
  FrameNavigateParams();
  ~FrameNavigateParams();

  // Page ID of this navigation. The renderer creates a new unique page ID
  // anytime a new session history entry is created. This means you'll get new
  // page IDs for user actions, and the old page IDs will be reloaded when
  // iframes are loaded automatically.
  int32 page_id;

  // URL of the page being loaded.
  GURL url;

  // URL of the referrer of this load. WebKit generates this based on the
  // source of the event that caused the load.
  GURL referrer;

  // The type of transition.
  PageTransition transition;

  // Lists the redirects that occurred on the way to the current page. This
  // vector has the same format as reported by the WebDataSource in the glue,
  // with the current page being the last one in the list (so even when
  // there's no redirect, there will be one entry in the list.
  std::vector<GURL> redirects;

  // Set to false if we want to update the session history but not update
  // the browser history.  E.g., on unreachable urls.
  bool should_update_history;

  // See SearchableFormData for a description of these.
  GURL searchable_form_url;
  std::string searchable_form_encoding;

  // See password_form.h.
  webkit_glue::PasswordForm password_form;

  // Contents MIME type of main frame.
  std::string contents_mime_type;

  // Remote address of the socket which fetched this resource.
  net::HostPortPair socket_address;
};

}  // namespace content

#endif  // CONTENT_PUBLIC_COMMON_FRAME_NAVIGATE_PARAMS_H_
