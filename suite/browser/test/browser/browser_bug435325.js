/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/* Ensure that clicking the button in the Offline mode neterror page makes the browser go online. See bug 435325. */

var proxyPrefValue;

function test() {
  waitForExplicitFinish();

  gBrowser.selectedTab = gBrowser.addTab();
  window.addEventListener("DOMContentLoaded", checkPage);


  // Tests always connect to localhost, and per bug 87717, localhost is now
  // reachable in offline mode.  To avoid this, disable any proxy.
  proxyPrefValue = Services.prefs.getIntPref("network.proxy.type");
  Services.prefs.setIntPref("network.proxy.type", 0);

  // Go offline and disable the proxy and cache, then try to load the test URL.
  Services.io.offline = true;
  Services.prefs.setBoolPref("browser.cache.disk.enable", false);
  Services.prefs.setBoolPref("browser.cache.memory.enable", false);
  content.location = "http://example.com/";
}

function checkPage() {
  if(content.location == "about:blank") {
    info("got about:blank, which is expected once, so return");
    return;
  }

  window.removeEventListener("DOMContentLoaded", checkPage);

  ok(Services.io.offline, "Setting Services.io.offline to true.");
  is(gBrowser.contentDocument.documentURI.substring(0,27),
    "about:neterror?e=netOffline", "Loading the Offline mode neterror page.");

  // Now press the "Try Again" button
  ok(gBrowser.contentDocument.getElementById("errorTryAgain"),
    "The error page has got a #errorTryAgain element");
  gBrowser.contentDocument.getElementById("errorTryAgain").click();

  ok(!Services.io.offline, "After clicking the Try Again button, we're back " +
                           "online.");

  finish();
}

registerCleanupFunction(function() {
  Services.prefs.setIntPref("network.proxy.type", proxyPrefValue);
  Services.prefs.setBoolPref("browser.cache.disk.enable", true);
  Services.prefs.setBoolPref("browser.cache.memory.enable", true);
  Services.io.offline = false;
  gBrowser.removeCurrentTab();
});
