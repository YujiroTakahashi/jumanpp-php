dnl $Id$
dnl config.m4 for extension jumanpp

PHP_ARG_ENABLE(jumanpp, whether to enable jumanpp support,
dnl Make sure that the comment is aligned:
[  --enable-jumanpp           Enable jumanpp support])

if test "$PHP_JUMANPP" != "no"; then
  PHP_REQUIRE_CXX()

  # --with-jumanpp -> check with-path
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/jumanpp/jumanpp.h"
  if test -r $PHP_JUMANPP/$SEARCH_FOR; then # path given as parameter
    JUMANPP_DIR=$PHP_JUMANPP
  else # search default path list
    AC_MSG_CHECKING([for jumanpp files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        JUMANPP_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$JUMANPP_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the jumanpp distribution, "$PHP_JUMANPP"])
  fi

  # --with-jumanpp -> add include path
  PHP_ADD_INCLUDE($JUMANPP_DIR/include/jumanpp)

  # --with-jumanpp -> check for lib and symbol presence
  LIBNAME="jumanpp"
  LIBSYMBOL="Jumanpp"

  PHP_SUBST(JUMANPP_SHARED_LIBADD)

  PHP_ADD_LIBRARY(stdc++, 1, JUMANPP_SHARED_LIBADD)
  PHP_ADD_LIBRARY(jumanpp, 1, JUMANPP_SHARED_LIBADD)
  CFLAGS="-O3 -funroll-loops"
  CXXFLAGS="-pthread -std=c++14 -funroll-loops -O3 -march=native"

  PHP_NEW_EXTENSION(jumanpp, classes/jpp.cc jumanpp.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
