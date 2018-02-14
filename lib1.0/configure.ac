# Prelude.
AC_INIT([hardshap],[1.0.1],[antonioscala@libero.it])
AM_INIT_AUTOMAKE(-Wall -Werror foreign)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([plplotcxxd], [init], [PLPLOTLIB=`pkg-config --cflags --libs plplotd-c++`])
AC_SUBST([PLPLOTLIB])

# FIXME: Replace `main' with a function in `-lInventor':
#AC_CHECK_LIB([Inventor], [main])
# FIXME: Replace `main' with a function in `-lInventorXt':
#AC_CHECK_LIB([InventorXt], [main])

## These libs are the result of  `pkg-config --cflags --libs plplotd-c++`
AC_CHECK_LIB([plplotcxxd], [main])
AC_CHECK_LIB([plplotd], [main])
AC_CHECK_LIB([qhull], [main])
AC_CHECK_LIB([csironn], [main])
AC_CHECK_LIB([ltdl], [main])
AC_CHECK_LIB([dl], [main])
AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([csirocsa], [main])
AC_CHECK_LIB([z], [main])
AC_CHECK_LIB([freetype], [main])


AC_CHECK_LIB([m],[cos])
AC_CHECK_LIB([gslcblas],[cblas_dgemm])
AC_CHECK_LIB([gsl],[gsl_blas_dgemm])


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow rint sqrt])

# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.

# Output files.
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT([Makefile lib/Makefile src/Makefile])
AC_OUTPUT