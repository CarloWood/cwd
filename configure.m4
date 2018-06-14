# cwds depends on utils if --disable-global-debug is not specified.
m4_if(cwm4_submodule_dirname, [], [m4_append_uniq([CW_SUBMODULE_SUBDIRS], utils, [ ])])

m4_if(cwm4_submodule_dirname, [], [m4_append_uniq([CW_SUBMODULE_SUBDIRS], cwm4_submodule_basename, [ ])])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/Makefile]), [ ])

AC_SUBST(CW_EXTRA_CWDS_LIBS)
AC_SUBST(CW_EXTRA_CWDS_R_LIBS)
