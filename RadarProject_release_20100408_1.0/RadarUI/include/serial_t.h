#ifndef C_SERIAL_T_H
#define C_SERIAL_T_H

/*!
  \file
  \brief ÉVÉäÉAÉãêßå‰ÇÃç\ë¢ëÃ

  \author Satofumi KAMIMURA

  $Id: serial_t.h 130 2008-07-25 06:00:54Z satofumi $
*/

#ifndef NO_DETECT_OS_H
#include "detect_os.h"
#endif

#if defined(WINDOWS_OS)
#include "serial_t_win.h"

#elif defined(LINUX_OS)
#include "serial_t_lin.h"

#else
#include "serial_t_other.h"

#endif

#endif /* !C_SERIAL_T_H */
