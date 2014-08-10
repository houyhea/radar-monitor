#ifndef QRK_C_SERIAL_T_H
#define QRK_C_SERIAL_T_H

/*!
  \file
  \brief ÉVÉäÉAÉãêßå‰ÇÃç\ë¢ëÃ

  \author Satofumi KAMIMURA

  $Id: serial_t.h 783 2009-05-05 08:56:26Z satofumi $
*/

#ifndef NO_DETECT_OS_H
#include "detect_os.h"
#endif

#if defined(WINDOWS_OS)
#include "serial_t_win.h"

#elif defined(LINUX_OS) || defined(MAC_OS)
#include "serial_t_lin.h"

#else
#include "serial_t_other.h"

#endif

#endif /* !QRK_C_SERIAL_T_H */
