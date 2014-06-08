prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${prefix}lib
includedir=${prefix}include

Name: @BLOBB_MONIKER@
Description: @BLOBB_TITLE@
Version: @BLOBB_VERSION@
Requires:
Libs: -L${libdir} -l@BLOBB_MONIKER@
Cflags: -I${includedir}
