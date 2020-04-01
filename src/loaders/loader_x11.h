#pragma once
#include <X11/Xlib.h>
#include <memory>

#include <string>
#include <dlfcn.h>

class libx11_loader {
 public:
  libx11_loader();
  libx11_loader(const std::string& library_name) { Load(library_name); }
  ~libx11_loader();

  bool Load(const std::string& library_name);
  bool IsLoaded() { return loaded_; }

  decltype(&::XOpenDisplay) XOpenDisplay;
  decltype(&::XCloseDisplay) XCloseDisplay;
  decltype(&::XQueryKeymap) XQueryKeymap;
  decltype(&::XKeysymToKeycode) XKeysymToKeycode;
  decltype(&::XStringToKeysym) XStringToKeysym;
  decltype(&::XGetGeometry) XGetGeometry;


 private:
  void CleanUp(bool unload);

  void* library_;
  bool loaded_;

  // Disallow copy constructor and assignment operator.
  libx11_loader(const libx11_loader&);
  void operator=(const libx11_loader&);
};

extern std::shared_ptr<libx11_loader> g_x11;
