#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(liquidfiles_unix, 0.1)
AM_INIT_AUTOMAKE(liquidfiles, 0.1)
AC_OUTPUT(Makefile src/Makefile)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
clean_CPPFLAGS=$CPPFLAGS
clean_LDFLAGS=$LDFLAGS
clean_LIBS=$LIBS
CURL_LIBS="-lcurl"
AC_ARG_WITH(curl,
AC_HELP_STRING([--with-curl=PATH],[search for curl in PATH]),
               [OPT_CURL="$withval"])

if test "$OPT_CURL" = "" ; then
  if test -d "$PWD/ext/`uname`/`uname -m`" ; then
    OPT_CURL="$PWD/ext/`uname`/`uname -m`"
    CURL_LIBS=`cat $OPT_CURL/lib/.libs` 
  fi
fi

dnl Add a nonempty path to the compiler flags
if test -n "$OPT_CURL"; then
   CPPFLAGS="$CPPFLAGS -I$OPT_CURL/include"
   LDFLAGS="$LDFLAGS -L$OPT_CURL/lib$libsuff"
fi

AC_CHECK_HEADER(curl/curl.h,
  [
  dnl curl/curl.h was found
  HAVE_CURL_H="1"
  ],
  [
    dnl curl/curl.h was not found, restore the flags
    CPPFLAGS=$clean_CPPFLAGS
    LDFLAGS=$clean_LDFLAGS]
  )

if test "$HAVE_CURL_H" == "1"
then
  dnl both header and lib were found!

  LIBS=$CURL_LIBS$clean_LIBS

  dnl replace 'HAVE_CURL' in the automake makefile.ams
  AMFIXLIB="1"
  AC_MSG_NOTICE([found curl.h header])
  curl_curl_msg="enabled"
else
  AC_MSG_WARN([configure not found curl header file])
  CPPFLAGS=$clean_CPPFLAGS
  LDFLAGS=$clean_LDFLAGS
  LIBS=$clean_LIBS
fi

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.

AC_OUTPUT