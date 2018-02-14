#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(hardshap, 1.0, antonioscala@libero.it)

AM_INIT_AUTOMAKE

##AC_CONFIG_SRCDIR([Test/test_segment.cpp])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_CPP

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lInventor':
AC_CHECK_LIB([Inventor], [main])
# FIXME: Replace `main' with a function in `-lInventorXt':
AC_CHECK_LIB([InventorXt], [main])

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

## FIXME: Replace `main' with a function in `-lSE2d':
#AC_CHECK_LIB([SE2d], [main])
## FIXME: Replace `main' with a function in `-lVec2d':
#AC_CHECK_LIB([Vec2d], [main])
## FIXME: Replace `main' with a function in `-lVec3d':
#AC_CHECK_LIB([Vec3d], [main])
## FIXME: Replace `main' with a function in `-lwrap_pl':
#AC_CHECK_LIB([wrap_pl], [main])


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow rint sqrt])

AC_CONFIG_FILES([Makefile
		 LLcells/Makefile
                 MC-SE2d/Makefile
                 SE2d/Makefile
                 Test/Makefile
                 VecNd/Makefile
                 Wrap_plplot/Makefile])
AC_OUTPUT
